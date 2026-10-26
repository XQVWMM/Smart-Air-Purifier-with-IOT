#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <math.h>
#include <DHT.h>

// ===================== WIFI & DASHBOARD =====================
const char* WIFI_SSID  = "*****";
const char* WIFI_PASS  = "***";
const char* SERVER_URL = "******";
const char* API_KEY    = "******";
const unsigned long INTERVAL_KIRIM = 1000;

#define TFT_CS    5
#define TFT_RST   22
#define TFT_DC    21

const int PIN_MQ7      = 34;
const int PIN_DUST_VO  = 35;
const int PIN_DUST_LED = 12;
const int PIN_FAN_PWM  = 17;

// ===================== SENSOR SUHU & KELEMBAPAN (DHT22) =====================
#define PIN_DHT   4
#define TIPE_DHT  DHT22
DHT dht(PIN_DHT, TIPE_DHT);

float suhuRuangan = 0;
float kelembapanRuangan = 0;
bool  dhtValid = false;
unsigned long waktuDHTTerakhir = 0;
const unsigned long INTERVAL_DHT = 2000;   // DHT22 tidak boleh dibaca lebih cepat dari 2 detik

const int PWM_FREQ  = 5000;
const int PWM_RES   = 8;
const int PWM_PELAN = 30;
const int PWM_PENUH = 255;

const float VCC_MQ7 = 5.0;
const float RL_MQ7  = 10000.0;
const float R0_MQ7  = 146207.0;

const float VOC_DUST_BASELINE = 0.6;
const float SENSITIVITAS_DUST = 0.2;

const float BATAS_DEBU_RINGAN = 35.0;
const float BATAS_DEBU_BERAT  = 100.0;
const float BATAS_GAS_RINGAN  = 3.0;
const float BATAS_GAS_BERAT   = 7.0;

const float BATAS_MAKSIMAL_DEBU = 1000.0;
const float BATAS_MAKSIMAL_GAS  = 2000.0;

const unsigned long INTERVAL_TFT       = 1000;
const unsigned long INTERVAL_CEK_WIFI  = 10000;

#define WARNA_HEADER   ST7735_BLUE
#define WARNA_KOTAK_BG ST7735_BLACK
#define WARNA_TEKS     ST7735_WHITE
#define WARNA_ABU      0x7BEF

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

unsigned long waktuKirimTerakhir  = 0;
unsigned long waktuTFTTerakhir    = 0;
unsigned long waktuCekWiFiTerakhir = 0;
unsigned long waktuMulai          = 0;
int lastHttpCode = 0, jumlahKirimOK = 0, jumlahKirimGagal = 0, jumlahDataDitolak = 0, siklusKe = 0;
String statusUdaraSebelumnya = "";

int skalaPWM(float nilai, float batasBawah, float batasAtas) {
  float persen = (nilai - batasBawah) / (batasAtas - batasBawah);
  if (persen < 0) persen = 0;
  if (persen > 1) persen = 1;
  return PWM_PELAN + persen * (PWM_PENUH - PWM_PELAN);
}

String formatUptime(unsigned long ms) {
  unsigned long detik = ms / 1000;
  char buf[12];
  sprintf(buf, "%02d:%02d:%02d", (int)(detik/3600), (int)((detik%3600)/60), (int)(detik%60));
  return String(buf);
}

float bacaRsMQ7() {
  long total = 0;
  const int N = 10;
  for (int i = 0; i < N; i++) { total += analogRead(PIN_MQ7); delay(2); }
  float raw = total / (float)N;
  float vRL = raw * (3.3 / 4095.0);
  if (vRL < 0.01) vRL = 0.01;
  return ((VCC_MQ7 / vRL) - 1) * RL_MQ7;
}

float konversiKePPM(float rs) {
  float rasio = rs / R0_MQ7;
  if (rasio <= 0) return 0;
  float logPPM = (log10(rasio) + 0.017) / -0.585;
  float ppm = pow(10, logPPM);
  if (isnan(ppm) || isinf(ppm)) return BATAS_MAKSIMAL_GAS;
  if (ppm > BATAS_MAKSIMAL_GAS) ppm = BATAS_MAKSIMAL_GAS;
  return ppm;
}

float bacaDustDensity() {
  long totalDust = 0;
  for (int i = 0; i < 20; i++) {
    digitalWrite(PIN_DUST_LED, LOW); delayMicroseconds(280);
    totalDust += analogRead(PIN_DUST_VO); delayMicroseconds(40);
    digitalWrite(PIN_DUST_LED, HIGH); delayMicroseconds(9680);
  }
  float voltDust = (totalDust / 20.0) * (3.3 / 4095.0);
  float dustDensity = (voltDust >= VOC_DUST_BASELINE) ? (voltDust - VOC_DUST_BASELINE) * SENSITIVITAS_DUST * 1000 : 0;
  if (dustDensity > BATAS_MAKSIMAL_DEBU) dustDensity = BATAS_MAKSIMAL_DEBU;
  return dustDensity;
}

void bacaDHT() {
  if (millis() - waktuDHTTerakhir < INTERVAL_DHT) return;
  waktuDHTTerakhir = millis();

  float s = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(s) || isnan(h)) {
    dhtValid = false;
    Serial.println("[DHT22] Gagal membaca sensor, cek kabel OUT ke GPIO 4.");
  } else {
    suhuRuangan = s;
    kelembapanRuangan = h;
    dhtValid = true;
  }
}

bool dataValidUntukDikirim(float debu, float gas) {
  if (isnan(debu) || isinf(debu) || isnan(gas) || isinf(gas)) return false;
  if (debu < 0 || gas < 0) return false;
  if (debu > BATAS_MAKSIMAL_DEBU || gas > BATAS_MAKSIMAL_GAS) return false;
  return true;
}

void sambungWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("\n[WIFI] Menyambung ke " + String(WIFI_SSID));
  unsigned long mulai = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - mulai < 15000) { delay(400); Serial.print("."); }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(" OK, IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println(" GAGAL, akan dicoba lagi otomatis di background.");
  }
}

void jagaKoneksiWiFi() {
  if (millis() - waktuCekWiFiTerakhir < INTERVAL_CEK_WIFI) return;
  waktuCekWiFiTerakhir = millis();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WIFI] Terputus, mencoba sambung ulang...");
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
  }
}

void kirimKeDashboard(float debu, float gasPPM, String status, int pwm) {
  if (!dataValidUntukDikirim(debu, gasPPM)) {
    jumlahDataDitolak++;
    Serial.println("[VALIDASI] Data ditolak, TIDAK dikirim ke dashboard.");
    return;
  }
  if (WiFi.status() != WL_CONNECTED) {
    lastHttpCode = -1; jumlahKirimGagal++; return;
  }
  WiFiClientSecure client; client.setInsecure();
  HTTPClient http; http.setTimeout(5000);
  http.begin(client, SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", API_KEY);
  status.trim();
  String json = "{\"debu\":" + String(debu,1) + ",\"gas\":" + String(gasPPM,1) +
                ",\"status\":\"" + status + "\",\"pwm\":" + String(pwm) + ",\"saklar\":0}";
  int kode = http.POST(json);
  lastHttpCode = kode;
  if (kode == 200) jumlahKirimOK++; else jumlahKirimGagal++;
  Serial.println("[DASHBOARD] " + json + " -> kode " + String(kode));
  http.end();
}

// ------------------------------------------------------------------
// TAMPILAN TFT (layout dirapatkan agar muat baris suhu & kelembapan)
// ------------------------------------------------------------------
void gambarHeader() {
  tft.fillRect(0, 0, 160, 16, WARNA_HEADER);
  tft.setTextSize(1); tft.setTextColor(WARNA_TEKS, WARNA_HEADER);
  tft.setCursor(6, 4); tft.print("AIR PURIFIER IoT - KEL 5");
}

void gambarKartuStatus(String status, uint16_t warna) {
  tft.fillRoundRect(4, 18, 152, 14, 3, warna);
  tft.setTextColor(ST7735_BLACK, warna); tft.setTextSize(1);
  int16_t x1,y1; uint16_t w,h; String t = status; t.trim();
  tft.getTextBounds(t, 0, 0, &x1, &y1, &w, &h);
  tft.setCursor(4 + (152-w)/2, 21); tft.print(t);
}

void gambarNilaiSensor(float debu, float gasPPM) {
  tft.setTextSize(1);
  tft.setCursor(6, 36);  tft.setTextColor(WARNA_ABU, WARNA_KOTAK_BG); tft.print("DEBU");
  tft.setCursor(90, 36); tft.setTextColor(WARNA_ABU, WARNA_KOTAK_BG); tft.print("GAS CO");

  tft.fillRect(6, 44, 80, 9, WARNA_KOTAK_BG);
  tft.fillRect(90, 44, 68, 9, WARNA_KOTAK_BG);

  tft.setCursor(6, 45);  tft.setTextColor(WARNA_TEKS, WARNA_KOTAK_BG);
  char b1[16]; sprintf(b1, "%.1f ug/m3", debu); tft.print(b1);

  tft.setCursor(90, 45); tft.setTextColor(WARNA_TEKS, WARNA_KOTAK_BG);
  char b2[16]; sprintf(b2, "%.1f ppm", gasPPM); tft.print(b2);
}

void gambarNilaiLingkungan() {
  tft.setTextSize(1);
  tft.setCursor(6, 56);  tft.setTextColor(WARNA_ABU, WARNA_KOTAK_BG); tft.print("SUHU");
  tft.setCursor(90, 56); tft.setTextColor(WARNA_ABU, WARNA_KOTAK_BG); tft.print("KELEMBAPAN");

  tft.fillRect(6, 64, 80, 9, WARNA_KOTAK_BG);
  tft.fillRect(90, 64, 68, 9, WARNA_KOTAK_BG);

  tft.setTextColor(WARNA_TEKS, WARNA_KOTAK_BG);
  tft.setCursor(6, 65);
  if (dhtValid) { char b1[16]; sprintf(b1, "%.1f C", suhuRuangan); tft.print(b1); }
  else          { tft.print("-- C"); }

  tft.setCursor(90, 65);
  if (dhtValid) { char b2[16]; sprintf(b2, "%.0f %%", kelembapanRuangan); tft.print(b2); }
  else          { tft.print("-- %"); }

  tft.drawFastHLine(0, 76, 160, WARNA_ABU);
}

void gambarKipas(int persen) {
  tft.setTextSize(1);
  tft.setCursor(6, 80); tft.setTextColor(WARNA_ABU, WARNA_KOTAK_BG); tft.print("KECEPATAN KIPAS (OTOMATIS)");

  tft.drawRect(6, 90, 120, 10, WARNA_TEKS);
  tft.fillRect(7, 91, 118, 8, WARNA_KOTAK_BG);
  int lebar = map(persen, 0, 100, 0, 118);
  uint16_t w = (persen>70?ST7735_RED:(persen>35?ST7735_YELLOW:ST7735_GREEN));
  tft.fillRect(7, 91, lebar, 8, w);

  tft.fillRect(128, 90, 32, 10, WARNA_KOTAK_BG);
  tft.setCursor(130, 91); tft.setTextColor(WARNA_TEKS, WARNA_KOTAK_BG);
  char b[6]; sprintf(b, "%3d%%", persen); tft.print(b);
}

void gambarFooter(bool wifiOn) {
  tft.drawFastHLine(0, 106, 160, WARNA_ABU);

  tft.fillRect(6, 112, 60, 8, WARNA_KOTAK_BG);
  tft.setCursor(6, 112);
  tft.setTextColor(wifiOn?ST7735_GREEN:ST7735_RED, WARNA_KOTAK_BG);
  tft.print(wifiOn ? "WiFi OK" : "WiFi OFF");

  tft.fillRect(70, 112, 84, 8, WARNA_KOTAK_BG);
  tft.setCursor(70, 112);
  String tx = lastHttpCode==200 ? "TX:200" : (lastHttpCode==-1 ? "TX:NoWiFi" : (lastHttpCode==0?"TX:---":"TX:ERR"));
  tft.setTextColor(lastHttpCode==200?ST7735_GREEN:ST7735_RED, WARNA_KOTAK_BG);
  tft.print(tx);
}

// ------------------------------------------------------------------
// SETUP
// ------------------------------------------------------------------
void setup() {
  Serial.begin(115200); delay(300);
  pinMode(PIN_DUST_LED, OUTPUT);
  digitalWrite(PIN_DUST_LED, HIGH);

  dht.begin();

  ledcAttach(PIN_FAN_PWM, PWM_FREQ, PWM_RES);
  ledcWrite(PIN_FAN_PWM, PWM_PENUH); delay(500); ledcWrite(PIN_FAN_PWM, PWM_PELAN);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(WARNA_KOTAK_BG); gambarHeader();

  sambungWiFi();
  waktuMulai = millis();
}

// ------------------------------------------------------------------
// LOOP UTAMA
// ------------------------------------------------------------------
void loop() {
  siklusKe++;
  jagaKoneksiWiFi();
  bacaDHT();

  float rsGas   = bacaRsMQ7();
  float gasPPM  = konversiKePPM(rsGas);
  float dustDensity = bacaDustDensity();

  String statusUdara; uint16_t warnaStatus; int fanSpeedPWM;

  if (dustDensity >= BATAS_DEBU_BERAT || gasPPM >= BATAS_GAS_BERAT) {
    statusUdara = "Polusi Berat"; warnaStatus = ST7735_RED; fanSpeedPWM = PWM_PENUH;
  } else if (dustDensity >= BATAS_DEBU_RINGAN || gasPPM >= BATAS_GAS_RINGAN) {
    statusUdara = "Polusi Ringan"; warnaStatus = ST7735_YELLOW;
    int pwmDust = skalaPWM(dustDensity, BATAS_DEBU_RINGAN, BATAS_DEBU_BERAT);
    int pwmGas  = skalaPWM(gasPPM, BATAS_GAS_RINGAN, BATAS_GAS_BERAT);
    fanSpeedPWM = max(pwmDust, pwmGas);
  } else {
    statusUdara = "Udara Bersih"; warnaStatus = ST7735_GREEN; fanSpeedPWM = PWM_PELAN;
  }

  int persen = map(fanSpeedPWM, 0, 255, 0, 100);
  ledcWrite(PIN_FAN_PWM, fanSpeedPWM);
  bool wifiOn = (WiFi.status() == WL_CONNECTED);

  if (millis() - waktuTFTTerakhir >= INTERVAL_TFT) {
    waktuTFTTerakhir = millis();
    gambarKartuStatus(statusUdara, warnaStatus);
    gambarNilaiSensor(dustDensity, gasPPM);
    gambarNilaiLingkungan();
    gambarKipas(persen);
    gambarFooter(wifiOn);
  }

  if (statusUdara != statusUdaraSebelumnya) {
    Serial.println("\n>>> PERUBAHAN STATUS: " + statusUdaraSebelumnya + " -> " + statusUdara);
    statusUdaraSebelumnya = statusUdara;
  }

  Serial.println("------------------------------------------------------------");
  Serial.printf("Siklus #%d | Uptime: %s | Ditolak: %d\n", siklusKe, formatUptime(millis()-waktuMulai).c_str(), jumlahDataDitolak);
  Serial.printf("  Debu   : %.1f ug/m3\n", dustDensity);
  Serial.printf("  Gas CO : %.1f ppm  (Rs=%.0f ohm, Rs/R0=%.3f)\n", gasPPM, rsGas, rsGas/R0_MQ7);
  if (dhtValid) {
    Serial.printf("  Suhu   : %.1f C | Kelembapan: %.1f %%\n", suhuRuangan, kelembapanRuangan);
  } else {
    Serial.println("  Suhu   : -- (sensor DHT22 belum terbaca)");
  }
  Serial.printf("  Status : %s | Kipas: %d%% (OTOMATIS) | WiFi: %s\n", statusUdara.c_str(), persen, wifiOn?"OK":"PUTUS");
  Serial.println("------------------------------------------------------------");

  if (millis() - waktuKirimTerakhir >= INTERVAL_KIRIM) {
    waktuKirimTerakhir = millis();
    kirimKeDashboard(dustDensity, gasPPM, statusUdara, fanSpeedPWM);
  }

  delay(1000);
}

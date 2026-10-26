// ai_peringatan.h - Peringatan dini udara memburuk (Random Forest) untuk ESP32
// Letakkan file ini DAN model_rf_peringatan.h di folder yang sama dengan file .ino.
//
// Cara kerja: tiap menit, simpan nilai rata-rata debu/gas/suhu/kelembapan. Setelah 6 menit
// terkumpul, hitung tren lalu minta model menghitung peluang udara MEMBURUK dalam
// AI_HORIZON_MENIT menit. Urutan fitur harus persis sama dengan train_peringatan_dini.py.
#pragma once
#include <math.h>
#include "model_rf_peringatan.h"

#define AI_N 6                  // jumlah menit riwayat yang dibutuhkan
#define AI_REF_DEBU 35.0f       // = BATAS_DEBU_RINGAN
#define AI_REF_GAS  3.0f        // = BATAS_GAS_RINGAN

float aiDebu[AI_N];
float aiGas[AI_N];
float aiSuhu[AI_N];
float aiLembap[AI_N];
int   aiJumlah = 0;

// Kosongkan riwayat (dipanggil saat ada menit tanpa data valid, agar tren tidak palsu)
void aiReset() {
  aiJumlah = 0;
}

// Tambah satu menit data (nilai rata-rata menit itu)
void aiTambahMenit(float debu, float gas, float suhu, float lembap) {
  if (aiJumlah < AI_N) {
    aiJumlah++;
  } else {
    for (int i = 0; i < AI_N - 1; i++) {
      aiDebu[i] = aiDebu[i + 1];
      aiGas[i] = aiGas[i + 1];
      aiSuhu[i] = aiSuhu[i + 1];
      aiLembap[i] = aiLembap[i + 1];
    }
  }
  aiDebu[aiJumlah - 1] = debu;
  aiGas[aiJumlah - 1] = gas;
  aiSuhu[aiJumlah - 1] = suhu;
  aiLembap[aiJumlah - 1] = lembap;
}

bool aiSiap() {
  return aiJumlah >= AI_N;
}

// sev = status saat ini: 0 Udara Bersih, 1 Polusi Ringan, 2 Polusi Berat
// Mengembalikan peluang (0..1) udara akan memburuk. Hanya panggil jika aiSiap() dan sev < 2.
float aiHitungPeluang(int sev) {
  int k = AI_N - 1;
  float debu = aiDebu[k];
  float gas = aiGas[k];
  float suhu = aiSuhu[k];
  float lembap = aiLembap[k];

  float debuD1 = debu - aiDebu[k - 1];
  float debuD3 = debu - aiDebu[k - 3];
  float debuD5 = debu - aiDebu[k - 5];
  float gasD1 = gas - aiGas[k - 1];
  float gasD3 = gas - aiGas[k - 3];
  float gasD5 = gas - aiGas[k - 5];
  float debuAcc = debuD1 - (debuD5 - debuD1) / 4.0f;
  float gasAcc = gasD1 - (gasD5 - gasD1) / 4.0f;

  float x[AI_JUMLAH_FITUR];
  x[0] = debu;
  x[1] = gas;
  x[2] = suhu;
  x[3] = lembap;
  x[4] = (float)sev;
  x[5] = debuD1;
  x[6] = debuD3;
  x[7] = debuD5;
  x[8] = gasD1;
  x[9] = gasD3;
  x[10] = gasD5;
  x[11] = debuAcc;
  x[12] = gasAcc;
  x[13] = suhu - aiSuhu[k - 5];
  x[14] = lembap - aiLembap[k - 5];
  x[15] = debu / AI_REF_DEBU;
  x[16] = gas / AI_REF_GAS;
  x[17] = (debu + 5.0f * debuD1) / AI_REF_DEBU;
  x[18] = (gas + 5.0f * gasD1) / AI_REF_GAS;
  return aiPeluangMemburuk(x);
}

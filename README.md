# Smart IoT & AI-Powered Air Purifier

An intelligent, adaptive air purification system that automatically adjusts fan speed based on real-time room air quality. It combines IoT sensors, rule-based control, and an on-device **Random Forest early-warning model** that anticipates worsening air quality before thresholds are crossed.

> Course: Intelligent Internet of Things (COMP8078041), BINUS University, Group 5

---

## 📌 Features
* **Adaptive Filtration:** Fan speed is scaled automatically (PWM) from air quality thresholds.
* **Triple-Sensor Monitoring:** CO gas, dust/smoke density, and temperature & humidity in real time.
* **AI Early Warning (Random Forest, on-device):** Estimates the probability that air quality will worsen within the next few minutes and raises the fan speed in advance.
* **Safety-First Design:** The AI can only *increase* fan speed, never lower it. Threshold rules remain the safety floor, so the system still works if the model is wrong.
* **On-Device Display:** 1.8" TFT shows air status, dust (µg/m³), CO (ppm), temperature, humidity, fan speed (%), WiFi/TX status, and AI status.
* **IoT Dashboard:** Real-time monitoring, historical charts, and CSV export (Gradio app hosted on Hugging Face Spaces).
* **Data Logging:** Every reading is stored with a server-side timestamp (WIB) into a CSV dataset used to train the model.
* **Data Validation:** Out-of-range readings are rejected on both the ESP32 and the server.

---

## 🛠️ Hardware Components
* **Microcontroller:** ESP32 Development Board (WiFi enabled)
* **Gas Sensor:** MQ-7 (Carbon Monoxide / CO)
* **Dust Sensor:** GP2Y1010AU0F (Optical Dust / PM)
* **Temperature & Humidity Sensor:** DHT22
* **Actuator:** 12V DC Fan + HEPA 11 Filter
* **Power & Control:** MOSFET IRF520 (PWM speed control), LM2596 Buck Converter (12V to 5V), 12V 2A adapter, LED voltmeter module
* **Display:** 1.8" TFT Display (SPI, ST7735)

| Signal | ESP32 Pin |
|---|---|
| MQ-7 (analog) | GPIO 34 |
| Dust sensor Vo (analog) | GPIO 35 |
| Dust sensor LED | GPIO 12 |
| DHT22 data | GPIO 4 |
| Fan PWM (to MOSFET) | GPIO 17 |
| TFT CS / DC / RST | GPIO 5 / 21 / 22 |

---

## ⚙️ How It Works (System Architecture)
1. **Sensing Layer:** MQ-7 and GP2Y1010AU0F provide analog readings, DHT22 provides digital temperature and humidity.
2. **Processing Layer (ESP32):**
   * Calibrates and converts raw readings (Rs/R0 → CO ppm, voltage → dust µg/m³).
   * **Rule-based classification** into *Clean Air*, *Light Pollution*, or *Heavy Pollution* using thresholds, which also sets the fan PWM.
   * **AI early warning:** once per minute, the 1-minute averages of dust, gas, temperature, and humidity are added to a 6-minute history. The Random Forest estimates the probability that air quality will worsen soon.
3. **Actuation Layer:** Fan speed is set via PWM through the IRF520 MOSFET. If the AI probability exceeds the trained threshold and the fan is below the anticipation level, the fan is raised to PWM 110 (~43%).
4. **Cloud / IoT Layer:** Telemetry is sent over HTTPS (HTTP POST, JSON) to the dashboard, which logs it to CSV and plots live and historical charts.


### Decision logic
| Condition | Status | Fan |
|---|---|---|
| Dust ≥ 100 µg/m³ or CO ≥ 7 ppm | Heavy Pollution | 100% (PWM 255) |
| Dust ≥ 35 µg/m³ or CO ≥ 3 ppm | Light Pollution | Scaled between PWM 30 and 255 |
| Below both thresholds | Clean Air | Minimum (PWM 30, ~12%) |
| AI predicts likely deterioration | (any status below Heavy) | At least PWM 110 (~43%) |

---

## 🤖 AI Component
* **Model:** Random Forest classifier, trained offline in Python (scikit-learn) and exported as C++ headers (`model_rf_peringatan.h`) so inference runs entirely on the ESP32 without internet.
* **Input:** 6-minute history of per-minute averages (dust, gas, temperature, humidity).
* **Output:** Probability that air quality worsens within the prediction horizon. The threshold is chosen during training (`AI_AMBANG_DEFAULT`).
* **Training data:** Collected from our own prototype and logged by the dashboard (CSV, 10,000+ records with timestamps).
* **Validation:** `uji_paritas.js` checks that the C++ implementation matches the Python model's output.

---

## 📁 Repository Structure
```
├── air_purifier_asg2_rule_based/      # Assignment 2: rule-based baseline (no AI)
│   └── air_purifier_asg2_rule_based.ino
├── air_purifier_ai/                   # AI-enhanced firmware
│   ├── air_purifier_ai.ino
│   ├── ai_peringatan.h                # early-warning logic (history + inference)
│   └── model_rf_peringatan.h          # exported Random Forest model
├── training/
│   ├── train_peringatan_dini.py       # early-warning model training
│   ├── train_random_forest.py         # Random Forest training
│   ├── eksperimen_batas_atas.py       # experiments
│   ├── eksperimen_prediksi.py
│   ├── eksperimen_prediksi2.py
│   └── uji_paritas.js                 # parity test (Python vs C++ model)
├── dashboard/
│   └── app.py                         # Gradio dashboard + REST API
├── dataset/
│   └── data_sensor.csv
└── README.md
```
*(Adjust folder names to match your actual repo.)*

---

## 📊 Dashboard & Data Pipeline
* **Endpoints:** `POST /api/data` (ESP32 → server, protected by an `X-API-Key` header) and `GET /api/csv` (dataset download).
* **Dashboard shows:** current status, dust, CO, temperature, humidity, fan %, last update time, charts for every sensor and PWM, and the 10 most recent records.
* **Dataset columns:** `waktu, debu, gas, suhu, kelembapan, status, pwm`.
* **Validation:** Values outside the valid range are rejected (HTTP 422); temperature and humidity are optional, so the system still works if the DHT22 cannot be read.

---

## 🚀 Getting Started
1. **Install Arduino libraries:** Adafruit GFX, Adafruit ST7735, DHT sensor library (plus Adafruit Unified Sensor).
2. **Configure credentials** in the firmware:
   ```cpp
   const char* WIFI_SSID  = "YOUR_WIFI_NAME";
   const char* WIFI_PASS  = "YOUR_WIFI_PASSWORD";
   const char* SERVER_URL = "https://<your-space>.hf.space/api/data";
   const char* API_KEY    = "YOUR_API_KEY";
   ```
   ⚠️ Never commit real passwords or API keys. Store the server key as a secret (`API_KEY`) in the Hugging Face Space settings.
3. **Let the MQ-7 warm up** for a few minutes before trusting its readings, then upload the sketch to the ESP32.
4. **For the AI version,** keep `ai_peringatan.h` and `model_rf_peringatan.h` in the same folder as the `.ino` file. The AI status shows "collecting data" until the 6-minute history is full.

---

## 📊 Testing & Performance Highlights
* **Normal conditions:** Gas < 1.8 ppm, dust 0 µg/m³ → minimum fan speed (PWM 30, ~12%).
* **Gas simulation:** Fan PWM scales up to 255 as gas concentration approaches the source.
* **Dust/smoke simulation:** Spikes up to 540 µg/m³ trigger 100% fan speed within 5–10 seconds.
* **Automatic recovery:** Fan speed scales back down once the air returns to clean levels.
* **AI early warning:** *(fill in from your own experiments, e.g. accuracy / recall, how many minutes earlier the fan reacted compared to the rule-based version)*

---

## ⚠️ Limitations
* The model is trained on data from our own small test room (cigarette smoke, lighter gas, powder), so other environments need more data.
* The MQ-7 drifts over time and is sensitive to temperature and humidity, so periodic recalibration of R0 is recommended.
* Not tested outdoors, and HEPA filter efficiency was not measured in a lab.

---

## 🔭 Future Enhancements
* Expand the dataset to more pollutants, rooms, and times of day.
* Predict fan PWM directly (regression) instead of a fixed anticipation level.
* Add an anomaly detector for faulty sensor readings.
* Filter-life estimation and automatic summaries on the dashboard.
* Persistent cloud storage for the dataset, since the Space disk is ephemeral.

---

## 👥 Contributors (Group 5)
* **Jefferson Darren Cendres**
* **Galio Geraldo**
* **Richard Andersen**

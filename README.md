# Smart IoT & AI-Powered Air Purifier

An intelligent, adaptive air purification system that automatically adjusts filtration levels based on real-time room air quality using IoT sensors and machine learning.

---

## 📌 Features
* **Adaptive Filtration:** Automatically controls fan speed based on detected air quality levels.
* **Dual-Sensor Monitoring:** Detects Carbon Monoxide (CO) and dust/smoke density in real-time.
* **On-Device Visual Status:** Features a 1.8" TFT display showing PPM, dust density ($\mu g/m^3$), fan speed (%), and air status.
* **IoT Dashboard:** Wirelessly transmits sensor trends and operational metrics for remote monitoring.

---

## 🛠️ Hardware Components
* **Microcontroller:** ESP32 Development Board (WiFi enabled)
* **Gas Sensor:** MQ-7 (Carbon Monoxide / CO)
* **Dust Sensor:** GP2Y1010AU0F (Optical Dust / PM)
* **Actuator:** 12V DC Fan + HEPA 11 Filter
* **Power & Control:** MOSFET IRF520 (PWM Speed Control), LM2596 Buck Converter (12V to 5V)
* **Display:** 1.8" TFT Display (SPI)

---

## ⚙️ How It Works (System Architecture)
1. **Sensing Layer:** MQ-7 and GP2Y1010AU0F continuously read ambient gas and dust levels, sending analog signals to the ESP32.
2. **Processing Layer:** ESP32 calibrates and averages sensor data, then classifies air condition into categories (*Clean Air*, *Light Pollution*, *Heavy Pollution*).
3. **Actuation Layer:** Adjusts fan speed via PWM signals through the MOSFET IRF520 while updating the TFT screen.
4. **Cloud / IoT Layer:** Sends telemetry data (HTTP/MQTT) to a real-time IoT dashboard.

---

## 📊 Testing & Performance Highlights
* **Normal Conditions:** Gas < 1.8 ppm, Dust 0 $\mu g/m^3$ ➔ Minimum Fan Speed (30 PWM / ~12%).
* **Gas Simulation:** Dynamically scales PWM up to 255 based on proximity to gas sources.
* **Dust/Smoke Simulation:** Detects sudden spikes (up to 540 $\mu g/m^3$) and triggers **100% Fan Speed** within 5–10 seconds.
* **Automatic Recovery:** Automatically scales down fan speed once air filters back to clean levels.

---

## 🚀 Future Enhancements
* Train and deploy an embedded **Random Forest classification model** on-device for advanced multi-class air quality prediction.
* Expand datasets to cover diverse pollutants and environmental conditions.

---

## 👥 Contributors (Group 5)
* **Jefferson Darren Cendres**
* **Galio Geraldo** 
* **Richard Andersen** 

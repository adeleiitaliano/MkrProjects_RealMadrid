# 🌍 Environmental Monitor (Temperature, Humidity, Pressure)

## 📌 Description

This project is an environmental monitoring system built using the Arduino MKR platform and the MKR IoT Carrier.  
It reads **temperature**, **humidity**, and **atmospheric pressure** using onboard sensors and outputs the data to the Serial Monitor.

---

## 🎯 Objective

Monitor key environmental parameters in real time using the integrated sensors of the MKR IoT Carrier.

---

## 🛠️ Technologies Used

- Arduino MKR 1010 board
- MKR IoT Carrier

---

## ⚙️ How It Works

The system performs the following steps:

1. Initializes serial communication 🔌
2. Initializes the MKR IoT Carrier ⚙️
3. Reads sensor data:
   - 🌡️ Temperature (°C)
   - 💧 Humidity (%)
   - 🌬️ Pressure (kPa)
4. Converts pressure from **kPa to Bar**
5. Sends values to the Serial Monitor 💻
6. Repeats every 3 seconds ⏱️

---

## 📊 Output Example

TEMPERATURE (°C):
24.50

HUMIDITY (%):
60.20

PRESSURE (Bar):
1.01

---

## ▶️ How to Run

1. Connect the Arduino board via USB 🔌
2. Open Arduino IDE 💻
3. Select the correct MKR board
4. Upload the code 🚀
5. Open Serial Monitor (9600 baud)
6. Observe real-time data

---

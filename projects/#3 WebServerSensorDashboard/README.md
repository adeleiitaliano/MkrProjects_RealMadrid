# 🌐 IoT Weather Station (Web Server)

## 📌 Description
This project transforms the Arduino MKR with MKR IoT Carrier into a **basic IoT weather station accessible via web browser**.  
It creates a **local web server** that displays real-time **temperature** and **humidity** data.

---

## 🎯 Objective
Build a simple IoT system capable of:
- 🌍 Connecting to a WiFi network  
- 🌡️ Reading environmental data  
- 💻 Serving data through a web page  

---

## 🛠️ Technologies Used
- Arduino MKR board
- MKR IoT Carrier
- 📚 Arduino **MKRIoTCarrier** library  
- 📡 **WiFiNINA** library  

---

## ⚙️ How It Works

The system performs the following steps:

1. Connects to a WiFi network 📡  
2. Starts a web server on port **80** 🌐  
3. Waits for incoming client connections  
4. When a client connects:
   - Reads temperature 🌡️  
   - Reads humidity 💧  
   - Generates an HTML page  
5. Sends the page to the client browser  
6. The page refreshes automatically every 2 seconds ⏱️  

---

## 🌐 Web Interface

The browser displays:

- 📊 Temperature (°C)  
- 💧 Humidity (%)  

Auto-refresh ensures near real-time updates.

---

## ▶️ How to Run

1. Connect the Arduino board via USB 🔌  
2. Open Arduino IDE 💻  
3. Insert your WiFi credentials (SSID and password)  
4. Upload the code 🚀  
5. Open Serial Monitor (115200 baud)  
6. Copy the IP address shown  
7. Paste it into a browser 🌐  

---
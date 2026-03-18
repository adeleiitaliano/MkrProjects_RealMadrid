# 🌍 Environmental Monitor with Display (Flickering vs Optimized)

## 📌 Description
This project extends the basic environmental monitor by adding a **graphical interface** on the MKR IoT Carrier display.  
It shows **temperature**, **humidity**, and **pressure** using dynamic bars and color indicators.

Two versions were developed:
- ⚠️ **Flickering version** → basic implementation
- ✅ **Optimized version** → reduced flickering and smoother updates

---

## 🎯 Objective
Create a real-time visual monitoring system with:
- 📊 Dynamic progress bars
- 🎨 Color-based feedback
- ⚡ Efficient screen updates

---

## 🛠️ Technologies Used
- Arduino MKR board
- MKR IoT Carrier
- 📚 Arduino **MKRIoTCarrier** library

---

## ⚙️ How It Works

The system:
1. Reads environmental data from sensors 🌡️💧🌬️  
2. Converts pressure to **Bar**  
3. Maps values to graphical bars 📊  
4. Assigns colors based on thresholds 🎨  
5. Displays everything on screen 📺  
6. Updates continuously in real time ⏱️  

---

# ⚠️ Version 1 — Flickering Display

## 📉 Problem
This version updates the display **too frequently and inefficiently**, causing visible flickering.

## ❌ Issues
- Screen areas are redrawn too often  
- No effective control over small value changes  
- Poor user experience  

## 🔧 Behavior
- Bars are cleared and redrawn frequently  
- Even small variations trigger updates  

## 📊 Result
- ❌ Unstable display  
- ❌ Visual noise  
- ❌ Inefficient rendering  

---

# ✅ Version 2 — Optimized (No Flickering)

## 🚀 Improvements
This version introduces **smart update logic** to eliminate flickering.

## ✅ Key Enhancements

### 1. Threshold-based updates
- Temperature updates only if change > 0.1 °C  
- Humidity updates only if change > 0.2 %  
- Pressure updates only if change > 0.002 bar  

👉 Prevents unnecessary redraws

---

### 2. Memory of previous state
- Stores last values and bar widths  
- Updates only when needed  

👉 Avoids redundant operations

---

### 3. Selective clearing
- Only the previous bar is cleared  
- Not the entire screen  

👉 Faster and cleaner rendering

---

## 🎨 Color Logic

### 🌡️ Temperature
- 🔵 Low (≤ 20°C)
- 🟢 Normal (20–30°C)
- 🔴 High (> 30°C)

### 💧 Humidity
- 🔴 Low (< 40%)
- 🟢 Optimal (40–70%)
- 🔵 High (> 70%)

### 🌬️ Pressure
- 🔴 Low (< 1.0 bar)
- 🟢 Normal (1.0–1.02 bar)
- 🟡 High (> 1.02 bar)

---

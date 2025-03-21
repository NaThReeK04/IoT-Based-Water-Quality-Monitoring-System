# IoT-Based Drinking Water Quality Monitoring System

## Overview
This project implements an **IoT-Based Drinking Water Quality Monitoring System** using the **ESP32 WiFi Module, TDS/EC Sensor, and Temperature Sensor**. The system continuously monitors water quality parameters such as **Electrical Conductivity (EC)** and **Temperature** and uploads the data to the **ThingSpeak IoT Server** for remote monitoring.

## Features
- **Real-time Water Quality Monitoring**
- **Measures Electrical Conductivity (EC) & Temperature**
- **Uses ESP32 for WiFi Connectivity**
- **Displays Data on 0.96” I2C OLED Display**
- **Graphical Data Visualization on ThingSpeak**
- **Remote Access from Anywhere in the World**

## WHO Standards for Drinking Water
- **Electrical Conductivity (EC):** Should not exceed **400 μS/cm (0.4 mS/cm)**.
- **Best Temperature for Drinking Water:**
  - Room Temperature: **20°C (68°F)** for maximum flavor.
  - Chilled Cold: **6°C (43°F)** for maximum refreshment.

## Components Used
- **ESP32 WiFi Module** – For data processing & IoT connectivity
- **TDS Sensor** – Measures Total Dissolved Solids (TDS) & Electrical Conductivity
- **DS18B20 Waterproof Temperature Sensor** – Measures water temperature
- **0.96” I2C OLED Display** – Displays real-time sensor data

## How It Works
1. The **TDS Sensor** measures the **Electrical Conductivity (EC)** of water.
2. The **DS18B20 sensor** records the **temperature**.
3. The **ESP32** processes the data and displays it on the **OLED display**.
4. The data is sent to **ThingSpeak**, where it is stored and visualized graphically.
5. Users can access the data from anywhere using the **ThingSpeak dashboard**.

## Setup & Installation
### Hardware Connections:
1. **TDS Sensor** → ESP32 Analog Pin
2. **DS18B20 Sensor** → ESP32 Digital Pin
3. **OLED Display** → ESP32 I2C Pins (SDA, SCL)

### Software Requirements:
Install the following libraries in the **Arduino IDE**:
```bash
ESP32WiFi.h
Adafruit_GFX.h
Adafruit_SSD1306.h
DallasTemperature.h
OneWire.h
```
Upload the code and configure **ThingSpeak** to receive real-time data.

## Applications
- Drinking Water Quality Monitoring
- Industrial Water Purity Analysis
- Smart Home & IoT Automation
- Remote Environmental Monitoring

## Future Improvements
- Add **pH Sensor** for better water quality analysis
- Integrate **mobile app** for real-time alerts
- Use **machine learning** to predict water contamination trends

## Author
Developed by **[Your Name]**

## License
This project is open-source and available under the **MIT License**.


Developed by Keerthan Ghodiwal

License

This project is open-source and available under the MIT License.

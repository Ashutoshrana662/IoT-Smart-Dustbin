# IoT Smart Dustbin

## 📌 Project Overview

The IoT Smart Dustbin is an IoT-based waste management system designed to monitor the fill level of a dustbin using an ultrasonic sensor.

The system uses an ESP8266 NodeMCU to process sensor data and communicate with the Blynk platform for remote monitoring.

## 🚀 Features

- Real-time dustbin fill-level detection
- Ultrasonic sensor-based measurement
- ESP8266 Wi-Fi connectivity
- Remote monitoring using Blynk
- Automatic sensor data processing
- IoT-based waste management

## 🛠️ Technologies & Components

- ESP8266 NodeMCU
- HC-SR04 Ultrasonic Sensor
- Blynk IoT Platform
- Arduino IDE
- C/C++ (Arduino Programming)

## ⚙️ Working Principle

```text
        ┌─────────────────────┐
        │   HC-SR04 Sensor    │
        │  Measures Distance  │
        └──────────┬──────────┘
                   │
                   ▼
        ┌─────────────────────┐
        │   ESP8266 NodeMCU   │
        │  Process Sensor Data│
        └──────────┬──────────┘
                   │
              Wi-Fi│
                   ▼
        ┌─────────────────────┐
        │     Blynk Cloud     │
        │ Remote Monitoring   │
        └─────────────────────┘

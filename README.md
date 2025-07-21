## IoT Environmental Monitoring System

This project demonstrates an Internet of Things (IoT) system designed for real-time monitoring of temperature and humidity using the ESP32 microcontroller and the DHT11 sensor. The system features local data display via an LCD screen and remote visualization and control using the Thinger.io cloud platform. Additionally, the system allows remote control of an LED device.
## Features

- Real-time temperature and humidity monitoring

- Local data display on LCD screen

- Remote data logging and dashboard visualization using Thinger.io

- Remote LED control via dashboard toggle

- Data analysis through historical graphs

- Secure wireless communication (Wi-Fi)

- Low-cost and modular design using ESP32 and standard components



## Technologies Used

- ESP32-C3 WROOM microcontroller

- DHT11 temperature and humidity sensor

- LCD Display (I2C)

- Thinger.io cloud platform

- C++/Arduino environment

- Adafruit DHT Sensor Library

- LiquidCrystal I2C Library

- Wi-Fi Communication

- Breadboard and jumper wires

- LED + resistor for actuator control
## Architecture

```bash
[DHT11 Sensor] ---+
                  |
                  +--> [ESP32] --> [LCD Display]
                  |           \
[LED Device] <----+            --> [Thinger.io Dashboard]
```

- Sensor sends data to ESP32

- ESP32 displays data on LCD and sends it to Thinger.io

- LED is controlled remotely through dashboard input



## How to use

### 1. Setup Hardware

- Assemble components on a breadboard (ESP32, DHT11, LCD, LED)

### 2. Upload Code

- Connect ESP32 via USB

- Install required libraries in Arduino IDE

- Flash code to ESP32

### 3. Connect to Thinger.io

- Create an account on Thinger.io

- Create a device and note credentials

- Add widgets for temperature, humidity, and LED toggle

### 4. Run the Project

- Observe real-time data on LCD

- Control LED from Thinger.io dashboard
##  Example Output

### LCD Display:
- Temp: 24°C Hum: 45%

### Thinger.io Dashboard:

- Real-time charts of last 24h

- Instant toggle for LED

- Logged records of past measurements

## Acknowledgements

This application was created as part of a 4th-year university project for the course Internet of Things. Special thanks to the Thinger.io platform for offering free and easy-to-use IoT tools, open-source libraries like Adafruit DHT and LiquidCrystal I2C for simplifying sensor integration, and the many online resources and tutorials that guided the development process.

## Authors

Filippos Psarros

informatics and telecommunications Student

GitHub: psarrosfilippos

Full project report and results -> https://github.com/psarrosfilippos/IoT-Environmental-Monitoring-System/blob/87e7a983ac6d317e6ca5c5c2b82d06935e5b1e06/IoT_Environmental_Monitoring_System_report.pdf

[README.md](https://github.com/user-attachments/files/21340188/README.md)

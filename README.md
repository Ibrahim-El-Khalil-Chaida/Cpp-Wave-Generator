# ESP32 Interrupt HTTP Client

An ESP32/Arduino sketch that uses a GPIO-change interrupt to fire off an HTTP GET reporting a device status to your server.

## 🔧 Features
- Interrupt-driven HTTP GET on pin change
- Easy configuration of WiFi credentials, device ID & server URL
- Built with the Arduino-ESP32 core and HTTPClient

## ⚙️ Prerequisites
- ESP32 development board
- Arduino IDE (https://www.arduino.cc/en/software) with “ESP32 by Espressif” support installed
- A server endpoint ready to accept GET requests

## 🔌 Wiring
- **GPIO 13** → your sensor or switch (pulled up internally)
- ESP32 GND → sensor GND

## 🚀 Usage

1. Clone this repo.
2. Open `sensor_interrupt_client.ino` in Arduino IDE.
3. Configure pins, WiFi, URL.
4. Upload to your ESP32.
5. Flip your sensor/switch → check Serial Monitor for HTTP response.

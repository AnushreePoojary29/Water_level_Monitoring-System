# Water Level Monitoring System

An IoT-based system to monitor water levels in real-time using an ESP8266 NodeMCU and an Ultrasonic Sensor (HC-SR04).

## 🧰 Hardware Requirements

1.  **NodeMCU ESP8266** (Microcontroller)
2.  **HC-SR04** (Ultrasonic Sensor)
3.  **Jumper Wires** (Female-to-Female)
4.  **USB Cable** (For power and programming)
5.  **Water Tank/Bucket** (For testing)

## 🔌 Wiring Diagram

Connect the HC-SR04 sensor to the NodeMCU as follows:

| HC-SR04 Pin | NodeMCU Pin | Description |
| :--- | :--- | :--- |
| **VCC** | **VIN** / **3V3** | Power (5V preferred, works on 3.3V) |
| **GND** | **GND** | Ground |
| **Trig** | **D1** (GPIO 5) | Trigger Pulse |
| **Echo** | **D2** (GPIO 4) | Echo Pulse |

> **Note:** If your HC-SR04 requires strictly 5V and you are powering NodeMCU via USB, connect VCC to **VIN** (which outputs ~5V from USB).

## 🛠️ Software Setup

1.  **Install Arduino IDE**: Download from [arduino.cc](https://www.arduino.cc/en/software).
2.  **Install ESP8266 Board**:
    - Go to `File` > `Preferences`.
    - Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to "Additional Boards Manager URLs".
    - Go to `Tools` > `Board` > `Boards Manager`.
    - Search for "esp8266" and install.
3.  **Select Board**:
    - Go to `Tools` > `Board` > `ESP8266 Boards` > `NodeMCU 1.0 (ESP-12E Module)`.
4.  **Upload Code**:
    - Open `WaterLevelMonitoring.ino`.
    - Update the `ssid` and `password` variables with your Wi-Fi credentials.
    - Connect NodeMCU via USB.
    - Select the correct Port in `Tools` > `Port`.
    - Click **Upload**.

## 🚀 Usage

1.  Open the Serial Monitor (`Tools` > `Serial Monitor`) and set baud rate to **115200**.
2.  Wait for the connection message: `WiFi connected. IP address: 192.168.x.x`.
3.  Open a web browser on your phone or laptop (connected to the same Wi-Fi).
4.  Enter the IP address shown in the Serial Monitor.
5.  View the real-time water level dashboard!

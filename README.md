![Banner](images/Banner.gif)

# 🚒 Smart RC Rescue Rover: Real-Time Environmental Monitoring Vehicle for Fire Emergency Operations

## 🏁 Introduction

The **Fire Rescue Assist Vehicle (FRAV)** is a remote-controlled robot aimed at enhancing safety and efficiency in fire rescue operations. Designed for hostile environments, FRAV collects real-time environmental data, providing situational awareness to responders. This system focuses on monitoring gas levels, temperature, and obstacles rather than fire suppression.

---

## 🎯 Objectives

1. Develop an RC vehicle equipped with:
   - BO motors for navigation.
   - L293D Motor Driver for control.
2. Integrate sensors for environmental monitoring:
   - Gas detection (MQ-2 or MQ-135).
   - Temperature monitoring (DS18B20).
   - Obstacle detection (IR Sensor).
3. Establish wireless communication via Bluetooth and WiFi.
4. Create a user-friendly interface for real-time data display.

---

## ⚙️ Hardware Overview

### 🛒 Components Used
- **Arduino Uno**: Microcontroller for motor and Bluetooth control.
- **ESP32**: For gas and temperature detection and WiFi-based data sharing.
- **Sensors**:
   - MQ-2 Gas Sensor: Detects LPG, methane, smoke, and more.
   - DS18B20: Temperature sensor for fire hazards.
   - IR Sensor: For detecting obstacles.
- **Actuators**:
   - BO Motors: Provide mobility.
   - Laser Module: For "Find Me" feature in low visibility.
- **Communication Modules**:
   - HC-05 Bluetooth Module.
   - WiFi Access Point via ESP32.
- **Power Components**: Stable power supply for uninterrupted operation.

---

## 💻 Software Description

The system consists of two main software components:
1. **Arduino System**: Manages motor control and Bluetooth commands.
2. **ESP32 System**: Handles sensor data collection and real-time WiFi-based data transmission.

### Development Tools
- **Arduino IDE**: For Arduino and ESP32 programming.
- **Python**: For remote control GUI.

---

## 📐 System Architecture

### Hardware Flow
1. **Initialization**: Power on and setup of Arduino and ESP32.
2. **Motor Control**: Controlled via Arduino using Bluetooth commands.
3. **Sensor Readings**: Handled by ESP32 for gas, temperature, and obstacles.
4. **Real-time Transmission**: Sensor data is sent via WiFi to a web interface.

### Software Flow
1. **Command Handling**:
   - Receive Bluetooth commands via HC-05.
   - Execute navigation commands on Arduino.
2. **Data Monitoring**:
   - ESP32 processes and transmits sensor data.
   - Updates displayed on a user-friendly web interface.

---

## 🛠 Code and Configuration

### Arduino Code for Vehicle Control
The Arduino code is responsible for:
1. Processing Bluetooth commands (forward, backward, stop, etc.).
2. Controlling motor movements via L293D Motor Driver.
3. Resolving power and pin conflicts.

### ESP32 Code for Gas and Temperature Detection
The ESP32:
1. Configures sensors for gas and temperature monitoring.
2. Sets up a WiFi access point for real-time data sharing.
3. Implements a "Find Me" feature using the laser module.

---

## ✨ Features

- **Remote Control**: Bluetooth-based navigation for safe operations.
- **Real-Time Data Monitoring**: Live updates on gas levels, temperature, and obstacles.
- **Find Me Functionality**: Laser module helps locate the vehicle in smoke or low-light areas.
- **Web Interface**: Intuitive interface for data visualization and control.

---

## 🧪 Testing Procedures

1. **Hardware Validation**:
   - Motor and sensor functionality.
   - Bluetooth and WiFi communication stability.
2. **Web Interface Testing**:
   - Real-time data updates.
   - Performance of "Find Me" feature.
3. **Performance Metrics**:
   - Sensor accuracy.
   - Motor response speed.

---

## 📊 Results and Observations

- **Sensor Performance**:
   - Accurate gas and temperature monitoring with real-time updates.
- **Vehicle Navigation**:
   - Smooth and responsive control via Bluetooth GUI.
- **Web Interface**:
   - Displays updated data every second, ensuring reliable situational awareness.
- **System Stability**:
   - Consistent WiFi and Bluetooth connectivity during testing.

---

## 🖼 Images and Outputs

Visual documentation of the project includes:
1. Circuit diagrams and vehicle prototypes.
2. Web interface screenshots displaying sensor data.
3. Laser "Find Me" feature in action.

---

## 🔚 Conclusion

The Smart RC Rescue Rover successfully integrates real-time monitoring and remote-controlled navigation, offering a practical solution for fire rescue operations. Its capabilities in providing accurate environmental data and maneuverability make it a valuable tool for enhancing the safety and efficiency of emergency responders.

---
# 🚀 Code and Snippets for Smart RC Rescue Rover

This document provides a comprehensive explanation of the code used in the **Smart RC Rescue Rover** project. The primary functionalities include vehicle control, environmental monitoring, and real-time data transmission.

---

## Arduino Code for Vehicle Control

The Arduino handles motor control and processes Bluetooth commands received from the HC-05 module.

### ⚙️ Code Structure
- **Motor Control**: Implements directional control using the L293D Motor Driver.
- **Bluetooth Communication**: Receives commands like forward, backward, left, and right.
- **Challenges**:
   - Pin conflicts between the motor shield and Bluetooth module were resolved by direct wiring.

### 📄 Code Snippet
```cpp
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
    Serial.begin(9600);
    motor1.setSpeed(200);  // Speed range: 0-255
    motor2.setSpeed(200);
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read();
        if (command == 'F') {  // Move Forward
            motor1.run(FORWARD);
            motor2.run(FORWARD);
        } else if (command == 'B') {  // Move Backward
            motor1.run(BACKWARD);
            motor2.run(BACKWARD);
        } else if (command == 'L') {  // Turn Left
            motor1.run(BACKWARD);
            motor2.run(FORWARD);
        } else if (command == 'R') {  // Turn Right
            motor1.run(FORWARD);
            motor2.run(BACKWARD);
        } else if (command == 'S') {  // Stop
            motor1.run(RELEASE);
            motor2.run(RELEASE);
        }
    }
}
```

---

## ESP32 Code for Gas and Temperature Detection

The ESP32 handles environmental monitoring and provides a web-based interface for data visualization.

### ⚙️ Features
- **Gas Detection**: Measures gas concentrations (LPG, methane, etc.) using the MQ-2 sensor.
- **Temperature Monitoring**: Tracks ambient temperature using the DS18B20 sensor.
- **Obstacle Detection**: IR sensor detects nearby obstacles.
- **WiFi Access Point**: Streams data to a web page.

### 📄 Code Snippet
```cpp
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char *ssid = "ESP32_AP";
const char *password = "123456789";

WiFiServer server(80);
OneWire oneWire(4);
DallasTemperature sensors(&oneWire);

void setup() {
    Serial.begin(115200);
    sensors.begin();
    WiFi.softAP(ssid, password);
    server.begin();
}

void loop() {
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);

    WiFiClient client = server.available();
    if (client) {
        client.println("<html><body>");
        client.print("<h1>Temperature: ");
        client.print(temperature);
        client.println(" &deg;C</h1>");
        client.println("</body></html>");
        client.stop();
    }
}
```

---

## Python GUI for Remote Control

A Python GUI application communicates with the Arduino via Bluetooth, enabling user-friendly control of the vehicle.

### ⚙️ Features
- **Directional Control**: Buttons for forward, backward, left, right, and stop.
- **Bluetooth Integration**: Communicates with the HC-05 module.

### 📄 Code Snippet
```python
import serial
import tkinter as tk

# Initialize Bluetooth connection
bluetooth = serial.Serial("COM5", 9600)  # Replace "COM5" with your Bluetooth port

def send_command(command):
    bluetooth.write(command.encode())

# GUI Setup
root = tk.Tk()
root.title("RC Vehicle Control")

tk.Button(root, text="Forward", command=lambda: send_command('F')).pack()
tk.Button(root, text="Backward", command=lambda: send_command('B')).pack()
tk.Button(root, text="Left", command=lambda: send_command('L')).pack()
tk.Button(root, text="Right", command=lambda: send_command('R')).pack()
tk.Button(root, text="Stop", command=lambda: send_command('S')).pack()

root.mainloop()
```

---

## 🧑‍💻 Usage
1. Upload the Arduino and ESP32 codes to their respective boards using the Arduino IDE.
2. Run the Python script to control the vehicle.
3. Connect to the ESP32 WiFi to view real-time sensor data.

---

## 📝 Notes
- Ensure proper sensor calibration before deployment.
- Update the Bluetooth and WiFi credentials as needed.
- Test the system in controlled environments before real-world use.



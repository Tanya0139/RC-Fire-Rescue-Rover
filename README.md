# 🚒 Smart RC Rescue Rover: Real-Time Environmental Monitoring Vehicle for Fire Emergency Operations

## 📋 Table of Contents
1. [Introduction](#introduction)
2. [Objectives](#objectives)
3. [⚙️ Hardware Overview](#hardware-overview)
4. [💻 Software Description](#software-description)
5. [📐 System Architecture](#system-architecture)
   - [Hardware Flow](#hardware-flow)
   - [Software Flow](#software-flow)
6. [🛠 Code and Configuration](#code-and-configuration)
   - [Arduino Code for Vehicle Control](#arduino-code-for-vehicle-control)
   - [ESP32 Code for Gas and Temperature Detection](#esp32-code-for-gas-and-temperature-detection)
7. [✨ Features](#features)
8. [🧪 Testing Procedures](#testing-procedures)
9. [📊 Results and Observations](#results-and-observations)
10. [🖼 Images and Outputs](#images-and-outputs)
11. [🔚 Conclusion](#conclusion)

---

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


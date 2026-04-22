# 📡 MCU-to-MCU Communication Hub: ESP32 & Arduino

Welcome to the complete, beginner-friendly guide to establishing direct communication between different microcontrollers! 

Often in complex electronics projects, you need multiple MCUs working together, but you might not have external displays (like OLEDs) to monitor their interactions. This repository provides highly stable, heavily commented, and "bulletproof" code to establish **Master-Slave communication** between an ESP32 and an Arduino Uno/Nano using three major protocols. All data exchanges can be viewed directly on your computer's Serial Monitor.

## 🛠️ Hardware Requirements
* 1x ESP32 Development Board (Master)
* 1x Arduino Uno or Nano (Slave)
* Jumper Wires
* 2x Resistors (1kΩ and 2kΩ) for safety
* 2x USB Data Cables (to view both serial monitors simultaneously)

---

## 📂 Repository Structure

```text
📦 MCU-Communication-Hub
 ┣ 📂 UART_Communication
 ┃ ┣ 📂 ESP32_Master
 ┃ ┃ ┗ 📜 ESP32_Master.ino
 ┃ ┗ 📂 Arduino_Slave
 ┃   ┗ 📜 Arduino_Slave.ino
 ┣ 📂 I2C_Communication
 ┃ ┣ 📂 ESP32_Master
 ┃ ┃ ┗ 📜 ESP32_Master.ino
 ┃ ┗ 📂 Arduino_Slave
 ┃   ┗ 📜 Arduino_Slave.ino
 ┗ 📂 SPI_Communication
   ┣ 📂 ESP32_Master
   ┃ ┗ 📜 ESP32_Master.ino
   ┗ 📂 Arduino_Slave
     ┗ 📜 Arduino_Slave.ino

##I2C
https://github.com/user-attachments/assets/79989435-d73c-475b-9683-951d26a908a4

##UART
https://github.com/user-attachments/assets/0165123b-ea0f-4052-ac86-df5c9e5ef475

##SPI
https://github.com/user-attachments/assets/c2e2e38f-89a2-4644-a9d0-65cf0564c5b4


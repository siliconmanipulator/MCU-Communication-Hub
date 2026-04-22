# 📡 MCU-to-MCU Communication: ESP32 & Arduino

Welcome to this beginner-friendly guide on making microcontrollers talk to each other! 

Often, we have multiple MCUs in a project but no screens (like an OLED) to see what's happening. This repository solves that by showing you how to establish direct Master-Slave communication between an ESP32 and an Arduino Uno/Nano, and view the results directly on your computer's Serial Monitor.

We are building a complete series here. Currently, the UART protocol is live, and SPI/I2C will be added very soon!

## 📂 Project Structure
```text
📦 MCU-Communication-Hub
 ┣ 📂 1_UART_Communication     <-- (We are here!)
 ┃ ┣ 📂 ESP32_Master
 ┃ ┃ ┗ 📜 ESP32_Master.ino
 ┃ ┗ 📂 Arduino_Slave
 ┃   ┗ 📜 Arduino_Slave.ino
 ┣ 📂 2_SPI_Communication      <-- (Coming Soon)
 ┗ 📂 3_I2C_Communication      <-- (Coming Soon)

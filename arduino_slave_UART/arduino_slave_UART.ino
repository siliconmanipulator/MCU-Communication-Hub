// ==========================================
// Arduino Slave Code - UART Communication
// ==========================================

#include <SoftwareSerial.h>

// Define SoftwareSerial pins
// RX = Pin 10 (Connects to ESP32 TX2)
// TX = Pin 11 (Connects to ESP32 RX2)
SoftwareSerial espSerial(10, 11); 

void setup() {
  // Initialize hardware serial for debugging on the PC Serial Monitor
  Serial.begin(9600); 
  
  // Initialize software serial for communication with the ESP32 Master
  espSerial.begin(9600); 
  
  Serial.println("Slave Ready. Waiting for master commands...");
  Serial.println("=========================================");
}

void loop() {
  // Check if any data is available to read from the ESP32
  if (espSerial.available()) {
    
    // Read the incoming string until a newline character ('\n') is received
    String msg = espSerial.readStringUntil('\n');
    
    // Clean up the string by removing any trailing whitespace or invisible characters (like '\r')
    msg.trim(); 

    // Print what the Master sent to the PC Serial Monitor
    Serial.print("Master says: ");
    Serial.println(msg);

    // Verify if the received message exactly matches the expected command
    if (msg == "Wait for my command") {
      // Send the exact required acknowledgment back to the Master
      espSerial.println("yes master");
      Serial.println("Action: Acknowledgment Sent 'Yes master'");
    } 
    else if (msg.length() > 0) {
      // If a message was received but it doesn't match the expected command
      Serial.println("Action: Ignored unknown command.");
    }
    
    // Print a separator line for better readability in the Serial Monitor
    Serial.println("-------------------------");
  }
}
// ==========================================
// Arduino Slave Code - I2C Communication
// ==========================================

#include <Wire.h>

// Define this device's I2C address
#define I2C_SLAVE_ADDR 0x08 

// Variables marked 'volatile' because they are changed inside interrupts
volatile bool newCommandReceived = false;
volatile bool sendAcknowledgment = false;
String receivedMsg = "";

void setup() {
  // Initialize PC Serial Monitor
  Serial.begin(9600);
  
  // Join the I2C bus as a Slave with address 0x08
  Wire.begin(I2C_SLAVE_ADDR); 
  
  // Register event handler when Master sends data
  Wire.onReceive(receiveEvent); 
  
  // Register event handler when Master requests data
  Wire.onRequest(requestEvent); 
  
  Serial.println("I2C Slave Ready. Listening for master...");
  Serial.println("=========================================");
}

void loop() {
  // Process the command only if a new message was received in the background
  if (newCommandReceived) {
    
    Serial.print("Master says: ");
    Serial.println(receivedMsg);

    // Verify if the received message exactly matches the expected command
    if (receivedMsg == "Wait for my command") {
      // Set a flag so the requestEvent() knows to send the correct reply
      sendAcknowledgment = true; 
      Serial.println("Action: Prepared to send acknowledgment.");
    } 
    else {
      sendAcknowledgment = false;
      Serial.println("Action: Ignored unknown command.");
    }
    
    Serial.println("-------------------------");
    
    // Reset the flag after processing
    newCommandReceived = false; 
  }
}

// ----------------------------------------------------
// INTERRUPT ROUTINE: Executes when Master sends data
// ----------------------------------------------------
void receiveEvent(int bytesReceived) {
  receivedMsg = ""; // Clear old message
  
  // Read all incoming characters
  while (Wire.available()) {
    receivedMsg += (char)Wire.read();
  }
  
  // Trigger the loop to process this new message
  newCommandReceived = true; 
}

// ----------------------------------------------------
// INTERRUPT ROUTINE: Executes when Master requests data
// ----------------------------------------------------
void requestEvent() {
  // If the correct command was received earlier, send the reply
  if (sendAcknowledgment) {
    // Send exactly 10 bytes to match the Master's request
    Wire.write("yes master"); 
    
    // Reset flag so we don't send it again without a new prompt
    sendAcknowledgment = false; 
  }
}

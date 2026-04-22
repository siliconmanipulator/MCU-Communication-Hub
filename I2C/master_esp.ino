// ==========================================
// ESP32 Master Code - I2C Communication
// ==========================================

#include <Wire.h>

// Define the unique I2C address for the slave device
#define I2C_SLAVE_ADDR 0x08 

void setup() {
  // Initialize PC Serial Monitor for debugging
  Serial.begin(115200);
  
  // Join the I2C bus as Master (Default pins: SDA=21, SCL=22)
  Wire.begin(); 
  
  Serial.println("I2C Master Ready. Initiating communication...");
}

void loop() {
  String command = "Wait for my command";
  
  // ----------------------------------------
  // STEP 1: Send command to the Slave
  // ----------------------------------------
  Wire.beginTransmission(I2C_SLAVE_ADDR); // Start communicating with slave 0x08
  Wire.print(command);                    // Send the string
  Wire.endTransmission();                 // Stop transmitting
  
  Serial.println("Master Sent: " + command);

  // Give the slave a moment to process the received command
  delay(500); 

  // ----------------------------------------
  // STEP 2: Request response from the Slave
  // ----------------------------------------
  // "yes master" is exactly 10 characters long
  Wire.requestFrom(I2C_SLAVE_ADDR, 10); 
  
  String response = "";
  
  // Read incoming bytes from the slave
  while (Wire.available()) {
    char c = Wire.read();
    response += c;
  }

  // Check if we received a valid response
  if (response.length() > 0) {
    Serial.print("Slave Replied: ");
    Serial.println(response);
  } else {
    Serial.println("Error: No Reply From Slave");
  }

  Serial.println("-------------------------");
  
  // Wait 2 seconds before the next cycle
  delay(2000); 
}

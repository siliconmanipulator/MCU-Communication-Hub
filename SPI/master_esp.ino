// ==============================================================================
// Project: SPI Master-Slave Communication
// Device: ESP32 (Master)
// Protocol: Serial Peripheral Interface (SPI)
// Description: This code configures the ESP32 as an SPI Master. It transmits a
//              string command to the Slave device and subsequently retrieves
//              an acknowledgment using a trigger byte and dummy clock cycles.
// ==============================================================================

#include <SPI.h>

// Define VSPI standard pins for ESP32
#define VSPI_MISO 19
#define VSPI_MOSI 23
#define VSPI_SCLK 18
#define VSPI_SS   5

void setup() {
  Serial.begin(115200);

  // Configure the Slave Select (SS) pin as an output
  pinMode(VSPI_SS, OUTPUT);
  
  // Set SS HIGH to ensure the Slave is initially inactive
  digitalWrite(VSPI_SS, HIGH); 

  // Initialize the SPI bus with predefined pins
  SPI.begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);

  // Reduce SPI clock speed to ensure data integrity over physical jumper wires
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.println("SPI Master Initialized. Commencing operation...");
  Serial.println("=============================================");
}

void loop() {
  String command = "Wait for my command\n";

  // ---------------------------------------------------------
  // Phase 1: Transmit the instruction to the Slave
  // ---------------------------------------------------------
  digitalWrite(VSPI_SS, LOW); // Pull SS LOW to activate the Slave device

  for (int i = 0; i < command.length(); i++) {
    SPI.transfer(command[i]);
    delayMicroseconds(20); // Micro-delay to allow the Slave time to process
  }

  digitalWrite(VSPI_SS, HIGH); // Pull SS HIGH to deactivate the Slave

  Serial.print("Master Transmitted: ");
  Serial.print(command);

  // Provide adequate time for the Slave to parse the command and prepare the response
  delay(500);

  // ---------------------------------------------------------
  // Phase 2: Retrieve the acknowledgment from the Slave
  // ---------------------------------------------------------
  digitalWrite(VSPI_SS, LOW); // Reactivate the Slave device

  // Transmit the designated trigger byte to instruct the Slave to begin replying
  SPI.transfer('?');
  delayMicroseconds(50);

  String response = "";
  
  // Generate 11 clock cycles by transmitting dummy bytes (0x00) to fetch the reply
  for (int i = 0; i < 11; i++) {
    char incomingByte = SPI.transfer(0x00);
    response += incomingByte;
    delayMicroseconds(20);
  }

  digitalWrite(VSPI_SS, HIGH); // Deactivate the Slave device

  // Sanitize and evaluate the received response
  response.trim();
  
  if (response.length() > 0) {
    Serial.print("Slave Acknowledged: ");
    Serial.println(response);
  } else {
    Serial.println("System Error: No acknowledgment received from Slave.");
  }

  Serial.println("---------------------------------------------");
  
  // Suspend execution for 2 seconds before initiating the next iteration
  delay(2000); 
}

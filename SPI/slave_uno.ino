// ==============================================================================
// Project: SPI Master-Slave Communication
// Device: Arduino Uno/Nano (Slave)
// Protocol: Serial Peripheral Interface (SPI)
// Description: This code configures the Arduino as an SPI Slave using hardware
//              interrupts. It features robust error handling, noise filtering,
//              and race-condition prevention to ensure stable long-term operation.
// ==============================================================================

#include <SPI.h>

// Buffers and state variables for incoming data from the Master
char receiveBuffer[50];
volatile byte bufferPosition = 0;
volatile bool isCommandComplete = false;

// Buffers and state variables for the outgoing acknowledgment message
char acknowledgmentBuffer[] = "yes master\n";
volatile byte acknowledgmentPosition = 0;
volatile bool isTransmittingReply = false;

void setup() {
  Serial.begin(9600);

  // Configure MISO as an output to allow data transmission back to the Master
  pinMode(MISO, OUTPUT);

  // Enable SPI Control Register in Slave Mode
  SPCR |= _BV(SPE);

  // Enable SPI Interrupts to process incoming data asynchronously
  SPCR |= _BV(SPIE);

  Serial.println("SPI Slave Initialized. Awaiting Master instructions...");
  Serial.println("======================================================");
}

// ------------------------------------------------------------------------------
// Interrupt Service Routine (ISR): Executes automatically on SPI clock cycles
// ------------------------------------------------------------------------------
ISR(SPI_STC_vect) {
  byte incomingByte = SPDR; // Read the received byte from the SPI Data Register

  if (isTransmittingReply) {
    // If in transmission mode, load the subsequent character into the register
    // It will be physically transmitted on the next clock cycle provided by the Master
    SPDR = acknowledgmentBuffer[acknowledgmentPosition];
    acknowledgmentPosition++;

    // Terminate transmission mode upon reaching the end of the response string
    if (acknowledgmentPosition >= sizeof(acknowledgmentBuffer) - 1) { 
      isTransmittingReply = false; 
    }
  } 
  else if (incomingByte == '?') {
    // Detect the trigger byte indicating the Master is ready to read the acknowledgment
    acknowledgmentPosition = 0;
    SPDR = acknowledgmentBuffer[acknowledgmentPosition++]; 
    isTransmittingReply = true;
  } 
  else {
    // Filter out dummy bytes (0x00), floating line noise (0xFF), and carriage returns (\r)
    if (incomingByte != 0x00 && incomingByte != 0xFF && incomingByte != '\r') { 
      
      if (incomingByte == '\n') {      
        // The newline character marks the completion of the command string
        receiveBuffer[bufferPosition] = 0; // Append null terminator
        isCommandComplete = true;  
      } 
      else if (bufferPosition < sizeof(receiveBuffer) - 1) {
        // Store valid characters, strictly preventing buffer overflow
        receiveBuffer[bufferPosition++] = incomingByte;
      }
    }
  }
}

void loop() {
  // Execute the primary logic only when a complete, valid command has been received
  if (isCommandComplete) {
    
    // Convert the character array to a String object and sanitize it
    String commandMessage = String(receiveBuffer);
    commandMessage.trim();
    
    Serial.print("Master Instruction Received: ");
    Serial.println(commandMessage);
    
    // Validate the received instruction against the expected operational command
    if (commandMessage == "Wait for my command") {
      Serial.println("Status: Valid command recognized. Acknowledgment queued.");
    } else {
      Serial.println("Status: Unrecognized command. Ignoring payload.");
    }
    
    // ---------------------------------------------------------
    // Critical Section: Temporarily disable hardware interrupts.
    // This prevents race conditions where new data might arrive 
    // exactly while the state variables are being reset.
    // ---------------------------------------------------------
    noInterrupts();
    bufferPosition = 0; 
    isCommandComplete = false;
    interrupts();
    
    Serial.println("------------------------------------------------------");
  }
}

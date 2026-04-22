// ==========================================
// ESP32 Master Code - UART Communication
// ==========================================

#define RXD2 16 // Receive pin for ESP32 (Connects to Arduino TX via voltage divider)
#define TXD2 17 // Transmit pin for ESP32 (Connects to Arduino RX)

void setup() {
  // Initialize serial communication for the PC Serial Monitor
  Serial.begin(115200); 
  
  // Initialize Hardware Serial 2 for communication with the Arduino slave
  // Parameters: Baud rate 9600, 8 data bits, no parity, 1 stop bit, RX pin, TX pin
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
  
  Serial.println("Master Ready. Sending command...");
}

void loop() {
  // Send the command string to the Slave (Arduino)
  Serial2.println("Wait for my command");
  Serial.println("Master Sent: Wait for my command");

  // Brief pause to allow the slave time to process the message and respond
  delay(500); 

  // Check if any data has been received back from the slave
  if (Serial2.available()) {
    // Read the incoming message until a newline character is found
    String reply = Serial2.readStringUntil('\n');
    
    // Remove any trailing whitespace, carriage returns, or newline characters
    reply.trim(); 
    
    // Display the received response on the PC Serial Monitor
    Serial.print("Slave Replied: ");
    Serial.println(reply);
  } else {
    // If no data is available in the buffer, indicate that there was no reply
    Serial.println("No Reply From Slave");
  }
  
  // Print a separator line for better readability in the Serial Monitor
  Serial.println("-------------------------");
  
  // Wait for 1 second before starting the next loop cycle
  delay(1000); 
}
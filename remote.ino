// Uses the new version of the IRremote library
#include <IRremote.hpp>

// Define the pin connected to the IR receiver module (on the Nano, use D0-D12 for digital input/output)
int RECEIVER_PIN = 11;

// Create an instance of the IR receiver object
IRrecv irrecv(RECEIVER_PIN);

decode_results results;

void setup() {
  // Initialize serial communication at 9600 baud rate to enable receiving values through the terminal
  Serial.begin(9600);
  
  // Enable IR receiver to start receiving signals
  IrReceiver.begin(RECEIVER_PIN);
}

void loop() {
  // Check if there is a value to be decoded from the IR receiver
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 
   
      IrReceiver.resume();

      delay(100);
  }
}

// Up -  F8070707
// Down - F40B0707


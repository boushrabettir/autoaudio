#include <IRremote.h>

// Define the pin connected to the IR receiver module (on the Nano, use D0-D12 for digital input/output)
int RECEIVER_PIN = 12;

// Create an instance of the IR receiver object
IRrecv irrecv(RECEIVER_PIN);

decode_results results;

void setup() {
  // Initialize serial communication at 9600 baud rate to enable receiving values through the terminal
  Serial.begin(9600);
  
  // Enable IR receiver to start receiving signals
  irrecv.enableIRIn();
}

void loop() {
  // Check if there is a value to be decoded from the IR receiver
  if (irrecv.decode(&results))
  {
    // Print the hexadecimal value of the received IR signal
    Serial.println(results.value, HEX);
    
    // Continue to receive more IR signals
    irrecv.resume();
    
    // Delay to view hex values in a slow manner
    delay(50);
  }
}

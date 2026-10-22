// Project : An Arduino Based Infrared Remote control lighting system, with integrated AC switching.
// By ElectroTech Media


/*
You would need to unstall the IR remote library first, the steps below will guide you
1) Open the Arduino IDE.
2) Navigate to Tools > Manage Libraries.
3) In the search bar, type "IRremote".
4) Look for the library named IRremote (by shirriff,z3t0,ArminJo).
5) And click install.
*/
// Include the IRremote library to handle infrared signals
#include <IRremote.h>

//Define pins
const int IR_RECEIVER_PIN = 11; // Digital pin connected to the IR receiver output
const int RELAY1_PIN = 4;       // Digital pin connected to Relay channel 1
const int RELAY2_PIN = 7;       // Digital pin connected to Relay channel 2
 
// Replace these hexadecimal codes with the actual codes from your spicific IR remote
// (You can find your remote codes by running  a simple IR receiver test sketch)
#define BUTTON_1 0xF30CFF00     // Remote button to control lamp 1
#define BUTTON_2 0xE718FF00     // Remote button to control lamp 2

// Variables to keep track of the current state of each lamp(false = OFF, true = ON)
bool lamp1State = false;
bool lamp2State = false;

void setup() {
  // Start the serial monitor for debugging/getting remote codes
  Serial.begin(9600);

  //Initialize the IR receiver
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);

  // Set relay pins as digital outputs
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  //Ensure both lamps start in the OFF state ( relays are often active LOW
  //meaning LOW turns the relay ON and HIGH turns the relay OFF depending on the module)
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  Serial.println("System ready. Press a remote button....");

}

void loop() {
  // Check if an IR signal has  been received
  if (IrReceiver.decode()){

    // Get the full 32-bit raw data code from the remote
    uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData;

    // print the received code to the serial monitor
    Serial.print("Pressed Code: 0x");
    Serial.println(receivedCode, HEX);

    // Check which button was pressed
    switch (receivedCode) {
      
      case BUTTON_1:
       lamp1State = !lamp1State; // Toggle the state (ON to OFF, OFF to ON)
       // If your relay is Active LOW, true sets it LOW(ON), false  sets it HIGH(OFF)
       digitalWrite(RELAY1_PIN, lamp1State ? LOW : HIGH);
       Serial.print("Lamp 1 toggled to: ");
       Serial.print(lamp1State ? "ON" : "OFF");
       break;
      
      case BUTTON_2:
       lamp2State = !lamp2State; // Toggle the state
       digitalWrite(RELAY2_PIN, lamp2State ? LOW : HIGH);
       Serial.print("Lamp 2 toggled to: ");
       Serial.println(lamp2State ? "ON" : "OFF");
       break;

       
    }

    // Receive the next value
    IrReceiver.resume();
  }

}

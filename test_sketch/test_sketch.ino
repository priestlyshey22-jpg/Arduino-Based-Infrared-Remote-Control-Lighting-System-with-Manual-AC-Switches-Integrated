#include <IRremote.hpp> // Using the modern .hpp header

#define IR_RECEIVE_PIN 11 // Connect your IR Receiver OUT pin here

void setup() {
  Serial.begin(9600);  // Open communication to your computer screen

  // start the receiver and flash the duilt-in Arduino LED when a signal is caught
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("IR Receiver Test Tool Ready. press any remote button...");
}

void loop() {
  // Check if the sensor has picked up an infrared signal
  if (IrReceiver.decode()){

    // print the clean protocol command (e.g., 0x45)
    Serial.print("Command (short hex): 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    // Print the full 32-bit raw data (e.g., 0xFFA25D)
    Serial.print("Raw Data (Long hex): 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    Serial.println("---------------------------------------------------");

    IrReceiver.resume(); // Reset and prepare to receive the next button press
  }

}

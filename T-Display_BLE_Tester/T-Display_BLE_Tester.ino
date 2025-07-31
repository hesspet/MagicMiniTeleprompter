//
// T-Display_BLE_Tester
//
// 
// - Advertise BLE
// - Get connection
// - Receive string
// - Show value on display
//
//
// Version 3
//
#include "DisplayHandler.h"
#include "BLEHandler.h"

DisplayHandler display;
BLEHandler ble;

void setup() {

  // just for debugging
  Serial.begin(115200);
  
  display.begin();
  delay(500);       // etwas Ruhe vor BLE-Init
  
  // fire up ble
  ble.begin(&display);
}

void loop() {
  delay(1000); // nothing to do
}
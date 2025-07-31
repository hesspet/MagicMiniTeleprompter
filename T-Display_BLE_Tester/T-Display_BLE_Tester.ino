//
// T-Display_BLE_Tester
//
// Version 2
//
#include "DisplayHandler.h"
#include "BLEHandler.h"

DisplayHandler display;
BLEHandler ble;

void setup() {
  Serial.begin(115200);
  
  display.begin();
  delay(500);       // etwas Ruhe vor BLE-Init
  ble.begin(&display);
}

void loop() {
  delay(1000); // nichts weiter nötig
}
//
// T-Display_MagicMiniTeleprompter
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
#include "ButtonManager.h"
#include "PowerManager.h"

DisplayHandler display;
BLEHandler ble;
ButtonManager buttonManager(0, 35);
PowerManager powerManager;

void setup() {

  // just for debugging
  Serial.begin(115200);
  
  display.begin();
  delay(500);       // etwas Ruhe vor BLE-Init
  
  buttonManager.begin();
  powerManager.begin(&buttonManager, &display);
  delay(500);       // etwas Ruhe vor BLE-Init

  // fire up ble
  ble.begin(&display);

  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("[BOOT] Aufgewacht durch BOOT-Taste (GPIO 0)");
  }

  buttonManager.setOnButton0Pressed([]() {
    Serial.println("GPIO 0 wurde kurz gedrückt");
  });

  buttonManager.setOnButton35Pressed([]() {
    Serial.println("GPIO 35 wurde kurz gedrückt");
  });
  
}

void loop() {
  buttonManager.update();
  powerManager.update();
}
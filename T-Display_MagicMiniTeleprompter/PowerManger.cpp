// PowerManager.cpp
#include <esp_sleep.h>
#include <BLEDevice.h>
#include "PowerManager.h"
#include "ButtonManager.h"
#include "DisplayHandler.h"
#include "BLEHandler.h"

void PowerManager::begin(ButtonManager* buttons, DisplayHandler* display, BLEHandler* ble) {
  buttonManager = buttons;
  displayHandler = display;
  bleHandler = ble;
}

void PowerManager::update() {
  if (!buttonManager) return;

  if (buttonManager->isButtonBPressed()) { // GPIO 35 gedrückt halten
    if (bothPressedSince == 0) {
      bothPressedSince = millis();
    } else {
      unsigned long elapsed = millis() - bothPressedSince;
      unsigned long remaining = (holdDuration - elapsed) / 1000;
      if (displayHandler && remaining <= 7) {
        displayHandler->showMessage("OFF IN: " + String(remaining), false);
      }
      if (elapsed >= holdDuration) {
        goToDeepSleep();
      }
    }
  } else {
    bothPressedSince = 0;
  }
}

void PowerManager::goToDeepSleep() {

  Serial.println("[POWER] Deep Sleep wird vorbereitet...");
 
  Serial.println("[POWER] Shutdown BLE");
  bleHandler->goOn = false;
  delay(100);
  BLEDevice::deinit(true);
  delay(300);

 if (displayHandler) {
    Serial.println("[POWER] Shutdown Display");
    displayHandler->shutdown();
  }

  Serial.println("[POWER] Start sleep prep");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);

  Serial.println("[POWER] Schlafmodus aktiviert.");
  delay(300);

  esp_deep_sleep_start();
}
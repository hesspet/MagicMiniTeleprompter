// PowerManager.cpp
#include "PowerManager.h"
#include "ButtonManager.h"
#include "DisplayHandler.h"
#include <esp_sleep.h>
#include <BLEDevice.h>
#include <TFT_eSPI.h>

#include "DisplayHandler.h"

void PowerManager::begin(ButtonManager* buttons, DisplayHandler* display) {
  buttonManager = buttons;
  displayHandler = display;
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
        displayHandler->showMessage("OFF IN: " + String(remaining));
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

  if (displayHandler) {
    displayHandler->shutdown();
  }

  BLEDevice::deinit(true);
  delay(300);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);
  Serial.println("[POWER] Schlafmodus aktiviert.");
  esp_deep_sleep_start();
}
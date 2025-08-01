#include "BatteryManager.h"
#include "DisplayHandler.h"

BatteryManager::BatteryManager(uint8_t pin, DisplayHandler* display)
  : analogPin(pin), displayHandler(display) {}

void BatteryManager::begin() {
  analogReadResolution(12); // max. 0–4095
}

void BatteryManager::update() {
  unsigned long now = millis();
  if (now - lastMeasure >= measureInterval || lastMeasure == 0) {
    lastMeasure = now;

    float voltage = readVoltage();
    uint8_t percent = calcPercentage(voltage);

    if (displayHandler) {
      displayHandler->updateBatteryBar(percent);
    }
  }
}

float BatteryManager::readVoltage() {
  int raw = analogRead(analogPin);
  return raw * 3.3 / 4095.0 * 2.0; // Spannungsteiler 1:2
}

uint8_t BatteryManager::calcPercentage(float voltage) {
  if (voltage >= 4.2) return 100;
  if (voltage >= 3.9) return 75;
  if (voltage >= 3.7) return 50;
  if (voltage >= 3.5) return 25;
  if (voltage >= 3.3) return 10;
  return 0;
}

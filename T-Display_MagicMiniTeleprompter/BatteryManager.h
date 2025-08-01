#pragma once
#include <Arduino.h>

class DisplayHandler;

class BatteryManager {
public:
  BatteryManager(uint8_t pin, DisplayHandler* display);
  void begin();
  void update(); // alle 30 Sekunden aufrufen

private:
  uint8_t analogPin;
  DisplayHandler* displayHandler;
  unsigned long lastMeasure = 0;
  const unsigned long measureInterval = 10000; // 30 - 30000 Sekunden

  float readVoltage();      // Spannung in Volt
  uint8_t calcPercentage(float voltage); // Schätzung aus Spannung
};
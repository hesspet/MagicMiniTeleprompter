#pragma once
// PowerManager.h
#include <Arduino.h>

class ButtonManager; 
class DisplayHandler; 
class BLEHandler;

class PowerManager {
public:
  void begin(ButtonManager* buttons, DisplayHandler* display, BLEHandler* ble);
  void update();

private:
  ButtonManager* buttonManager = nullptr;
  DisplayHandler* displayHandler = nullptr; 
  BLEHandler* bleHandler = nullptr;

  const unsigned long holdDuration = 7000; // 7 Sekunden
  unsigned long bothPressedSince = 0;

  void goToDeepSleep();
};
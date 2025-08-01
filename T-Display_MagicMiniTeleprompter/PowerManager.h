// PowerManager.h
#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <Arduino.h>

class ButtonManager; 
class DisplayHandler; 

class PowerManager {
public:
  void begin(ButtonManager* buttons, DisplayHandler* display);
  void update();

private:
  ButtonManager* buttonManager = nullptr;
   DisplayHandler* displayHandler = nullptr; 
  const unsigned long holdDuration = 7000; // 7 Sekunden
  unsigned long bothPressedSince = 0;

  void goToDeepSleep();
};

#endif

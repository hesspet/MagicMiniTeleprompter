// ButtonManager.h
#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include <Arduino.h>
#include <functional>

class ButtonManager {

public:

  ButtonManager(int pinA, int pinB);

  void begin();
  void update();

  bool isButtonAPressed() const;
  bool isButtonBPressed() const;
  bool areBothButtonsPressed() const;

  void setOnButton0Pressed(std::function<void()> callback);
  void setOnButton35Pressed(std::function<void()> callback);

private:

  int pinA;
  int pinB;
  bool stateA = false;
  bool stateB = false;
  bool lastStateA = false;
  bool lastStateB = false;

  std::function<void()> onButton0Pressed = nullptr;
  std::function<void()> onButton35Pressed = nullptr;

  unsigned long pressStart35 = 0;
  const unsigned long longPressThreshold = 7000; // ms
};

#endif

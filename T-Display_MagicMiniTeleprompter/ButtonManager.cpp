// ButtonManager.cpp
#include "ButtonManager.h"

ButtonManager::ButtonManager(int pinA, int pinB)
  : pinA(pinA), pinB(pinB) {}

void ButtonManager::begin() {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
}

void ButtonManager::update() {
  // Button A (GPIO 0)
  lastStateA = stateA;
  stateA = digitalRead(pinA) == LOW;
  if (stateA && !lastStateA && onButton0Pressed) {
    Serial.println("[ButtonManager] Button 0 pressed");
    onButton0Pressed();
  }

  // Button B (GPIO 35)
  lastStateB = stateB;
  stateB = digitalRead(pinB) == LOW;

  if (stateB && !lastStateB) {
    pressStart35 = millis();
  }
  if (!stateB && lastStateB) {
    unsigned long duration = millis() - pressStart35;
    if (duration < longPressThreshold && onButton35Pressed) {
      Serial.println("[ButtonManager] Button 35 short press");
      onButton35Pressed();
    }
  }
}

bool ButtonManager::isButtonAPressed() const {
  return stateA;
}

bool ButtonManager::isButtonBPressed() const {
  return stateB;
}

bool ButtonManager::areBothButtonsPressed() const {
  return stateA && stateB;
}

void ButtonManager::setOnButton0Pressed(std::function<void()> callback) {
  onButton0Pressed = callback;
}

void ButtonManager::setOnButton35Pressed(std::function<void()> callback) {
  onButton35Pressed = callback;
}

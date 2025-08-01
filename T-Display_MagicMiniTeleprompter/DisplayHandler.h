// DisplayHandler.h
#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include <TFT_eSPI.h>
#include <SPI.h>
#include "StatusText.h"

class DisplayHandler {
public:
  void begin();
  void showStatus(const String& text, uint16_t color);
  void showMessage(const String& message);
  void shutdown();
  
private:
  TFT_eSPI tft = TFT_eSPI();

  TFT_eSprite statusSprite = TFT_eSprite(&tft); // Sprite für Statusanzeige
  uint16_t statusColor = TFT_BLACK;

  void drawStatusOverlay();  
};

#endif

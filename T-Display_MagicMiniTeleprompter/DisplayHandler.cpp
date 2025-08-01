// DisplayHandler.cpp
#include "DisplayHandler.h"

void DisplayHandler::begin() {

  tft.init();
  tft.setRotation(1); // Querformat
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM); // Mitte zentriert
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

 // Status-Sprite vorbereiten
  statusSprite.setColorDepth(8); // 256 Farben reichen
  statusSprite.createSprite(20, 20); // kleiner Sprite (Größe Statuskreis)
  statusSprite.setSwapBytes(true);  // falls Du mit 16-bit Farbformat arbeitest

   // 🆕 Initialanzeige direkt beim Start
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("📡 Starte BLE...", tft.width() / 2, tft.height() / 2);

}

void DisplayHandler::showStatus(const String& text, uint16_t color) {
  Serial.println("[STATUS] " + text);
  statusColor = color;
  drawStatusOverlay();  // Sprite neu zeichnen
}

void DisplayHandler::showMessage(const String& message) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);  // Mitte zentriert
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  // Maximale Displaygröße
  int maxWidth  = tft.width() - 10;   // etwas Rand lassen
  int maxHeight = tft.height() - 10;

  int bestSize = 1;
  for (int size = 1; size <= 8; ++size) {  // 1 bis 7 sind vernünftig
    tft.setTextSize(size);
    int16_t w = tft.textWidth(message);
    int16_t h = 8 * size;  // Standardhöhe der Schrift bei Größe 1 = 8px

    if (w > maxWidth || h > maxHeight) {
      break;  // letzte gültige Größe war bestSize
    }
    bestSize = size;
  }

  tft.setTextSize(bestSize);
  tft.drawString(message, tft.width() / 2, tft.height() / 2);

  drawStatusOverlay();  // Sprite neu zeichnen}
}

//
// drawStatusOverlay
//
void DisplayHandler::drawStatusOverlay() {

  statusSprite.fillSprite(TFT_BLACK);  // Hintergrundfarbe für Transparenz
  int radius = 8;

  // Kreis zeichnen
  statusSprite.fillCircle(10, 10, radius, statusColor);
  statusSprite.drawCircle(10, 10, radius, TFT_BLACK);

  // Sprite überlagern – rechts oben
  int x = tft.width() - statusSprite.width() - 4;
  int y = 4;
  statusSprite.pushSprite(x, y, TFT_BLACK);  // TFT_BLACK = transparente Farbe
}

void DisplayHandler::shutdown() {
  tft.fillScreen(TFT_BLACK); // optional: Display leeren
  tft.writecommand(TFT_DISPOFF); // Display aus
  tft.writecommand(TFT_SLPIN);   // Display in Schlafmodus
  delay(100);                    // kurz warten
}
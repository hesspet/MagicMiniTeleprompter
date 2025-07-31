// BLEHandler.cpp
#include "BLEHandler.h"
#include "DisplayHandler.h"  // zum Anzeigen

class MyCallbacks : public BLECharacteristicCallbacks {
public:  
  MyCallbacks(DisplayHandler *display)
    : display(display) {}

  void onWrite(BLECharacteristic *pCharacteristic) override {
    String value = pCharacteristic->getValue();
    if (value.length() > 0 && display) {
      display->showMessage(value);
    }
  }

private:
  DisplayHandler *display;
};

void BLEHandler::begin(DisplayHandler *displayRef) {
  display = displayRef;

  BLEDevice::init("ESP32_Display");
  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks(display));

  BLEService *service = server->createService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");

  rxCharacteristic = service->createCharacteristic(
    "6E400003-B5A3-F393-E0A9-E50E24DCCA9E",
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);

  rxCharacteristic->setCallbacks(new MyCallbacks(display));
  service->start();
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->start();
   display->showStatus(StatusText::BLE_ADVERTISING, TFT_BLUE);
}



void BLEHandler::ServerCallbacks::onConnect(BLEServer *pServer) {
  display->showStatus(StatusText::BLE_CONNECTED, TFT_GREEN);
}

void BLEHandler::ServerCallbacks::onDisconnect(BLEServer *pServer) {
  display->showStatus(StatusText::BLE_DISCONNECTED, TFT_RED);
  delay(500);
  BLEDevice::startAdvertising();
  display->showStatus(StatusText::BLE_ADVERTISING, TFT_BLUE);
}

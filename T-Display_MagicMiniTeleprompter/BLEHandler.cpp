#include "BLEHandler.h"
#include "StatusText.h"

const char* STRING_RECEIVE_GUID = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";

// Konstruktor
BLEHandler::ServerCallbacks::ServerCallbacks(DisplayHandler* d, BLEHandler* handler)
  : display(d), parent(handler) {}

void BLEHandler::ServerCallbacks::onConnect(BLEServer* pServer) {
  if (display && parent->goOn)
    display->showStatus(StatusText::BLE_CONNECTED, TFT_GREEN);
}

void BLEHandler::ServerCallbacks::onDisconnect(BLEServer* pServer) {

  if (display && parent->goOn)
    display->showStatus(StatusText::BLE_DISCONNECTED, TFT_RED);
  delay(500);

  if (parent && parent->goOn)
    parent->startAdvertising();
}

class MyCallbacks : public BLECharacteristicCallbacks {
public:
  MyCallbacks(DisplayHandler* display) : display(display) {}

  void onWrite(BLECharacteristic* pCharacteristic) override {
    String value = pCharacteristic->getValue();
    if (value.length() > 0 && display ) {
      display->showMessage(value);
    }
  }

private:
  DisplayHandler* display;
};

void BLEHandler::begin(DisplayHandler* displayRef) {
  display = displayRef;

  BLEDevice::init("ESP32_Display");

  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks(display, this));

  BLEService* service = server->createService(STRING_RECEIVE_GUID);
  rxCharacteristic = service->createCharacteristic(STRING_RECEIVE_GUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
  rxCharacteristic->setCallbacks(new MyCallbacks(display));

  service->start();

  startAdvertising();
}

void BLEHandler::startAdvertising() {
  BLEDevice::startAdvertising();
  if (display)
    display->showStatus(StatusText::BLE_ADVERTISING, TFT_BLUE);
}

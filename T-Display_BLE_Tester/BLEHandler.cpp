// BLEHandler.cpp
#include "BLEHandler.h"
#include "DisplayHandler.h"  // zum Anzeigen

const char * STRING_RECEIVE_GUID = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";

//
// Called when a new message comes in
//
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
  
  // create and initialize BLE Server

  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks(display));

  // build up a service - Standard value for strings

  BLEService *service = server->createService(STRING_RECEIVE_GUID);
  rxCharacteristic = service->createCharacteristic(STRING_RECEIVE_GUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
  rxCharacteristic->setCallbacks(new MyCallbacks(display));

  service->start();
  
  startAdvertising(); 
}


//
// When a connection is established - write out a message
//
void BLEHandler::ServerCallbacks::onConnect(BLEServer *pServer) {
  display->showStatus(StatusText::BLE_CONNECTED, TFT_GREEN);
}

//
// When a connection is disconnected - write out a message
// The restart the advertising
//
void BLEHandler::ServerCallbacks::onDisconnect(BLEServer *pServer) {

  display->showStatus(StatusText::BLE_DISCONNECTED, TFT_RED);
  delay(500);

  startAdvertising(); 
}

void BLEHandler::startAdvertising() 
{
  BLEDevice::startAdvertising(); 
  display->showStatus(StatusText::BLE_ADVERTISING, TFT_BLUE);
}

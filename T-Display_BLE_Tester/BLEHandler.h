// BLEHandler.h
#ifndef BLEHANDLER_H
#define BLEHANDLER_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include "DisplayHandler.h"

//
// * Encapsulates the BLE Handling
// * Gets displayhandler injected in constructor
// 
class BLEHandler {
public:
  
  void begin(DisplayHandler* display);
 
  ServerCallbacks(DisplayHandler* display) : display(display) {}
  
  void onConnect(BLEServer* pServer) override;
  void onDisconnect(BLEServer* pServer) override;

private:
  
  void startAdvertising();

  BLEServer* pServer = nullptr;
  DisplayHandler* display = nullptr;  
  BLECharacteristic* rxCharacteristic = nullptr;

  class ServerCallbacks : public BLEServerCallbacks {
  
    // reference to the display, set in begin(...)
    DisplayHandler* display;
     
  };
};

#endif

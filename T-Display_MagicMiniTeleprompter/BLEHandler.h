#pragma once
// BLEHandler.h

#include <BLEDevice.h>
#include <BLEServer.h>
#include "DisplayHandler.h"

class BLEHandler {
public:
  void begin(DisplayHandler* display);
  bool goOn = true;
  
  class ServerCallbacks : public BLEServerCallbacks {
  public:
    ServerCallbacks(DisplayHandler* d, BLEHandler* handler);
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;

  private:
    DisplayHandler* display;
    BLEHandler* parent;
  };

private:
  void startAdvertising();

  BLEServer* pServer = nullptr;
  DisplayHandler* display = nullptr;
  BLECharacteristic* rxCharacteristic = nullptr;
};


// BLEHandler.h
#ifndef BLEHANDLER_H
#define BLEHANDLER_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include "DisplayHandler.h"

class BLEHandler {
public:
  void begin(DisplayHandler* display);

private:
  BLEServer* pServer = nullptr;
  DisplayHandler* display = nullptr;  
  BLECharacteristic* rxCharacteristic = nullptr;

  class ServerCallbacks : public BLEServerCallbacks {
  public:
    ServerCallbacks(DisplayHandler* display) : display(display) {}
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;
  private:
    DisplayHandler* display;
     
  };
};

#endif

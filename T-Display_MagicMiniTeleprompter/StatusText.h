#pragma once
// StatusText.h

namespace StatusText {
  // Systemstatus
  constexpr const char* STARTING       = "[•] STARTE";
  constexpr const char* INIT_OK        = "[OK] INIT";
  constexpr const char* INIT_FAIL      = "[!] FEHLER";

  // BLE
  constexpr const char* BLE_ADVERTISING = "[BLE] WERBUNG";
  constexpr const char* BLE_CONNECTED   = "[✓] VERBUNDEN";
  constexpr const char* BLE_DISCONNECTED = "[X] GETRENNT";
  constexpr const char* BLE_RESTARTED   = "[BLE] NEUSTART";

  // Nachrichten
  constexpr const char* MESSAGE_RECEIVED = "[MSG] TEXT";
  constexpr const char* INVALID_MESSAGE  = "[!] FEHLER";
}
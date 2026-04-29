#include "ble.h"

#include <Arduino.h>
#include <NimBLEDevice.h>

#include "Logger.h"
#include "queue.h"

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

NimBLECharacteristic* pTx;
bool isConnected = false;

class ConnectionCallback : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) {
    isConnected = true;
    Logger::info("iPhone connected!");
  }
  void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) {
    isConnected = false;
    Logger::info("iPhone unconnected!");
    pServer->startAdvertising();
  }
};

class IncomeDataCallback : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
    std::string value = pCharacteristic->getValue();
    queueSend(value.c_str());
  }
};

void bleInit() {
  NimBLEDevice::init("ESP32");
  NimBLEServer* server = NimBLEDevice::createServer();
  server->setCallbacks(new ConnectionCallback(), true);

  NimBLEService* service = server->createService(SERVICE_UUID);

  pTx = service->createCharacteristic(CHAR_TX, NIMBLE_PROPERTY::NOTIFY);
  pTx->createDescriptor("2902");

  NimBLECharacteristic* pRx = service->createCharacteristic(CHAR_RX, NIMBLE_PROPERTY::WRITE);
  pRx->setCallbacks(new IncomeDataCallback());

  NimBLEAdvertising* adv = server->getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->start();
  Logger::info("BLE is running, waiting for iphone...");
}

void bleLoop() {
}

void bleSend(const char* msg) {
  if (!isConnected) return;

  pTx->setValue(msg);
  pTx->notify();
}

void bleSend(std::string msg) {
  if (!isConnected) return;

  pTx->setValue(msg);
  pTx->notify();
}
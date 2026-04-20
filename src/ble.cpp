#include "ble.h"

#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "queue.h"

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

BLECharacteristic* pTx;
bool isConnected = false;

class SpojeniCallback : public BLEServerCallbacks {
  void onConnect(BLEServer* s) {
    isConnected = true;
    Serial.println("iPhone connected!");
  }
  void onDisconnect(BLEServer* s) {
    isConnected = false;
    Serial.println("iPhone unconnected!.");
    s->getAdvertising()->start();
  }
};

class PrijataDataCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* c) {
    String cmd = c->getValue().c_str();
    cmd.trim();
    queueSend(cmd);
  }
};

void bleInit() {
  BLEDevice::init("ESP32");
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new SpojeniCallback());

  BLEService* service = server->createService(SERVICE_UUID);

  pTx = service->createCharacteristic(CHAR_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pTx->addDescriptor(new BLE2902());

  BLECharacteristic* pRx = service->createCharacteristic(CHAR_RX, BLECharacteristic::PROPERTY_WRITE);
  pRx->setCallbacks(new PrijataDataCallback());

  service->start();
  server->getAdvertising()->start();
  Serial.println("BLE is running, waiting for iphone...");
}

void bleLoop() {
}

void bleSend(String& msg) {
  if (!isConnected) return;

  pTx->setValue(msg.c_str());
  pTx->notify();
}
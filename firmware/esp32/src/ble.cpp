#include "ble.h"

#include <Arduino.h>
#include <NimBLEDevice.h>

#include "Logger.h"
#include "queue.h"
#include "BleParser.h"
#include "Arduino.h"
#include "BlePacketBuilder.h"

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
    flags.IRStream = false;
    flags.USStream = false;
    Logger::info("iPhone unconnected!");
    pServer->startAdvertising();
  }
};

class IncomeDataCallback : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
    std::string raw = pCharacteristic->getValue();
    std::string hex;

    for (uint8_t b : raw) {
      char buf[4];
      sprintf(buf, "%02X ", b);
      hex += buf;
    }

    Logger::info(hex);
    BleParser::feed(
      (const uint8_t*)raw.data(), 
      raw.length());

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

StreamFlags flags;

void bleLoop() {
  delay(10);
  if (flags.IRStream) {
    ResponsePacket p = BlePacketBuilder::buildIRPacket();
    bleSend(p.buf, p.len);
    // Serial.printf("IR ptr=%p\n", p.buf);
    // Serial.println("Sent IR");
  }
  delay(10);
  if (flags.USStream) {
    ResponsePacket p = BlePacketBuilder::buildUSPacket();
    bleSend(p.buf, p.len);
    // Serial.printf("US ptr=%p\n", p.buf);
    // Serial.println("Sent US");
  }
}

void bleSend(const char* msg) {
  if (!isConnected) return;

  pTx->setValue(msg);
  pTx->notify();
}

void bleSend(std::string msg) {
  if (msg.empty()) return;
  if (!isConnected) return;
  pTx->setValue(msg);
  pTx->notify();
}
void bleSend(const uint8_t* data, size_t len) {
  pTx->setValue(data, len);
  pTx->notify();
}
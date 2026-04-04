#include <motors.h>
#include <ble.h>
#include <CommandHandler.h>
#include <BLEDevice.h> // zakladni inicializace BLE cipu
#include <BLEServer.h> // esp32 jako BLE server ke kteremu se pripojuji ostatni
#include <BLEUtils.h> // pomocne funkce 
#include <BLE2902.h> // descriptor ktery rika iphonu tato charekteristika umi posilat notifikace

#define SERVICE_UUID      "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_RX           "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_TX           "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"



BLECharacteristic* pTx;
bool pripojeno = false;

class SpojeniCallback : public BLEServerCallbacks {
  void onConnect(BLEServer* s) {
    pripojeno = true;
    Serial.println("iPhone pripojeny!");
  }
  void onDisconnect(BLEServer* s) {
    pripojeno = false;
    Serial.println("iPhone odpojen.");
    s->startAdvertising();
  }
};

class PrijataDataCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* c) {
    String cmd = c->getValue().c_str();
    Serial.println("Prijato: " + cmd);

    String result = Commands.handle(cmd);

    Serial.println("Result: " + result);

    pTx->setValue(result.c_str());
    pTx->notify();
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
  Serial.println("BLE bezi, cekam na iPhone...");
}

void bleLoop() {
}

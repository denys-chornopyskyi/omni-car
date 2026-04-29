#include "UltrasonicSensorsManager.h"

#include <Arduino.h>

#include "utils.h"

UltrasonicSensorsManager::UltrasonicSensorsManager(UltrasonicSensor* sensors,
                                                   size_t ammount,
                                                   Protocol& protocol) : _sensors(sensors),
                                                                         _size(ammount),
                                                                         _protocol(protocol) {}

void UltrasonicSensorsManager::begin() {
  for (uint8_t i = 0; i < _size; i++) {
    _sensors[i].begin();
  }
}

void UltrasonicSensorsManager::update() {
  for (uint8_t i = 0; i < _size; i++) {
    // Serial.println(sensorArray[i]->readDistanceCM());
    uint8_t dist = _sensors[i].readDistanceCM();
    _protocol.sendDist(_sensors[i].getType(), dist);
    _sensors[i].printToSerial(dist);
  }
}
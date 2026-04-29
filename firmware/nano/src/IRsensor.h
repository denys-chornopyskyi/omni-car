#pragma once
#include <PCF8574.h>
#include <SoftwareSerial.h>

#include "Counter.h"
#include "Protocol.h"
#include "stdio.h"

class IRsensor {
 public:
  IRsensor(Protocol& protocol);
  void update();
  void begin();

 private:
  void readSensors();
  void printToSerial();
  uint8_t _sensorValues[5];
  Counter counter;
  PCF8574 pcf8574;
  Protocol& _protocol;
};
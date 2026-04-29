#pragma once
#include <SoftwareSerial.h>
#include <stdio.h>

#include "Counter.h"
#include "utils.h"

class UltrasonicSensor {
 public:
  UltrasonicSensor(uint8_t trigPin, uint8_t echoPin, msgType type, const char* name);
  void begin();
  uint8_t readDistanceCM();
  const char* getName();
  msgType getType();
  void printToSerial(uint8_t dist);

 private:
  uint8_t _trigPin;
  uint8_t _echoPin;
  Counter counter;
  msgType _type;
  const char* _name;
};
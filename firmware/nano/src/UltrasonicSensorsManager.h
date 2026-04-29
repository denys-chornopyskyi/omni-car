#pragma once
#include <SoftwareSerial.h>

#include "Protocol.h"
#include "UltrasonicSensor.h"

class UltrasonicSensorsManager {
 public:
  UltrasonicSensorsManager(UltrasonicSensor* sensors, size_t amount, Protocol& protocol);
  void begin();
  void update();

 private:
  UltrasonicSensor* _sensors;
  size_t _size;
  Protocol& _protocol;
};
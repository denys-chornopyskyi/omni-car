#pragma once

#include "SafetyGuard.h"
#include "SensorStore.h"

class ObjectAvoidance {
 public:
  ObjectAvoidance(SafetyGuard& guard) : _guard(guard) {};
  void update();
  void setThreshold(uint8_t dist);

 private:
  SensorData& data = SensorStore::getInstance().data;
  SafetyGuard& _guard;
  uint8_t _THRESHOLD = 20;
};
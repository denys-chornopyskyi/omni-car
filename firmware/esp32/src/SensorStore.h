#pragma once
#include <stdio.h>

struct SensorData {
  uint8_t distance[4];
  uint8_t ir[5];
};

class SensorStore {
 public:
  static SensorStore& getInstance() {
    static SensorStore instance;
    return instance;
  };

  SensorData data;

 private:
  SensorStore() {};
};
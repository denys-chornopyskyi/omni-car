#pragma once
#include <stdio.h>

struct SensorData {
  uint8_t distance[6] = {1, 2, 3, 4, 5, 6};
  uint8_t ir[5] = {0, 0, 0, 1, 1};
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
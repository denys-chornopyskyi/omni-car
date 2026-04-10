#include <map>

#include "Arduino.h"
#include "motors.h"
#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H

#define RX 21
#define TX 22

class LineFollower {
 public:
  LineFollower();
  ~LineFollower();
  void update();

 private:
  void receiveSensorData();
  HardwareSerial mySerial;
  uint8_t _sensorValues[5];
};

extern LineFollower* lineFollower;

#endif
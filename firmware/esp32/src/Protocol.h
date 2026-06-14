#pragma once
#include "HardwareSerial.h"

enum msgType {
  IR_ARRAY = 0xF0,
  FORWARD_DIST = 0xF1,
  BACKWARD_DIST = 0xF2,
  LEFT_DIST = 0xF3,
  RIGHT_DIST = 0xF4,
  FORWARD_LEFT_DIST = 0xF5,
  FORWARD_RIGHT_DIST = 0xF6
};

class Protocol {
 public:
  Protocol(HardwareSerial& serial) : _serial(serial) {};
  void update();

 private:
  void parsePacket(uint8_t type, uint8_t* payload, uint8_t len);
  HardwareSerial& _serial;
  static constexpr uint8_t START_BYTE = 0xAA;
};
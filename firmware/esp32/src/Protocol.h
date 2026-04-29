#pragma once
#include "HardwareSerial.h"

enum msgType {
  IR_ARRAY = 0xF0,
  DIST_1 = 0xF1,
  DIST_2 = 0xF2,
  DIST_3 = 0xF3,
  DIST_4 = 0xF4
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
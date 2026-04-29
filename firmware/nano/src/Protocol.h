#pragma once
#include "SoftwareSerial.h"
#include "utils.h"

class Protocol {
 public:
  Protocol(SoftwareSerial& serial);
  void sendIR(uint8_t* values, size_t len);
  void sendDist(msgType type, uint8_t dist);

 private:
  SoftwareSerial& _serial;
  static constexpr uint8_t START_BYTE = 0xAA;
};
#include "Protocol.h"

#include "Arduino.h"

Protocol::Protocol(SoftwareSerial& serial) : _serial(serial) {}

void Protocol::sendIR(uint8_t* values, size_t len) {
  _serial.write(START_BYTE);
  // Serial.print(START_BYTE);
  _serial.write(msgType::IR_ARRAY);
  // Serial.print(msgType::IR_ARRAY);
  _serial.write(0x05);
  // Serial.print(0x05);

  for (uint8_t i = 0; i < 5; i++) {
    _serial.write(values[i]);
    // Serial.print(values[i]);
  }
  Serial.println();
}

void Protocol::sendDist(msgType type, uint8_t dist) {
  _serial.write(START_BYTE);
  // Serial.print(START_BYTE);
  _serial.write(type);
  // Serial.print(type);
  _serial.write(0x01);
  // Serial.print(0x01);
  _serial.write(dist);
  // Serial.println(dist);
}
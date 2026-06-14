#pragma once
#include <Arduino.h>
#include "queue.h"

class BleParser {
  public:
  static void feed(const uint8_t* data, size_t len);
  static void reset();
  static std::function<void(const char*)> onError;

  private:
  static constexpr uint8_t START = 0xAA;
  static constexpr uint8_t END = 0xFF;
  static constexpr uint8_t BUF_SIZE = 64;

  static uint8_t _buf[BUF_SIZE];
  static size_t _len;

  static void _parse();
  static void _error(const char*);
  static ParsedPacket _buildPacket(uint8_t type, const uint8_t* payload, size_t plen);

};
#pragma once
#include <Arduino.h>

class BleParser {
  public:
  static std::string feed(const uint8_t* data, size_t len);
  static void reset();
  static std::function<void(const char*)> onError;

  const enum PacketType {
    Motion = 0x01,
  };

  const enum MotionButton {
  Center = 0x0a,
  UpLeft = 0x14,
  Up = 0x1e,
  UpRight = 0x28,
  Left = 0x32,
  Right = 0x3c,
  DownLeft = 0x46,
  Down = 0x50,
  DownRight = 0x5a,
};

  private:
  static constexpr uint8_t START = 0xAA;
  static constexpr uint8_t END = 0xFF;
  static constexpr uint8_t BUF_SIZE = 64;

  static uint8_t _buf[BUF_SIZE];
  static size_t _len;

  static std::string _parce();
  static void _error(const char*);
  static std::string _toCommand(uint8_t type, const uint8_t* payload, size_t plen);

};
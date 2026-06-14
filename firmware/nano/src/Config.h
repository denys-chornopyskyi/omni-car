#pragma once
#include <stdio.h>

namespace Config {

constexpr uint8_t TRIG_PIN = 8;
constexpr uint8_t ECHO_PINS[6] = {7, 6, 5, 4, 3, 2};

constexpr const char* SENSOR_NAMES[6] = {"forward", "backward", "left", "right", "forward-left", "forward-right"};

constexpr const uint32_t BAUD_RATE = 9600;

constexpr uint8_t ESP_RX = 9;
constexpr uint8_t ESP_TX = 10;

constexpr unsigned long DEBUG_INTERVAL_MS = 5000;
}
enum msgType {
  IR_ARRAY = 0xF0,
  FORWARD_DIST = 0xF1,
  BACKWARD_DIST = 0xF2,
  LEFT_DIST = 0xF3,
  RIGHT_DIST = 0xF4,
  FORWARD_LEFT_DIST = 0xF5,
  FORWARD_RIGHT_DIST = 0xF6
};
#pragma once
#include <stdio.h>

namespace Config {

constexpr uint8_t TRIG_PIN = 10;
constexpr uint8_t ECHO_PINS[4] = {7, 6, 5, 4};

constexpr const char* SENSOR_NAMES[4] = {"first", "second", "third", "fourth"};

constexpr const uint32_t BAUD_RATE = 9600;

constexpr uint8_t ESP_RX = 8;
constexpr uint8_t ESP_TX = 9;

constexpr unsigned long DEBUG_INTERVAL_MS = 5000;

}  // namespace Config
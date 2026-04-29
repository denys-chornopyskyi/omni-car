#include "RealMotor.h"

#include <Arduino.h>

#include "Logger.h"

RealMotor::RealMotor(uint8_t pinIn1, uint8_t pinIn2, uint8_t ch1, uint8_t ch2)
    : _in1(pinIn1), _in2(pinIn2), _ch1(ch1), _ch2(ch2) {}

void RealMotor::init() {
  Logger::info(_name + std::string(" init"));
  ledcSetup(_ch1, 1000, 8);
  ledcAttachPin(_in1, _ch1);
  ledcSetup(_ch2, 1000, 8);
  ledcAttachPin(_in2, _ch2);
}

void RealMotor::setSpeed(int16_t speed) {
  speed = constrain(speed, -255, 255);

  if (speed > 0) {
    ledcWrite(_ch1, speed);
    ledcWrite(_ch2, 0);
  } else if (speed < 0) {
    ledcWrite(_ch1, 0);
    ledcWrite(_ch2, -speed);
  } else {
    ledcWrite(_ch1, 0);
    ledcWrite(_ch2, 0);
  }

  Logger::verbose(_name + std::string("speed=") + std::to_string(speed));
}

void RealMotor::stop() { setSpeed(0); }
#pragma once
#include <stdint.h>

#include "IMotor.h"

class RealMotor : public IMotor {
 public:
  RealMotor(uint8_t pinIn1, uint8_t pinIn2, uint8_t ch1, uint8_t ch2);
  void init();
  void setName(const char* name);
  void setSpeed(int16_t speed);
  void stop();

 private:
  const char* _name = "MotorX";
  uint8_t _in1;
  uint8_t _in2;
  uint8_t _ch1;
  uint8_t _ch2;
};
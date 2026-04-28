#pragma once
#include <stdint.h>

class IMotor {
 public:
  virtual void init() = 0;
  virtual void setSpeed(int16_t speed) = 0;
  virtual ~IMotor() = default;
};
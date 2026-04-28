#pragma once

#include "IMotor.h"

class MockMotor : public IMotor {
 public:
  MockMotor(const char* name);
  void init();
  void setSpeed(int16_t);

 private:
  const char* _name;
};
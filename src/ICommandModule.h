#pragma once
#include <Arduino.h>

class ICommandModule {
 public:
  virtual ~ICommandModule() = default;

  virtual String handleCommand(String cmd) = 0;
  virtual void update() {};
};
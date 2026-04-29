#pragma once

#include <Arduino.h>

class IModule {
 public:
  virtual ~IModule() = default;

  virtual std::string handleCommand(std::string name, std::string value) = 0;
  virtual void update() {};
};
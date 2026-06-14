#pragma once

#include <Arduino.h>
#include "BleProtocol.h"

class IModule {
 public:
  virtual ~IModule() = default;

  virtual commandResult handleCommand(std::string& name, std::string& value) = 0;
  virtual void update() {};
  virtual uint8_t getId() = 0;
};
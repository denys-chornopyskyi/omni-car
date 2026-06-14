#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "IModule.h"
#include "JoystickController.h"
#include "BleProtocol.h"

class ManualModule : public IModule {
 public:
  ManualModule(MotionController& motion) : joystick(motion) {}
  commandResult handleCommand(std::string& name, std::string& value);
  uint8_t getId() override {
    return 1;
  }

 private:
  JoystickController joystick;
};

#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "IModule.h"
#include "JoystickController.h"

class ManualModule : public IModule {
 public:
  ManualModule(MotionController& motion);
  std::string handleCommand(std::string name, std::string value);

 private:
  JoystickController joystick;
};

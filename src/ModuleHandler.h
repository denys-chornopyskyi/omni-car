#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Arduino.h"
#include "ICommandModule.h"
#include "MotorCommands.h"
#include "motors.h"

class ModuleHandler {
 public:
  // enum class Mode {
  //   Manual,
  //   LineFollow,
  // };
  ModuleHandler() = default;
  String handleCommand(String& cmd);
  void update();

 private:
  // volatile Mode currentMode;
  std::shared_ptr<ICommandModule> activeModule;
};
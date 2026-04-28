#include "ManualModule.h"

ManualModule::ManualModule(MotionController& motion) : joystick(motion) {
}

std::string ManualModule::handleCommand(std::string name, std::string value) {
  if (std::string(name).find('!') != -1) {
    return joystick.handle(name);
  }
  return std::string("");
}
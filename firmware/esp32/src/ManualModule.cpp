#include "ManualModule.h"
#include "Logger.h"

std::string ManualModule::handleCommand(std::string& name, std::string& value) {
  Logger::info(name);
  if (name.find('!') != std::string::npos) {
    return joystick.handle(name);
  }
  return std::string("");
}
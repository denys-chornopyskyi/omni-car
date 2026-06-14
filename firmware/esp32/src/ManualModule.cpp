#include "ManualModule.h"
#include "Logger.h"

commandResult ManualModule::handleCommand(std::string& name, std::string& value) {
  // Logger::info(name);
  if (name.find('!') != std::string::npos) {
    return joystick.handle(name);
  }
  if(name == "stop") {
    joystick.reset();
    return commandResult::ok();
  } 
  return commandResult::err(ErrorType::UnknownCmd);
}
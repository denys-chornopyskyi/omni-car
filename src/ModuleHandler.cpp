#include "ModuleHandler.h"

#include "LineFollower.h"
#include "ManualModule.h"
#include "MotorCommands.h"
#include "motors.h"

// volatile Mode currentMode = Mode::Manual;

String ModuleHandler::handleCommand(String& cmd) {
  
  if (cmd == "manual") {
    activeModule = std::make_shared<ManualModule>();
    return "mode:manual";
  }
  if (cmd == "linefollow") {
    activeModule = std::make_shared<LineFollower>();
    return "mode:linefollow";
  }
  if (activeModule) {
    return activeModule->handleCommand(cmd);
  }

  return "no module";
}
void ModuleHandler::update() {
  if (activeModule) {
    activeModule->update();
  }
}
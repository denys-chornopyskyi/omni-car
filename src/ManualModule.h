#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "ICommandModule.h"
#include "MotorCommands.h"

class JoystickController {
 public:
  JoystickController();
  String handle(String& cmd);
  enum class JoystickButton {
    Num1,
    Num2,
    Num3,
    Num4,
    Up,
    Down,
    Left,
    Right,
  };

 private:
  void keyDown(JoystickButton btn);
  void keyUp(JoystickButton btn);
  void updateMotors();

  std::map<std::vector<JoystickButton>, std::shared_ptr<ICommand>> combos;
  std::set<JoystickButton> activeKeys;
};

class ManualModule : public ICommandModule {
 public:
  ManualModule();
  String handleCommand(String cmd) override;

 private:
  JoystickController joystick;

  String processCommand(const String& cmd);
  String handleQuery(const String& cmd);
  String handleParam(const String& key, const String& value);

  std::map<std::string, std::function<String()>> commands;
  std::map<std::string, std::function<String()>> queries;
  std::map<std::string, std::function<String(String)>> params;
};

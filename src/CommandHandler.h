#pragma once

#include <Arduino.h>
#include <MotorCommands.h>
#include <motors.h>

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

enum class Mode {
  Manual,
  LineFollow,
};

extern volatile Mode currentMode;

class CommandHandler {
 public:
  CommandHandler();
  String handle(String cmd);

 private:
  String handleSimple(const String& cmd);
  String handleParam(const String& key, const String& value);
  String handleJoystickBtn(const String& cmd);

  std::map<std::string, std::function<String()>> commands;
  std::map<std::string, std::function<String()>> queries;
  std::map<std::string, std::function<String(String)>> params;

  void keyDown(JoystickButton btn);
  void keyUp(JoystickButton btn);
  void updateMotors();

  std::map<std::vector<JoystickButton>, std::shared_ptr<ICommand>> combos;
  std::set<JoystickButton> activeKeys;
};

extern CommandHandler Commands;
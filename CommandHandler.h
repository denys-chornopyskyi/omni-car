#pragma once
#include <functional>
#include <Arduino.h>
#include <motors.h>
#include <map>
#include <memory>
#include <string>
#include <MotorCommands.h>
#include <set>

class CommandHandler {
  public:
    CommandHandler();
    String handle(String cmd);
  private:
    String handleSimple(const String& cmd);
    String handleParam(const String& key, const String& value);
    String handleJoystickBtn(const String& cmd);

    std::map<std::string, std::shared_ptr<ICommand>> commands;
    std::map<std::string, std::function<String()>> queries;
    std::map<std::string, std::function<String(String)>> params;

    void keyDown(JoystickButton btn);
    void keyUp(JoystickButton btn);
    void updateMotors();

    std::map<std::vector<JoystickButton>, std::shared_ptr<ICommand>> combos;
    std::set<JoystickButton> activeKeys;
};

extern CommandHandler Commands;
#pragma once
#include <Arduino.h>

class CommandHandler {
  public:
    String handle(String cmd);
  private:
    String handleSimple(String cmd);
    String handleParam(String key, String value);
    String handleJoystickBtn(String cmd);
};

extern CommandHandler commands;
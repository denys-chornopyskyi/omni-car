#pragma once

#include <functional>
#include <map>
#include <set>
#include <vector>

#include "MotionController.h"

class JoystickController {
 public:
  JoystickController(MotionController& motion);
  std::string handle(std::string cmd);
  enum class JoystickButton {
    Num1 = '1',
    Num2 = '2',
    Num3 = '3',
    Num4 = '4',
    Up = '5',
    Down = '6',
    Left = '7',
    Right = '8',
  };

 private:
  void keyDown(JoystickButton btn);
  void keyUp(JoystickButton btn);
  void updateMotors();

  MotionController* _motion = nullptr;

  std::map<std::vector<JoystickButton>, std::function<void()>> combos;
  std::set<JoystickButton> activeKeys;
};

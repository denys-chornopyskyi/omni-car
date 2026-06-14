#pragma once

#include <functional>
#include <map>
#include <set>
#include <vector>

#include "MotionController.h"
#include "BleProtocol.h"

class JoystickController {
 public:
  JoystickController(MotionController& motion);
  commandResult handle(const std::string& cmd);
  enum class JoystickButton {
    Center = '1',
    UpLeft = '2',
    Up = '3',
    UpRight = '4',
    Left = '5',
    Right = '6',
    DownLeft = '7',
    Down = '8',
    DownRight = '9'
  };
  void reset();

 private:
  void keyDown(JoystickButton btn);
  void keyUp(JoystickButton btn);
  void updateMotors();

  MotionController* _motion = nullptr;

  std::map<std::vector<JoystickButton>, std::function<void()>> combos;
  std::set<JoystickButton> activeKeys;
};

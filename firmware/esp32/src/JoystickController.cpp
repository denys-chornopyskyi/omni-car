#include "JoystickController.h"

#include "Response.h"

JoystickController::JoystickController(MotionController& motion) : _motion(&motion) {
  combos = {
      {{JoystickButton::Up}, [this]() { _motion->forward(); }},
      {{JoystickButton::Down}, [this]() { _motion->backward(); }},
      {{JoystickButton::Left}, [this]() { _motion->left(); }},
      {{JoystickButton::Right}, [this]() { _motion->right(); }},
      {{JoystickButton::UpLeft}, [this]() { _motion->forwardLeft(); }},
      {{JoystickButton::UpRight}, [this]() { _motion->forwardRight(); }},
      {{JoystickButton::DownLeft}, [this]() { _motion->backwardLeft(); }},
      {{JoystickButton::DownRight}, [this]() { _motion->backwardRight(); }},
      {{JoystickButton::Center, JoystickButton::Right}, [this]() { _motion->turningRight(); }},
      {{JoystickButton::Center, JoystickButton::Left}, [this]() { _motion->turningLeft(); }},
      {{JoystickButton::Up, JoystickButton::UpLeft}, [this]() { _motion->curvedTrajectoryLeft(); }},
      {{JoystickButton::Up, JoystickButton::UpRight}, [this]() { _motion->curvedTrajectoryRight(); }},
      {{JoystickButton::Center, JoystickButton::Right}, [this]() { _motion->lateralArc(); }},
  };

}

void JoystickController::updateMotors() {
  std::vector<JoystickButton> pressed(activeKeys.begin(), activeKeys.end());

  if (combos.count(pressed)) {
    combos[pressed]();
  } else {
    _motion->stopAll();
  }
}

void JoystickController::keyUp(JoystickButton btn) {
  activeKeys.erase(btn);
  updateMotors();
}

void JoystickController::keyDown(JoystickButton btn) {
  activeKeys.insert(btn);
  updateMotors();
}

using Button = JoystickController::JoystickButton;

std::string JoystickController::handle(std::string cmd) {
  JoystickButton btn = static_cast<JoystickButton>(cmd[2]);

  bool isPressed = cmd[3] == '1';

  isPressed ? keyDown(btn) : keyUp(btn);

  return std::string("");
}
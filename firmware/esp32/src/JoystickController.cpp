#include "JoystickController.h"

#include "Response.h"

JoystickController::JoystickController(MotionController& motion) : _motion(&motion) {
  combos = {
      {{JoystickButton::Up}, [this]() { _motion->forward(); }},
      {{JoystickButton::Down}, [this]() { _motion->backward(); }},
      {{JoystickButton::Left}, [this]() { _motion->left(); }},
      {{JoystickButton::Right}, [this]() { _motion->right(); }},
      {{JoystickButton::Up, JoystickButton::Left}, [this]() { _motion->forwardLeft(); }},
      {{JoystickButton::Up, JoystickButton::Right}, [this]() { _motion->forwardRight(); }},
      {{JoystickButton::Down, JoystickButton::Left}, [this]() { _motion->backwardLeft(); }},
      {{JoystickButton::Down, JoystickButton::Right}, [this]() { _motion->backwardRight(); }},
      {{JoystickButton::Num2, JoystickButton::Num4}, [this]() { _motion->turningRight(); }},
      {{JoystickButton::Num1, JoystickButton::Num3}, [this]() { _motion->turningLeft(); }},
      {{JoystickButton::Num1, JoystickButton::Up}, [this]() { _motion->curvedTrajectoryLeft(); }},
      {{JoystickButton::Num2, JoystickButton::Up}, [this]() { _motion->curvedTrajectoryRight(); }},
      {{JoystickButton::Num3, JoystickButton::Up}, [this]() { _motion->lateralArc(); }},
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
  JoystickButton btn = (JoystickButton)cmd[2];

  bool isPressed = cmd[3] == '1';

  isPressed ? keyDown(btn) : keyUp(btn);

  return Response::ok("handled");
}
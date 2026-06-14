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
      {{JoystickButton::UpLeft, JoystickButton::Up}, [this]() { _motion->curvedTrajectoryLeft(); }},
      {{JoystickButton::Up, JoystickButton::UpRight}, [this]() { _motion->curvedTrajectoryRight(); }},
      {{JoystickButton::Center, JoystickButton::Right}, [this]() { _motion->lateralArc(); }},
      {{JoystickButton::Down, JoystickButton::DownRight}, [this]() { _motion->curvedTrajectoryBackwardRight();}},
      {{JoystickButton::DownLeft, JoystickButton::Down}, [this]() { _motion->curvedTrajectoryBackwardLeft();}},
      {{JoystickButton::Up, JoystickButton::Left}, [this]() { _motion->arcLeft(_motion->radius);}}
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

void JoystickController::reset() {
  activeKeys.clear();
  _motion->stopAll();
}

commandResult JoystickController::handle(const std::string& cmd) {
  JoystickButton btn = static_cast<JoystickButton>(cmd[2]);

  bool isPressed = cmd[3] == '1';

  isPressed ? keyDown(btn) : keyUp(btn);

  return commandResult::ok();
}
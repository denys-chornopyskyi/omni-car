#include "MotionController.h"

#include <Arduino.h>

#include "Logger.h"

MotionController::MotionController(IMotor* a, IMotor* b, IMotor* c, IMotor* d)
    : _motorA(a), _motorB(b), _motorC(c), _motorD(d) {}

void MotionController::stopAll() {
  Logger::info("stop");
  _motorA->setSpeed(0);
  _motorB->setSpeed(0);
  _motorC->setSpeed(0);
  _motorD->setSpeed(0);
}

void MotionController::init() {
  _motorA->init();
  _motorB->init();
  _motorC->init();
  _motorD->init();

#ifndef DEBUGE_MODE
  pinMode(STBY1, OUTPUT);
  pinMode(STBY2, OUTPUT);

  digitalWrite(STBY1, HIGH);
  digitalWrite(STBY2, HIGH);
#endif

  stopAll();

  Logger::info("Motors initiated");
}

int16_t MotionController::applyK(int16_t speed, float k) {
  return constrain((int)(speed * k), -255, 255);
}

void MotionController::attachGuard(SafetyGuard& guard) {
  _guard = &guard;
}

void MotionController::forward() {
  if (_guard && _guard->isFrontBlocked()) {
    Logger::info("forward: emergency stop");
    return;
  }
  Logger::info("forward");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(applyK(baseSpeed, kB));
  _motorC->setSpeed(applyK(baseSpeed, kC));
  _motorD->setSpeed(applyK(baseSpeed, kD));
}

void MotionController::backward() {
  if (_guard && _guard->isBackBlocked()) {
    Logger::info("backward: emergency stop");
    return;
  }
  Logger::info("backward");
  _motorA->setSpeed(applyK(-baseSpeed, kA));
  _motorB->setSpeed(applyK(-baseSpeed, kB));
  _motorC->setSpeed(applyK(-baseSpeed, kC));
  _motorD->setSpeed(applyK(-baseSpeed, kD));
}

void MotionController::left() {
  if (_guard && _guard->isLeftBlocked()) {
    Logger::info("left: emergency stop");
    return;
  }
  Logger::info("left");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(applyK(-baseSpeed, kB));
  _motorC->setSpeed(applyK(-baseSpeed, kC));
  _motorD->setSpeed(applyK(baseSpeed, kD));
}

void MotionController::right() {
  if (_guard && _guard->isRightBlocked()) {
    Logger::info("right: emergency stop");
    return;
  }
  Logger::info("right");
  _motorA->setSpeed(applyK(-baseSpeed, kA));
  _motorB->setSpeed(applyK(baseSpeed, kB));
  _motorC->setSpeed(applyK(baseSpeed, kC));
  _motorD->setSpeed(applyK(-baseSpeed, kD));
}

void MotionController::forwardRight() {
  if ((_guard && _guard->isFrontBlocked()) || (_guard && _guard->isRightBlocked())) {
    Logger::info("forwardRight: emergency stop");
    return;
  }
  Logger::info("forwardRight");
  _motorA->setSpeed(0);
  _motorB->setSpeed(applyK(baseSpeed, kB));
  _motorC->setSpeed(applyK(baseSpeed, kC));
  _motorD->setSpeed(0);
}

void MotionController::forwardLeft() {
  if ((_guard && _guard->isFrontBlocked()) || (_guard && _guard->isLeftBlocked())) {
    Logger::info("forwardLeft: emergency stop");
    return;
  }
  Logger::info("forwardLeft");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(0);
  _motorC->setSpeed(0);
  _motorD->setSpeed(applyK(baseSpeed, kD));
}

void MotionController::backwardRight() {
  if (_guard && _guard->isBackBlocked() && (_guard && _guard->isRightBlocked())) {
    Logger::info("backwardRight: emergency stop");
    return;
  }
  Logger::info("backwardRight");
  _motorA->setSpeed(applyK(-baseSpeed, kA));
  _motorB->setSpeed(0);
  _motorC->setSpeed(0);
  _motorD->setSpeed(applyK(-baseSpeed, kD));
}

void MotionController::backwardLeft() {
  if (_guard && _guard->isBackBlocked() && (_guard && _guard->isLeftBlocked())) {
    Logger::info("backwardLeft: emergency stop");
    return;
  }
  Logger::info("backwardLeft");
  _motorA->setSpeed(0);
  _motorB->setSpeed(applyK(-baseSpeed, kB));
  _motorC->setSpeed(applyK(-baseSpeed, kC));
  _motorD->setSpeed(0);
}

void MotionController::turningRight() {
  Logger::info("turningRight");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(applyK(baseSpeed, kB));
  _motorC->setSpeed(applyK(-baseSpeed, kC));
  _motorD->setSpeed(applyK(-baseSpeed, kD));
}

void MotionController::turningLeft() {
  Logger::info("turningLeft");
  _motorA->setSpeed(applyK(-baseSpeed, kA));
  _motorB->setSpeed(applyK(-baseSpeed, kB));
  _motorC->setSpeed(applyK(baseSpeed, kC));
  _motorD->setSpeed(applyK(baseSpeed, kD));
}

void MotionController::lateralArc() {
  if (_guard && _guard->isRightBlocked()) {
    Logger::info("forward: emergency stop");
    return;
  }
  Logger::info("lateralArc");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(0);
  _motorC->setSpeed(applyK(-baseSpeed, kC));
  _motorD->setSpeed(0);
}

void MotionController::curvedTrajectoryRight() {
  if (_guard && _guard->isRightBlocked()) {
    Logger::info("forward: emergency stop");
    return;
  }
  Logger::info("curvedTrajectoryRight");
  _motorA->setSpeed(applyK(baseSpeed, curveK));
  _motorB->setSpeed(applyK(baseSpeed, curveK));
  _motorC->setSpeed(applyK(baseSpeed, kC));
  _motorD->setSpeed(applyK(baseSpeed, kD));
}

void MotionController::curvedTrajectoryRight(float cK) {
  if (_guard && _guard->isFrontBlocked()) {
    Logger::info("forward: emergency stop");
    return;
  }
  char buf[32];
  snprintf(buf, sizeof(buf), "%.2f", cK);
  Logger::info(buf);
  Logger::info("curvedTrajectoryRight");
  _motorA->setSpeed(applyK(baseSpeed, 1.0 - cK));
  _motorB->setSpeed(applyK(baseSpeed, 1.0 - cK));
  _motorC->setSpeed(applyK(baseSpeed, kC));
  _motorD->setSpeed(applyK(baseSpeed, kD));
}

void MotionController::curvedTrajectoryLeft() {
  if (_guard && _guard->isLeftBlocked()) {
    Logger::info("forward: emergency stop");
    return;
  }
  Logger::info("curvedTrajectoryLeft");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(applyK(baseSpeed, kB));
  _motorC->setSpeed(applyK(baseSpeed, curveK));
  _motorD->setSpeed(applyK(baseSpeed, curveK));
}

void MotionController::curvedTrajectoryLeft(float cK) {
  if (_guard && _guard->isLeftBlocked()) {
    Logger::info("forward: emergency stop");
    return;
  }
  static char buf[32];
  snprintf(buf, sizeof(buf), "%.2f", cK);
  Logger::info(buf);
  Logger::info("curvedTrajectoryLeft");
  _motorA->setSpeed(applyK(baseSpeed, kA));
  _motorB->setSpeed(applyK(baseSpeed, kB));
  _motorC->setSpeed(applyK(baseSpeed, 1.0 - cK));
  _motorD->setSpeed(applyK(baseSpeed, 1.0 - cK));
}

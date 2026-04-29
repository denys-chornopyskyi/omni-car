#include "ObjectAvoidance.h"

#include "Arduino.h"
#include "Logger.h"

bool ObjectAvoidance::_enabled = false;
uint8_t ObjectAvoidance::_threshold = 20;

void ObjectAvoidance::update() {
  updateDirection(data.distance[0], _threshold, &SafetyGuard::setFrontBlocked, &SafetyGuard::isFrontBlocked);
  updateDirection(data.distance[1], _threshold, &SafetyGuard::setRightBlocked, &SafetyGuard::isRightBlocked);
  updateDirection(data.distance[2], _threshold, &SafetyGuard::setBackBlocked, &SafetyGuard::isBackBlocked);
  updateDirection(data.distance[3], _threshold, &SafetyGuard::setLeftBlocked, &SafetyGuard::isLeftBlocked);
}

void ObjectAvoidance::updateDirection(uint8_t value, uint8_t threshold, void (SafetyGuard::*setter)(bool), bool (SafetyGuard::*getter)()) {
  if (value < threshold && !(_guard.*getter)()) {
    (_guard.*setter)(true);
    _motion.stopAll();
  } else if (value > threshold + 20 && (_guard.*getter)()) {
    (_guard.*setter)(false);
  }
}

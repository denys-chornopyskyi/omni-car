#include "ObjectAvoidance.h"

#include "Arduino.h"
#include "Logger.h"

bool ObjectAvoidance::_enabled = false;
uint8_t ObjectAvoidance::_threshold = 30;


void ObjectAvoidance::update() {
  if(!_enabled && lastEnabled) {
    _guard.setFrontBlocked(false);
    _guard.setBackBlocked(false);
    _guard.setLeftBlocked(false);
    _guard.setRightBlocked(false);
  }
  if(!this->_enabled) return;
  updateDirection(data.distance[0], _threshold, &SafetyGuard::setFrontBlocked, &SafetyGuard::isFrontBlocked, _lastDistance[0]);
  updateDirection(data.distance[1], _threshold, &SafetyGuard::setBackBlocked, &SafetyGuard::isBackBlocked, _lastDistance[1]);
  updateDirection(data.distance[2], _threshold, &SafetyGuard::setLeftBlocked, &SafetyGuard::isLeftBlocked, _lastDistance[2]);
  updateDirection(data.distance[3], _threshold, &SafetyGuard::setRightBlocked, &SafetyGuard::isRightBlocked, _lastDistance[3]);
  lastEnabled = _enabled;
}

void ObjectAvoidance::updateDirection(uint8_t value, uint8_t threshold, void (SafetyGuard::*setter)(bool), bool (SafetyGuard::*getter)(), uint8_t& lastValue) {
  if (value == 0) value = lastValue;
  else lastValue = value;
  
  if (value < threshold && !(_guard.*getter)()) {
    (_guard.*setter)(true);
    _motion.stopAll();
  } else if (value > threshold && (_guard.*getter)()) {
    (_guard.*setter)(false);
  }
}

#pragma once

#include "Arduino.h"
#include "MotionController.h"
#include "SafetyGuard.h"
#include "SensorStore.h"

class ObjectAvoidance {
 public:
  ObjectAvoidance(SafetyGuard& guard, MotionController& motion) : _guard(guard), _motion(motion) {};
  void update();

  static void setThreshold(uint8_t dist) { _threshold = constrain(dist, 1, 255); };  //
  static uint8_t getThreshold() { return _threshold; };
  static bool isEnabled() { return _enabled; };
  static void setEnabled(bool v) { _enabled = v; };

 private:
  void updateDirection(uint8_t value, uint8_t threshold, void (SafetyGuard::*setter)(bool), bool (SafetyGuard::*getter)());
  SensorData& data = SensorStore::getInstance().data;
  SafetyGuard& _guard;
  MotionController& _motion;
  static uint8_t _threshold;
  static bool _enabled;
};
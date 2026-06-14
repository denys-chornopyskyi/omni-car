#include "SafetyGuard.h"
#include "Arduino.h"

bool SafetyGuard::isFrontBlocked() {
  return _frontBlocked;
}
bool SafetyGuard::isBackBlocked() {
  return _backBlocked;
}
bool SafetyGuard::isLeftBlocked() {
  return _leftBlocked;
}
bool SafetyGuard::isRightBlocked() {
  return _rightBlocked;
}

void SafetyGuard::setFrontBlocked(bool blocked) {
  Serial.print("FrontBlocked: ");
  Serial.println(blocked ? "True" : "False");
  _frontBlocked = blocked;
}
void SafetyGuard::setBackBlocked(bool blocked) {
  Serial.print("BackBlocked: ");
  Serial.println(blocked ? "True" : "False");
  _backBlocked = blocked;
}
void SafetyGuard::setLeftBlocked(bool blocked) {
  Serial.print("LeftBlocked: ");
  Serial.println(blocked ? "True" : "False");
  _leftBlocked = blocked;
}
void SafetyGuard::setRightBlocked(bool blocked) {
  Serial.print("RightBlocked: ");
  Serial.println(blocked ? "True" : "False");
  _rightBlocked = blocked;
}
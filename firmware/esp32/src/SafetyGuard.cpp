#include "SafetyGuard.h"

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
  _frontBlocked = blocked;
}
void SafetyGuard::setBackBlocked(bool blocked) {
  _backBlocked = blocked;
}
void SafetyGuard::setLeftBlocked(bool blocked) {
  _leftBlocked = blocked;
}
void SafetyGuard::setRightBlocked(bool blocked) {
  _rightBlocked = blocked;
}
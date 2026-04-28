#pragma once

class SafetyGuard {
 public:
  bool isFrontBlocked();
  bool isBackBlocked();
  bool isRightBlocked();
  bool isLeftBlocked();

  void setFrontBlocked(bool blocked);
  void setLeftBlocked(bool blocked);
  void setBackBlocked(bool blocked);
  void setRightBlocked(bool blocked);

 private:
  bool _frontBlocked = false;
  bool _backBlocked = false;
  bool _rightBlocked = false;
  bool _leftBlocked = false;
};
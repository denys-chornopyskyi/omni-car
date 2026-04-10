#pragma once

enum class JoystickButton {
  Num1 = '1',
  Num2 = '2',
  Num3 = '3',
  Num4 = '4',
  Up = '5',
  Down = '6',
  Left = '7',
  Right = '8'
};

class ICommand {
 public:
  virtual void execute() = 0;
  virtual ~ICommand() = default;
};

class ForwardCommand : public ICommand {
 public:
  void execute() override;
};

class BackwardCommand : public ICommand {
 public:
  void execute() override;
};

class LeftCommand : public ICommand {
 public:
  void execute() override;
};

class RightCommand : public ICommand {
 public:
  void execute() override;
};

class ForwardLeftCommand : public ICommand {
 public:
  void execute() override;
};

class ForwardRightCommand : public ICommand {
 public:
  void execute() override;
};

class BackwardLeftCommand : public ICommand {
 public:
  void execute() override;
};

class BackwardRightCommand : public ICommand {
 public:
  void execute() override;
};

class TurningRightCommand : public ICommand {
 public:
  void execute() override;
};

class TurningLeftCommand : public ICommand {
 public:
  void execute() override;
};

class CurvedTrajectoryRightCommand : public ICommand {
 public:
  void execute() override;
};

class CurvedTrajectoryLeftCommand : public ICommand {
 public:
  void execute() override;
};

class LateralArcCommand : public ICommand {
 public:
  void execute() override;
};

class StopCommand : public ICommand {
 public:
  void execute() override;
};

class ManualCommand : public ICommand {
 public:
  void execute() override;
};

class LineFollowingCommand : public ICommand {
 public:
  void execute() override;
};

#include <MotorCommands.h>
#include <motors.h>

void ForwardCommand::execute() { forward(); }
void BackwardCommand::execute() { backward(); }
void LeftCommand::execute() { left(); }
void RightCommand::execute() { right(); }
void ForwardLeftCommand::execute() { forwardLeft(); }
void ForwardRightCommand::execute() { forwardRight(); }
void BackwardLeftCommand::execute() { backwardLeft(); }
void BackwardRightCommand::execute() { backwardRight(); }
void TurningRightCommand::execute() { turningRight(); }
void TurningLeftCommand::execute() { turningLeft(); }
void CurvedTrajectoryLeftCommand::execute() { curvedTrajectoryLeft(); }
void CurvedTrajectoryRightCommand::execute() { curvedTrajectoryRight(); }
void LateralArcCommand::execute() { lateralArc(); }
void StopCommand::execute() { stopAll(); }
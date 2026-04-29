#pragma once
#include "IMotor.h"
#include "SafetyGuard.h"

#define M1_IN1 26  // Мотор A вперёд
#define M1_IN2 25  // Мотор A назад
#define M2_IN1 5   // Мотор B вперёд
#define M2_IN2 18  // Мотор B назад
#define M3_IN1 14  // Мотор C вперёд
#define M3_IN2 27  // Мотор C назад
#define M4_IN1 16  // Мотор D вперёд
#define M4_IN2 17  // Мотор D назад
#define STBY1 4    // Enable чип 1 (моторы A+B)
#define STBY2 13   // Enable чип 2 (моторы C+D)

#define M1_CH1 0  // Мотор A вперёд
#define M1_CH2 1  // Мотор A назад
#define M2_CH1 2  // Мотор B вперёд
#define M2_CH2 3  // Мотор B назад
#define M3_CH1 4  // Мотор C вперёд
#define M3_CH2 5  // Мотор C назад
#define M4_CH1 6  // Мотор D вперёд
#define M4_CH2 7

class MotionController {
 public:
  MotionController(IMotor& a, IMotor& b, IMotor& c, IMotor& d) : _motorA(a), _motorB(b), _motorC(c), _motorD(d) {};
  void init();
  void stopAll();

  void forward();
  void backward();
  void left();
  void right();

  void forwardRight();
  void forwardLeft();
  void backwardRight();
  void backwardLeft();

  void turningRight();
  void turningLeft();
  void curvedTrajectoryRight();
  void curvedTrajectoryRight(float cK);
  void curvedTrajectoryLeft();
  void curvedTrajectoryLeft(float cK);
  void lateralArc();

  void attachGuard(SafetyGuard& guard);

  uint8_t baseSpeed = 200;
  float kA = 1.0;
  float kB = 1.0;
  float kC = 1.0;
  float kD = 1.0;
  float curveK = 0.3;
  IMotor& _motorA;
  IMotor& _motorB;
  IMotor& _motorC;
  IMotor& _motorD;

 private:
  int16_t applyK(int16_t speed, float k);
  SafetyGuard* _guard = nullptr;
};
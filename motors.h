#pragma once

#define M1_IN1  25  // Мотор A вперёд
#define M1_IN2  26  // Мотор A назад
#define M2_IN1  27  // Мотор B вперёд
#define M2_IN2  16  // Мотор B назад
#define M3_IN1  17  // Мотор C вперёд
#define M3_IN2  18  // Мотор C назад
#define M4_IN1  32  // Мотор D вперёд
#define M4_IN2  33  // Мотор D назад
#define DRIVER1_ON  4  // Enable чип 1 (моторы A+B)
#define DRIVER2_ON 13  // Enable чип 2 (моторы C+D)

extern int baseSpeed;

extern float kA;
extern float kB;
extern float kC;
extern float kD;

void motorsInit();
void motorA(int speed);
void motorB(int speed);
void motorC(int speed);
void motorD(int speed);

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
void curvedTrajectoryLeft();
void lateralArc();
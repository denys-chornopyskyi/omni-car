#ifndef MOTORS_H  // если MOTORS_H не определён — читай дальше
#define MOTORS_H

#define M1_IN1 25  // Мотор A вперёд
#define M1_IN2 26  // Мотор A назад
#define M2_IN1 27  // Мотор B вперёд
#define M2_IN2 16  // Мотор B назад
#define M3_IN1 17  // Мотор C вперёд
#define M3_IN2 18  // Мотор C назад
#define M4_IN1 32  // Мотор D вперёд
#define M4_IN2 33  // Мотор D назад
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

extern int baseSpeed;

extern float kA;
extern float kB;
extern float kC;
extern float kD;
extern float curveK;

class Motor {
 public:
  Motor(int pinIn1, int pinIn2, int ch1, int ch2);
  void init();
  void setSpeed(int speed);
  void stop();

 private:
  int _in1;
  int _in2;
  int _ch1;
  int _ch2;
};

extern Motor motorA;
extern Motor motorB;
extern Motor motorC;
extern Motor motorD;

void motorsInit();

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
void curvedTrajectoryRight(float cK = curveK);
void curvedTrajectoryLeft(float cK = curveK);
void lateralArc();

#endif
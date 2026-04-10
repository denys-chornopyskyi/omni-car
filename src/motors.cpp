#include "motors.h"

#include <Arduino.h>

int baseSpeed = 200;

float kA = 1.0;
float kB = 1.0;
float kC = 1.0;
float kD = 1.0;

float curveK = 0.3;

Motor::Motor(int pinIn1, int pinIn2, int ch1, int ch2) {
  _in1 = pinIn1;
  _in2 = pinIn2;
  _ch1 = ch1;
  _ch2 = ch2;
}

void Motor::init() {
  ledcSetup(_ch1, 1000, 8);
  ledcAttachPin(_in1, _ch1);
  ledcSetup(_ch2, 1000, 8);
  ledcAttachPin(_in2, _ch2);
}

void Motor::setSpeed(int speed) {
  speed = constrain(speed, -255, 255);

  if (speed > 0) {
    ledcWrite(_ch1, speed);
    ledcWrite(_ch2, 0);
  } else if (speed < 0) {
    ledcWrite(_ch1, 0);
    ledcWrite(_ch2, -speed);
  } else {
    ledcWrite(_ch1, 0);
    ledcWrite(_ch2, 0);
  }
}

void Motor::stop() { setSpeed(0); }

Motor motorA(M1_IN1, M1_IN2, M1_CH1, M1_CH2);
Motor motorB(M2_IN1, M2_IN2, M2_CH1, M2_CH2);
Motor motorC(M3_IN1, M3_IN2, M3_CH1, M3_CH2);
Motor motorD(M4_IN1, M4_IN2, M4_CH1, M4_CH2);

int applyK(int speed, float k) {
  return constrain((int)(speed * k), -255, 255);
}

void motorsInit() {
  motorA.init();
  motorB.init();
  motorC.init();
  motorD.init();

  pinMode(STBY1, OUTPUT);
  pinMode(STBY2, OUTPUT);

  digitalWrite(STBY1, HIGH);
  digitalWrite(STBY2, HIGH);

  stopAll();
}

void stopAll() {
  motorA.setSpeed(0);
  motorB.setSpeed(0);
  motorC.setSpeed(0);
  motorD.setSpeed(0);
}

void forward() {
  motorA.setSpeed(applyK(baseSpeed, kA));
  motorB.setSpeed(applyK(baseSpeed, kB));
  motorC.setSpeed(applyK(baseSpeed, kC));
  motorD.setSpeed(applyK(baseSpeed, kD));
}

void backward() {
  motorA.setSpeed(applyK(-baseSpeed, kA));
  motorB.setSpeed(applyK(-baseSpeed, kB));
  motorC.setSpeed(applyK(-baseSpeed, kC));
  motorD.setSpeed(applyK(-baseSpeed, kD));
}

void left() {
  motorA.setSpeed(applyK(baseSpeed, kA));
  motorB.setSpeed(applyK(-baseSpeed, kB));
  motorC.setSpeed(applyK(-baseSpeed, kC));
  motorD.setSpeed(applyK(baseSpeed, kD));
}

void right() {
  motorA.setSpeed(applyK(-baseSpeed, kA));
  motorB.setSpeed(applyK(baseSpeed, kB));
  motorC.setSpeed(applyK(baseSpeed, kC));
  motorD.setSpeed(applyK(-baseSpeed, kD));
}

void forwardRight() {
  motorA.stop();
  motorB.setSpeed(applyK(baseSpeed, kB));
  motorC.setSpeed(applyK(baseSpeed, kC));
  motorD.stop();
}

void forwardLeft() {
  motorA.setSpeed(applyK(baseSpeed, kA));
  motorB.stop();
  motorC.stop();
  motorD.setSpeed(applyK(baseSpeed, kD));
}

void backwardRight() {
  motorA.setSpeed(applyK(-baseSpeed, kA));
  motorB.stop();
  motorC.stop();
  motorD.setSpeed(applyK(-baseSpeed, kD));
}

void backwardLeft() {
  motorA.stop();
  motorB.setSpeed(applyK(-baseSpeed, kB));
  motorC.setSpeed(applyK(-baseSpeed, kC));
  motorD.stop();
}

void turningRight() {
  motorA.setSpeed(applyK(baseSpeed, kA));
  motorB.setSpeed(applyK(baseSpeed, kB));
  motorC.setSpeed(applyK(-baseSpeed, kC));
  motorD.setSpeed(applyK(-baseSpeed, kD));
}

void turningLeft() {
  motorA.setSpeed(applyK(-baseSpeed, kA));
  motorB.setSpeed(applyK(-baseSpeed, kB));
  motorC.setSpeed(applyK(baseSpeed, kC));
  motorD.setSpeed(applyK(baseSpeed, kD));
}

void lateralArc() {
  motorA.setSpeed(applyK(baseSpeed, kA));
  motorB.stop();
  motorC.setSpeed(applyK(-baseSpeed, kC));
  motorD.stop();
}

void curvedTrajectoryRight() {
  motorA.setSpeed(applyK(baseSpeed, curveK));
  motorB.setSpeed(applyK(baseSpeed, curveK));
  motorC.setSpeed(applyK(baseSpeed, kC));
  motorD.setSpeed(applyK(baseSpeed, kD));
}

void curvedTrajectoryLeft() {
  motorA.setSpeed(applyK(baseSpeed, kA));
  motorB.setSpeed(applyK(baseSpeed, kB));
  motorC.setSpeed(applyK(baseSpeed, curveK));
  motorD.setSpeed(applyK(baseSpeed, curveK));
}

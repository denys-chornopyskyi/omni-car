#include <Arduino.h>
#include <motors.h>

int baseSpeed = 200;

float kA = 1.0;
float kB = 1.0;
float kC = 1.0;
float kD = 1.0;

int applyK(int speed, float k) {
  int result = (int)(speed * k);
  if (result > 255) result = 255;
  if (result < -255 ) result - -255;
  return result;
}


void motorsInit(){
  ledcAttach(M1_IN1, 1000, 8);
  ledcAttach(M1_IN2, 1000, 8);
  ledcAttach(M2_IN1, 1000, 8);
  ledcAttach(M2_IN2, 1000, 8);
  ledcAttach(M3_IN1, 1000, 8);
  ledcAttach(M3_IN2, 1000, 8);
  ledcAttach(M4_IN1, 1000, 8);
  ledcAttach(M4_IN2, 1000, 8);

  pinMode(DRIVER1_ON, OUTPUT);
  pinMode(DRIVER2_ON, OUTPUT);

  digitalWrite(DRIVER1_ON, HIGH);
  digitalWrite(DRIVER2_ON, HIGH);

  stopAll();

  Serial.println("Моторы готовы!");
}

void motorA(int speed) {
  if (speed > 0) {
    ledcWrite(M1_IN1, speed);
    ledcWrite(M1_IN2, 0);
  } else if (speed < 0) {
    ledcWrite(M1_IN1, 0);
    ledcWrite(M1_IN2, -speed);
  } else {
    ledcWrite(M1_IN1, 0);
    ledcWrite(M1_IN2, 0);
  }
}

void motorB(int speed) {
  if (speed > 0) {
    ledcWrite(M2_IN1, speed);
    ledcWrite(M2_IN2, 0);
  } else if (speed < 0) {
    ledcWrite(M2_IN1, 0);
    ledcWrite(M2_IN2, -speed);
  } else {
    ledcWrite(M2_IN1, 0);
    ledcWrite(M2_IN2, 0);
  }
}

void motorC(int speed) {
  if (speed > 0) {
    ledcWrite(M3_IN1, speed);
    ledcWrite(M3_IN2, 0);
  } else if (speed < 0) {
    ledcWrite(M3_IN1, 0);
    ledcWrite(M3_IN2, -speed);
  } else {
    ledcWrite(M3_IN1, 0);
    ledcWrite(M3_IN2, 0);
  }
}

void motorD(int speed) {
  if (speed > 0) {
    ledcWrite(M4_IN1, speed);
    ledcWrite(M4_IN2, 0);
  } else if (speed < 0) {
    ledcWrite(M4_IN1, 0);
    ledcWrite(M4_IN2, -speed);
  } else {
    ledcWrite(M4_IN1, 0);
    ledcWrite(M4_IN2, 0);
  }
}

void stopAll() {
  motorA(0);
  motorB(0);
  motorC(0);
  motorD(0);
}

void forward(){
  motorA(applyK(baseSpeed, kA));
  motorB(applyK(baseSpeed, kB));
  motorC(applyK(baseSpeed, kC));
  motorD(applyK(baseSpeed, kD));
}

void backward(){
  motorA(applyK(-baseSpeed, kA));
  motorB(applyK(-baseSpeed, kB));
  motorC(applyK(-baseSpeed, kC));
  motorD(applyK(-baseSpeed, kD));
}

void left(){
  motorA(applyK(baseSpeed, kA));
  motorB(applyK(-baseSpeed, kB));
  motorC(applyK(-baseSpeed, kC));
  motorD(applyK(baseSpeed, kD));
}

void right(){
  motorA(applyK(-baseSpeed, kA));
  motorB(applyK(baseSpeed, kB));
  motorC(applyK(baseSpeed, kC));
  motorD(applyK(-baseSpeed, kD));
}

void forwardRight(){
  motorA(0);
  motorB(applyK(baseSpeed, kB));
  motorC(applyK(baseSpeed, kC));
  motorD(0);
}

void forwardLeft(){
  motorA(applyK(baseSpeed, kA));
  motorB(0);
  motorC(0);
  motorD(applyK(baseSpeed, kD));
}

void backwardRight(){
  motorA(applyK(-baseSpeed, kA));
  motorB(0);
  motorC(0);
  motorD(applyK(-baseSpeed, kD));
}

void backwardLeft(){
  motorA(0);
  motorB(applyK(-baseSpeed, kB));
  motorC(applyK(-baseSpeed, kC));
  motorD(0);
}

void turningRight(){
  motorA(applyK(baseSpeed, kA));
  motorB(applyK(baseSpeed, kB));
  motorC(applyK(-baseSpeed, kC));
  motorD(applyK(-baseSpeed, kD));
}

void turningLeft(){
  motorA(applyK(-baseSpeed, kA));
  motorB(applyK(-baseSpeed, kB));
  motorC(applyK(baseSpeed, kC));
  motorD(applyK(baseSpeed, kD));
}

void lateralArc(){
  motorA(0);
  motorB(applyK(baseSpeed, kB));
  motorC(0);
  motorD(applyK(-baseSpeed, kD));
}

void curvedTrajectoryRight(){
  motorA(applyK(baseSpeed, kA));
  motorB(applyK(baseSpeed, kB));
  motorC(applyK(baseSpeed, kC - 0.2));
  motorD(applyK(baseSpeed, kD - 0.2));
}

void curvedTrajectoryLeft(){
  motorA(applyK(baseSpeed, kA - 0.2));
  motorB(applyK(baseSpeed, kB - 0.2));
  motorC(applyK(baseSpeed, kC));
  motorD(applyK(baseSpeed, kD));
}







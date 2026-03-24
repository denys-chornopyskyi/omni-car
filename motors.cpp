#include <Arduino.h>
#include <motors.h>
#include <calibration.h>

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


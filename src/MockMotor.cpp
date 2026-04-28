#include "MockMotor.h"

#include "Arduino.h"

MockMotor::MockMotor(const char* name) : _name(name) {}

void MockMotor::init() {
  Serial.print("[MOCK] ");
  Serial.print(_name);
  Serial.println(" init");
}

void MockMotor::setSpeed(int16_t speed) {
  Serial.print("[MOCK] ");
  Serial.print(_name);
  Serial.print(" speed =");
  Serial.println(speed);
}

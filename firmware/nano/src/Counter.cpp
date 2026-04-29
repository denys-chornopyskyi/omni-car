#include "Counter.h"

#include "Arduino.h"

void Counter::increment() {
  _count += 1;
}

void Counter::printToSerial(const char* msg, unsigned int ms) {
  if (millis() - prevTime > ms) {
    Serial.println(msg + String(_count / (ms / 1000)));
    prevTime = millis();
    _count = 0;
  }
}
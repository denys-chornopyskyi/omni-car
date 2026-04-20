#include "LineFollower.h"

LineFollower* lineFollower = nullptr;

LineFollower::LineFollower() : mySerial(2) {
  mySerial.begin(9600, SERIAL_8N1, RX, TX);
}

String LineFollower::handleCommand(String cmd) {
  return "unsupported";
}

LineFollower::~LineFollower() { stopAll(); }

void LineFollower::receiveSensorData() {
  while (mySerial.available() >= 6) {
    if (mySerial.peek() == 0xFF) {
      mySerial.read();
      for (uint8_t i = 0; i < 5; i++) {
        _sensorValues[i] = mySerial.read();
      }
    }
    mySerial.read();
  }
}

void LineFollower::calibrate() {
}

float LineFollower::calcPosition() {
  uint8_t* v = _sensorValues;
  int8_t sum = v[0] + v[1] + v[2] + v[3] + v[4];

  return (-2 * v[0] + -1 * v[1] + 0 * v[2] + 1 * v[3] + 2 * v[4]) / sum;
}

void LineFollower::update() {
  receiveSensorData();
}
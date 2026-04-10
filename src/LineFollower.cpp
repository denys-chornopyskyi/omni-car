#include "LineFollower.h"

LineFollower* lineFollower = nullptr;

LineFollower::LineFollower() : mySerial(2) {
  mySerial.begin(9600, SERIAL_8N1, RX, TX);
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

void LineFollower::update() {
  receiveSensorData();
}
#include "CommandHandler.h"
#include "LineFollower.h"
#include "ble.h"
#include "motors.h"

void setup() {
  Serial.begin(115200);
  motorsInit();
  bleInit();
}

void loop() {
  switch (currentMode) {
    case Mode::Manual:
      break;
    case Mode::LineFollow:
      lineFollower->update();
      break;
  }
}
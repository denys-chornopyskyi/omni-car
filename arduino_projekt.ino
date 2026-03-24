#include "motors.h"
#include "calibration.h"
#include "ble.h"
#include "commands.h"

void setup() {
  Serial.begin(115200);
  motorsInit();
  bleInit();
  Serial.println("Готово!");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    commands.handle(cmd)
  }
  bleLoop();
}
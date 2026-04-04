#include "motors.h"
#include "ble.h"
#include "CommandHandler.h"

void setup() {
  Serial.begin(115200);
  motorsInit();
  bleInit();
  Serial.println("Готово!");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    Commands.handle(cmd);
  }
  bleLoop();
}
#include "ModuleHandler.h"
#include "ble.h"
#include "motors.h"
#include "queue.h"

ModuleHandler Module;

void setup() {
  Serial.begin(115200);
  motorsInit();
  queueInit();
  bleInit();
}

void loop() {
  String cmd;
  if (queueReceive(cmd)) {
    String response = Module.handleCommand(cmd);
    bleSend(response);
  }

  Module.update();
}
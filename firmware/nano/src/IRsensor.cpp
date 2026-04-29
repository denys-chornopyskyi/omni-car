#include "IRsensor.h"

#include <Arduino.h>

#include "utils.h"

IRsensor::IRsensor(Protocol& protocol)
    : counter(), pcf8574(0x20), _protocol(protocol) {};

void IRsensor::begin() {
  if (!pcf8574.begin()) {
    Serial.println("Couldn't find PCF8574");
  }

  for (int i = 0; i < 5; i++) {
    pcf8574.pinMode(P0 + i, INPUT);
  }
}

void IRsensor::update() {
  // counter.printToSerial("IRsensorCount: ", 5000);
  readSensors();
  _protocol.sendIR(_sensorValues, 5);
    // printToSerial();
  // counter.increment();
}

void IRsensor::readSensors() {
  for (int i = 0; i < 5; i++) {
    _sensorValues[i] = pcf8574.digitalRead(P0 + i);
  }
}

void IRsensor::printToSerial() {
  String sendingValues = "IR: ";

  for (int i = 0; i < 5; i++) {
    sendingValues += String(_sensorValues[i]);
  }

  Serial.println(sendingValues);
}
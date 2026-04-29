#include "UltrasonicSensor.h"

#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin, msgType type, const char* name)
    : _trigPin(trigPin), _echoPin(echoPin), counter(), _type(type), _name(name) {}

void UltrasonicSensor::begin() {
  pinMode(_echoPin, INPUT);
  pinMode(_trigPin, OUTPUT);

  digitalWrite(_trigPin, LOW);
}

uint8_t UltrasonicSensor::readDistanceCM() {
  // String msg = String(getName()) + ": ";
  // counter.printToSerial(msg.c_str(), 5000);
  // TRIG pulse
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  long duration = pulseIn(_echoPin, HIGH, 10000);

  float floatDistance = duration * 0.0343 / 2.0;
  uint8_t distance(floatDistance);
  // counter.increment();
  if (distance > 255) return 255;
  return distance;
}

const char* UltrasonicSensor::getName() {
  return _name;
}

msgType UltrasonicSensor::getType() {
  return _type;
}

void UltrasonicSensor::printToSerial(uint8_t dist) {
  Serial.println(String(getName()) + ": " + dist);
}

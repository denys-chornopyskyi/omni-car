#include <Arduino.h>

#include "Config.h"
#include "IRsensor.h"
#include "Protocol.h"
#include "UltrasonicSensor.h"
#include "UltrasonicSensorsManager.h"

SoftwareSerial espSerial(Config::ESP_RX, Config::ESP_TX);
Protocol protocol(espSerial);

IRsensor IRsensors(protocol);

UltrasonicSensor sensors[6] = {
    {Config::TRIG_PIN, Config::ECHO_PINS[0], msgType::FORWARD_DIST, Config::SENSOR_NAMES[0]},
    {Config::TRIG_PIN, Config::ECHO_PINS[1], msgType::BACKWARD_DIST, Config::SENSOR_NAMES[1]},
    {Config::TRIG_PIN, Config::ECHO_PINS[2], msgType::LEFT_DIST, Config::SENSOR_NAMES[2]},
    {Config::TRIG_PIN, Config::ECHO_PINS[3], msgType::RIGHT_DIST, Config::SENSOR_NAMES[3]},
    {Config::TRIG_PIN, Config::ECHO_PINS[4], msgType::FORWARD_LEFT_DIST, Config::SENSOR_NAMES[4]},
    {Config::TRIG_PIN, Config::ECHO_PINS[5], msgType::FORWARD_RIGHT_DIST, Config::SENSOR_NAMES[5]},
};

UltrasonicSensorsManager manager(sensors, 6, protocol);

void setup() {
  IRsensors.begin();
  Serial.begin(9600);
  espSerial.begin(9600);
  manager.begin();
}

void loop() {
  IRsensors.update();
  manager.update();
  // Serial.println("------------------------------");
  // delay(1000);
}

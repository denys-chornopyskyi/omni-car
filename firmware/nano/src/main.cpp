#include <Arduino.h>

#include "Config.h"
#include "IRsensor.h"
#include "Protocol.h"
#include "UltrasonicSensor.h"
#include "UltrasonicSensorsManager.h"

SoftwareSerial espSerial(Config::ESP_RX, Config::ESP_TX);
Protocol protocol(espSerial);

IRsensor IRsensors(protocol);

UltrasonicSensor sensors[4] = {
    {Config::TRIG_PIN, Config::ECHO_PINS[0], msgType::DIST_1, Config::SENSOR_NAMES[0]},
    {Config::TRIG_PIN, Config::ECHO_PINS[1], msgType::DIST_2, Config::SENSOR_NAMES[1]},
    {Config::TRIG_PIN, Config::ECHO_PINS[2], msgType::DIST_3, Config::SENSOR_NAMES[2]},
    {Config::TRIG_PIN, Config::ECHO_PINS[3], msgType::DIST_4, Config::SENSOR_NAMES[3]},
};

UltrasonicSensorsManager manager(sensors, 4, protocol);

void setup() {
  IRsensors.begin();
  Serial.begin(9600);
  espSerial.begin(9600);
  manager.begin();
}

void loop() {
  IRsensors.update();
  manager.update();
  Serial.println("------------------------------");
  delay(1000);
}

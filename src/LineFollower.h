#include <map>
#include <memory>

#include "Arduino.h"
#include "ICommandModule.h"
#include "MotorCommands.h"
#include "motors.h"
#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H

#define RX 21
#define TX 22

class LineFollower : public ICommandModule {
 public:
  LineFollower();
  ~LineFollower();
  String handleCommand(String cmd) override;
  void update() override;

 private:
  HardwareSerial mySerial;
  uint8_t _sensorValues[5];
  float _curveK;

  std::map<std::string, std::shared_ptr<ICommand>> commands;

  void receiveSensorData();
  void calibrate();
  float calcPosition();
};

extern LineFollower* lineFollower;

#endif
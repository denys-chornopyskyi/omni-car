#pragma once

#include <map>
#include <memory>

#include "Arduino.h"
#include "IModule.h"
#include "MotionController.h"

class LineFollower : public IModule {
 public:
  void begin();
  LineFollower(MotionController& motion);
  ~LineFollower();
  std::string handleCommand(std::string name, std::string value) override;
  void update() override;

 private:
  float _curveK;
  struct Range {
    float start;
    float end;
  };
  Range _curveRange;
  MotionController* _motion = nullptr;

  std::map<std::string, std::function<std::string(std::string)>> _commands;

  void receiveSensorData();
  void calibrate();
  float calcPosition();
  float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
};

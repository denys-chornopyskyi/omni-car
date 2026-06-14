#pragma once

#include <map>
#include <memory>

#include "Arduino.h"
#include "IModule.h"
#include "MotionController.h"
#include "BleProtocol.h"

class LineFollower : public IModule {
 public:
  void begin();
  LineFollower(MotionController& motion);
  ~LineFollower();
  commandResult handleCommand(std::string& name, std::string& value) override;
  void update() override;
  uint8_t getId() override {
    return 2;
  }
  bool isEnabled() { return _enabled; }
  void setEnabled(bool v) { _enabled = v; }
 
 private:
  bool _enabled = false;
  bool _lastEnabled = false;
  float _curveK;
  struct Range {
    float start;
    float end;
  };
  Range _curveRange;
  MotionController* _motion = nullptr;

  std::map<std::string, std::function<commandResult(std::string)>> _commands;

  void receiveSensorData();
  void calibrate();
  float calcPosition();
  float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
  
};

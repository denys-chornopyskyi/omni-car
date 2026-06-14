#include "LineFollower.h"

#include "Logger.h"
#include "ManualModule.h"
#include "Response.h"
#include "SensorStore.h"
#include "ble.h"

LineFollower::LineFollower(MotionController& motion) : _motion(&motion) {
  _curveRange.start = 0;
  _curveRange.end = 0.7;
  Logger::info("Line iniated");
}

void LineFollower::begin() {
  _commands["crs"] = [this](const std::string& v) {_curveRange.start = atof(v.c_str()); return commandResult::ok();};
  _commands["crs?"] = [this](const std::string& v) {return commandResult::okFloat(_curveRange.start);};
  _commands["cre?"] = [this](const std::string& v) {return commandResult::okFloat(_curveRange.end);};
  _commands["cre"] = [this](const std::string& v) {_curveRange.end = atof(v.c_str()); return commandResult::ok();};
  _commands["sl"] = [this](const std::string& v) {this->setEnabled(true); return commandResult::ok();};
  _commands["el"] = [this](const std::string& v) {this->setEnabled(false); return commandResult::ok();};
  _commands["sIRs"] = [this](const std::string& v) {flags.IRStream = true; return commandResult::ok();};
  _commands["eIRs"]= [this](const std::string& v) {flags.IRStream = false; return commandResult::ok();};
  _commands["stop"]= [this](const std::string& v) {_motion->stopAll(); setEnabled(false); return commandResult::ok();};
}

commandResult LineFollower::handleCommand(std::string& name, std::string& value) {
  if (_commands.count(name)) {
    return _commands[name](value);
  }
  return commandResult::err(ErrorType::UnknownParam);
}

LineFollower::~LineFollower() { _motion->stopAll(); }

void LineFollower::calibrate() {
  float correction;
  do {
    receiveSensorData();
    correction = calcPosition();

    if (!correction) break;

    if (correction > 0) {
      _motion->turningRight();
    } else {
      _motion->turningLeft();
    }

  } while (correction);
  _motion->stopAll();
}

float LineFollower::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float LineFollower::calcPosition() {
  using IRArray = uint8_t[5];
  IRArray& ir = SensorStore::getInstance().data.ir;
  uint8_t inv[5];
  for (int i = 0; i < 5; i++) inv[i] = 1 - ir[i];

  int8_t sum = inv[0] + inv[1] + inv[2] + inv[3] + inv[4];

  if (sum == 0) return 0;

  return (2 * ir[0] + 1 * ir[1] + 0 * ir[2] + -1 * ir[3] + -2 * ir[4]) / (float)sum;
}

void LineFollower::update() {
  if (!_enabled && _lastEnabled) {
    _motion->stopAll();
    _lastEnabled = _enabled;
  }
  if (!_enabled) return;
  auto convertedValue = calcPosition();
  Serial.print("ConvertedValue: ");
  Serial.println(convertedValue);
  // Logger::info(std::to_string(convertedValue));
  auto _curveK = mapFloat(abs(convertedValue), 0, 2, _curveRange.start, _curveRange.end);
  Serial.print("curveK: ");
  Serial.println(_curveK);
  if (convertedValue == 0) {
    _motion->forward();
  } else if (convertedValue > 0) {
    _motion->turningRight();
  } else {
    _motion->turningLeft();
  }
  _lastEnabled = _enabled;
}
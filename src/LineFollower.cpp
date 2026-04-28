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
  _commands["crs?"] = [this](std::string v) {
    return Response::ok("curveRangeStart=" + std::to_string(_curveRange.start));
  };
  _commands["crs"] = [this](std::string v) {
    _curveRange.start = atof(v.c_str());
    return Response::ok("curveRangeStart=" + std::to_string(_curveRange.start));
  };
  _commands["cre?"] = [this](std::string v) {
    return Response::ok("curveRangeEnd=" + std::to_string(_curveRange.end));
  };
  _commands["cre"] = [this](std::string v) {
    _curveRange.end = atof(v.c_str());
    return Response::ok("curveRangeEnd=" + std::to_string(_curveRange.end));
  };
}

std::string LineFollower::handleCommand(std::string name, std::string value) {
  if (_commands.count(name)) {
    return _commands[name](value);
  }

  return Response::err(name);
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
  int8_t sum = ir[0] + ir[1] + ir[2] + ir[3] + ir[4];

  if (sum == 0) return 0;

  return (-2 * ir[0] + -1 * ir[1] + 0 * ir[2] + 1 * ir[3] + 2 * ir[4]) / (float)sum;
}

void LineFollower::update() {
  auto convertedValue = calcPosition();
  Logger::info(std::to_string(convertedValue));
  auto _curveK = mapFloat(abs(convertedValue), 0, 2, _curveRange.start, _curveRange.end);
  if (convertedValue == 0) {
    _motion->forward();
  } else if (convertedValue > 0) {
    _motion->curvedTrajectoryRight(_curveK);
  } else {
    _motion->curvedTrajectoryLeft(_curveK);
  }
}
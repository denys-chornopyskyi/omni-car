#include "ObjectFollower.h"

bool ObjectFollower::_enabled = false;
bool ObjectFollower::_lastEnabled = false;
uint8_t ObjectFollower::_minDist = 10;
uint8_t ObjectFollower::_maxDist = 22;


void ObjectFollower::begin() {
   _commands["startFollowing"] = [this](const std::string& v) {this->setEnabled(true); return commandResult::ok();};
   _commands["stopFollowing"] = [this](const std::string& v) {this->setEnabled(false); return commandResult::ok();};
   _commands["minDist"] = [this](const std::string& v) {this->setMinDist(atoi(v.c_str())); return commandResult::ok();};
   _commands["minDist?"] = [this](const std::string& v) {return commandResult::okInt(_minDist);};
   _commands["maxDist"] = [this](const std::string& v) {this->setMaxDist(atoi(v.c_str())); return commandResult::ok();};
   _commands["maxDist?"] = [this](const std::string& v) {return commandResult::okInt(_maxDist);};
   _commands["stop"] = [this](const std::string& v) {_motion.stopAll(); setEnabled(false); return commandResult::ok();};
}

commandResult ObjectFollower::handleCommand(std::string& name, std::string& value) {
  if (_commands.count(name)) {
    return _commands[name](value);
  }
  return commandResult::err(ErrorType::UnknownParam);
}

void ObjectFollower::update() {
  if (_lastEnabled && !_enabled) {
    _motion.stopAll();
    _lastEnabled = _enabled;
  }

  if (!_enabled) return;

  SensorData& data = SensorStore::getInstance().data;

  uint8_t front = data.distance[0];
  uint8_t left = data.distance[4];
  uint8_t right = data.distance[5];

  Serial.print("Front: ");
  Serial.println(front);
  Serial.print("Left: ");
  Serial.println(left);
  Serial.print("Right: ");
  Serial.println(right);
  Serial.println("---------------");
  


  bool seesFront = front < _maxDist;
  bool seesLeft  = left  < _maxDist;
  bool seesRight = right < _maxDist;


  if (!seesFront && !seesLeft && !seesRight) {
    _motion.stopAll();
    return;
  }

  if (!seesFront && seesLeft)  { _motion.turningLeft();  return; }
  if (!seesFront && seesRight) { _motion.turningRight(); return; }

  if (front < _minDist) {
    _motion.backward();
    return;
  }

  if (seesFront && seesLeft)  { _motion.curvedTrajectoryLeft();  return; }
  if (seesFront && seesRight) { _motion.curvedTrajectoryRight(); return; }

  _motion.forward();

  _lastEnabled = _enabled;
}
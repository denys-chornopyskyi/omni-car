#include "IModule.h"
#include "MotionController.h"
#include "SensorStore.h"
#include <map>

class ObjectFollower : public IModule {
 public:
  ObjectFollower(MotionController& motion) : _motion(motion) {};
  void begin();
  void update() override;
  commandResult handleCommand(std::string& name, std::string& value) override;
  uint8_t getId() override { return 3; }

  static bool isEnabled() { return _enabled; }
  static void setEnabled(bool v) { _enabled = v; }
  static void setMinDist(uint8_t d) { _minDist = d; }
  static void setMaxDist(uint8_t d) { _maxDist = d; }

 private:
  MotionController& _motion;

  std::map<std::string, std::function<commandResult(std::string)>> _commands;

  static bool _enabled;
  static uint8_t _minDist;
  static uint8_t _maxDist;   
  static bool _lastEnabled;
};
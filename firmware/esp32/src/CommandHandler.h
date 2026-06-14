#pragma once

#include <functional>
#include <map>
#include <string>

#include "IModule.h"
#include "MotionController.h"
#include "BleProtocol.h"

class CommandHandler {
 public:
 CommandHandler(MotionController& motion) : _motion(motion) {};
 commandResult handle(const std::string& cmd);
 void begin(std::initializer_list<std::pair<const char*, IModule*>> modules);
 void setModule(IModule* module);
 void update();
 commandResult dispatch(const ParsedPacket& p);


 private:
  std::map<std::string, std::function<commandResult(const std::string&)>> _global;
  IModule* _activeModule = nullptr;
  std::map<std::string, IModule*> _modules;

  commandResult _dispatchSimple(const ParsedPacket& p);
  commandResult _dispatchMotion(const ParsedPacket& p);
  commandResult _dispatchParam(const ParsedPacket& p);

  float _readFloat(const uint8_t* data);

  void _registerGlobal();
  MotionController& _motion;
};
#pragma once

#include <functional>
#include <map>
#include <string>

#include "IModule.h"
#include "MotionController.h"

class CommandHandler {
 public:
  void begin(std::initializer_list<std::pair<const char*, IModule*>> modules);
  CommandHandler(MotionController& motion);
  std::string handle(const char* raw);
  void setModule(IModule* module);
  void update();

 private:
  std::map<std::string, std::function<std::string(std::string)>> _global;
  IModule* _activeModule = nullptr;
  std::map<std::string, IModule*> _modules;

  void _registerGlobal();
  MotionController* _motion = nullptr;
};
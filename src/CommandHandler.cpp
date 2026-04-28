#include "CommandHandler.h"

#include "Logger.h"
#include "Response.h"

void CommandHandler::_registerGlobal() {
  _global["base"] = [this](std::string v) {
    _motion->baseSpeed = atoi(v.c_str()); 
    return Response::ok("base= " + std::string(v)); };
  _global["kA"] = [this](std::string v) {
    _motion->kA = atof(v.c_str());
    return Response::ok("kA=" + std::string(v));
  };

  _global["kB"] = [this](std::string v) {
    _motion->kB = atof(v.c_str());
    return Response::ok("kB=" + std::string(v));
  };

  _global["kC"] = [this](std::string v) {
    _motion->kC = atof(v.c_str());
    return Response::ok("kC=" + std::string(v));
  };

  _global["kD"] = [this](std::string v) {
    _motion->kD = atof(v.c_str());
    return Response::ok("kD=" + std::string(v));
  };

  // Query parameters
  _global["kA?"] = [this](std::string v) {
    return Response::ok("kA=" + std::to_string(_motion->kA));
  };

  _global["kB?"] = [this](std::string v) {
    return Response::ok("kB=" + std::to_string(_motion->kB));
  };

  _global["kC?"] = [this](std::string v) {
    return Response::ok("kC=" + std::to_string(_motion->kC));
  };

  _global["kD?"] = [this](std::string v) {
    return Response::ok("kD=" + std::to_string(_motion->kD));
  };

  _global["base?"] = [this](std::string v) {
    return Response::ok("base=" + std::to_string(_motion->baseSpeed));
  };

  _global["cK?"] = [this](std::string v) {
    return Response::ok("cK=" + std::to_string(_motion->curveK));
  };

  // Motor speed control
  _global["mA"] = [this](std::string v) {
    _motion->_motorA->setSpeed(atoi(v.c_str()));
    return Response::ok("mA=" + std::string(v));
  };

  _global["mB"] = [this](std::string v) {
    _motion->_motorB->setSpeed(atoi(v.c_str()));
    return Response::ok("mB=" + std::string(v));
  };

  _global["mC"] = [this](std::string v) {
    _motion->_motorC->setSpeed(atoi(v.c_str()));
    return Response::ok("mC=" + std::string(v));
  };

  _global["mD"] = [this](std::string v) {
    _motion->_motorD->setSpeed(atoi(v.c_str()));
    return Response::ok("mD=" + std::string(v));
  };

  _global["cK"] = [this](std::string v) {
    _motion->curveK = atof(v.c_str());
    return Response::ok("cK=" + std::string(v));
  };

  _global["module"] = [this](std::string v) {
    if (_modules.count(v)) {
      this->setModule(_modules[v]);
      return Response::ok("module: " + v);
    }
    return std::string("");
  };

  _global["bleprint"] = [this](std::string v) {
    Logger::blePrint = !Logger::blePrint;
    return Response::ok("bleprint");
  };
  Logger::info("_globalRegister");
}

CommandHandler::CommandHandler(MotionController& motion) : _motion(&motion) {};

void CommandHandler::begin(std::initializer_list<std::pair<const char*, IModule*>> modules) {
  for (auto& pair : modules) {
    _modules[pair.first] = pair.second;
  }
  _registerGlobal();
}

void CommandHandler::setModule(IModule* module) {
  _activeModule = module;
}

std::string CommandHandler::handle(const char* raw) {
  std::string cmd(raw);
  Logger::info("Incoming msg:" + cmd);

  int8_t sep = cmd.find(':');

  std::string name = sep == -1 ? cmd.c_str() : cmd.substr(0, sep).c_str();
  std::string arg = sep == -1 ? "" : cmd.substr(sep + 1).c_str();

  name.erase(name.find_last_not_of(" \n\r\t") + 1);
  arg.erase(arg.find_last_not_of(" \n\r\t") + 1);

  Logger::verbose("name:" + name);
  Logger::verbose("arg:" + arg);

  if (_global.count(name)) {
    Logger::verbose("GLOBAL");
    std::string result = _global[name](arg);
    if (!result.empty()) return result;
  }

  if (_activeModule) {
    Logger::verbose("ACTIVE MODULE");
    std::string result = _activeModule->handleCommand(name, arg);
    if (!result.empty()) return result;
  }

  return Response::err(cmd);
}

void CommandHandler::update() {
  if (_activeModule) {
    _activeModule->update();
  }
}

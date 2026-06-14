#include "CommandHandler.h"

#include "Logger.h"
#include "ObjectAvoidance.h"
#include "Response.h"
#include "ble.h"

void CommandHandler::_registerGlobal() {
  _global = {
    {"base", [this](const std::string& v) {_motion.baseSpeed = atoi(v.c_str()); return commandResult::ok();}},
    {"kA", [this](const std::string& v) {_motion.kA = atof(v.c_str()); return commandResult::ok();}},
    {"kB", [this](const std::string& v) {_motion.kB = atof(v.c_str()); return commandResult::ok();}},
    {"kC", [this](const std::string& v) {_motion.kC = atof(v.c_str()); return commandResult::ok();}},
    {"kD", [this](const std::string& v) {_motion.kD = atof(v.c_str()); return commandResult::ok();}},
    {"kA?", [this](const std::string& v) {return commandResult::okFloat(_motion.kA);}},
    {"kB?", [this](const std::string& v) {return commandResult::okFloat(_motion.kB);}},
    {"kC?", [this](const std::string& v) {return commandResult::okFloat(_motion.kC);}},
    {"kD?", [this](const std::string& v) {return commandResult::okFloat(_motion.kD);}},
    {"base?", [this](const std::string& v) {return commandResult::okInt(_motion.baseSpeed);}},
    {"cK?", [this](const std::string& v) {return commandResult::okFloat(_motion.curveK);}},
    {"mA", [this](const std::string& v) {_motion._motorA.setSpeed(atoi(v.c_str())); return commandResult::ok();}},
    {"mB", [this](const std::string& v) {_motion._motorB.setSpeed(atoi(v.c_str())); return commandResult::ok();}},
    {"mC", [this](const std::string& v) {_motion._motorC.setSpeed(atoi(v.c_str())); return commandResult::ok();}},
    {"mD", [this](const std::string& v) {_motion._motorD.setSpeed(atoi(v.c_str())); return commandResult::ok();}},
    {"cK", [this](const std::string& v) {_motion.curveK = atof(v.c_str()); return commandResult::ok();}},
    {"module", [this](const std::string& v) {if (_modules.count(v)) {this->setModule(_modules[v]); return commandResult::ok();} return commandResult::err(ErrorType::UnknownParam);}},
    {"module?", [this] (const std::string& v) {return commandResult::okInt(_activeModule->getId());}},
    {"safetymode", [this](const std::string& v) {ObjectAvoidance::setEnabled(atoi(v.c_str()) ? true : false); return commandResult::ok();}},
    {"safetymode?", [this](const std::string& v) {return commandResult::okInt(ObjectAvoidance::isEnabled() ? 1 : 0);}},
    {"threshold?", [this](const std::string& v) {return commandResult::okInt(ObjectAvoidance::getThreshold());}},
    {"threshold", [this](const std::string& v) {ObjectAvoidance::setThreshold(atoi(v.c_str())); return commandResult::ok();}},
    {"sUSs", [this](const std::string& v) {flags.USStream = true; return commandResult::ok();}},
    {"eUSs", [this](const std::string& v) {flags.USStream = false; return commandResult::ok();}},
    {"radius?", [this](const std::string& v) {return commandResult::okFloat(_motion.radius);}},
    {"radius", [this](const std::string& v) {_motion.radius = atof(v.c_str()); return commandResult::ok();}},

  };
}

void CommandHandler::begin(std::initializer_list<std::pair<const char*, IModule*>> modules) {
  for (const auto& pair : modules) {
    _modules[pair.first] = pair.second;
  }
  _registerGlobal();
}

void CommandHandler::setModule(IModule* module) {
  _activeModule = module;
}

commandResult CommandHandler::handle(const std::string& cmd) {
  // Logger::info("CommandHandler::handle(\"" + cmd + "\")");

  int8_t sep = cmd.find(':');

  std::string name = sep == -1 ? cmd.c_str() : cmd.substr(0, sep).c_str();
  std::string arg = sep == -1 ? "" : cmd.substr(sep + 1).c_str();

  name.erase(name.find_last_not_of(" \n\r\t") + 1);
  arg.erase(arg.find_last_not_of(" \n\r\t") + 1);

  // Logger::verbose("name:" + name.empty() ? "empty" : name);
  // Logger::verbose("arg:" + arg.empty() ? "empty" : arg);

  if (_global.count(name)) {
    // Logger::verbose("_global");
    commandResult result = _global[name](arg);
    return result;
  }

  if (_activeModule) {
    // Logger::verbose("ACTIVE MODULE");
    commandResult result = _activeModule->handleCommand(name, arg);
    return result;
  }

  return commandResult::err(ErrorType::UnknownCmd);
}

void CommandHandler::update() {
  if (_activeModule) {
    _activeModule->update();
  }
}

commandResult CommandHandler::dispatch(const ParsedPacket& packet) {
  switch (packet.type) {
    case (uint8_t)PacketType::Motion: {
      return _dispatchMotion(packet);    
    }
    case (uint8_t)PacketType::SimpleCmd: {
      return _dispatchSimple(packet);
    }
    case (uint8_t)PacketType::ParamCmd: {
      return _dispatchParam(packet);
    }
    default:
    Logger::error("CommandHandler::dispatch -> unknown type");
    Serial.println(packet.type);
    return commandResult::err(ErrorType::UnknownType);
  }
}

commandResult CommandHandler::_dispatchMotion(const ParsedPacket& p) {
  char buf[8];
  if (p.payloadLen < 1) return commandResult::err(ErrorType::InvalidPayload);

  uint8_t btn = (p.payload[0] / 10) * 10;
  uint8_t state = p.payload[0] % 10;

  sniprintf(buf, sizeof(buf), "!B%u%u", btn / 10, state);

  Logger::info(std::string(buf));
  return handle(buf); 
}

commandResult CommandHandler::_dispatchSimple(const ParsedPacket& p) {
  if (p.payloadLen < 1) return commandResult::err(ErrorType::InvalidPayload);

  switch(p.payload[0]) {
    case SimpleCmd::Stop: return handle("stop");
    case SimpleCmd::Base_Q: return handle("base?");
    case SimpleCmd::ModuleManual: return handle("module:manual");
    case SimpleCmd::ModuleLine: return handle("module:line");
    case SimpleCmd::Threshold_Q: return handle("threshold?");
    // case SimpleCmd::SafetyMode: return handle("safetymode");
    case SimpleCmd::SafetyMode_Q: return handle("safetymode?");
    case SimpleCmd::Module_Q: return handle("module?");
    // case SimpleCmd::Ka_Q: return handle("kA?");
    // case SimpleCmd::Kb_Q: return handle("kB?");
    // case SimpleCmd::Kc_Q: return handle("kC?");
    // case SimpleCmd::Kd_Q: return handle("kD?");
    case SimpleCmd::Ck_Q: return handle("cK?");
    case SimpleCmd::Crs_Q: return handle("crs?");
    case SimpleCmd::Cre_Q: return handle("cre?");
    case SimpleCmd::StartIRstream: return handle("sIRs");
    case SimpleCmd::EndIRstream: return handle("eIRs");
    case SimpleCmd::StartUSstream: return handle("sUSs");
    case SimpleCmd::EndUSstream: return handle("eUSs");
    case SimpleCmd::StartLine: return handle("sl");
    case SimpleCmd::EndLine: return handle("el");
    case SimpleCmd::ModuleObjectFollowing: return handle("module:object");
    case SimpleCmd::StartFollowing: return handle("startFollowing");
    case SimpleCmd::StopFollowing: return handle("stopFollowing");
    case SimpleCmd::MinDist_Q: return handle("minDist?");
    case SimpleCmd::MaxDist_Q: return handle("maxDist?");
    case SimpleCmd::Radius_Q: return handle("radius?");

    default: return commandResult::err(ErrorType::UnknownCmd);
  }

}

commandResult CommandHandler::_dispatchParam(const ParsedPacket& p) {
  if (p.payloadLen < 2) return commandResult::err(ErrorType::InvalidPayload);

  char buf[32];

  switch(p.payload[0]) {
    case ParamCmd::Base: snprintf(buf, sizeof(buf), "base:%d", (uint8_t)p.payload[1]); break;
    case ParamCmd::MinDist: snprintf(buf, sizeof(buf), "minDist:%d", (uint8_t)p.payload[1]); break;
    case ParamCmd::MaxDist: snprintf(buf, sizeof(buf), "maxDist:%d", (uint8_t)p.payload[1]); break;
    case ParamCmd::Threshold: snprintf(buf, sizeof(buf), "threshold:%d", (uint8_t)p.payload[1]); break;
    case ParamCmd::Ck: snprintf(buf, sizeof(buf), "cK:%.2f", _readFloat(&p.payload[1])); break;
    case ParamCmd::SafetyMode: snprintf(buf, sizeof(buf), "safetymode:%d", (uint8_t)p.payload[1]); break;
    case ParamCmd::Crs: snprintf(buf, sizeof(buf), "crs:%.2f", _readFloat(&p.payload[1])); break;
    case ParamCmd::Cre: snprintf(buf, sizeof(buf), "cre:%.2f", _readFloat(&p.payload[1])); break;
    case ParamCmd::Radius: snprintf(buf, sizeof(buf), "radius:%.2f", _readFloat(&p.payload[1])); break;
    default: return commandResult::err(ErrorType::UnknownCmd);
  }
  Serial.println(_readFloat(&p.payload[1]));
  Serial.println(buf);
  return handle(buf);
}

float CommandHandler::_readFloat(const uint8_t* data) {
  float value;
  memcpy(&value, data, sizeof(value));
  return value;
}
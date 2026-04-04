#include <iterator>
#include <vector>
#include <memory>
#include <CommandHandler.h>
#include <motors.h>
#include <string>
#include <MotorCommands.h>


CommandHandler Commands;

String ok(String cmd){
  return "ok: " + cmd;
}

String err(String cmd){
  return "unknown: " + cmd;
}

CommandHandler::CommandHandler() {
  commands = {
    {"forward",  std::make_shared<ForwardCommand>()},
    {"backward",  std::make_shared<BackwardCommand>()},
  };

  queries = {
    {"kA?",   []() { return ok("kA:"   + String(kA)); }},
    {"kB?",   []() { return ok("kB:"   + String(kB)); }},
    {"kC?",   []() { return ok("kC:"   + String(kC)); }},
    {"kD?",   []() { return ok("kD:"   + String(kD)); }},
    {"base?", []() { return ok("base:" + String(baseSpeed)); }},
  };

  params = {
    {"base", [](String v) { baseSpeed = v.toInt();   return ok("base=" + v); }},
    {"kA",   [](String v) { kA = v.toFloat();        return ok("kA="  + v); }},
    {"kB",   [](String v) { kB = v.toFloat();        return ok("kB="  + v); }},
    {"kC",   [](String v) { kC = v.toFloat();        return ok("kC="  + v); }},
    {"kD",   [](String v) { kD = v.toFloat();        return ok("kD="  + v); }},
    {"mA",   [](String v) { motorA(v.toInt());       return ok("mA="  + v); }},
    {"mB",   [](String v) { motorB(v.toInt());       return ok("mB="  + v); }},
    {"mC",   [](String v) { motorC(v.toInt());       return ok("mC="  + v); }},
    {"mD",   [](String v) { motorD(v.toInt());       return ok("mD="  + v); }},
  };

  combos = {
    {{JoystickButton::Up},    std::make_shared<ForwardCommand>()},
    {{JoystickButton::Down},  std::make_shared<BackwardCommand>()},
    {{JoystickButton::Left},  std::make_shared<LeftCommand>()},
    {{JoystickButton::Right}, std::make_shared<RightCommand>()},
    {{JoystickButton::Num1},  std::make_shared<ForwardLeftCommand>()},
    {{JoystickButton::Num2},  std::make_shared<ForwardRightCommand>()},
    {{JoystickButton::Num3},  std::make_shared<BackwardLeftCommand>()},
    {{JoystickButton::Num4},  std::make_shared<BackwardRightCommand>()},
  };
}

String CommandHandler::handle(String cmd) {
  cmd.trim();

  int sep = cmd.indexOf(':');
  bool isBtn = cmd.startsWith("!B");

  if (sep == -1 && !isBtn) return handleSimple(cmd);
  else if (isBtn) return handleJoystickBtn(cmd);
  else return handleParam(cmd.substring(0, sep), cmd.substring(sep + 1));
}

String CommandHandler::handleSimple(const String& cmd) {
  std::string key(cmd.c_str());

  if (queries.count(key)) {
    return queries[key]();
  }
  
  if (commands.count(key)) {
    commands[key]->execute();
    return "ok";
  }

  return err(cmd);
}

String CommandHandler::handleParam(const String& key, const String& value) {
  std::string k(key.c_str());

  if (params.count(k)) {
    return params[k](value);
  }

  return err(key);
}

void CommandHandler::updateMotors() {
  std::vector<JoystickButton> pressed(activeKeys.begin(), activeKeys.end());

  if (combos.count(pressed)) {
    combos[pressed]->execute();
  } else {
    stopAll();
  }
}

void CommandHandler::keyUp(JoystickButton btn) {
  activeKeys.erase(btn);
  updateMotors();
}

void CommandHandler::keyDown(JoystickButton btn) {
  activeKeys.insert(btn);
  updateMotors();
}


String CommandHandler::handleJoystickBtn(const String& cmd) {
  JoystickButton btn = (JoystickButton)cmd[2];
  bool pressed = cmd[3] == '1';

  pressed ? keyDown(btn) : keyUp(btn);

  return ok("zajebis");
}
#include "ManualModule.h"

#include "motors.h"

String ok(const String& cmd) { return "ok: " + cmd; }

String err(const String& cmd) { return "unknown: " + cmd; }

ManualModule::ManualModule() {
  // clang-format off
  commands = {
      {"forward", []() { forward(); return ok("forward");}},
      {"backward", []() { backward(); return ok("backward");}},
      {"stop", []() { stopAll(); return ok("stop");}},
  };

  queries = {
      {"kA?", []() { return ok("kA:" + String(kA)); }},
      {"kB?", []() { return ok("kB:" + String(kB)); }},
      {"kC?", []() { return ok("kC:" + String(kC)); }},
      {"kD?", []() { return ok("kD:" + String(kD)); }},
      {"base?", []() { return ok("base:" + String(baseSpeed)); }},
      {"cK?", []() { return ok("curveK:" + String(curveK)); }},
      {"curvedL?", []() { curvedTrajectoryLeft(); return ok("base:" + String(baseSpeed)); }},
      {"curvedR?",[]() { curvedTrajectoryRight(); return ok("base:" + String(baseSpeed)); }},
      {"lateral?",[]() { lateralArc(); return ok("base:" + String(baseSpeed)); }},
  };

  params = {
      {"base", [](String v) { baseSpeed = v.toInt(); return ok("base=" + v); }},
      {"kA", [](String v) { kA = v.toFloat(); return ok("kA=" + v); }},
      {"kB", [](String v) { kB = v.toFloat(); return ok("kB=" + v); }},
      {"kC", [](String v) { kC = v.toFloat(); return ok("kC=" + v); }},
      {"kD", [](String v) { kD = v.toFloat(); return ok("kD=" + v); }},
      {"mA", [](String v) { motorA.setSpeed(v.toInt()); return ok("mA=" + v); }},
      {"mB", [](String v) { motorB.setSpeed(v.toInt()); return ok("mB=" + v); }},
      {"mC", [](String v) { motorC.setSpeed(v.toInt()); return ok("mC=" + v); }},
      {"mD", [](String v) { motorD.setSpeed(v.toInt()); return ok("mD=" + v); }},
      {"cK", [](String v) { curveK = v.toFloat(); return ok("cK=" + v); }},
  };

  // clang-format on
}

String ManualModule::handleCommand(String cmd) {
  int sep = cmd.indexOf(':');
  int isQuery = cmd.indexOf('?');
  int isBtn = cmd.indexOf("!B");

  if (sep == -1 && isQuery == -1)
    return processCommand(cmd);
  else if (isQuery && sep == -1)
    return handleQuery(cmd);
  else if (isBtn)
    return joystick.handle(cmd);
  else
    return handleParam(cmd.substring(0, sep), cmd.substring(sep + 1));
}

String ManualModule::processCommand(const String& cmd) {
  std::string key(cmd.c_str());

  if (commands.count(key)) {
    return commands[key]();
  }

  return err(cmd);
}

String ManualModule::handleQuery(const String& cmd) {
  std::string key(cmd.c_str());

  if (queries.count(key)) {
    return queries[key]();
  }

  return err(cmd);
}

String ManualModule::handleParam(const String& key, const String& value) {
  std::string k(key.c_str());

  if (params.count(k)) {
    // !! passing string
    return params[k](value);
  }

  return err(key);
}

JoystickController::JoystickController() {
  combos = {
      {{JoystickButton::Up}, std::make_shared<ForwardCommand>()},
      {{JoystickButton::Down}, std::make_shared<BackwardCommand>()},
      {{JoystickButton::Left}, std::make_shared<LeftCommand>()},
      {{JoystickButton::Right}, std::make_shared<RightCommand>()},
      {{JoystickButton::Up, JoystickButton::Left}, std::make_shared<ForwardLeftCommand>()},
      {{JoystickButton::Up, JoystickButton::Right}, std::make_shared<ForwardRightCommand>()},
      {{JoystickButton::Down, JoystickButton::Left}, std::make_shared<BackwardLeftCommand>()},
      {{JoystickButton::Down, JoystickButton::Right}, std::make_shared<BackwardRightCommand>()},
      {{JoystickButton::Num2, JoystickButton::Num4}, std::make_shared<TurningRightCommand>()},
      {{JoystickButton::Num1, JoystickButton::Num3}, std::make_shared<TurningLeftCommand>()},
      {{JoystickButton::Num1, JoystickButton::Up}, std::make_shared<CurvedTrajectoryLeftCommand>()},
      {{JoystickButton::Num2, JoystickButton::Up}, std::make_shared<CurvedTrajectoryRightCommand>()},
      {{JoystickButton::Num3, JoystickButton::Up}, std::make_shared<LateralArcCommand>()},
  };
}

void JoystickController::updateMotors() {
  std::vector<JoystickButton> pressed(activeKeys.begin(), activeKeys.end());

  if (combos.count(pressed)) {
    combos[pressed]->execute();
  } else {
    stopAll();
  }
}

void JoystickController::keyUp(JoystickButton btn) {
  activeKeys.erase(btn);
  updateMotors();
}

void JoystickController::keyDown(JoystickButton btn) {
  activeKeys.insert(btn);
  updateMotors();
}

using Button = JoystickController::JoystickButton;

String JoystickController::handle(String& cmd) {
  JoystickButton btn = (JoystickButton)(int(cmd[2]) - 1);

  bool isPressed = cmd[3] == '1';

  isPressed ? keyDown(btn) : keyUp(btn);

  return ok("handled");
}
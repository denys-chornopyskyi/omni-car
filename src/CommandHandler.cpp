#include "CommandHandler.h"

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "LineFollower.h"
#include "MotorCommands.h"
#include "motors.h"

volatile Mode currentMode = Mode::Manual;

CommandHandler Commands;

#define OK(cmd) String("ok: ") + cmd

String ok(String cmd) { return "ok: " + cmd; }

String err(String cmd) { return "unknown: " + cmd; }

CommandHandler::CommandHandler() {
  // clang-format off
  commands = {
      {"forward", []() { forward(); return ok("forward");}},
      {"backward", []() { backward(); return ok("backward");}},
      {"stop", []() { stopAll(); return ok("stop");}},
      {"manual", []() {
        if (lineFollower != nullptr) {
          delete lineFollower;
          lineFollower = nullptr;
          currentMode = Mode::Manual;
          return ok("mode:manual");
        }
       }},
      {"linefollow", []() {
        if (lineFollower == nullptr) {
          lineFollower = new LineFollower();
          currentMode = Mode::LineFollow;
          return ok("mode:linefollow");
        }
       }},
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
// clang-format on

String CommandHandler::handle(String cmd) {
  cmd.trim();

  bool isMode = cmd == "manual" || cmd == "linefollow";

  if (currentMode != Mode::Manual && !isMode) {
    return err("not in manual mode");
  }

  int sep = cmd.indexOf(':');
  bool isBtn = cmd.startsWith("!B");

  if (sep == -1 && !isBtn)
    return handleSimple(cmd);
  else if (isBtn)
    return handleJoystickBtn(cmd);
  else
    return handleParam(cmd.substring(0, sep), cmd.substring(sep + 1));
}

String CommandHandler::handleSimple(const String& cmd) {
  std::string key(cmd.c_str());

  if (queries.count(key)) {
    return queries[key]();
  }

  if (commands.count(key)) {
    return commands[key]();
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
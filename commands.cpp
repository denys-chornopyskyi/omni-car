#include <commands.h>
#include <motors.h>
#include <calibration.h>


CommandHandler commands;

enum class JoystickButtons {
  Num1 = '1',
  Num2 = '2',
  Num3 = '3',
  Num4 = '4',
  Up = '5',
  Down = '6',
  Left = '7',
  Right = '8'
}

enum class BtnState {
  Released,
  Pressed
}

String CommandHandler::handle(String cmd) {
  cmd.trim();

  int sep = cmd.indexOf(':');
  bool isBtn = cmd.startsWith("!B");

  if (sep == -1 && !isBtn) return handleSimple(cmd);
  else if (isBtn) return handleJoystickBtn(cmd);
  else return handleParam(cmd.substring(0, sep), cmd.substring(sep + 1));
}

String CommandHandler::handleSimple(String cmd) {
    if      (cmd == "go")   { forward();  return "ok: go";   }
  else if (cmd == "back") { backward(); return "ok: back";  }
  else if (cmd == "stop") { stopAll();  return "ok: stop";  }

  else if (cmd == "kA?")   { return "kA:"   + String(kA);          }
  else if (cmd == "kB?")   { return "kB:"   + String(kB);          }
  else if (cmd == "kC?")   { return "kC:"   + String(kC);          }
  else if (cmd == "kD?")   { return "kD:"   + String(kD);          }
  else if (cmd == "base?") { return "base:" + String(baseSpeed);    }


  return "unknown: " + cmd;
}

String CommandHandler::handleParam(String key, String value) {
  if      (key == "base") { baseSpeed = value.toInt();  return "ok: base=" + value; }
  else if (key == "kA")   { kA = value.toFloat();       return "ok: kA="   + value; }
  else if (key == "kB")   { kB = value.toFloat();       return "ok: kB="   + value; }
  else if (key == "kC")   { kC = value.toFloat();       return "ok: kC="   + value; }
  else if (key == "kD")   { kD = value.toFloat();       return "ok: kD="   + value; }
  else if (key == "mA")   { motorA(value.toInt());      return "ok: mA="   + value; }
  else if (key == "mB")   { motorB(value.toInt());      return "ok: mB="   + value; }
  else if (key == "mC")   { motorC(value.toInt());      return "ok: mC="   + value; }
  else if (key == "mD")   { motorD(value.toInt());      return "ok: mD="   + value; }

  return "unknown: " + key;
}

String CommandHandler::handleJoystickBtn(String cmd) {
  JoystickButtons btn = (JoystickButtons)cmd[2];
  BtnState state = (cmd[3] == '1') ? BtnState::Pressed : BtnState::Released;

  switch(btn) {
    case JoystickButtons::Up: 
  }


  if (btn == "")
}
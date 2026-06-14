#pragma once
#include <stdint.h>

namespace PROTOCOL {
  constexpr uint8_t START = 0xAA;
  constexpr uint8_t END = 0xFF;
}

enum PacketType {
  Motion = 0x01,
  SimpleCmd = 0x02,
  ParamCmd = 0x03,
  SuccessResponse = 0x50,
  ErrorResponse = 0x51,
  IRSensor = 0x04,
  USSensor = 0x05,
};

enum SimpleCmd {
  Stop = 1,
  Base_Q = 2,
  Ck_Q = 10,

  ModuleManual = 3,
  Module_Q = 15,

  ModuleLine = 4,
  Crs_Q = 12,
  Cre_Q = 13,

  // SafetyMode = 5,
  SafetyMode_Q = 14,
  Threshold_Q = 11,
  // Ka_Q = 6,
  // Kb_Q = 7,
  // Kc_Q = 8,
  // Kd_Q = 9,
  StartIRstream = 16,
  EndIRstream = 17,
  StartUSstream = 18,
  EndUSstream = 19,
  StartLine = 20,
  EndLine = 21,
  ModuleObjectFollowing = 22,
  StartFollowing = 23,
  StopFollowing = 24,
  MinDist_Q = 25,
  MaxDist_Q = 26,
  Radius_Q = 27,
};

enum ParamCmd {
  Base = 1,
  // Module = 12,
  // Ka = 2,
  // Kb = 3,
  // Kc = 4,
  // Kd = 5,
  Ck = 6,
  // Ma = 7,
  // Mb = 8,
  // Mc = 9,
  // Md = 10,
  Threshold = 11,
  MinDist = 12,
  MaxDist = 13,
  SafetyMode = 14,
  Crs = 15,
  Cre = 16,
  Radius = 17,
};

enum MotionButton {
  Center = 0x0a,
  UpLeft = 0x14,
  Up = 0x1e,
  UpRight = 0x28,
  Left = 0x32,
  Right = 0x3c,
  DownLeft = 0x46,
  Down = 0x50,
  DownRight = 0x5a,
};

enum class ModuleType : uint8_t {
  Manual = 1,
  Line = 2,
};

struct ParsedPacket {
  uint8_t type;
  bool needsResponse;
  uint8_t payloadLen;
  uint8_t payload[16];

};

struct ResponsePacket {
  uint8_t buf[16];
  uint8_t len;
};


enum class ErrorType : uint8_t {
  None           = 0x00,
  UnknownCmd     = 0x01,
  UnknownParam   = 0x02,
  InvalidPayload = 0x03,
  UnknownType    = 0x04,
};

enum class ResultType : uint8_t {
  None = 0x00,
  IntValue = 0x01,
  FloatValue = 0x02,
  BoolValue = 0x03,
};

struct commandResult {
  bool success;
  ErrorType error;
  ResultType resultType;

  union {
    uint8_t intValue;
    float floatValue;
    bool boolValue;
  };

  static commandResult ok() {
    return {true, ErrorType::None, ResultType::None};
  }

  static commandResult okInt(uint8_t v) {
    commandResult r;
    r.success = true;
    r.error = ErrorType::None;
    r.resultType = ResultType::IntValue;
    r.intValue = v;
    return r;
  }

  static commandResult okFloat(float v) {
    commandResult r;
    r.success = true;
    r.error = ErrorType::None;
    r.resultType = ResultType::FloatValue;
    r.floatValue = v;
    return r;
  }

  static commandResult okBool(bool v) {
    commandResult r;
    r.success = true;
    r.error = ErrorType::None;
    r.resultType = ResultType::BoolValue;
    r.boolValue = v;
    return r;
  }

  static commandResult err(ErrorType e) {
    return {false, e, ResultType::None};
  } 

};
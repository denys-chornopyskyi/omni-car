#pragma once
#include <Arduino.h>

#include "ble.h"

#define DEBUGE_MODE

enum class LogLevel {
  None,
  Error,
  Info,
  Verbose
};

class Logger {
 public:
  static LogLevel level;

  static void error(const char* msg) {
    if (level >= LogLevel::Error) {
      Serial.print("[ERROR] ");
      Serial.println(msg);
    }
  };
  static void error(std::string msg) {
    if (level >= LogLevel::Error) {
      Serial.print("[ERROR] ");
      Serial.println(msg.c_str());
    }
  };

  static void info(const char* msg) {
    if (level >= LogLevel::Info) {
      Serial.print("[INFO]  ");
      Serial.println(msg);
    }
  }
  static void info(std::string msg) {
    if (level >= LogLevel::Info) {
      Serial.print("[INFO]  ");
      Serial.println(msg.c_str());
    }
  }

  static void verbose(const char* msg) {
    if (level >= LogLevel::Verbose) {
      Serial.print("[VERB]  ");
      Serial.println(msg);
    }
  }
  static void verbose(std::string msg) {
    if (level >= LogLevel::Verbose) {
      Serial.print("[VERB]  ");
      Serial.println(msg.c_str());
    }
  }
};

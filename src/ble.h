#pragma once
#include <Arduino.h>

void bleInit();
void bleSend(const char* msg);
void bleSend(std::string msg);
void bleLoop();
extern bool isConnected;
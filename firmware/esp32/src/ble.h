#pragma once
#include <Arduino.h>

void bleInit();
void bleSend(const char* msg);
void bleSend(std::string msg);
void bleSend(const uint8_t* data, size_t len);
void bleLoop();
extern bool isConnected;
struct StreamFlags {
    bool IRStream = false;
    bool USStream = false;
};
extern StreamFlags flags;
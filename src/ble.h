#pragma once
#include <Arduino.h>

void bleInit();
void bleSend(String& msg);
void bleLoop();
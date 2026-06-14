#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "BleProtocol.h"

extern QueueHandle_t commandQueue;

void queueInit();
void queueSend(const ParsedPacket& packet);
bool queueReceive(ParsedPacket& packet);
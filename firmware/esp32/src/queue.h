#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

extern QueueHandle_t commandQueue;

void queueInit();
void queueSend(const char* cmd);
bool queueReceive(char* cmd);
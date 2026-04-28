#include "queue.h"

QueueHandle_t commandQueue;

void queueInit() {
  commandQueue = xQueueCreate(10, sizeof(char) * 32);
}

void queueSend(const char* cmd) {
  char buf[32];
  strncpy(buf, cmd, sizeof(buf));
  xQueueSend(commandQueue, buf, 0);
}

bool queueReceive(char* buf) {
  return xQueueReceive(commandQueue, buf, 0) == pdTRUE;
}
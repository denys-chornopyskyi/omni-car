#include "queue.h"

QueueHandle_t commandQueue;

void queueInit() {
  commandQueue = xQueueCreate(10, sizeof(char) * 32);
}

void queueSend(String cmd) {
  char buf[32];
  cmd.toCharArray(buf, 32);
  xQueueSend(commandQueue, buf, 0);
}

bool queueReceive(String& cmd) {
  char buf[32];
  if (xQueueReceive(commandQueue, buf, 0) == pdTRUE) {
    cmd = String(buf);
    return true;
  }
  return false;
}
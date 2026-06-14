#include "queue.h"
#include "Logger.h"

QueueHandle_t commandQueue;

void queueInit() {
  commandQueue = xQueueCreate(10, sizeof(ParsedPacket));
}

void queueSend(const ParsedPacket& packet) {
    // Serial.print("[INFO]  ");
    // Serial.print("Type: ");
    // Serial.println(packet.type);

    // Serial.print("[INFO]  ");
    // Serial.print("NeedsResponse: ");
    // Serial.println(packet.needsResponse ? "True" : "False");

    // Serial.print("[INFO]  ");
    // Serial.print("PayloadLen: ");
    // Serial.println(packet.payloadLen);

    std::string loggerPayload;
    for (uint8_t i = 0; i < packet.payloadLen; i++) {
      char buf[8];
      sprintf(buf, "%d, ", packet.payload[i]);
      loggerPayload += buf;
    }
    // Logger::info("Payload: [" + loggerPayload + ']');
  xQueueSend(commandQueue, &packet, 0);
}

bool queueReceive(ParsedPacket& packet) {
  return xQueueReceive(commandQueue, &packet, 0) == pdTRUE;
}
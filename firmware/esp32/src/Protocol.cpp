#include "Protocol.h"

#include "SensorStore.h"

void Protocol::update() {
  while (_serial.available()) {
    if (_serial.peek() != START_BYTE) {
      _serial.read();
      return;
    }

    if (_serial.available() < 11) return;
    _serial.read();
    uint8_t type = _serial.read();
    uint8_t len = _serial.read();

    uint8_t payload[8];
    for (uint8_t i = 0; i < len; i++) {
      payload[i] = _serial.read();
    }
    parsePacket(type, payload, len);
  }
}
void Protocol::parsePacket(uint8_t type, uint8_t* payload, uint8_t len) {
  switch (type) {
    case msgType::IR_ARRAY:
      for (uint8_t i = 0; i < len; i++) {
        SensorStore::getInstance().data.ir[i] = payload[i];
      }
      break;
    case msgType::FORWARD_DIST:
      if (payload[0] == 0) break;
      SensorStore::getInstance().data.distance[0] = payload[0];
      break;
    case msgType::BACKWARD_DIST:
      if (payload[0] == 0) break;
      SensorStore::getInstance().data.distance[1] = payload[0];
      break;
    case msgType::LEFT_DIST:
      if (payload[0] == 0) break;
      SensorStore::getInstance().data.distance[2] = payload[0];
      break;
    case msgType::RIGHT_DIST:
      if (payload[0] == 0) break;
      SensorStore::getInstance().data.distance[3] = payload[0];
      break;
    case msgType::FORWARD_LEFT_DIST:
      if (payload[0] == 0) break;
      SensorStore::getInstance().data.distance[4] = payload[0];
      break;
    case msgType::FORWARD_RIGHT_DIST:
      if (payload[0] == 0) break;
      SensorStore::getInstance().data.distance[5] = payload[0];
      break;
  }
}
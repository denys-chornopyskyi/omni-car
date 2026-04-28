#include "Protocol.h"

#include "SensorStore.h"

void Protocol::update() {
  while (_serial.available()) {
    if (_serial.peek() != START_BYTE) {
      _serial.read();
      return;
    }

    if (_serial.available() < 11) return;
    // Serial.println(_serial.read());
    _serial.read();
    uint8_t type = _serial.read();
    // Serial.println(type);
    uint8_t len = _serial.read();
    // Serial.println(len);

    uint8_t payload[8];
    for (uint8_t i = 0; i < len; i++) {
      // uint8_t byte = _serial.read();
      payload[i] = _serial.read();
      // Serial.println(i);
    }
    parsePacket(type, payload, len);
  }
}
void Protocol::parsePacket(uint8_t type, uint8_t* payload, uint8_t len) {
  // Serial.println(String("type: ") + type);
  // Serial.println(String("len: ") + len);
  // Serial.println(type);
  // Serial.println(len);
  // for (uint8_t i = 0; i < len; i++) {
  //   // uint8_t byte = _serial.read();
  //   Serial.print(payload[i]);
  // }
  // Serial.println();
  switch (type) {
    case msgType::IR_ARRAY:
      // Serial.print("IR_ARRAY: ");
      for (uint8_t i = 0; i < len; i++) {
        // Serial.print(payload[0]);
        SensorStore::getInstance().data.ir[i] = payload[i];
        // Serial.println(SensorStore::getInstance().data.ir[i]);
      }
      Serial.println();
      break;

    case msgType::DIST_1:
      // Serial.print("DIST_1: ");
      // Serial.println(payload[0]);
      SensorStore::getInstance().data.distance[0] = payload[0];

      // Serial.println(SensorStore::getInstance().data.distance[0]);
      break;
    case msgType::DIST_2:
      // Serial.print("DIST_2: ");
      // Serial.println(payload[0]);
      SensorStore::getInstance().data.distance[1] = payload[0];

      // Serial.println(SensorStore::getInstance().data.distance[1]);
      break;
    case msgType::DIST_3:
      // Serial.print("DIST_3: ");
      // Serial.println(payload[0]);
      SensorStore::getInstance().data.distance[2] = payload[0];

      // Serial.println(SensorStore::getInstance().data.distance[2]);
      break;
    case msgType::DIST_4:
      // Serial.print("DIST_4: ");
      // Serial.println(payload[0]);
      SensorStore::getInstance().data.distance[3] = payload[0];

      // Serial.println(SensorStore::getInstance().data.distance[3]);
      break;
  }
}
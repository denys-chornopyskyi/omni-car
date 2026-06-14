#include "BlePacketBuilder.h"
#include "BleProtocol.h"
#include "ble.h"
#include "SensorStore.h"

ResponsePacket BlePacketBuilder::buildResponse(const commandResult& result, const ParsedPacket& packet) {
  ResponsePacket r = {};
  uint8_t i = 0;

  r.buf[i++] = PROTOCOL::START;

  if (result.success) {
    r.buf[i++] = PacketType::SuccessResponse;

    switch (result.resultType) {

      case ResultType::None:
        r.buf[i++] = 3;
        r.buf[i++] = packet.type;
        r.buf[i++] = packet.payload[0];
        r.buf[i++] = (uint8_t)ResultType::None;  
        break;

      case ResultType::FloatValue:
        r.buf[i++] = 3 + sizeof(float);
        r.buf[i++] = packet.type;
        r.buf[i++] = packet.payload[0];
        r.buf[i++] = (uint8_t)ResultType::FloatValue;
        memcpy(r.buf + i, &result.floatValue, sizeof(float));
        i += sizeof(float);
        break;

      case ResultType::IntValue:
        r.buf[i++] = 4;
        r.buf[i++] = packet.type;
        r.buf[i++] = packet.payload[0];
        r.buf[i++] = (uint8_t)ResultType::IntValue;
        r.buf[i++] = result.intValue;
        break;

    }
  } else {
    r.buf[i++] = PacketType::ErrorResponse;
    r.buf[i++] = 4;
    r.buf[i++] = packet.type;
    r.buf[i++] = packet.payload[0];
    r.buf[i++] = (uint8_t)ResultType::None;
    r.buf[i++] = (uint8_t)result.error;
  }

  r.buf[i++] = PROTOCOL::END;
  r.len = i;
  return r;
}

ResponsePacket BlePacketBuilder::buildIRPacket() {
  SensorData store = SensorStore::getInstance().data;
  ResponsePacket r = {};
  uint8_t i = 0;

  r.buf[i++] = PROTOCOL::START;
  r.buf[i++] = PacketType::IRSensor;
  r.buf[i++] = 5;
  for (uint8_t k = 0; k < 5; k++) {
    r.buf[i++] = store.ir[k];
  }
  r.buf[i++] = PROTOCOL::END;
  r.len = i;
  return r;
}

ResponsePacket BlePacketBuilder::buildUSPacket() {
  SensorData store = SensorStore::getInstance().data;
  ResponsePacket r = {};
  uint8_t i = 0;

  r.buf[i++] = PROTOCOL::START;
  r.buf[i++] = PacketType::USSensor;
  r.buf[i++] = 4;
  for (uint8_t k = 0; k < 4; k++) {
    r.buf[i++] = store.distance[k];
  }
  r.buf[i++] = PROTOCOL::END;
  r.len = i;
  return r;
}

// void BlePacketBuilder::_sendSuccessResponse(const ParsedPacket& packet, const commandResult& result) {
//   uint8_t response[32];
//   uint8_t responseLen;
//   buildAndSend(PacketType::SuccessResponse, packet.type, packet.payload, packet.payloadLen, response, responseLen);
//   bleSend(response, responseLen);
// }

// void BlePacketBuilder::_sendErrorResonse(const ParsedPacket& packet, const commandResult& result) {
//   uint8_t response[32];
//   uint8_t responseLen;
//   buildAndSend(PacketType::ErrorResponse, packet.type, packet.payload, packet.payloadLen, response, responseLen);
//   bleSend(response, responseLen);
// }

#include "BleParser.h"
#include "Logger.h"
#include "BleProtocol.h"

uint8_t BleParser::_buf[BleParser::BUF_SIZE] = {};
size_t BleParser::_len = 0;
std::function<void(const char*)> BleParser::onError = nullptr;

void BleParser::reset() {
  BleParser::_len = 0;
}

void BleParser::_error(const char* msg) {
  Logger::error(msg);
  if (onError) onError(msg);
}

void BleParser::feed(const uint8_t* data, size_t len) {
  // Logger::info("Feeding start");
  for (size_t i = 0; i < len; i++) {
    if (_len < BUF_SIZE) {
      _buf[_len++] = data[i];
    } else {
      reset();
      Logger::error("Bleparser: overflow");
    }
  }
  // Logger::info("Feeding end");
  return _parse();
}

void BleParser::_parse() {
  // Logger::info("Before loop");
  while(_len >= 3) {
    // Logger::info("within loop");
    size_t start = 0;
    while (start < _len && _buf[start] != START) start++;

    if (start == _len) {
      reset();
    }

    if (start > 0) {
      memmove(_buf, _buf + start, _len - start);
      _len -= start;
    }

    if (_len < 3) return;

    uint8_t plen = _buf[2];
    uint8_t total = 1 + 1 + 1 + plen + 1;

    if (_len < total) return;

    if (_buf[total - 1] != END) {
      memmove(_buf, _buf + 1, _len - 1);
      _len--;
      continue;
    }

    uint8_t type = _buf[1];
    uint8_t* payload = _buf + 3;

    // Logger::info("buildPacket");
    
    ParsedPacket packet = _buildPacket(type, payload, plen);

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

    // Serial.print("[INFO]  ");
    // Serial.print("Type: ");
    // Serial.println(packet.type);
    queueSend(packet);

    memmove(_buf, _buf + total, _len - total);
    _len -= total;
  }
}
ParsedPacket BleParser::_buildPacket(uint8_t type, const uint8_t* payload, size_t plen) {
  uint8_t FLAG = 0x80;

  ParsedPacket packet = {};
  packet.type = type & ~FLAG; // remove flag
  packet.needsResponse = type & FLAG; // check the flag
  packet.payloadLen = plen;
  memcpy(packet.payload, payload, plen);
  return packet;
}

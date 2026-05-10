#include "BleParser.h"
#include "Logger.h"

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

std::string BleParser::feed(const uint8_t* data, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (_len < BUF_SIZE) {
      _buf[_len++] = data[i];
    } else {
      reset();
      Logger::error("Bleparser: overflow");
      return "";
    }
  }

  return _parce();
}

std::string BleParser::_parce() {
  while(_len >= 3) {
    uint8_t start = 0;
    while (start < _len && start != START) start++;

    if (start == _len) {
      reset();
      return "";
    }

    if (start > 0) {
      memmove(_buf, _buf + start, _len - start);
      _len -= start;
    }

    if (_len < 3) return "";

    uint8_t plen = _buf[2];
    uint8_t total = 1 + 1 + 1 + plen + 1;

    if (_len < total) return "";

    if (_buf[total - 1] != END) {
      memmove(_buf, _buf + 1, _len - 1);
      _len--;
      continue;
    }

    uint8_t type = _buf[1];
    uint8_t* payload = _buf + 3;

    std::string cmd = _toCommand(type, payload, plen);

    memmove(_buf, _buf + total, _len - total);
    _len -= total;

    return cmd;
  }
  return "";
}

std::string BleParser::_toCommand(uint8_t type, const uint8_t* payload, size_t plen) {
  char buf[32];

  switch (type) {
    case PacketType::Motion: {
        if (plen < 1) return;

        uint8_t btn = (payload[0] / 10) * 10;
        uint8_t state = payload[0] % 10;

        sniprintf(buf, sizeof(buf), "!B%u%u", btn / 10, state);

        return std::string(buf);    
    }
    default:
    Logger::error("BleParser: unknown type");
    return "";

  }

}
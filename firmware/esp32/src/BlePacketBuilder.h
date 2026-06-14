#pragma once
#include "Arduino.h"
#include "BleProtocol.h"

class BlePacketBuilder {
  public: 
    static ResponsePacket buildResponse(const commandResult& result, const ParsedPacket& packet);
    static ResponsePacket buildIRPacket();
    static ResponsePacket buildUSPacket();
};

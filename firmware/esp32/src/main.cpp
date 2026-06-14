#include "CommandHandler.h"
#include "HardwareSerial.h"
#include "LineFollower.h"
#include "Logger.h"
#include "ManualModule.h"
#include "MockMotor.h"
#include "MotionController.h"
#include "ObjectAvoidance.h"
#include "Protocol.h"
#include "RealMotor.h"
#include "SensorStore.h"
#include "ble.h"
#include "queue.h"
#include "BlePacketBuilder.h"
#include "ObjectFollower.h"

#define RX 21
#define TX 22

#ifdef DEBUGE_MODE
MockMotor motors[4] = {
  {"MotorA"},
  {"MotorB"},
  {"MotorC"},
  {"MotorD"},
};
#else
RealMotor motors[4] = {
  {M1_IN1, M1_IN2, M1_CH1, M1_CH2, "MotorA"},
  {M2_IN1, M2_IN2, M2_CH1, M2_CH2, "MotorB"},
  {M3_IN1, M3_IN2, M3_CH1, M3_CH2, "MotorC"},
  {M4_IN1, M4_IN2, M4_CH1, M4_CH2, "MotorD"},
};
#endif

#ifdef DEBUGE_MODE
LogLevel Logger::level = LogLevel::Verbose;
#else
LogLevel Logger::level = LogLevel::Info;
#endif

HardwareSerial nanoSerial(2);
Protocol protocol(nanoSerial);
SafetyGuard guard;

MotionController motion(motors[0], motors[1], motors[2], motors[3]);
CommandHandler handler(motion);
LineFollower lineModule(motion);
ManualModule manualModule(motion);
ObjectFollower objectModule(motion);
ObjectAvoidance avoidance(guard, motion);


void setup() {
  Serial.begin(115200);
  nanoSerial.begin(9600, SERIAL_8N1, RX, TX); 
  motion.init();
  motion.attachGuard(guard);
  queueInit();
  bleInit();

  lineModule.begin();
  objectModule.begin();
  handler.begin({{"manual", &manualModule},
                 {"line", &lineModule},
                 {"object", &objectModule}});
  handler.setModule(&manualModule);
}

void loop() {
  protocol.update();
  avoidance.update();
  ParsedPacket packet;
  if (queueReceive(packet)) {
    commandResult result = handler.dispatch(packet);

    Serial.print("[INFO]  ");
    Serial.print("Success: ");
    Serial.println(result.success ? "True" : "False");

    Serial.print("[INFO]  ");
    Serial.print("Error: ");
    Serial.println((uint8_t)result.error);

    Serial.print("[INFO]  ");
    Serial.print("ResultType: ");
    Serial.println((uint8_t)result.resultType);

    if (packet.needsResponse) {
      ResponsePacket response = BlePacketBuilder::buildResponse(result, packet);
      bleSend(response.buf, response.len);
    }
    
    
    // uint8_t resBuf[20];
    // uint8_t resLen = 0;

    // if (result.success) {
    //   uint8_t payload[8];
    //   uint8_t pLen = 0;
    //   if (result.resultType == ResultType::IntValue) {
    //     payload[0] = result.intValue;
    //     pLen = 1;
    //   } else if (result.resultType == ResultType::FloatValue) {
    //     memcpy(payload, &result.floatValue, 4);
    //     pLen = 4;
    //   }
    //   BlePacketBuilder::build(PacketType::SuccessResponse, payload, pLen, resBuf, resLen);
    // } else {
    //   uint8_t payload[1] = {(uint8_t)result.error};
    //   BlePacketBuilder::build(PacketType::ErrorResponse, payload, 1, resBuf, resLen);
    // }
    // bleSend(resBuf, resLen);
  }
  handler.update();
  bleLoop();

  // SensorData& data = SensorStore::getInstance().data;

  // Serial.print(String("IR: "));
  // for (uint8_t i = 0; i < 5; i++) {
  //   Serial.print(data.ir[i]);
  //   data.ir[i] = !data.ir[i];
  // }
  // Serial.println();

  // for (uint8_t i = 0; i < 6; i++) {
  //   Serial.print(String("Sensor") + i + ": ");
  //   Serial.println(data.distance[i]++);
  // }
  // delay(500);
}
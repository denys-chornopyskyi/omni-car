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

#define RX 21
#define TX 22

#ifdef DEBUGE_MODE
MockMotor mA("MotorA");
MockMotor mB("MotorB");
MockMotor mC("MotorC");
MockMotor mD("MotorD");
#else
RealMotor mA(M1_IN1, M1_IN2, M1_CH1, M1_CH2);
RealMotor mB(M2_IN1, M2_IN2, M2_CH1, M2_CH2);
RealMotor mC(M3_IN1, M3_IN2, M3_CH1, M3_CH2);
RealMotor mD(M4_IN1, M4_IN2, M4_CH1, M4_CH2);
#endif

#ifdef DEBUGE_MODE
LogLevel Logger::level = LogLevel::Info;
bool Logger::blePrint = true;
#else
LogLevel Logger::level = LogLevel::Info;
bool Logger::blePrint = true;
#endif

HardwareSerial nanoSerial(2);
Protocol protocol(nanoSerial);
SafetyGuard guard;

MotionController motion(mA, mB, mC, mD);
CommandHandler handler(motion);
LineFollower lineModule(motion);
ManualModule manualModule(motion);
ObjectAvoidance avoidance(guard, motion);

void setup() {
  Serial.begin(115200);
  nanoSerial.begin(9600, SERIAL_8N1, RX, TX);
  motion.init();
  motion.attachGuard(guard);
  queueInit();
  bleInit();

  lineModule.begin();
  handler.begin({{"manual", &manualModule},
                 {"line", &lineModule}});
  handler.setModule(&manualModule);
}

void loop() {
  protocol.update();
  avoidance.update();
  char cmd[32];
  if (queueReceive(cmd)) {
    std::string response = handler.handle(cmd);
    bleSend(response.c_str());
  }
  handler.update();

  // SensorData& data = SensorStore::getInstance().data;

  // delay(500);

  // Serial.print(String("IR: "));
  // for (uint8_t i = 0; i < 5; i++) {
  //   Serial.print(data.ir[i]);
  // }
  // Serial.println();

  // for (uint8_t i = 0; i < 4; i++) {
  //   Serial.print(String("Sensor") + i + ": ");
  //   Serial.println(data.distance[i]);
  // }
  delay(1000);
}
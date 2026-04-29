#pragma once

class Counter {
 public:
  void increment();
  void printToSerial(const char* msg, unsigned int ms);

 private:
  int _count = 0;
  unsigned long prevTime = 0;
};
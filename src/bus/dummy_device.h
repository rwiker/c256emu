#pragma once

#include <cstdint>

class DummyDevice {
 public:
  void StoreByte(uint32_t addr, uint8_t v) {};
  uint8_t ReadByte(uint32_t addr) {return 0;};
};

#include "bus/float_copro.h"

#include <gtest/gtest.h>

#include "cpu.h"

class FloatCoprocessorTest: public ::testing::Test {
protected:
  void SetUp() override {
    bus.SetIo(
        [this](uint32_t addr) -> uint8_t { return copro.ReadByte(addr); },
	[this](uint32_t addr, uint8_t val) { copro.StoreByte(addr, val); },
	0, 0);
  }
  SimpleSystemBus<16> bus;
  FloatCoprocessor copro;
};

uint32_t floatAsUInt32(float v) {
  union {
    uint32_t ui;
    float fp;
  } value;
  value.fp = v;
  return value.ui;
}

float uint32AsFloat(uint32_t v) {
  union {
    uint32_t ui;
    float fp;
  } value;
  value.ui = v;
  return value.fp;
}

uint32_t floatAsFixed(float v) {
  return static_cast<uint32_t>(static_cast<int32_t>(v * 4096));
}

TEST_F(FloatCoprocessorTest, TestRead1FP) {
  bus.WriteByte(FP_MATH_CTRL1, 0x03);
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(1.0));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(1.0));
}

static constexpr float pi = 3.1415928;
static constexpr float e = 2.7182818;

TEST_F(FloatCoprocessorTest, TestMulFp) {
  bus.WriteByte(FP_MATH_CTRL0, 0x00);
  bus.WriteByte(FP_MATH_CTRL1, 0x00);
  bus.PokeU32LE(FP_MATH_INPUT0, floatAsUInt32(pi));
  bus.PokeU32LE(FP_MATH_INPUT1, floatAsUInt32(e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(pi * e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(pi * e));
}

TEST_F(FloatCoprocessorTest, TestDivFp) {
  bus.WriteByte(FP_MATH_CTRL0, 0x00);
  bus.WriteByte(FP_MATH_CTRL1, 0x01);
  bus.PokeU32LE(FP_MATH_INPUT0, floatAsUInt32(pi));
  bus.PokeU32LE(FP_MATH_INPUT1, floatAsUInt32(e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(pi / e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(pi / e));
}

TEST_F(FloatCoprocessorTest, TestAddFp) {
  bus.WriteByte(FP_MATH_CTRL0, 0x48);
  bus.WriteByte(FP_MATH_CTRL1, 0x02);
  bus.PokeU32LE(FP_MATH_INPUT0, floatAsUInt32(pi));
  bus.PokeU32LE(FP_MATH_INPUT1, floatAsUInt32(e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(pi + e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(pi + e));
}

TEST_F(FloatCoprocessorTest, TestSubFp) {
  bus.WriteByte(FP_MATH_CTRL0, 0x40);
  bus.WriteByte(FP_MATH_CTRL1, 0x02);
  bus.PokeU32LE(FP_MATH_INPUT0, floatAsUInt32(pi));
  bus.PokeU32LE(FP_MATH_INPUT1, floatAsUInt32(e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(pi - e));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(pi - e));
}

TEST_F(FloatCoprocessorTest, TestAddFixed) {
  const float pi40 = 125.663;
  bus.WriteByte(FP_MATH_CTRL0, 0x49);
  bus.WriteByte(FP_MATH_CTRL1, 0x02);
  bus.PokeU32LE(FP_MATH_INPUT0, floatAsFixed(pi40));
  bus.PokeU32LE(FP_MATH_INPUT1, floatAsUInt32(0.0));
  // EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(pi40));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(pi40));
}

TEST_F(FloatCoprocessorTest, TestZeroRes) {
  bus.WriteByte(FP_MATH_CTRL0, 0x00);
  bus.WriteByte(FP_MATH_CTRL1, 0x00);
  bus.PokeU32LE(FP_MATH_INPUT0, floatAsUInt32(pi));
  bus.PokeU32LE(FP_MATH_INPUT1, floatAsUInt32(0.0));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FP), floatAsUInt32(0.0));
  EXPECT_EQ(bus.PeekU32LE(FP_MATH_OUTPUT_FIXED), floatAsFixed(0.0));
  EXPECT_EQ(bus.ReadByte(FP_MATH_MULT_STAT) & 0x08, 0x08);
}


#pragma once

#include <cstdint>

constexpr uint32_t FP_MATH_CTRL0 = 0xafe200;
constexpr uint32_t FP_MATH_CTRL1 = 0xafe201;
constexpr uint32_t FP_MATH_CTRL2 = 0xafe202;
constexpr uint32_t FP_MATH_CTRL3 = 0xafe203;
constexpr uint32_t FP_MATH_MULT_STAT = 0xafe204;
constexpr uint32_t FP_MATH_DIV_STAT = 0xafe205;
constexpr uint32_t FP_MATH_ADD_STAT = 0xafe206;
constexpr uint32_t FP_MATH_CONV_STAT = 0xafe207;
constexpr uint32_t FP_MATH_INPUT0 = 0xafe208;
constexpr uint32_t FP_MATH_INPUT1 = 0xafe20c;
constexpr uint32_t FP_MATH_OUTPUT_FP = 0xafe208;
constexpr uint32_t FP_MATH_OUTPUT_FIXED = 0xafe20c;

class FloatCoprocessor {
public:
  FloatCoprocessor();
  void StoreByte(uint32_t addr, uint8_t v);
  uint8_t ReadByte(uint32_t addr);
protected:
  void recompute();
  float readfloat(uint8_t *val, bool isfixed);
  void writefloat(float val, uint8_t* addr, bool isfixed);

  uint8_t input_ctrl_;
  uint8_t output_ctrl_;
  uint8_t input0_[4];
  uint8_t input1_[4];
  uint8_t stat_mult_;
  uint8_t stat_div_;
  uint8_t stat_add_;
  uint8_t stat_conv_;
  uint8_t output_fp_[4];
  uint8_t output_fixed_[4];
  bool dirty_;
};

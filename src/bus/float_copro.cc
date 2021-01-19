#include "float_copro.h"

#include <cmath>

FloatCoprocessor::FloatCoprocessor()
  : dirty_(true), input_ctrl_(0), output_ctrl_(0)
{
  for (size_t i = 0; i < 4; i++) {
    input0_[i] = input1_[i]
      = output_fixed_[i] = output_fp_[i] = 0;
  }
}

void FloatCoprocessor::StoreByte(uint32_t addr, uint8_t v) {
  addr |= 0xaf0000;
  dirty_ = true;
  if (addr == FP_MATH_CTRL0) {
    input_ctrl_ = v;
  }
  else if (addr == FP_MATH_CTRL1) {
    output_ctrl_ = v;
  }
  else if (addr >= FP_MATH_INPUT0 && addr < (FP_MATH_INPUT0 + 4)) {
    input0_[addr - FP_MATH_INPUT0] = v;
  }
  else if (addr >= FP_MATH_INPUT1 && addr < (FP_MATH_INPUT1 + 4)) {
    input1_[addr - FP_MATH_INPUT1] = v;
  }
}

uint8_t FloatCoprocessor::ReadByte(uint32_t addr) {
  addr |= 0xaf0000;
  if (dirty_) {
    recompute();
  }
  if (addr == FP_MATH_CTRL0) {
    return input_ctrl_;
  }
  else if (addr == FP_MATH_CTRL1) {
    return output_ctrl_;
  }
  else if (addr == FP_MATH_MULT_STAT) {
    return stat_mult_;
  }
  else if (addr == FP_MATH_DIV_STAT) {
    return stat_div_;
  }
  else if (addr == FP_MATH_ADD_STAT) {
    return stat_add_;
  }
  else if (addr == FP_MATH_CONV_STAT) {
    return stat_conv_;
  }
  else if (addr >= FP_MATH_OUTPUT_FP && addr < (FP_MATH_OUTPUT_FP + 4)) {
    return output_fp_[addr - FP_MATH_OUTPUT_FP];
  }
  else if (addr >= FP_MATH_OUTPUT_FIXED && addr < (FP_MATH_OUTPUT_FIXED + 4)) {
    return output_fixed_[addr - FP_MATH_OUTPUT_FIXED];
  }
  /* ELSE */
  return 0;
}

float FloatCoprocessor::readfloat(uint8_t *val, bool isfixed) {
  union {
    uint32_t i;
    float fp;
  } value;
  value.i = val[0] | (val[1] << 8) | (val[2] << 16) | (val[3] << 24);
  if (isfixed) {
    return static_cast<float>(static_cast<int32_t>(value.i)) / 4096.0;
  }
  /* ELSE */
  return value.fp;
}

void FloatCoprocessor::writefloat(float val, uint8_t* addr, bool isfixed) {
  union {
    uint32_t i;
    float fp;
  } value;
  if (isfixed) {
    if (val == 0.0) {
      stat_conv_ |= 0x08;
    }
    else if ((val > static_cast<float>((1 << 19) -1)) ||
	(val < static_cast<float>(-(1 << 19)))) {
      stat_conv_ |= 0x2;
    }
    else if ((val > (- 1.0 / 4096.0)) && (val < (1.0 / 4096.0))) {
      stat_conv_ |= 0x04;
    }
    value.i = static_cast<uint32_t>(static_cast<int32_t>(val * 4096.0));
  }
  else {
    value.fp = val;
  }
  addr[0] = value.i & 0xff;
  addr[1] = (value.i >> 8) & 0xff;
  addr[2] = (value.i >> 16) & 0xff;
  addr[3] = (value.i >> 24) & 0xff;
}

uint8_t genstatflags(float value) {
  uint8_t ret = 0;
  if (std::isnan(value)) {
    ret |= 0x01;
  }
  if (std::isinf(value)) {
    ret |= 0x02;
  }
  if (value == 0.0) {
    ret |= 0x08;
  }
  else if (! std::isnormal(value)) {
    ret |= 0x04;
  }
  return ret;
}

void FloatCoprocessor::recompute() {
  float input0, input1, res_mul, res_div, res_add, result;
  stat_mult_ = stat_div_ = stat_add_ = stat_conv_ = 0x00;
  input0 = readfloat(input0_, input_ctrl_ & 0x01);
  input1 = readfloat(input1_, input_ctrl_ & 0x02);
  res_mul = input0 * input1;
  res_div = input0 / input1;
  float adder_inputs[4] = {input0, input1, res_mul, res_div};
  float add0 = adder_inputs[(input_ctrl_ >> 4) & 0x03];
  float add1 = adder_inputs[(input_ctrl_ >> 6) & 0x03];
  if (input_ctrl_ & 0x08) {
    res_add = add0 + add1;
  }
  else {
    res_add = add0 - add1;
  }
  stat_mult_ = genstatflags(res_mul);
  stat_div_ = genstatflags(res_div) | (input1 == 0.0 ? 0x10 : 0x00);
  stat_add_ = genstatflags(res_add);
  float results[4] = {res_mul, res_div, res_add, 1.0};
  result = results[output_ctrl_ & 0x03];
  writefloat(result,output_fixed_, true);
  writefloat(result, output_fp_, false);
  dirty_ = false;
}

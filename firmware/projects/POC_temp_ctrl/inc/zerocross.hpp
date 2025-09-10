/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file zerocross.hpp
 * @brief zero crossing detector class definitions
 */
#ifndef ZEROCROSS_HPP
#define ZEROCROSS_HPP
#include <cstdint>

class ZeroCross {
 public:
  ZeroCross() = default;
  ~ZeroCross() = default;

  void Init() {
    current_ticks = 0;
    zero_crosses = 0;
    zero_cross_count = 0;
    is_ac_power_present = false;
  }

  void Progress(std::uint32_t ticks, std::uint32_t ticks_per_second) {
    if (current_ticks + ticks_per_second < ticks) {
      current_ticks = ticks;
      if (zero_crosses > 95 && zero_crosses < 105)
        is_ac_power_present = true;
      else
        is_ac_power_present = false;
      zero_cross_count = zero_crosses;
      zero_crosses = 0;
    }
  }

  bool Detected() {
    return is_ac_power_present;
  }

  /**
   * @brief We have detected a zero crossing
   */
  void Update() {
    zero_crosses = zero_crosses + 1;
  }
  std::uint32_t zero_cross_count;  // amount of zerocrosses
 private:
  std::uint32_t current_ticks;  // tick count when measured zero crosses
  std::uint32_t zero_crosses;   // amount of zerocrosses detected
  bool is_ac_power_present;     // true if AC power is present
};

#endif
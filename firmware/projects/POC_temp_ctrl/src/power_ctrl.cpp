/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file power_ctrl.cpp
 * @brief Soldering iron power control class implementation
 */
#include "power_ctrl.hpp"

void Power_ctrl::init(void) {
  current_ticks = 0;
  zero_crosses = 0;
  zero_cross_count = 0;
  is_ac_power_present = false;
}

void Power_ctrl::progress(std::uint32_t ticks, std::uint32_t ticks_per_second) {
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

bool Power_ctrl::is_power_present(void) {
  return is_ac_power_present;
}

void Power_ctrl::zero_cross_isr(void) {
  zero_crosses = zero_crosses + 1;
}
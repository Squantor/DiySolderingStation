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
#include <POC_temp_control_nuclone.hpp>

void Power_ctrl::init(void) {
  current_ticks = 0;
  zero_crosses = 0;
  zero_cross_count = 0;
  is_ac_power_present = false;
  demo_value = 0;
  output_error_accumulator = 0;
  output_setting = 0;
  set_safe_state();
}

void Power_ctrl::progress(std::uint32_t ticks, std::uint32_t ticks_per_second) {
  if (current_ticks + ticks_per_second < ticks) {
    current_ticks = ticks;
    if (zero_crosses > 95 && zero_crosses < 105)
      is_ac_power_present = true;
    else {
      is_ac_power_present = false;
      set_safe_state();
    }
    zero_cross_count = zero_crosses;
    zero_crosses = 0;
  }
}

bool Power_ctrl::is_power_present(void) {
  return is_ac_power_present;
}

void Power_ctrl::zero_cross_isr(void) {
  zero_crosses = zero_crosses + 1;
  if (zero_crosses & 1) {
    // we only check every other zerocrossing
    output_error_accumulator = output_error_accumulator + output_setting;
    if (output_error_accumulator >= 50) {
      set_power_control_1(true);
      set_power_control_2(false);
      output_error_accumulator = output_error_accumulator - 100;
    } else {
      set_power_control_1(false);
      set_power_control_2(true);
    }
  }
}

void Power_ctrl::set_safe_state() {
  set_power_control_1(false);
  set_power_control_2(false);
}

void Power_ctrl::set_power(std::size_t channel, std::uint32_t percentage) {
  output_setting = percentage;
}

void Power_ctrl::handle_event(Event_data event) {
  static std::uint32_t second_counter = 0;
  if (event.event == Events::seconds) {
    second_counter++;
    if (second_counter > 0) {
      second_counter = 0;
      if (is_ac_power_present) {
        demo_value += 2;
        if (demo_value > 100) {
          demo_value = 0;
        }
        set_power(0, demo_value);
      } else {
        demo_value = 0;
      }
    }
  }
}
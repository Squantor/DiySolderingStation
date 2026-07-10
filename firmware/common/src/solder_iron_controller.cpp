/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file solder_iron_controller.cpp
 * @brief Definitions for solder iron controller class
 *
 */
#include <solder_iron_controller.hpp>

void Solder_iron_controller::init(void) {
  current_ticks = 0;
  zero_crosses = 0;
  zero_cross_count = 0;
  is_ac_power_present = false;
  set_safe_state();
}

void Solder_iron_controller::progress() {}

bool Solder_iron_controller::is_power_present(void) {
  return is_ac_power_present;
}

void Solder_iron_controller::systick_isr(std::uint32_t current_tick) {
  if (current_ticks + ticks_per_second < current_tick) {
    current_ticks = current_tick;
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

void Solder_iron_controller::zero_cross_isr(void) {
  zero_crosses = zero_crosses + 1;
  if (zero_crosses & 1) {
    // we only check every other zerocrossing
    for (std::size_t i = 0; i < iron_hal.get_iron_count(); i++) {
      output_error_accumulators[i] += output_settings[i];
      if (output_error_accumulators[i] >= 50) {
        iron_hal.set_iron_output(i, true);
        output_error_accumulators[i] -= 100;
      } else {
        iron_hal.set_iron_output(i, false);
      }
    }
  }
}

void Solder_iron_controller::set_safe_state() {
  for (std::size_t i = 0; i < iron_hal.get_iron_count(); i++) {
    output_error_accumulators[i] = 0;
    output_settings[i] = 0;
    iron_hal.set_iron_output(i, false);
  }
}

void Solder_iron_controller::set_power(std::size_t channel, std::uint32_t percentage) {
  output_settings[channel] = percentage;
}

void Solder_iron_controller::handle_event(Event_data event) {
  static std::uint32_t second_counter = 0;
  if (event.event == Events::seconds) {
    second_counter++;
  }
}
/**
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file POC_temp_control_hal.cpp
 * @brief HAL for POC_temp_control_nuclone declaration
 */
#include "POC_temp_control_hal.hpp"
#include "POC_temp_control_nuclone.hpp"

void POC_temp_control_hal::set_iron_output(std::size_t index, bool on_state) {
  if (index < get_iron_count()) {
    if (index == 0) {
      set_power_control_1(on_state);
    } else if (index == 1) {
      set_power_control_2(on_state);
    }
    // could use some kind of assertion if we exceed the value?
  }
}
/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file solder_iron_controller.cpp
 * @brief tests for solder iron controller
 * @copyright Copyright (c) 2026
 *
 */
#include <minunit.h>
#include <solder_iron_hal_if.hpp>
#include <solder_iron_controller.hpp>

namespace {

struct Solder_iron_hal_mock : public Solder_iron_hal_base {
  /**
   * @brief Initialize the solder iron controller mock
   *
   */
  void init(void) {
    set_iron_output_on_count.fill(0);
    set_iron_output_off_count.fill(0);
  }
  std::size_t get_iron_count(void) override {
    return 4;
  }

  void set_iron_output(std::size_t index, bool on_state) override {
    if (on_state) {
      set_iron_output_on_count[index]++;
    } else {
      set_iron_output_off_count[index]++;
    }
  }
  std::array<std::uint8_t, 4> set_iron_output_on_count;
  std::array<std::uint8_t, 4> set_iron_output_off_count;
};

Solder_iron_hal_mock solder_iron_hal_mock;
Solder_iron_controller solder_iron_controller_dut(solder_iron_hal_mock);

}  // namespace
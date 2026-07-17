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
  std::size_t get_iron_count(void) final {
    return 4;
  }

  void set_iron_output(std::size_t index, bool on_state) final {
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

MINUNIT_SETUP(solderIronControllerSetup) {
  solder_iron_hal_mock.init();
  solder_iron_controller_dut.init();
  MINUNIT_PASS();
}

MINUNIT_ADD(solder_iron_controller_init, solderIronControllerSetup, nullptr) {
  for (auto &element : solder_iron_hal_mock.set_iron_output_on_count) {
    MINUNIT_CHECK(element == 0);
  }
  for (auto &element : solder_iron_hal_mock.set_iron_output_off_count) {
    MINUNIT_CHECK(element == 1);
  }
}

//! @todo test for power on detection with 200 zerocrosses

MINUNIT_ADD(solder_iron_controller_power_control, solderIronControllerSetup, nullptr) {
  solder_iron_controller_dut.set_power(0, 0);
  solder_iron_controller_dut.set_power(1, 1);
  solder_iron_controller_dut.set_power(2, 50);
  solder_iron_controller_dut.set_power(3, 99);
  for (int i = 0; i < 200; i++)
    solder_iron_controller_dut.zero_cross_isr();
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_on_count[0] == 0);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_on_count[1] == 1);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_on_count[2] == 50);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_on_count[3] == 99);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_off_count[0] == 101);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_off_count[1] == 100);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_off_count[2] == 51);
  MINUNIT_CHECK(solder_iron_hal_mock.set_iron_output_off_count[3] == 2);
}

}  // namespace
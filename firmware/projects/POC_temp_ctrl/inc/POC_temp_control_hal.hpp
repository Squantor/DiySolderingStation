/**
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file POC_temp_control_hal.cpp
 * @brief HAL for POC_temp_control_nuclone definition
 */
#ifndef POC_TEMP_CONTROL_HAL_HPP
#define POC_TEMP_CONTROL_HAL_HPP

#include <solder_iron_hal_if.hpp>

class POC_temp_control_hal : public Solder_iron_hal_base {
 public:
  POC_temp_control_hal(std::size_t count) : iron_count(count) {}

  std::size_t get_iron_count(void) final {
    return iron_count;
  }

  void set_iron_output(std::size_t index, bool on_state) final;

 private:
  std::size_t iron_count;
};

#endif
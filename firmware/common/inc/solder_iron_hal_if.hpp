/**
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file solder_iron_hal_if.hpp
 * @brief solder iron hal interface class declaration
 */
#ifndef SOLDER_IRON_HAL_IF_HPP
#define SOLDER_IRON_HAL_IF_HPP

#include <cstdint>

/**
 * @brief solder iron hal base class
 * You will never copy/move a Solder_iron_hal, they are "eternal" with respect to program lifetime
 */
struct Solder_iron_hal_base {
  Solder_iron_hal_base() = default;
  ~Solder_iron_hal_base() = default;
  Solder_iron_hal_base(const Solder_iron_hal_base&) = delete;
  Solder_iron_hal_base& operator=(const Solder_iron_hal_base&) = delete;
  Solder_iron_hal_base(Solder_iron_hal_base&&) = delete;
  Solder_iron_hal_base& operator=(Solder_iron_hal_base&&) = delete;
  /**
   * @brief Get the amount of irons connected to the solder iron controller
   */
  virtual std::size_t get_iron_count(void) = 0;
  /**
   * @brief Set the iron output state
   * @param index Which iron to turn on/off
   * @param on_state true for on, false for off
   */
  virtual void set_iron_output(std::size_t index, bool on_state) = 0;
};

#endif
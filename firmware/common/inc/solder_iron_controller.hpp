/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file solder_iron_controller.cpp
 * @brief Definitions for solder iron controller class
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SOLDER_IRON_CONTROLLER_HPP
#define SOLDER_IRON_CONTROLLER_HPP

#include <cstdint>
#include <array>
#include "event_handler.hpp"
#include <solder_iron_hal_if.hpp>

namespace detail {
struct Power_state {
  std::uint8_t power_setting_percentage;
  volatile std::int8_t power_error_percentage;
};
}  // namespace detail

/**
 * @brief Soldering iron power control
 *
 */
class Solder_iron_controller : public Event_handler {
 public:
  /**
   * @brief Construct a new Power_ctrl object
   */
  Solder_iron_controller(Solder_iron_hal_base &hal) : iron_hal(hal) {}
  /**
   * @brief Initializes power control
   */
  void init(void);
  /**
   * @brief Updates power control
   * @param ticks
   * @param ticks_per_second
   */
  void progress(std::uint32_t ticks, std::uint32_t ticks_per_second);
  /**
   * @brief Is power present
   * @return True for power is present
   */
  bool is_power_present(void);
  /**
   * @brief Call from zerocross interrupt
   */
  void zero_cross_isr(void);
  /**
   * @brief Set power control to safe state
   */
  void set_safe_state(void);
  /**
   * @brief Event handler, sensitive to seconds
   * @param event event to handle, second elapsed event is expected
   */
  void handle_event(Event_data event) override final;

  void set_power(std::size_t channel, std::uint32_t percentage);

  std::uint32_t get_power(std::size_t channel);

  volatile std::uint32_t zero_cross_count;  // amount of zerocrosses
 private:
  std::uint32_t current_ticks;          // tick count when measured zero crosses
  volatile std::uint32_t zero_crosses;  // amount of zerocrosses detected
  bool is_ac_power_present;             // true if AC power is present
  std::uint8_t demo_value;
  Solder_iron_hal_base &iron_hal;
  std::array<std::uint8_t, 4> output_settings;
  std::array<std::int16_t, 4> output_error_accumulators;
};

#endif
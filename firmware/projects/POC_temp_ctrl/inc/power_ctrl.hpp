/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file power_ctrl.hpp
 * @brief Soldering iron power control class definition
 */
#ifndef POWER_CTRL_HPP
#define POWER_CTRL_HPP

#include <cstdint>
#include <array>
#include "event_handler.hpp"

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
class Power_ctrl : public Event_handler {
 public:
  /**
   * @brief Construct a new Power_ctrl object
   */
  Power_ctrl() = default;
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
  volatile std::int8_t output_error_accumulator;
  std::int8_t output_setting;
};

#endif
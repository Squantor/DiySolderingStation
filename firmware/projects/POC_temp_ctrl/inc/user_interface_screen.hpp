/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface_screen.hpp
 * @brief Embedded user interface screen class definition
 *
 */
#ifndef USER_INTERFACE_SCREEN_HPP
#define USER_INTERFACE_SCREEN_HPP

#include "user_interface_actions.hpp"

template <typename User_interface_events>
struct User_interface_screen {
  /**
   * @brief Handles button events, only called when screen is active
   */
  [[nodiscard]] virtual User_interface_actions handle_event(User_interface_events) = 0;
  /**
   * @brief Activates the screen
   */
  virtual void activate() = 0;
  /**
   * @brief Deactivates the screen
   */
  virtual void deactivate() = 0;
  /**
   * @brief Get what action the user interface should
   * @return User_interface_action
   */
};

#endif
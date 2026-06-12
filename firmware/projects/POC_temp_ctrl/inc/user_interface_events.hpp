/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface_events.hpp
 * @brief Embedded user interface event enum definition
 *
 */
#ifndef USER_INTERFACE_EVENTS_HPP
#define USER_INTERFACE_EVENTS_HPP

enum class User_interface_events {
  none,                 /*!< No event */
  enter_button_pressed, /*!< Enter button pressed */
  left_button_pressed,  /*!< Left button pressed */
  right_button_pressed, /*!< Right button pressed */
};

#endif
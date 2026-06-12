/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface_actions.hpp
 * @brief Embedded user interface action enum definition
 *
 */
#ifndef USER_INTERFACE_ACTIONS_HPP
#define USER_INTERFACE_ACTIONS_HPP

enum class User_interface_actions {
  none,            /*!< No action needed */
  next_screen,     /*!< Switch to next screen */
  previous_screen, /*!< Switch to previous screen */
};

#endif
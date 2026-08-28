/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file events.hpp
 * @brief Event handler definitions
 */
#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <cstdint>

/** @brief Possible events
 */
enum class Events : std::uint8_t {
  none,    /*!< No event */
  button,  /*!< Button event */
  seconds, /*!< Second event */
};

enum class Button : std::uint8_t {
  down_0, /*!< Button 0 down */
  up_0,   /*!< Button 0 up */
  down_1, /*!< Button 1 down */
  up_1,   /*!< Button 1 up */
  down_2, /*!< Button 2 down */
  up_2,   /*!< Button 2 up */
  down_3, /*!< Button 3 down */
  up_3,   /*!< Button 3 up */
  down_4, /*!< Button 4 down */
  up_4,   /*!< Button 4 up */
};

struct Event_data {
  Events event;
  union {
    Button button;
    std::uint32_t seconds;
  };
};

#endif
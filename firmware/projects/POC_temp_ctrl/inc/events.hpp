/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file events.hpp
 * Event handler definitions
 */
#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <cstdint>

/** @brief Possible events
 */
enum class Events : uint8_t {
  None,   /*!< No event */
  Button, /*!< Button event */
};

enum class Button : uint8_t {
  Button0Down, /*!< Button 0 down */
  Button0Up,   /*!< Button 0 up */
  Button1Down, /*!< Button 1 down */
  Button1Up,   /*!< Button 1 up */
  Button2Down, /*!< Button 2 down */
  Button2Up,   /*!< Button 2 up */
  Button3Down, /*!< Button 3 down */
  Button3Up,   /*!< Button 3 up */
  Button4Down, /*!< Button 4 down */
  Button4Up,   /*!< Button 4 up */
};

struct EventData {
  Events event;
  union {
    Button button;
  };
};

#endif
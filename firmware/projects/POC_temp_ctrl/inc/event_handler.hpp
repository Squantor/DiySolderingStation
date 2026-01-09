/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file event_handler.hpp
 * Event handler definitions
 */
#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "events.hpp"

struct EventHandler {
  virtual void HandleEvent(EventData event) = 0;
};

#endif
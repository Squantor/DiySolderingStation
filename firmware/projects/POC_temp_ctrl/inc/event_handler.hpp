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

struct Event_handler {
  virtual void handle_event(Event_data event) = 0;
};

#endif
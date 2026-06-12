/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file button_handler.hpp
 * Button handler class
 */
#ifndef BUTTON_HANDLER_HPP
#define BUTTON_HANDLER_HPP

#include "event_handler.hpp"
#include "application.hpp"

namespace application {
class Button_handler : public Event_handler {
 public:
  void handle_event(Event_data event);
};

}  // namespace application

#endif
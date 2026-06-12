/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file buttons.hpp
 * Translation class from buttons to events
 */
#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include "event_dispatch.hpp"
#include "events.hpp"
#include "application.hpp"

class Buttons {
 public:
  Buttons(std::uint8_t default_pin_state, Event_dispatcher& dispatcher)
    : pin_state(default_pin_state), event_dispatcher(dispatcher) {}

  void set_port_data(std::uint8_t data) {
    std::uint8_t changed = data ^ pin_state;
    if ((changed & 0x01) != 0) {
      if (data & 0x01) {
        event_dispatcher.post_event(Event_data{Events::button, Button::up_0});
      } else {
        event_dispatcher.post_event(Event_data{Events::button, Button::down_0});
      }
    }
    if ((changed & 0x02) != 0) {
      if (data & 0x02) {
        event_dispatcher.post_event(Event_data{Events::button, Button::up_1});
      } else {
        event_dispatcher.post_event(Event_data{Events::button, Button::down_1});
      }
    }
    if ((changed & 0x04) != 0) {
      if (data & 0x04) {
        event_dispatcher.post_event(Event_data{Events::button, Button::up_2});
      } else {
        event_dispatcher.post_event(Event_data{Events::button, Button::down_2});
      }
    }
    if ((changed & 0x08) != 0) {
      if (data & 0x08) {
        event_dispatcher.post_event(Event_data{Events::button, Button::up_3});
      } else {
        event_dispatcher.post_event(Event_data{Events::button, Button::down_3});
      }
    }
    if ((changed & 0x10) != 0) {
      if (data & 0x10) {
        event_dispatcher.post_event(Event_data{Events::button, Button::up_4});
      } else {
        event_dispatcher.post_event(Event_data{Events::button, Button::down_4});
      }
    }
    // update internal state
    pin_state = data;
  }

 private:
  std::uint8_t pin_state;
  Event_dispatcher& event_dispatcher;
};

#endif
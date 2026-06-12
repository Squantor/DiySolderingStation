/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface.hpp
 * @brief Embedded user interface library interface
 *
 */
#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <span>
#include <cstdio>
#include <cstdint>
#include "event_dispatch.hpp"
#include "user_interface_screen.hpp"
#include "user_interface_actions.hpp"
#include "user_interface_events.hpp"

template <typename Button_enum, typename User_interface_event_enum>
struct User_interface : public Event_handler {
  User_interface(std::span<User_interface_screen<User_interface_events>*> application_screens)
    : current_screen_index(0), screens(application_screens) {}

  void init() {
    screens[current_screen_index]->activate();
  }

  void handle_event(Event_data event) override final {
    User_interface_event_enum interface_event = User_interface_events::none;
    if (event.event == Events::button) {
      switch (event.button) {
        case Button_enum::down_0:
          interface_event = User_interface_events::left_button_pressed;
          break;
        case Button_enum::down_1:
          interface_event = User_interface_events::enter_button_pressed;
          break;
        case Button_enum::down_2:
          interface_event = User_interface_events::right_button_pressed;
          break;
        default:
          break;
      }
    } else {
      return;
    }

    User_interface_actions action = screens[current_screen_index]->handle_event(interface_event);
    if (action == User_interface_actions::previous_screen) {
      screens[current_screen_index]->deactivate();
      if (current_screen_index > 0) {
        current_screen_index--;
      } else {
        current_screen_index = screens.size() - 1;
      }
      screens[current_screen_index]->activate();
    } else if (action == User_interface_actions::next_screen) {
      screens[current_screen_index]->deactivate();
      if ((current_screen_index + 1) < screens.size()) {
        current_screen_index++;
      } else {
        current_screen_index = 0;
      }
      screens[current_screen_index]->activate();
    }
  }

 private:
  std::size_t current_screen_index;
  std::span<User_interface_screen<User_interface_events>*> screens;
};

#endif
/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file screen_second.hpp
 * @brief Secondary screen definition
 *
 */
#ifndef SCREEN_SECOND_HPP
#define SCREEN_SECOND_HPP

#include "event_handler.hpp"
#include "user_interface_events.hpp"
#include "user_interface.hpp"
#include "mid/gfx_display.hpp"
#include "application_font.hpp"

template <auto &display>
class Second_screen : public User_interface_screen<User_interface_events>, public Event_handler {
 public:
  Second_screen() : entry_count(0), event_count(0), enter_count(0) {}

  User_interface_actions handle_event(User_interface_events event) override final {
    User_interface_actions action = User_interface_actions::none;

    switch (event) {
      case User_interface_events::enter_button_pressed:
        enter_count++;
        break;
      case User_interface_events::left_button_pressed:
        action = User_interface_actions::previous_screen;
        break;
      case User_interface_events::right_button_pressed:
        action = User_interface_actions::next_screen;
        break;
      default:
        break;
    }
    render();
    return action;
  }
  void activate() override final {
    is_active = true;
    entry_count++;
    render();
  }
  void deactivate() override final {
    is_active = false;
  }
  void handle_event(Event_data event) {
    (void)event;
    render();
  }

 private:
  void render() {
    if (is_active) {
      libmcumid::Dec dec_enter_count{static_cast<std::int32_t>(enter_count)};
      display.clear();
      display.print("Second screen.\nIn tha house!\n", application_font);
      display.print("Enter count: ", application_font);
      display.print(dec_enter_count, application_font);
      display.print("\n", application_font);
      display.flip();
    }
  }
  std::size_t entry_count;
  std::size_t event_count;
  std::size_t enter_count;
  bool is_active;
};

#endif
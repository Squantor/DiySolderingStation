/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file screen_main.hpp
 * @brief Main screen definition
 *
 */
#ifndef SCREEN_MAIN_HPP
#define SCREEN_MAIN_HPP

#include "user_interface_events.hpp"
#include "event_handler.hpp"
#include "user_interface.hpp"
#include "mid/gfx_display.hpp"
#include "application_font.hpp"
#include "POC_temp_control_nuclone.hpp"
#include "solder_iron_controller.hpp"

template <auto &display>
class Main_screen : public User_interface_screen<User_interface_events>, public Event_handler {
 public:
  Main_screen(Solder_iron_controller &controller) : solder_iron_controller(controller) {}
  User_interface_actions handle_event(User_interface_events event) final {
    User_interface_actions action = User_interface_actions::none;
    switch (event) {
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
  void activate() final {
    is_active = true;
    render();
  }
  void deactivate() final {
    is_active = false;
  }
  void handle_event(Event_data event) {
    switch (event.event) {
      case Events::seconds:
        break;

      default:
        break;
    }
    render();
  }

 private:
  void render() {
    if (is_active) {
      libmcumid::Dec power_one{static_cast<std::int32_t>(solder_iron_controller.get_power(0))};
      libmcumid::Dec power_two{static_cast<std::int32_t>(solder_iron_controller.get_power(1))};
      display.clear();
      display.print("Power 1: ", application_font);
      display.print(power_one, application_font);
      display.print("\n", application_font);
      display.print("Power 2: ", application_font);
      display.print(power_two, application_font);
      display.print("\n", application_font);
      display.flip();
    }
  }
  bool is_active;
  Solder_iron_controller &solder_iron_controller;
};

#endif
/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */

#include <application.hpp>
#include <cmdline_simple.hpp>
#include <console.hpp>
#include <event_dispatch.hpp>
#include <button_handler.hpp>
#include <buttons.hpp>
#include <user_interface.hpp>
#include <screen_main.hpp>
#include <screen_menu.hpp>
#include <menu_item.hpp>
#include <menu_item_value_dummy.hpp>
#include <menu_item_exit.hpp>
#include <menu_item_contrast.hpp>
#include <menu_item_power_out.hpp>
#include <solder_iron_controller.hpp>
#include <POC_temp_control_hal.hpp>

namespace application {

// Commandline definitions
squLib::console<usart_peripheral> command_console;
squLib::Command_value_stack<8, command_console> command_values;
squLib::Command_interpreter<command_handlers, command_values, command_console> command_interpreter;
squLib::commandlineSimple<80, command_console, command_interpreter> commandline;

POC_temp_control_hal iron_hal(4);
Solder_iron_controller solder_iron_controller(iron_hal, ticks_per_second);

// User interface definitions
Menu_item_contrast contrast_menu_item;
Menu_item_power_out power_out_first_menu_item(0);
Menu_item_power_out power_out_second_menu_item(1);
Menu_item_exit exit_menu;

std::array<Menu_item* const, 4> menu_items = {&contrast_menu_item, &power_out_first_menu_item, &power_out_second_menu_item,
                                              &exit_menu};

Main_screen<application_display> main_screen(solder_iron_controller);
Menu_screen<application_display> menu_screen(menu_items);

std::array<User_interface_screen<User_interface_events>*, 2> screens = {&main_screen, &menu_screen};
User_interface<Button, User_interface_events> user_interface{screens};

// event handling definitions
Buttons buttons{0xFF, event_dispatcher};
Button_handler button_handler;
std::array<const Event_handler_pair, 4> event_handlers = {
  Event_handler_pair{&button_handler, Events::button},
  Event_handler_pair{&user_interface, Events::button},
  Event_handler_pair{&main_screen, Events::seconds},
  Event_handler_pair{&solder_iron_controller, Events::seconds},
};
Event_dispatcher event_dispatcher(event_handlers);

auto button_call_lambda = [](std::uint8_t port_data) {
  buttons.set_port_data(port_data);
};

Results Application::init() {
  command_console.print("DIY soldering station POC temperature sensing\n");
  ui_port_expander.RegisterCallback(button_call_lambda);
  solder_iron_controller.init();
  while (eeprom_24xxx.state != libmcu::States::Idle) {
    board_progress();
  }
  // settings init
  // eeprom_24xxx.test();
  // before we initialize display we need to make sure the screen is properly setup
  while (ui_display.state != libmcu::States::Idle) {
    board_progress();
  }
  user_interface.init();
  return Results::no_error;
}

Results Application::progress() {
  // second event generator
  static std::uint32_t current_ticks = ticks;
  if (current_ticks + ticks_per_second < ticks) {
    event_dispatcher.post_event(Event_data{.event = Events::seconds, .seconds = ticks / ticks_per_second});
    current_ticks = ticks;
  }
  // commandline handling
  if (usart_peripheral.GetReceiveLevel() > 0) {
    static std::array<char, 1> data;
    usart_peripheral.Receive(data);
    commandline.input(data);
  }
  // zerocrossing detection
  solder_iron_controller.progress();
  // state handling
  switch (state) {
    case Application_state::usb_powered:
      if (is_mains_present() && solder_iron_controller.is_power_present())
        state = Application_state::ready;
      break;
    case Application_state::ready:
      if (!is_mains_present() || !solder_iron_controller.is_power_present())
        set_usb_powered_state();
      break;
    case Application_state::operating:
      if (!is_mains_present() || !solder_iron_controller.is_power_present())
        set_usb_powered_state();
      break;
    case Application_state::error:
      break;

    default:
      command_console.print("Unknown state!!!");
      return Results::error;
      break;
  }
  event_dispatcher.process();
  return Results::no_error;
}

void Application::set_usb_powered_state() {
  set_safe_usb_powered();
  state = Application_state::usb_powered;
}
}  // namespace application

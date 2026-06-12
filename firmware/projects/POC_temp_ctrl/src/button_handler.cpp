/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file button_handler.cpp
 * Button handler class implementation
 */

#include "button_handler.hpp"
#include "application.hpp"

namespace application {

void Button_handler::handle_event(Event_data event) {
  if (event.event != Events::button)
    return;
  switch (event.button) {
    case Button::down_0:
      command_console.print("Button 0 down\n");
      break;
    case Button::up_0:
      command_console.print("Button 0 up\n");
      break;
    case Button::down_1:
      command_console.print("Button 1 down\n");
      break;
    case Button::up_1:
      command_console.print("Button 1 up\n");
      break;
    case Button::down_2:
      command_console.print("Button 2 down\n");
      break;
    case Button::up_2:
      command_console.print("Button 2 up\n");
      break;
    case Button::down_3:
      command_console.print("Button 3 down\n");
      break;
    case Button::up_3:
      command_console.print("Button 3 up\n");
      break;
    case Button::down_4:
      command_console.print("Button 4 down\n");
      break;
    case Button::up_4:
      command_console.print("Button 4 up\n");
      break;
  }
}

}  // namespace application
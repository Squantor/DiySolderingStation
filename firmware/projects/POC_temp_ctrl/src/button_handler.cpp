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

void ButtonHandler::HandleEvent(EventData event) {
  if (event.event != Events::Button)
    return;
  switch (event.button) {
    case Button::Button0Down:
      command_console.print("Button 0 down\n");
      break;
    case Button::Button0Up:
      command_console.print("Button 0 up\n");
      break;
    case Button::Button1Down:
      command_console.print("Button 1 down\n");
      break;
    case Button::Button1Up:
      command_console.print("Button 1 up\n");
      break;
    case Button::Button2Down:
      command_console.print("Button 2 down\n");
      break;
    case Button::Button2Up:
      command_console.print("Button 2 up\n");
      break;
    case Button::Button3Down:
      command_console.print("Button 3 down\n");
      break;
    case Button::Button3Up:
      command_console.print("Button 3 up\n");
      break;
    case Button::Button4Down:
      command_console.print("Button 4 down\n");
      break;
    case Button::Button4Up:
      command_console.print("Button 4 up\n");
      break;
  }
}

}  // namespace application
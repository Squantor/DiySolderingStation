/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_stat.cpp
 * @brief command handler for printing application state
 */
#include <commands.hpp>
#include <application.hpp>

namespace application {

squLib::results stat(std::span<const char>) {
  switch (controller.get_state()) {
    case Application_state::usb_powered:
      command_console.print("Powered only by USB\n");
      break;

    case Application_state::ready:
      command_console.print("System fully operational\n");
      break;

    case Application_state::operating:
      command_console.print("Power stage is operating\n");
      break;

    case Application_state::error:
      command_console.print("We are in an error state\n");
      break;

    default:
      command_console.print("Unknown state!\n");
      break;
  }
  return squLib::results::ok;
}

squLib::Command_handler stat_handler{"stat", "prints the current application state\n", stat};

}  // namespace application
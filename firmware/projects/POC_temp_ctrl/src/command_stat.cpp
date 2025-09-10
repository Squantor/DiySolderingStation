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

squLib::results stat(std::span<const char> commandLine) {
  (void)commandLine;
  switch (controller.GetState()) {
    case ApplicationState::usbPowered:
      command_console.print("Powered only by USB\n");
      break;

    case ApplicationState::ready:
      command_console.print("System fully operational\n");
      break;

    case ApplicationState::operating:
      command_console.print("Power stage is operating\n");
      break;

    case ApplicationState::error:
      command_console.print("We are in an error state\n");
      break;

    default:
      command_console.print("Unknown state!\n");
      break;
  }
  return squLib::results::ok;
}

squLib::commandHandler statHandler{"stat", "prints the current application state\n", stat};

}  // namespace application
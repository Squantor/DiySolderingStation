/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command handlers definitions
 * @brief central gathering spot for all command handlers
 */
#include <commands.hpp>
#include <application.hpp>
#include <print.hpp>

namespace application {

squLib::results stat(std::span<const char> commandLine) {
  (void)commandLine;
  switch (controller.getState()) {
    case applicationState::usbPowered:
      Print("Powered only by USB\n");
      break;

    case applicationState::ready:
      Print("System fully operational\n");
      break;

    case applicationState::standby:
      Print("One or more irons is in standby\n");
      break;

    case applicationState::operational:
      Print("One iron is being heated\n");
      break;

    default:
      Print("Unknown state!\n");
      break;
  }
  return squLib::results::ok;
}

squLib::commandHandler statHandler{"stat", "Prints the current application state\n", stat};

}  // namespace application
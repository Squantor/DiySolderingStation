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

namespace application {

squLib::results Disp(std::span<const char> commandLine) {
  (void)commandLine;
  // commandConsole.print("Your command interpreter works perfectly!\n");
  return squLib::results::ok;
}

squLib::commandHandler disp_handler{"disp", "Does something with the display\n", Disp};

}  // namespace application
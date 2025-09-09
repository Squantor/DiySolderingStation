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

squLib::results drop(std::span<const char> commandLine);

squLib::commandHandler dropHandler{"drop", "Drops top of stack\n", drop};

squLib::results drop(std::span<const char> commandLine) {
  (void)commandLine;
  if (command_values.size() == 0) {
    command_console.print("Stack is empty\n");
    return squLib::results::error;
  }
  command_values.drop();
  command_console.print("\n");
  return squLib::results::ok;
}

}  // namespace application
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
  if (commandValues.size() == 0) {
    commandConsole.print("Stack is empty\n");
    return squLib::results::error;
  }
  commandValues.drop();
  commandConsole.print("\n");
  return squLib::results::ok;
}

}  // namespace application
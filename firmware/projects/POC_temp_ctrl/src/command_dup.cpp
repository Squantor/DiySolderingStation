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

squLib::results dup(std::span<const char> commandLine);

squLib::commandHandler dupHandler{"dup", "Duplicates top of the stack\n", dup};

squLib::results dup(std::span<const char> commandLine) {
  (void)commandLine;
  if (command_values.size() == 0) {
    command_console.print("Stack is empty\n");
    return squLib::results::error;
  }
  command_values.dup();
  command_console.print("\n");
  return squLib::results::ok;
}

}  // namespace application
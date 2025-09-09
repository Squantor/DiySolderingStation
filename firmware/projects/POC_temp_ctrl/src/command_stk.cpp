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

squLib::results printStack(std::span<const char> commandLine);

squLib::commandHandler stkHandler{"stk", "Prints stack values\n", printStack};

squLib::results printStack(std::span<const char> commandLine) {
  (void)commandLine;
  if (command_values.size() == 0)
    command_console.print("Stack is empty\n");
  for (std::size_t i = 0; i < command_values.topOfStack; i++) {
    std::int32_t value{command_values.valueStack[i]};
    command_console.print("Index : ", i, " value : ", squLib::Dec{value}, "\n");
  }
  return squLib::results::ok;
}

}  // namespace application
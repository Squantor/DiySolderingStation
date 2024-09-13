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
#include <command_stk.hpp>
#include <application.hpp>
#include <print.hpp>

namespace application {

squLib::results printStack(std::span<const char> commandLine);

squLib::commandHandler stkHandler{"stk", "Prints stack values\n", printStack};

squLib::results printStack(std::span<const char> commandLine) {
  (void)commandLine;
  if (commandValues.size() == 0)
    Print("Stack is empty\n");
  std::size_t maxIndex = commandValues.valueStack.level();
  for (std::size_t i = 0; i < maxIndex; i++) {
    std::int32_t value;
    commandValues.valueStack.popBack(value);
    Print("Index : ", i, " value : ", value, "\n");
    commandValues.valueStack.pushFront(value);
  }
  return squLib::results::ok;
}

}  // namespace application
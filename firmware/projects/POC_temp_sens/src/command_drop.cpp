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
#include <command_empty.hpp>
#include <application.hpp>
#include <print.hpp>

namespace application {

squLib::results drop(std::span<const char> commandLine);

squLib::commandHandler dropHandler{"drop", "Drops top of stack\n", drop};

squLib::results drop(std::span<const char> commandLine) {
  (void)commandLine;
  if (commandValues.size() == 0) {
    Print("Stack is empty\n");
    return squLib::results::error;
  }
  commandValues.drop();
  Print("\n");
  return squLib::results::ok;
}

}  // namespace application
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

squLib::results empty(std::span<const char> commandLine);

squLib::commandHandler emptyHandler{"empty", "Does nothing\n", empty};

squLib::results empty(std::span<const char> commandLine) {
  (void)commandLine;
  Print("Your command interpreter works perfectly!\n");
  return squLib::results::ok;
}

}  // namespace application
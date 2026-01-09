/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_button.cpp
 * @brief Command that simulates button presses
 */
#include <commands.hpp>
#include <application.hpp>

namespace application {

squLib::results button(std::span<const char> commandLine) {
  (void)commandLine;
  if (command_values.size() != 1) {
    command_console.print("Need one element on stack, element is button press index\n");
    return squLib::results::error;
  }

  return squLib::results::ok;
}

squLib::commandHandler button_handler{"button", "Simulates button press\n", button};

}  // namespace application
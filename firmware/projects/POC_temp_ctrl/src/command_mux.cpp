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

squLib::results mux(std::span<const char> commandLine);

squLib::commandHandler muxHandler{"mux", "Sets up the multiplexer, needs 2 stack elements and power needs to be present\n", mux};

squLib::results mux(std::span<const char> commandLine) {
  (void)commandLine;
  if (commandValues.size() < 2) {
    commandConsole.print("Insufficient elments on the operand stack\n");
    return squLib::results::error;
  }
  if (controller.getState() == applicationState::usbPowered) {
    commandConsole.print("cant switch when running on USB power\n");
    return squLib::results::error;
  }
  std::uint32_t value1 = commandValues.pop().value_or(0);
  std::uint32_t value2 = commandValues.pop().value_or(0);
  SetMultiplexers(value1, value2);
  return squLib::results::ok;
}

}  // namespace application
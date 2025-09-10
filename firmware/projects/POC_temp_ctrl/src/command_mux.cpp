/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_mux.cpp
 * @brief command handler for setting up the multiplexer
 */
#include <commands.hpp>
#include <application.hpp>

namespace application {

squLib::results mux(std::span<const char> commandLine);

squLib::commandHandler muxHandler{"mux", "Sets up the multiplexer, needs 2 stack elements and power needs to be present\n", mux};

squLib::results mux(std::span<const char> commandLine) {
  (void)commandLine;
  if (command_values.size() < 2) {
    command_console.print("Insufficient elments on the operand stack\n");
    return squLib::results::error;
  }
  if (controller.GetState() == ApplicationState::usbPowered) {
    command_console.print("cant switch when running on USB power\n");
    return squLib::results::error;
  }
  std::uint32_t value1 = command_values.pop().value_or(0);
  std::uint32_t value2 = command_values.pop().value_or(0);
  SetMultiplexers(value1, value2);
  return squLib::results::ok;
}

}  // namespace application
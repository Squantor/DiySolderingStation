/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */
#include <POC_temp_sense_nuclone.hpp>
#include <application.hpp>
#include <print.hpp>
#include <cmdline_simple.hpp>

class commandHandle {
 public:
  commandHandle() {}
  void handle(std::span<const char> input) {
    Print("command: ", input, "\n");
  }
};

commandHandle commandHandler;

squLib::commandlineSimple<80, usartPeripheral, commandHandler> commandline;

namespace application {
void application::init() {}
void application::progress() {
  static std::uint32_t currentTicks = ticks;
  if (currentTicks + 100 < ticks) {
    // Print("test:\t", currentTicks, "\t", print::Hex{currentTicks}, "\n");
    currentTicks = ticks;
  }
  // echo characters
  if (usartPeripheral.receiveDataAvailable() > 0) {
    static std::array<char, 1> data;
    usartPeripheral.read(data);
    commandline.input(data);
  }
}
}  // namespace application

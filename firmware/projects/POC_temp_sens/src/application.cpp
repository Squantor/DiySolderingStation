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
#include <command_interpreter.hpp>

squLib::result helpFunction(std::span<const char> commandLine);

squLib::commandHandler helpHandler{"help", "Prints out all help commands\n", helpFunction};

std::array<squLib::commandHandler, 1> commandHandlerTable{helpHandler};
std::span<const squLib::commandHandler> commandHandlers{commandHandlerTable};

squLib::commandInterpreter<commandHandlers, usartPeripheral> commandInterpreter;
squLib::commandlineSimple<80, usartPeripheral, commandInterpreter> commandline;

squLib::result helpFunction(std::span<const char> commandLine) {
  (void)commandLine;
  commandInterpreter.printHelp();
  return squLib::result::ok;
}

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

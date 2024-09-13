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
#include <command_handlers.hpp>
#include <application.hpp>

namespace application {

squLib::results helpFunction(std::span<const char> commandLine);

squLib::commandHandler helpHandler{"help", "Prints out all help commands\n", helpFunction};

squLib::results helpFunction(std::span<const char> commandLine) {
  (void)commandLine;
  commandInterpreter.printHelp();
  return squLib::results::ok;
}

std::array<squLib::commandHandler, 1> commandHandlerTable{helpHandler};
std::span<const squLib::commandHandler> commandHandlers{commandHandlerTable};

}
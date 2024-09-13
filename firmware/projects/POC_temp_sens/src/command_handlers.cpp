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
#include <command_stk.hpp>
#include <command_empty.hpp>
#include <command_drop.hpp>
#include <command_dup.hpp>

namespace application {

squLib::results helpFunction(std::span<const char> commandLine);

squLib::commandHandler helpHandler{"help", "Prints out all help commands\n", helpFunction};

squLib::results helpFunction(std::span<const char> commandLine) {
  (void)commandLine;
  commandInterpreter.printHelp();
  return squLib::results::ok;
}

std::array<squLib::commandHandler, 5> commandHandlerTable{helpHandler, stkHandler, emptyHandler, dropHandler, dupHandler};
std::span<const squLib::commandHandler> commandHandlers{commandHandlerTable};

}
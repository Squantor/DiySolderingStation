/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command handler class
 * @brief class for implementing a command handler
 */
#ifndef COMMAND_INTERPRETER_HPP
#define COMMAND_INTERPRETER_HPP

#include <span>
#include <cctype>
#include <cstdint>
#include <results.hpp>
#include <command_handler.hpp>

namespace squLib {
/**
 * @brief
 * @tparam &commandTable
 * @tparam &consoleDriver
 */
template <std::span<const Command_handler> &commandTable, auto &consoleDriver>
struct Command_interpreter {
  results handle(std::span<const char> command) {
    // empty command
    if (command.size() == 0)
      return results::error;
    // find command
    for (const Command_handler &element : commandTable) {
      std::size_t commandIndex = 0;
      while ((command[commandIndex] == element.commandString[commandIndex]) && (element.commandString[commandIndex] != '\0'))
        commandIndex++;
      if (element.commandString[commandIndex] == '\0') {
        return element.handler(command);
      }
    }
    return results::notFound;
  }

  void print_help() {
    for (const Command_handler &element : commandTable) {
      consoleDriver.Transmit(element.commandString);
      consoleDriver.Transmit(" \t: ");
      consoleDriver.Transmit(element.helpString);
    }
  }
};
}  // namespace squLib

#endif
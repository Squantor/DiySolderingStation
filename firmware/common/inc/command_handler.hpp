/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file command_handler.hpp
 * @brief class for implementing a command handler
 */
#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <span>
#include <results.hpp>

namespace squLib {
struct Command_handler {
  const char* commandString;
  const char* helpString;
  results (*handler)(std::span<const char> commandLine);
};
}  // namespace squLib

#endif
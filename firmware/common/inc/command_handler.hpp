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
#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <span>
#include <results.hpp>

namespace squLib {
struct commandHandler {
  const char* commandString;
  const char* helpString;
  result (*handler)(std::span<const char> commandLine);
};
}  // namespace squLib

#endif
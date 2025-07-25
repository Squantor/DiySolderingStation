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
#ifndef COMMAND_HANDLERS_HPP
#define COMMAND_HANDLERS_HPP

#include <command_handler.hpp>

namespace application {
extern std::span<const squLib::commandHandler> commandHandlers;
}  // namespace application
#endif
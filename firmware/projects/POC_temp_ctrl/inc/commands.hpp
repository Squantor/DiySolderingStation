/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file gathering place for all command handlers
 * @brief definitions for all command handlers
 */
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <command_handler.hpp>

namespace application {
extern squLib::Command_handler stk_handler;
extern squLib::Command_handler empty_handler;
extern squLib::Command_handler dup_handler;
extern squLib::Command_handler drop_handler;
extern squLib::Command_handler stat_handler;
extern squLib::Command_handler mux_handler;
extern squLib::Command_handler tc_handler;
extern squLib::Command_handler zerocross_handler;
extern squLib::Command_handler disp_handler;
extern squLib::Command_handler button_handler;
}  // namespace application

#endif
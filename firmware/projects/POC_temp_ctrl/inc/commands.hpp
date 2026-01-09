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
extern squLib::commandHandler stkHandler;
extern squLib::commandHandler emptyHandler;
extern squLib::commandHandler dupHandler;
extern squLib::commandHandler dropHandler;
extern squLib::commandHandler statHandler;
extern squLib::commandHandler muxHandler;
extern squLib::commandHandler tcHandler;
extern squLib::commandHandler zerocross_handler;
extern squLib::commandHandler disp_handler;
extern squLib::commandHandler button_handler;
}  // namespace application

#endif
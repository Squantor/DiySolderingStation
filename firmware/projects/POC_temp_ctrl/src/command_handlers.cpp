/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_handlers.cpp
 * @brief central gathering spot for all command handlers
 */
#include <command_handlers.hpp>
#include <application.hpp>
#include <commands.hpp>

namespace application {

squLib::results help_function(std::span<const char>);

squLib::Command_handler help_handler{"help", "Prints out all help commands\n", help_function};
squLib::Command_handler number_handler{"0??", "Any integer will get pushed on the stack\n", nullptr};
squLib::Command_handler hex_num_handler{"0x0?", "Any hex unsigned integer will get pushed on the stack\n", nullptr};

squLib::results help_function(std::span<const char>) {
  command_interpreter.printHelp();
  return squLib::results::ok;
}

std::array<squLib::Command_handler, 12> command_handler_table{help_handler,  number_handler, hex_num_handler,   stk_handler,
                                                              empty_handler, drop_handler,   dup_handler,       stat_handler,
                                                              mux_handler,   tc_handler,     zerocross_handler, button_cmd};
std::span<const squLib::Command_handler> command_handlers{command_handler_table};

}  // namespace application
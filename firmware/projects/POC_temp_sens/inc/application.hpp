/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application class
 */
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <POC_temp_sense_nuclone.hpp>
#include <command_interpreter_number.hpp>
#include <command_value_stack.hpp>
#include <command_handlers.hpp>

namespace application {
struct application {
  application() {}
  void init();
  void progress();
};

extern squLib::commandValueStack<8, usartPeripheral> commandValues;
extern squLib::commandInterpreter<commandHandlers, commandValues, usartPeripheral> commandInterpreter;

}  // namespace application

#endif
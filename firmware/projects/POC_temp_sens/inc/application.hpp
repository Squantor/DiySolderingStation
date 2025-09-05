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
#include <console.hpp>

namespace application {

enum class applicationState : std::uint8_t {
  usbPowered, /*!< USB powered only */
  ready,      /*!< fully powered and ready */
  operating,  /*!< an iron is heating */
  error       /*!< error state */
};

class application {
 public:
  application() : state{applicationState::usbPowered} {}
  void init();
  void progress();
  applicationState getState() {
    return state;
  }

 private:
  void setUsbPoweredState();
  applicationState state;
};

extern squLib::console<usart_peripheral> commandConsole;
extern squLib::commandValueStack<8, commandConsole> commandValues;
extern squLib::commandInterpreter<commandHandlers, commandValues, commandConsole> commandInterpreter;
extern application controller;

}  // namespace application

#endif
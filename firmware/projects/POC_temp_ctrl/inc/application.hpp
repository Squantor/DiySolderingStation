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

#include <POC_temp_control_nuclone.hpp>
#include <command_interpreter_number.hpp>
#include <command_value_stack.hpp>
#include <command_handlers.hpp>
#include <console.hpp>

namespace application {

enum class ApplicationState : std::uint8_t {
  usbPowered, /*!< USB powered only */
  ready,      /*!< fully powered and ready */
  operating,  /*!< an iron is heating */
  error       /*!< error state */
};

enum class Results : std::uint8_t {
  NoError = static_cast<std::uint8_t>(libmcu::Results::NoError),
  Error = static_cast<std::uint8_t>(libmcu::Results::Error),
};

class Application {
 public:
  Application() : state{ApplicationState::usbPowered} {}
  [[nodiscard]] Results Init();
  [[nodiscard]] Results Progress();
  ApplicationState GetState() {
    return state;
  }

 private:
  void SetUsbPoweredState();
  ApplicationState state;
};

extern squLib::console<usart_peripheral> command_console;
extern squLib::commandValueStack<8, command_console> command_values;
extern squLib::commandInterpreter<commandHandlers, command_values, command_console> command_interpreter;
extern Application controller;

}  // namespace application

#endif
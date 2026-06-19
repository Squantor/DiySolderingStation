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
#include <event_dispatch.hpp>
#include <power_ctrl.hpp>

/**
 * @brief application wide result/return values
 * @note this is a subset of libmcu::Results
 * This is defined in the global namespace for now as it is used application wide
 */
enum class Results : std::uint8_t {
  no_error = static_cast<std::uint8_t>(libmcu::Results::NoError),
  error = static_cast<std::uint8_t>(libmcu::Results::Error),
};

namespace application {

enum class Application_state : std::uint8_t {
  usb_powered, /*!< USB powered only */
  ready,       /*!< fully powered and ready */
  operating,   /*!< an iron is heating */
  error        /*!< error state */
};

class Application {
 public:
  Application() : state{Application_state::usb_powered} {}
  [[nodiscard]] Results init();
  [[nodiscard]] Results progress();
  Application_state get_state() {
    return state;
  }

 private:
  void set_usb_powered_state();
  Application_state state;
};

extern squLib::console<usart_peripheral> command_console;
extern squLib::Command_value_stack<8, command_console> command_values;
extern squLib::Command_interpreter<command_handlers, command_values, command_console> command_interpreter;
extern Application controller;
extern Power_ctrl solder_iron_power_ctrl;
extern Event_dispatcher event_dispatcher;

}  // namespace application

#endif
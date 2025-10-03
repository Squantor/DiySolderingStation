/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */

#include <application.hpp>
#include <cmdline_simple.hpp>
#include <console.hpp>
#include <zerocross.hpp>

namespace application {

squLib::console<usart_peripheral> command_console;
squLib::commandValueStack<8, command_console> command_values;
squLib::commandInterpreter<commandHandlers, command_values, command_console> command_interpreter;
squLib::commandlineSimple<80, command_console, command_interpreter> commandline;
ZeroCross zerocross;

Results Application::Init() {
  usart_peripheral.Claim();
  display.init();
  command_console.print("DIY soldering station POC temperature sensing\n");
  zerocross.Init();
  return Results::NoError;
}

Results Application::Progress() {
  static std::uint32_t currentTicks = ticks;
  if (currentTicks + 100 < ticks) {
    // Print("test:\t", currentTicks, "\t", print::Hex{currentTicks}, "\n");
    currentTicks = ticks;
  }
  // echo characters
  if (usart_peripheral.GetReceiveLevel() > 0) {
    static std::array<char, 1> data;
    usart_peripheral.Receive(data);
    commandline.input(data);
  }
  // power control
  zerocross.Progress(ticks, ticks_per_second);
  // state handling
  switch (state) {
    case ApplicationState::usbPowered:
      if (IsMainsPresent() && zerocross.Detected())
        state = ApplicationState::ready;
      break;
    case ApplicationState::ready:
      if (!IsMainsPresent() || !zerocross.Detected())
        SetUsbPoweredState();
      break;
    case ApplicationState::operating:
      if (!IsMainsPresent() || !zerocross.Detected())
        SetUsbPoweredState();
      break;
    case ApplicationState::error:
      break;

    default:
      command_console.print("Unknown state!!!");
      return Results::Error;
      break;
  }
  return Results::NoError;
}

void Application::SetUsbPoweredState() {
  SetSafeUsbPowered();
  state = ApplicationState::usbPowered;
}
}  // namespace application

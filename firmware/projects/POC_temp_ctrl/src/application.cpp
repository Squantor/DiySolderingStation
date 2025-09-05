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

namespace application {

squLib::console<usart_peripheral> commandConsole;
squLib::commandValueStack<8, commandConsole> commandValues;
squLib::commandInterpreter<commandHandlers, commandValues, commandConsole> commandInterpreter;
squLib::commandlineSimple<80, commandConsole, commandInterpreter> commandline;

void application::init() {
  usart_peripheral.Claim();
  commandConsole.print("DIY soldering station POC temperature sensing\n");
}

void application::progress() {
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
  // state handling
  switch (state) {
    case applicationState::usbPowered:
      if (isMainsPresent())
        state = applicationState::ready;
      break;
    case applicationState::ready:
      if (!isMainsPresent())
        setUsbPoweredState();
      break;
    case applicationState::operating:
      if (!isMainsPresent())
        setUsbPoweredState();
      break;
    case applicationState::error:
      if (!isMainsPresent())
        setUsbPoweredState();
      break;

    default:
      commandConsole.print("Unknown state!!!");
      break;
  }
}

void application::setUsbPoweredState() {
  setSafeUsbPowered();
  state = applicationState::usbPowered;
}
}  // namespace application

/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */
#include <POC_temp_sense_nuclone.hpp>
#include <application.hpp>
#include <print.hpp>

namespace application {
void application::init() {}
void application::progress() {
  static std::uint32_t currentTicks = ticks;
  if (currentTicks + 100 < ticks) {
    Print("test: ");
    Print(12345);
    Print(" ");
    Print(print::Hex{0x12AB});
    Print(" ");
    Print(currentTicks);
    Print(" ");
    Print(print::Hex{currentTicks});
    Print("\n");
    currentTicks = ticks;
  }
  // echo characters
  if (usartPeripheral.receiveDataAvailable() > 0) {
    static std::array<char, 1> data;
    usartPeripheral.receive(data);
    usartPeripheral.transmit(data);
  }
}
}  // namespace application

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

namespace application {
void application::init() {}
void application::progress() {
  static std::uint32_t currentTicks = ticks;
  static std::array<std::uint8_t, 6> transmitBuffer{"test\n"};
  if (currentTicks + 100 < ticks) {
    usartPeripheral.transmit(transmitBuffer);
    currentTicks = ticks;
  }
}
}  // namespace application

/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_tc.cpp
 * @brief command handler for thermocouple measurement
 */
#include <commands.hpp>
#include <application.hpp>

namespace application {

squLib::results tc(std::span<const char> commandLine) {
  (void)commandLine;
  if (controller.GetState() == ApplicationState::usbPowered) {
    command_console.print("cant measure TC when running on USB power\n");
    return squLib::results::error;
  }
  std::uint32_t sample = adc_peripheral.Sample(pin_tc_amp);
  std::uint32_t muvPerLsb = 3000000 / 4096;
  command_console.print("Adc output is ", (sample * muvPerLsb) / 1000, " millivolt \n");
  return squLib::results::ok;
}

squLib::commandHandler tcHandler{"tc", "Measures Thermocouple amplifier\n", tc};

}  // namespace application
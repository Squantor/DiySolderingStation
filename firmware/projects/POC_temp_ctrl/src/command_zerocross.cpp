/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_zerocross.cpp
 * @brief command handler for zero crossing detection
 */
#include <commands.hpp>
#include <application.hpp>

namespace application {

squLib::results Zero_cross(std::span<const char>) {
  if (!zero_cross.is_detected()) {
    command_console.print("zerocrosses not detected\n");
    return squLib::results::error;
  }
  command_console.print(zero_cross.zero_cross_count, " zerocrosses detected\n");
  return squLib::results::ok;
}

squLib::Command_handler zerocross_handler{"zc", "zero crossing detection statistics\n", Zero_cross};

}  // namespace application
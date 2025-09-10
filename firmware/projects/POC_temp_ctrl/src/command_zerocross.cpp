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

squLib::results ZeroCross(std::span<const char>) {
  if (!zerocross.Detected()) {
    command_console.print("zerocrosses not detected\n");
    return squLib::results::error;
  }
  command_console.print(zerocross.zero_cross_count, " zerocrosses detected\n");
  return squLib::results::ok;
}

squLib::commandHandler zerocross_handler{"zc", "zero crossing detection statistics\n", ZeroCross};

}  // namespace application
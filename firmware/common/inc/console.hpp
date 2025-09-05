/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file character based console class
 * @brief console with zero buffering and immediate passthrough
 */
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <span>
#include <cstdint>
#include <string.h>
#include <toascii.hpp>
#include "console_common.hpp"

namespace squLib {

template <auto &driver>
struct console {
  constexpr void reset() {}
  /**
   * @brief read from console
   * @param output buffer to put read console data in
   */
  void read(std::span<char> output) {
    driver.Receive(output);
  }
  constexpr void write(const char *s) {
    std::size_t maxIndex = strlen(s);
    for (std::size_t index = 0; index < maxIndex; index++) {
      driver.Transmit(s[index]);
    }
  }
  constexpr void write(std::span<const char> s) {
    driver.Transmit(s);
  }
  constexpr void write(const char &c) {
    driver.Transmit(c);
  }

  template <typename... Ts>
  void print(Ts... t) {
    (toascii<driver>(t), ...);
  }
};
}  // namespace squLib

#endif
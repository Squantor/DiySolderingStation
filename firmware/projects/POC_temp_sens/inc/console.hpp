/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file
 * @brief
 */
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <span>
#include <string.h>

namespace application {
template <auto &driver>
struct console {
  constexpr void write(const char *s) {
    std::size_t maxIndex = strlen(s);
    for (std::size_t index = 0; index < maxIndex; index++) {
      driver.write(s[index]);
    }
  }
  constexpr void write(std::span<const char> s) {
    driver.write(s);
  }
  constexpr void write(const char &c) {
    driver.write(c);
  }
};
}  // namespace application

#endif
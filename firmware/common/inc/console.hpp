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
#include "console_common.hpp"

namespace squLib {

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
  void print(const char *) {}
  void print(std::span<const char>) {}
  void print(std::uint32_t) {}
  void print() {}
  void print(Dec) {}
  template <typename T>
  void print(T *p) {
    print(Hex{reinterpret_cast<uint32_t>(p)});
  }
  template <typename... Ts>
  void print(Ts... t) {
    (print(t), ...);
  }
};
}  // namespace squLib

#endif
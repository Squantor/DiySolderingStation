/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file interprets ascii strings as numbers and maintains a stack definitions
 * @brief class that interprets ascii strings as numbers and maintains a stack
 * TODO: doxygen
 */
#ifndef COMMAND_VALUE_STACK_HPP
#define COMMAND_VALUE_STACK_HPP

#include <cstdint>
#include <cctype>
#include <array>
#include <span>
#include <optional>
#include <parse_digit.hpp>
#include <ringbuffer.hpp>
#include <results.hpp>

namespace squLib {
template <std::size_t stackSize, auto &consoleDriver>
struct commandValueStack {
  /**
   * @brief resets stack state to empty
   */
  void reset() {
    topOfStack = 0;
  }
  /**
   * @brief returns amount of elements on the stack
   * @return amount of elements on the stack
   */
  std::size_t size() {
    return topOfStack;
  }

  void push(std::int32_t value) {
    valueStack[topOfStack] = value;
    topOfStack = topOfStack + 1;
  }

  results push(std::span<const char> string) {
    std::size_t index{0};
    bool isNegative{false};
    std::int32_t value{0};
    if (string[index] == '-') {
      isNegative = true;
      index++;
    }
    if (isdigit(string[index]) == 0)
      return results::error;
    // strip leading zeroes
    while (string[index] == '0')
      index = index + 1;
    if (string[index] == 'x') {
      index = index + 1;
      if (isNegative == true)
        return results::error;
      //   handle hex number
      while (index < string.size()) {
        std::optional<unsigned int> result = parseDigitHex(string[index]);
        if (result.has_value() == false)
          return results::error;
        value = value * 16;
        value = value + *result;
        index = index + 1;
      }
      push(value);
    } else {
      // handle positive number
      while (index < string.size()) {
        std::optional<unsigned int> result = parseDigitDec(string[index]);
        if (result.has_value() == false)
          return results::error;
        value = value * 10;
        value = value + *result;
        index = index + 1;
      }
      if (isNegative)
        value = -value;
      push(value);
    }
    return results::ok;
  }

  std::optional<std::int32_t> pop() {
    if (topOfStack > 0) {
      topOfStack = topOfStack - 1;
      return valueStack[topOfStack];
    } else
      return {};
  }

  void dup() {
    if (topOfStack == 0)
      return;
    valueStack[topOfStack] = valueStack[topOfStack - 1];
    topOfStack = topOfStack + 1;
  }

  void drop() {
    if (topOfStack > 0)
      topOfStack = topOfStack - 1;
  }

  void swap() {}

  void over() {}

  void rot() {}
  std::size_t topOfStack;
  std::array<std::int32_t, stackSize> valueStack;
};
}  // namespace squLib

#endif
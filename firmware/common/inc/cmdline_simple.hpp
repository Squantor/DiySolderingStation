/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file commandline handler class with minimum functionality
 * @brief commandline handler that handles backspaces and recalling previous commands
 */
#ifndef CMDLINE_SIMPLE_HPP
#define CMDLINE_SIMPLE_HPP

#include <cstdint>
#include <array>
#include <span>

namespace squLib {
namespace detail {
enum class commandlineState {
  normal,      /**< normal operation */
  ansiSquence, /**< parsing an ansi squence */
};
}  // namespace detail
/**
 * @brief simple commandline parser
 * Can only recall previous command, no command completion0
 * @tparam N max commandline size
 */
template <std::size_t N>
class commandlineSimple {
 public:
  commandlineSimple() : bufferIndex{0}, state{detail::commandlineState::normal} {};

  /**
   * @brief Resets the commandline state
   */
  void reset() {
    bufferIndex = 0;
    state = detail::commandlineState::normal;
  };
  /**
   * @brief input a block of characters
   * @param inputBuffer block of characters
   */
  void input(std::span<const char> inputBuffer) {
    for (const char &element : inputBuffer)
      input(element);
  }
  /**
   * @brief input one character
   * @param c character to input
   */
  void input(const char &c) {
    switch (c) {
      case '\n':
        // emit character
        // TODO: send full string to caller
        break;
      case '\b':
        // emit character sequence erasing previous one

        if (bufferIndex != 0)
          bufferIndex = bufferIndex - 1;
        break;

      default:
        break;
    }
    // check if we have a special sequence/character
    // no, add to buffer
    // yes
    // CR/LF/backspace?
    // handle it
    // ansi character?
    // handle it
  }

 private:
  std::array<char, N> buffer;
  std::size_t bufferIndex;
  detail::commandlineState state;
};
}  // namespace squLib
#endif
/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief simple commandline handler class
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
   * @brief input one character
   * @param c character to input
   */
  void input(const char &c) {}
  /**
   * @brief input a block of characters
   * @param inputBuffer block of characters
   */
  void input(std::span<const char> inputBuffer) {
    for (const char &element : inputBuffer)
      input(element);
  }

 private:
  std::array<char, N> buffer;
  std::size_t bufferIndex;
  detail::commandlineState state;
};
}  // namespace squLib
#endif
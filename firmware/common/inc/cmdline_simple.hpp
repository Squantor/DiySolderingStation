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
#include <console.hpp>
#include <ansi_parse.hpp>

namespace squLib {
namespace detail {
enum class commandlineState {
  normal,      /**< normal operation */
  ansiSquence, /**< parsing an ansi squence */
};
}  // namespace detail
template <std::size_t N, auto &consoleDriver, auto &commandHandler>
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
      case '\r':
        if (bufferIndex != 0) {
          consoleDriver.write(c);
          commandHandler.handle(std::span<char>(buffer).first(bufferIndex));
          bufferIndex = 0;
        }
        goto done;
        break;
      case '\b':
        if (bufferIndex != 0) {
          consoleDriver.write('\b');
          consoleDriver.write(' ');
          consoleDriver.write('\b');
          bufferIndex = bufferIndex - 1;
        } else
          consoleDriver.write('\a');  // send a bell
        goto done;
        break;

      default:
        break;
    }
    // ansi character?
    //   yes, parse and dont print
    //   done parsing and it is a ansi sequence? then handle it
    // nothing special to handle, normal char
    consoleDriver.write(c);
    buffer[bufferIndex] = c;
    bufferIndex = bufferIndex + 1;
  done:
    return;  // added to supress warning
  }

 private:
  ansiParse ansiParser;
  std::array<char, N> buffer;
  std::size_t bufferIndex;
  detail::commandlineState state;
};
}  // namespace squLib
#endif
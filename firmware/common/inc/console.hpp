/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file character based console class
 * @brief console that supports single line buffering and transfers
 */
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <cstdint>
#include <array>
#include <span>

namespace squLib {
/**
 * @brief console handler class
 * @tparam N size of buffer
 * @tparam ioDevice device to read/write from
 */
template <std::size_t N, auto &ioDevice>
class console {
 public:
  console() : bufferIndex{0} {}
  void reset() {
    bufferIndex = 0;
  }
  void read(std::span<char> output) {
    ioDevice.read(output);
  }
  void write(std::span<const char> input) {
    for (const char &element : input) {
      if (bufferIndex == N) {
        ioDevice.write(buffer);
        bufferIndex = 0;
      }
      buffer[bufferIndex] = element;
      bufferIndex = bufferIndex + 1;
      if (element == '\n') {
        ioDevice.write(std::span<char>(buffer).first(bufferIndex));
        bufferIndex = 0;
      }
    }
  }

 private:
  std::size_t bufferIndex;
  std::array<char, N> buffer;
};
}  // namespace squLib

#endif
/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file character device mock
 * @brief character device mock used for tests
 */
#ifndef MOCK_CHAR_DEVICE_HPP
#define MOCK_CHAR_DEVICE_HPP

#include <cstdint>
#include <array>
#include <span>

namespace mocks {
template <std::size_t N>
class charDevice {
 public:
  void read(std::span<char> output) {
    for (char &element : output) {
      element = readBuffer[readIndex];
      readIndex = readIndex + 1;
    }
  }
  void write(std::span<const char> input) {
    for (const char &element : input) {
      writeBuffer[writeIndex] = element;
      writeIndex = writeIndex + 1;
    }
  }
  std::size_t readIndex;
  std::array<char, N> readBuffer;
  std::size_t writeIndex;
  std::array<char, N> writeBuffer;

 private:
};
}  // namespace mocks

#endif
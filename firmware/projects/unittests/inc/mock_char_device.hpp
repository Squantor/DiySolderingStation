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
/**
 * @brief Simple character device mock
 * @tparam N maximum buffer size
 */
template <std::size_t N>
class charDevice {
 public:
  /**
   * @brief read some data from buffer
   * @param output data buffer to write to
   */
  void read(std::span<char> output) {
    for (char &element : output) {
      element = readBuffer[readIndex];
      readIndex = readIndex + 1;
    }
  }
  /**
   * @brief write some data to buffer
   * @param input data buffer to read from
   */
  void write(std::span<const char> input) {
    for (const char &element : input) {
      writeBuffer[writeIndex] = element;
      writeIndex = writeIndex + 1;
    }
  }
  std::size_t readIndex;           /*!< read index in read buffer */
  std::array<char, N> readBuffer;  /*!< buffer to read from */
  std::size_t writeIndex;          /*!< write index in write buffer */
  std::array<char, N> writeBuffer; /*!< buffer to write to */

 private:
};
}  // namespace mocks

#endif
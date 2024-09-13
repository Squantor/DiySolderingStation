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
#include <cstring>
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
   * @brief reset the mock
   */
  void reset() {
    readIndex = 0;
    writeIndex = 0;
    readBuffer.fill(0);
    writeBuffer.fill(0);
  }
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
   * @param input data to read from
   */
  void write(const char &input) {
    std::array<char, 1> inputBuffer{input};
    write(inputBuffer);
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
  /**
   * @brief write some data to buffer
   * @param input C style string to read from
   */
  void write(const char *input) {
    std::size_t maxIndex = std::strlen(input);
    for (std::size_t index = 0; index < maxIndex; index++) {
      write(input[index]);
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
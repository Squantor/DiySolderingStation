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
  /**
   * @brief Construct a new console object
   */
  console() : writeIndex{0} {}
  /**
   * @brief reset the console buffer
   */
  void reset() {
    writeIndex = 0;
  }
  /**
   * @brief read from console
   * @param output buffer to put read console data in
   */
  void read(std::span<char> output) {
    ioDevice.read(output);
  }
  /**
   * @brief Write data to console
   * overflow of buffer or a \n will cause a flush to character driver
   * @param input character to write to console
   */
  void write(const char &input) {
    std::array<char, 1> inputBuf{input};
    write(inputBuf);
  }
  /**
   * @brief write data to console
   * overflow of buffer or a \n will cause a flush to character driver
   * @param input buffer to write to console
   */
  void write(std::span<const char> input) {
    for (const char &element : input) {
      if (writeIndex == N) {
        ioDevice.write(writeBuffer);
        writeIndex = 0;
      }
      writeBuffer[writeIndex] = element;
      writeIndex = writeIndex + 1;
      if (element == '\n') {
        ioDevice.write(std::span<char>(writeBuffer).first(writeIndex));
        writeIndex = 0;
      }
    }
  }

 private:
  std::size_t writeIndex;          /*!< write data buffer index */
  std::array<char, N> writeBuffer; /*!< write data buffer */
};
}  // namespace squLib

#endif
/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file console class common definitions
 * @brief common definitions for character based console classes
 */
#ifndef CONSOLE_COMMON_HPP
#define CONSOLE_COMMON_HPP

#include <cstdint>

namespace squLib {
/**
 * @brief wrapper for printing hex numbers in the console
 */
struct Hex {
  std::uint32_t v;
};
/**
 * @brief wrapper for printing decimal numbers in the console
 */
struct Dec {
  std::int32_t v;
};
}  // namespace squLib

#endif
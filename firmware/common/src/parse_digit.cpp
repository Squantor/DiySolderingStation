/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file digit parsing function header
 * @brief functions for transforming digits
 */
#include <parse_digit.hpp>

namespace squLib {

std::optional<unsigned int> parseDigitDec(const char c) {
  if (c >= '0' && c <= '9')
    return {c - '0'};
  return {};
}
std::optional<unsigned int> parseDigitHex(const char c) {
  if (c >= '0' && c <= '9')
    return {c - '0'};
  if (c >= 'a' && c <= 'f')
    return {c - 'W'};
  if (c >= 'A' && c <= 'F')
    return {c - '7'};
  return {};
}
}
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
#ifndef PARSE_DIGIT_HPP
#define PARSE_DIGIT_HPP

#include <optional>
namespace squLib {

/**
 * @brief Parses a character and returns its decimal value
 * @param c any character from 0 to 9
 * @return returns integer value if valid decimal digit, otherwise empty
 */
std::optional<unsigned int> parseDigitDec(const char c);
/**
 * @brief Parses a character and returns its hexdecimal value
 * @param c any character from 0 to 9, a to f and A to F
 * @return returns integer value if valid hexadecimal digit, otherwise empty
 */
std::optional<unsigned int> parseDigitHex(const char c);
};  // namespace squLib

#endif
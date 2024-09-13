/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file results class
 * @brief various results that can be returned
 */
#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <cstdint>

namespace squLib {
enum class results : std::uint8_t {
  ok = 0,   /*!< Everything okay*/
  error,    /*!< Unspecified error */
  notFound, /*!< not found */
};
}  // namespace squLib

#endif
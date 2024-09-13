/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file interprets ascii strings as numbers and maintains a stack definitions
 * @brief class that interprets ascii strings as numbers and maintains a stack
 */
#ifndef COMMAND_VALUE_STACK_HPP
#define COMMAND_VALUE_STACK_HPP

#include <cstdint>

namespace squLib {
template <std::size_t stackSize>
struct commandValueStack {};
}  // namespace squLib

#endif
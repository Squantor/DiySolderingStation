/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief common macros for whatever
 */
#ifndef COMMON_HPP
#define COMMON_HPP

/**
 * \brief Macro to generate a single 1 bit pattern
 * 
 * Helper macro shift a one bit to a position
 * @param[in]  value    shift count
 */
#define BITPOS(value) (1 << value)

#endif
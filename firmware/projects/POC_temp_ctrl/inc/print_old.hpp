/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief simple print functionality taken from https://github.com/zhmu/dogfood/blob/develop/kernel/lib.h
 */
#ifndef PRINT_HPP
#define PRINT_HPP

#include <cstdint>
#include <span>

namespace print {
struct Hex {
  std::uint32_t v;
};
struct Dec {
  std::int32_t v;
};

namespace detail {
void Print(const char*);
void Print(std::span<const char>);
void Print(std::uint32_t);
void Print(Hex);
void Print(Dec);
template <typename T>
void Print(T* p) {
  Print(Hex{reinterpret_cast<uint32_t>(p)});
}
}  // namespace detail
}  // namespace print

template <typename... Ts>
void Print(Ts... t) {
  (print::detail::Print(t), ...);
}

#endif
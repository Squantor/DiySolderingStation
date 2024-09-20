/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file various type to ascii string converters definitions
 * @brief various converters for various types to ascii spans/strings
 * TODO: documentation
 */
#ifndef TOASCII_HPP
#define TOASCII_HPP

#include <cstdint>
#include <span>
namespace squLib {
namespace detail {
constexpr char hextab[] = "0123456789abcdef";

template <typename Emitter>
void put8(const uint8_t v, Emitter emit) {
  emit(hextab[v >> 4]);
  emit(hextab[v & 0xff]);
}

template <typename Emitter>
void putint(const unsigned int base, const uintmax_t n, Emitter emit) {
  // Determine the number of digits we need to print and the maximum divisor
  uintmax_t divisor = 1;
  unsigned int p = 0;
  for (uintmax_t i = n; i >= base; i /= base, p++, divisor *= base)
    /* nothing */;

  // Print from most-to-least significant digit
  for (unsigned int i = 0; i <= p; i++, divisor /= base)
    emit(hextab[(n / divisor) % base]);
}
}  // namespace detail
/**
 * @brief wrapper for converting uint32 to ascii hex numbers
 */
struct Hex {
  std::uint32_t v;
};
/**
 * @brief wrapper for converting uint32 to ascii decimal numbers
 */
struct Dec {
  std::int32_t v;
};
/**
 * @brief wrapper for writing a single character
 */
struct Chr {
  char c;
};

template <auto &charDevice>
void toascii(const char *s) {
  charDevice.write(std::span{s, strlen(s)});
}

template <auto &charDevice>
void toascii(std::span<const char> buf) {
  charDevice.write(buf);
}

template <auto &charDevice>
void toascii(std::uint32_t num) {
  detail::putint(10, num, [](const auto ch) {
    charDevice.write(ch);
  });
}

template <auto &charDevice>
void toascii(Hex num) {
  detail::putint(16, num.v, [](const auto ch) {
    charDevice.write(ch);
  });
}

template <auto &charDevice>
void toascii(Dec num) {
  int32_t value{num.v};
  if (value < 0) {
    charDevice.write('-');
    value = -value;
  }
  detail::putint(10, value, [](const auto ch) {
    charDevice.write(ch);
  });
}

template <auto &charDevice>
void toascii(Chr c) {
  charDevice.write(c.c);
}

template <auto &charDevice, typename T>
void toascii(T *p) {
  toascii<charDevice>(Hex{reinterpret_cast<uint32_t>(p)});
}

}  // namespace squLib

#endif
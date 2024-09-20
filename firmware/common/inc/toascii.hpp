/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief simple print functionality taken from https://github.com/zhmu/dogfood/blob/develop/kernel/lib.h
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

template <auto& charDevice>
struct toascii {
  void convert(const char& c) {
    charDevice.write(std::span{&c, 1});
  }
  void convert(const char* s) {
    charDevice.write(std::span{s, strlen(s)});
  }
  void convert(std::span<const char> buf) {
    charDevice.write(buf);
  }
  void convert(std::uint32_t num) {
    detail::putint(10, num, [](const auto ch) {
      charDevice.write(ch);
    });
  }
  void convert(Hex num) {
    detail::putint(16, num.v, [](const auto ch) {
      charDevice.write(ch);
    });
  }
  void convert(Dec num) {
    int32_t value{num.v};
    if (value < 0) {
      charDevice.write('-');
      value = -value;
    }
    detail::putint(10, value, [](const auto ch) {
      charDevice.write(ch);
    });
  }
  /*
  template <typename T>
  void convert(T* p) {
    convert(Hex{reinterpret_cast<uint32_t>(p)});
  }
  */
};

}  // namespace squLib

#endif
/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief simple print functionality taken from https://github.com/zhmu/dogfood/blob/develop/kernel/lib.cpp
 */
#include <string.h>
#include <print.hpp>
#include <POC_temp_sense_nuclone.hpp>

namespace {
const char hextab[] = "0123456789abcdef";

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
}  // namespace

namespace print::detail {

void WriteConsole(const char* ptr, std::size_t len) {
  usartPeripheral.write(std::span{ptr, len});
}

void WriteConsole(char c) {
  usartPeripheral.write(std::span{&c, 1});
}

void Print(std::span<const char> buffer) {
  WriteConsole(buffer.data(), buffer.size());
}

void Print(const char* s) {
  WriteConsole(s, strlen(s));
}

void Print(std::uint32_t n) {
  putint(10, n, [](const auto ch) {
    WriteConsole(&ch, 1);
  });
}

void Print(Dec n) {
  int32_t value{n.v};
  if (value < 0) {
    WriteConsole('-');
    value = -value;
  }
  putint(10, value, [](const auto ch) {
    WriteConsole(&ch, 1);
  });
}

void Print(Hex n) {
  putint(16, n.v, [](const auto ch) {
    WriteConsole(&ch, 1);
  });
}
}  // namespace print::detail
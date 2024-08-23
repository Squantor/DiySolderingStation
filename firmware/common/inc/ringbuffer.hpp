/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file ringbuffer.hpp
 *
 * Implements a ringbuffer class
 *
 */
#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <array>
#include <cstdint>

namespace libMcu {
template <typename T, std::size_t N>
class RingBuffer {
 public:
  using iterator = typename std::array<T, N>::iterator;

  RingBuffer() {
    static_assert(N > 0, "ringbuffer size of zero is not allowed!");
    reset();
  }

  void reset() {
    front = data.begin();
    back = data.begin();
  }

  bool full() {
    return increment(front) == back;
  }

  bool empty() const {
    return front == back;
  }

  bool pushBack(const T& p) {
    if (full())
      return false;
    auto temp = decrement(back);
    back = temp;
    *back = p;
    return true;
  }

  bool pushFront(const T& p) {
    if (full())
      return false;
    auto temp = increment(front);
    *front = p;
    front = temp;
    return true;
  }

  bool popBack(T& p) {
    if (empty())
      return false;
    auto temp = increment(back);
    p = *back;
    back = temp;
    return true;
  }

  bool popFront(T& p) {
    if (empty())
      return false;
    auto temp = decrement(front);
    p = *temp;
    front = temp;
    return true;
  }

 private:
  iterator decrement(const iterator p) {
    if (p == data.begin())
      return data.end() - 1;
    else
      return p - 1;
  }

  iterator increment(const iterator p) {
    if (p + 1 == data.end())
      return data.begin();
    else
      return p + 1;
  }

  iterator front;            /**< first element of the ringbuffer */
  iterator back;             /**< last element of the ringbuffer */
  std::array<T, N + 1> data; /**< ringbuffer data, one element is added as we need always one element free */
};
}  // namespace libMcu

#endif

/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_ringbuf.cpp
 *
 * All tests for the ring buffer class
 */
#include <MinUnit.h>
#include <stdint.h>
#include <ringbuffer.hpp>

libMcu::RingBuffer<uint16_t, 10> RingBufferDutU16;

MINUNIT_ADD(RingBufferCppEmpty, NULL, NULL) {
  RingBufferDutU16.reset();
  minUnitCheck(RingBufferDutU16.empty() == true);
  minUnitCheck(RingBufferDutU16.full() == false);
}

MINUNIT_ADD(RingBufferCppPushBack, NULL, NULL) {
  uint16_t number = 42;
  RingBufferDutU16.reset();
  minUnitCheck(RingBufferDutU16.empty() == true);
  minUnitCheck(RingBufferDutU16.pushBack(number) == true);
  minUnitCheck(RingBufferDutU16.empty() == false);
}

MINUNIT_ADD(RingBufferCppPushBackFull, NULL, NULL) {
  uint16_t number = 42;
  RingBufferDutU16.reset();
  minUnitCheck(RingBufferDutU16.empty() == true);
  for (uint16_t i = 0; i < 10; i++) {
    minUnitCheck(RingBufferDutU16.pushBack(i) == true);
  }
  minUnitCheck(RingBufferDutU16.pushBack(number) == false);
  minUnitCheck(RingBufferDutU16.full() == true);
}

MINUNIT_ADD(RingBufferCppPushFront, NULL, NULL) {
  uint16_t number = 42;
  RingBufferDutU16.reset();
  minUnitCheck(RingBufferDutU16.empty() == true);
  minUnitCheck(RingBufferDutU16.pushFront(number) == true);
  minUnitCheck(RingBufferDutU16.empty() == false);
}

MINUNIT_ADD(RingBufferCppPushFrontFull, NULL, NULL) {
  uint16_t number = 42;
  RingBufferDutU16.reset();
  minUnitCheck(RingBufferDutU16.empty() == true);
  for (uint16_t i = 0; i < 10; i++) {
    minUnitCheck(RingBufferDutU16.pushFront(i) == true);
  }
  minUnitCheck(RingBufferDutU16.pushFront(number) == false);
  minUnitCheck(RingBufferDutU16.full() == true);
}

MINUNIT_ADD(RingBufferCppPopBack, NULL, NULL) {
  uint16_t number = 42;
  uint16_t output = 0;
  RingBufferDutU16.reset();
  minUnitCheck(RingBufferDutU16.popBack(output) == false);
  minUnitCheck(RingBufferDutU16.pushFront(number) == true);
  minUnitCheck(RingBufferDutU16.popBack(output) == true);
  minUnitCheck(output == 42);
  minUnitCheck(RingBufferDutU16.popBack(output) == false);
  for (uint16_t i = 0; i < 10; i++) {
    RingBufferDutU16.pushFront(i);
  }
  for (uint16_t i = 0; i < 10; i++) {
    minUnitCheck(RingBufferDutU16.popBack(output) == true);
    minUnitCheck(output == i);
  }
  minUnitCheck(RingBufferDutU16.popBack(output) == false);
  for (uint16_t i = 0; i < 10; i++) {
    RingBufferDutU16.pushBack(i);
  }
  for (uint16_t i = 0; i < 10; i++) {
    minUnitCheck(RingBufferDutU16.popBack(output) == true);
    minUnitCheck(output == 9 - i);
  }
  minUnitCheck(RingBufferDutU16.popBack(output) == false);
}

MINUNIT_ADD(RingBufferCppPopFront, NULL, NULL) {
  uint16_t number = 42;
  uint16_t output = 0;
  minUnitCheck(RingBufferDutU16.popFront(output) == false);
  minUnitCheck(RingBufferDutU16.pushFront(number) == true);
  minUnitCheck(RingBufferDutU16.popFront(output) == true);
  minUnitCheck(output == 42);
  minUnitCheck(RingBufferDutU16.popFront(output) == false);
  for (uint16_t i = 0; i < 10; i++) {
    RingBufferDutU16.pushFront(i);
  }
  for (int i = 0; i < 10; i++) {
    minUnitCheck(RingBufferDutU16.popFront(output) == true);
    minUnitCheck(output == 9 - i);
  }
  minUnitCheck(RingBufferDutU16.popFront(output) == false);
  for (uint16_t i = 0; i < 10; i++) {
    RingBufferDutU16.pushBack(i);
  }
  for (uint16_t i = 0; i < 10; i++) {
    minUnitCheck(RingBufferDutU16.popFront(output) == true);
    minUnitCheck(output == i);
  }
  minUnitCheck(RingBufferDutU16.popFront(output) == false);
}
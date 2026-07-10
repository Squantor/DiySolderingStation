/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file Tests for command value stack interpreter
 */
#include <minunit.h>
#include <array>
#include <results.hpp>
#include <command_value_stack.hpp>
#include <mock_char_device.hpp>

static mocks::charDevice<200> charDeviceMock;

squLib::Command_value_stack<6, charDeviceMock> commandValueStackDut;

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(commandValueStackSetup) {
  charDeviceMock.reset();
  commandValueStackDut.reset();
  MINUNIT_PASS();
}

/**
 * @brief Teardown
 */
MINUNIT_TEARDOWN(commandValueStackTeardown) {
  MINUNIT_PASS();
}

/**
 * @brief testing adding and removing elements on the stack
 */
MINUNIT_ADD(testPushAndPop, commandValueStackSetup, commandValueStackTeardown) {
  MINUNIT_CHECK(commandValueStackDut.size() == 0);
  commandValueStackDut.push(1234);
  MINUNIT_CHECK(commandValueStackDut.size() == 1);
  std::optional<std::int32_t> value1 = commandValueStackDut.pop();
  MINUNIT_CHECK(commandValueStackDut.size() == 0);
  MINUNIT_CHECK(value1.has_value() == true);
  MINUNIT_CHECK(*value1 == 1234);
  std::optional<std::int32_t> value2 = commandValueStackDut.pop();
  MINUNIT_CHECK(value2.has_value() == false);
}

MINUNIT_ADD(testDropAndDup, commandValueStackSetup, commandValueStackTeardown) {
  commandValueStackDut.push(1234);
  commandValueStackDut.push(5678);
  MINUNIT_CHECK(commandValueStackDut.size() == 2);
  commandValueStackDut.dup();
  MINUNIT_CHECK(commandValueStackDut.size() == 3);
  commandValueStackDut.dup();
  MINUNIT_CHECK(commandValueStackDut.size() == 4);
  commandValueStackDut.drop();
  MINUNIT_CHECK(commandValueStackDut.size() == 3);
  std::optional<std::int32_t> value;
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == true);
  MINUNIT_CHECK(*value == 5678);
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == true);
  MINUNIT_CHECK(*value == 5678);
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == true);
  MINUNIT_CHECK(*value == 1234);
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == false);
}

MINUNIT_ADD(testPushString, commandValueStackSetup, commandValueStackTeardown) {
  // std::array<const char, 5> value1234{"1234"};
  std::span<const char> value1234{"1234"};
  std::span<const char> value89AB{"0x89AB"};
  std::span<const char> valueMinus5678{"-5678"};
  MINUNIT_CHECK(commandValueStackDut.push(value1234.subspan(0, 4)) == squLib::results::ok);
  MINUNIT_CHECK(commandValueStackDut.push(value89AB.subspan(0, 6)) == squLib::results::ok);
  MINUNIT_CHECK(commandValueStackDut.push(valueMinus5678.subspan(0, 5)) == squLib::results::ok);
  MINUNIT_CHECK(commandValueStackDut.size() == 3);
  std::optional<std::int32_t> value;
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == true);
  MINUNIT_CHECK(*value == -5678);
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == true);
  MINUNIT_CHECK(*value == 35243);
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == true);
  MINUNIT_CHECK(*value == 1234);
  value = commandValueStackDut.pop();
  MINUNIT_CHECK(value.has_value() == false);
}

// TODO: test forth primitives swap rot over

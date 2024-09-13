/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file Tests for command value stack interpreter
 */
#include <MinUnit.h>
#include <array>
#include <results.hpp>
#include <command_value_stack.hpp>
#include <mock_char_device.hpp>

static mocks::charDevice<200> charDeviceMock;

squLib::commandValueStack<6, charDeviceMock> commandValueStackDut;

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(commandValueStackSetup) {
  charDeviceMock.reset();
  commandValueStackDut.reset();
  minUnitPass();
}

/**
 * @brief Teardown
 */
MINUNIT_TEARDOWN(commandValueStackTeardown) {
  minUnitPass();
}

/**
 * @brief testing adding and removing elements on the stack
 */
MINUNIT_ADD(testPushAndPop, commandValueStackSetup, commandValueStackTeardown) {
  minUnitCheck(commandValueStackDut.size() == 0);
  commandValueStackDut.push(1234);
  minUnitCheck(commandValueStackDut.size() == 1);
  std::optional<std::int32_t> value1 = commandValueStackDut.pop();
  minUnitCheck(commandValueStackDut.size() == 0);
  minUnitCheck(value1.has_value() == true);
  minUnitCheck(*value1 == 1234);
  std::optional<std::int32_t> value2 = commandValueStackDut.pop();
  minUnitCheck(value2.has_value() == false);
}

MINUNIT_ADD(testDropAndDup, commandValueStackSetup, commandValueStackTeardown) {
  commandValueStackDut.push(1234);
  commandValueStackDut.push(5678);
  minUnitCheck(commandValueStackDut.size() == 2);
  commandValueStackDut.dup();
  minUnitCheck(commandValueStackDut.size() == 3);
  commandValueStackDut.dup();
  minUnitCheck(commandValueStackDut.size() == 4);
  commandValueStackDut.drop();
  minUnitCheck(commandValueStackDut.size() == 3);
  std::optional<std::int32_t> value;
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == true);
  minUnitCheck(*value == 5678);
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == true);
  minUnitCheck(*value == 5678);
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == true);
  minUnitCheck(*value == 1234);
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == false);
}

MINUNIT_ADD(testPushString, commandValueStackSetup, commandValueStackTeardown) {
  // std::array<const char, 5> value1234{"1234"};
  std::span<const char> value1234{"1234"};
  std::span<const char> value89AB{"0x89AB"};
  minUnitCheck(commandValueStackDut.push(value1234.subspan(0, 4)) == squLib::results::ok);
  minUnitCheck(commandValueStackDut.push(value89AB.subspan(0, 6)) == squLib::results::ok);
  minUnitCheck(commandValueStackDut.size() == 2);
  std::optional<std::int32_t> value;
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == true);
  minUnitCheck(*value == 35243);
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == true);
  minUnitCheck(*value == 1234);
  value = commandValueStackDut.pop();
  minUnitCheck(value.has_value() == false);
}

// TODO: test forth primitives swap rot over

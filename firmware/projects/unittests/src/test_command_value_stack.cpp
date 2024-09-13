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
#include <command_value_stack.hpp>

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(commandValueStackSetup) {
  minUnitPass();
}

/**
 * @brief Teardown
 */
MINUNIT_TEARDOWN(commandValueStackTeardown) {
  minUnitPass();
}

/**
 * @brief Test 1
 */
MINUNIT_ADD(test1, commandValueStackSetup, commandValueStackTeardown) {
  minUnitPass();
}

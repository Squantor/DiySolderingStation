/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file test template
 */
#include <MinUnit.h>

/**
 * @brief setup and initialisation
 */
MINUNIT_SETUP(testSetup) {
  minUnitPass();
}

/**
 * @brief Teardown
 */
MINUNIT_TEARDOWN(testTeardown) {
  minUnitPass();
}

/**
 * @brief Test 1
 */
MINUNIT_ADD(test1, testSetup, testTeardown) {
  minUnitPass();
}

/**
 * @brief Test 2 with no setup/teardowns
 */
MINUNIT_ADD(test2, nullptr, nullptr) {
  minUnitPass();
}
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

MINUNIT_ADD(test1, testSetup, nullptr) {
  minUnitPass();
}

MINUNIT_ADD(test2, nullptr, nullptr) {
  minUnitPass();
}
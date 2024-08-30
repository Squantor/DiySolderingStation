/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_cmdline_simple.cpp
 * All tests for testing the simple commandline parser class
 */
#include <MinUnit.h>
#include <stdint.h>
#include <cmdline_simple.hpp>

MINUNIT_SETUP(cmdlineSimpleSetup) {
  minUnitPass();
}

MINUNIT_SETUP(cmdlineSimpleTeardown) {
  minUnitPass();
}

MINUNIT_ADD(cmdlineSimpleTest1, cmdlineSimpleSetup, cmdlineSimpleTeardown) {
  minUnitPass();
}

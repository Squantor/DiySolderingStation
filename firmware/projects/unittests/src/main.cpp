/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main unittest entry point
 */
#include <cstdio>
#include <MinUnit.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

void minunitReport(const char* string) {
  printf("%s", string);
}

int main() {
  minunitRun();
  if (minunitTestState.failures != 0) {
    minunitReport("Test failures detected\n");
  } else {
    minunitReport("All tests passed\n");
  }
  printf("executed %d tests with %d checks where %d failed\n", minunitTestState.executed, minunitTestState.checks,
         minunitTestState.failures);
}
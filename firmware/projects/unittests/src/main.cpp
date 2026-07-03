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
#include <minunit.h>

void minunit_report(const char* string) {
  printf("%s", string);
}

int main(int, char*[]) {
  minunit_run();
  if (minunit_test_state.failures != 0) {
    minunit_report("Test failures detected\n");
  } else {
    minunit_report("All tests passed\n");
  }
  printf("executed %d tests with %d checks where %d failed\n", minunit_test_state.executed, minunit_test_state.checks,
         minunit_test_state.failures);
}
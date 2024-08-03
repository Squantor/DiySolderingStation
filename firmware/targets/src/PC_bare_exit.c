/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
Based on Rt0: https://github.com/lpsantil/rt0
Modified with help from: https://github.com/zhmu
*/

#include <PC_bare_syscall.h>

void _exit(int r) {
  syscall1(SYS_exit, r);
  while (1)
    ;
}

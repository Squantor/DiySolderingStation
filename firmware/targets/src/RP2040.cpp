/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
@file RP2040 interrupts, based on the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
*/

#if defined(__cplusplus)
extern "C" {
#endif

void Dummy_Handler(void);

#if defined(__cplusplus)
}  // extern "C"
#endif

#include "cortexm0plus_irqs.cpp"
#include "isr_RP2040.cpp"

void Dummy_Handler(void) {
  while (1)
    ;
}

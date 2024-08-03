/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#if defined(__cplusplus)
extern "C" {
#endif

void Dummy_Handler(void);

#if defined(__cplusplus)
}  // extern "C"
#endif

#include "cortexm_irqs_standard.cpp"
#include "isr_STM32F103C8.cpp"

void Dummy_Handler(void) {
  while (1)
    ;
}

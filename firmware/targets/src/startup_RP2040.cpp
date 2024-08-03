/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
@file RP2040 startup code, based on the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
*/
#include <stdint.h>

/* We define some clock definitions here to silence a warning */
#define CLOCK_XTAL (12000000u)
#define CLOCK_CPU (12000000u)

#include <mcu_ll.h>

extern int main(void);

#if defined(__cplusplus)
extern "C" {
#endif

// vector table
extern void (*const core_vector_table[16])(void);
// linker symbols used to prepare C/C++ environment
extern uint32_t _flash_start;
extern uint32_t _text_start;
extern uint32_t _text_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _stack_top;
extern void _stack_end(void);
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);

void Reset_Handler(void);

#if defined(__cplusplus)
}  // extern "C"
#endif

/**
 * @brief Reset handler
 */
__attribute__((section(".romfunc"))) void Reset_Handler(void) {
  uint32_t *src, *dst;
  // Copy flash to RAM based sections .text and .data
  // we copy everything in one go starting at _text_start until _data_end
  src = &_flash_start;
  dst = &_text_start;
  while (dst < &_data_end) *dst++ = *src++;
  // zero out bss
  dst = &_bss_start;
  while (dst < &_bss_end) *dst++ = 0;

  // execute C++ constructors
  auto preInitFunc = __preinit_array_start;
  while (preInitFunc < __preinit_array_end) {
    (*preInitFunc)();
    preInitFunc++;
  }
  auto initFunc = __init_array_start;
  while (initFunc < __init_array_end) {
    (*initFunc)();
    initFunc++;
  }

  SCB->VTOR = reinterpret_cast<uint32_t>(core_vector_table);

  asm(R"asm(
    msr    msp, %[sp]
    bx     %[reset]
    )asm" ::[sp] "r"(&_stack_top),
      [reset] "r"(main));

  __builtin_unreachable();
}

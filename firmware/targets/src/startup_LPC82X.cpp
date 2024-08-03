/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
 * LPC82X specific startup file, adding division routines from ROM
 *
 *
 * Put together by Paul Sokolovsky based on article by Vanya Sergeev
 * http://dev.frozeneskimo.com/notes/cortex_cmsis/ , GNU ld documentation
 * and numerous other public resources. Further modified by Bart Bilos
 *
 */

#include <stdint.h>

extern int main(void);

#if defined(__cplusplus)
extern "C" {
#endif

/* Linker symbols that are used to prepare the C/C++ environment */
extern uint32_t _flash_data;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern void _stack_end(void);
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);

void Reset_Handler(void);

#define PTR_ROM_DRIVER_TABLE ((unsigned int *)(0x1FFF1FF8))
// Variables to store addresses of idiv and udiv functions within MCU ROM
unsigned int *pDivRom_idiv;
unsigned int *pDivRom_uidiv;

#if defined(__cplusplus)
}  // extern "C"
#endif

__attribute__((section(".romfunc"))) void Reset_Handler(void) {
  uint32_t *src, *dst;

  /* Copy data section from flash to RAM */
  src = &_flash_data;
  dst = &_data_start;
  while (dst < &_data_end) *dst++ = *src++;

  /* Clear the bss section*/
  dst = &_bss_start;
  while (dst < &_bss_end) *dst++ = 0;

  /* execute c++ constructors */
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

  // Get address of Integer division routines function table in ROM
  unsigned int *div_ptr = (unsigned int *)((unsigned int *)*(PTR_ROM_DRIVER_TABLE))[4];
  // Get addresses of integer divide routines in ROM
  // These address are then used by the code in aeabi_romdiv_patch.s
  pDivRom_idiv = (unsigned int *)div_ptr[0];
  pDivRom_uidiv = (unsigned int *)div_ptr[1];

  main();

  /* we omit executing destructors so gcc can optimize them away*/

  while (1)
    ;
}

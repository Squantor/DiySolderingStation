/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
@file CortexM0plus base ISR's, based on the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
*/
#if defined(__cplusplus)
extern "C" {
#endif

extern void _stack_top(void);
extern void Reset_Handler(void);
extern void Dummy_Handler(void);

void NMI_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined(__cplusplus)
}  // extern "C"
#endif

/* 16 standard Cortex-M vectors - these are present in every MCU */
extern void (*const core_vector_table[16])(void);
__attribute__((used, section(".cortex_vectors"))) void (*const core_vector_table[16])(void) = {
  // See http://sourceware.org/binutils/docs/ld/Source-Code-Reference.html
  // why the address is used here (if not intuitive)
  &_stack_top,       /*!< stack pointer, not used in the RP2040*/
  Reset_Handler,     /*!< Reset handler address, not used in the RP2040 */
  NMI_Handler,       /*!<  */
  HardFault_Handler, /*!<  */
  0,                 /*!<  */
  0,                 /*!<  */
  0,                 /*!<  */
  0,                 /*!<  */
  0,                 /*!<  */
  0,                 /*!<  */
  0,                 /*!<  */
  SVC_Handler,       /*!<  */
  DebugMon_Handler,  /*!<  */
  0,                 /*!<  */
  PendSV_Handler,    /*!<  */
  SysTick_Handler,   /*!<  */
};

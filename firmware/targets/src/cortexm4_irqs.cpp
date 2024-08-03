/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#if defined(__cplusplus)
extern "C" {
#endif

extern void _stack_end(void);
extern void Reset_Handler(void);
extern void Dummy_Handler(void);

void NMI_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
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
  &_stack_end,
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
};

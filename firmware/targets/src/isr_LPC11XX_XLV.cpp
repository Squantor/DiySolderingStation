/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#if defined(__cplusplus)
extern "C" {
#endif

void WAKEUP0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP4_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP5_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP6_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP7_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP8_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP9_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP10_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP11_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WAKEUP12_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SSP1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIMER16_0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIMER16_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIMER32_0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIMER32_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SSP0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WDT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void BOD_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void FMC_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOINT3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOINT2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOINT1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOINT0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined(__cplusplus)
}  // extern "C"
#endif

extern void (*const vendor_vector_table[])(void);
void (*const vendor_vector_table[])(void) __attribute__((used, section(".vendor_vectors"))) = {
  WAKEUP0_IRQHandler,    // 00: WAKEUP0
  WAKEUP1_IRQHandler,    // 01: WAKEUP1
  WAKEUP2_IRQHandler,    // 02: WAKEUP2
  WAKEUP3_IRQHandler,    // 03: WAKEUP3
  WAKEUP4_IRQHandler,    // 04: WAKEUP4
  WAKEUP5_IRQHandler,    // 05: WAKEUP5
  WAKEUP6_IRQHandler,    // 06: WAKEUP6
  WAKEUP7_IRQHandler,    // 07: WAKEUP7
  WAKEUP8_IRQHandler,    // 08: WAKEUP8
  WAKEUP9_IRQHandler,    // 09: WAKEUP9
  WAKEUP10_IRQHandler,   // 10: WAKEUP10
  WAKEUP11_IRQHandler,   // 11: WAKEUP11
  WAKEUP12_IRQHandler,   // 12: WAKEUP12
  0,                     // 13: Reserved
  SSP1_IRQHandler,       // 14: SSP1 Interrupt
  I2C_IRQHandler,        // 15: I2C0
  TIMER16_0_IRQHandler,  // 16: CT16B0 (16-bit Timer 0)
  TIMER16_1_IRQHandler,  // 17: CT16B1 (16-bit Timer 1)
  TIMER32_0_IRQHandler,  // 18: CT32B0 (32-bit Timer 0)
  TIMER32_1_IRQHandler,  // 19: CT32B1 (32-bit Timer 1)
  SSP0_IRQHandler,       // 20: SPI/SSP0 Interrupt
  UART_IRQHandler,       // 21: UART0
  0,                     // 22: Reserved
  0,                     // 23: Reserved
  ADC_IRQHandler,        // 24: ADC   (A/D Converter)
  WDT_IRQHandler,        // 25: WDT   (Watchdog Timer)
  BOD_IRQHandler,        // 26: BOD   (Brownout Detect)
  FMC_IRQHandler,        // 16+27: IP2111 Flash Memory Controller
  PIOINT3_IRQHandler,    // 28: PIO INT3
  PIOINT2_IRQHandler,    // 29: PIO INT2
  PIOINT1_IRQHandler,    // 30: PIO INT1
  PIOINT0_IRQHandler,    // 31: PIO INT0
};

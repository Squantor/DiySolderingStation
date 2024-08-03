/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#if defined(__cplusplus)
extern "C" {
#endif

void SPI0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SCT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void MRT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void CMP_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WDT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void BOD_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WKT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT4_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT5_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT6_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PININT7_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined(__cplusplus)
}  // extern "C"
#endif

extern void (*const vendor_vector_table[])(void);
void (*const vendor_vector_table[])(void) __attribute__((used, section(".vendor_vectors"))) = {
  SPI0_IRQHandler,
  SPI1_IRQHandler,
  0,
  UART0_IRQHandler,
  UART1_IRQHandler,
  UART2_IRQHandler,
  0,
  0,
  I2C0_IRQHandler,
  SCT_IRQHandler,
  MRT_IRQHandler,
  CMP_IRQHandler,
  WDT_IRQHandler,
  BOD_IRQHandler,
  0,
  WKT_IRQHandler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  PININT0_IRQHandler,
  PININT1_IRQHandler,
  PININT2_IRQHandler,
  PININT3_IRQHandler,
  PININT4_IRQHandler,
  PININT5_IRQHandler,
  PININT6_IRQHandler,
  PININT7_IRQHandler,
};

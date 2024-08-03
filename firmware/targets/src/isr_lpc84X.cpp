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
void DAC0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SCT0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void MRT0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void CMP_CAPT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WDT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void BOD_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WKT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC0_SEQA_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC0_SEQB_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC0_THCMP_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC0_OVR_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void DMA0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void CTIMER0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT4_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT5_DAC1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT6_USART3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT7_USART4_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined(__cplusplus)
}  // extern "C"
#endif

extern void (*const vendor_vector_table[])(void);
void (*const vendor_vector_table[])(void) __attribute__((used, section(".vendor_vectors"))) = {
  SPI0_IRQHandler,             // 16: SPI0 interrupt
  SPI1_IRQHandler,             // 17: SPI1 interrupt
  DAC0_IRQHandler,             // 18: DAC0 interrupt
  USART0_IRQHandler,           // 19: USART0 interrupt
  USART1_IRQHandler,           // 20: USART1 interrupt
  USART2_IRQHandler,           // 21: USART2 interrupt
  0,                           // 22: Reserved
  I2C1_IRQHandler,             // 23: I2C1 interrupt
  I2C0_IRQHandler,             // 24: I2C0 interrupt
  SCT0_IRQHandler,             // 25: State configurable timer interrupt
  MRT0_IRQHandler,             // 26: Multi-rate timer interrupt
  CMP_CAPT_IRQHandler,         // 27: Analog comparator or Capacitive Touch interrupt
  WDT_IRQHandler,              // 28: Windowed watchdog timer interrupt
  BOD_IRQHandler,              // 29: BOD interrupts
  FLASH_IRQHandler,            // 30: flash interrupt
  WKT_IRQHandler,              // 31: Self-wake-up timer interrupt
  ADC0_SEQA_IRQHandler,        // 32: ADC0 sequence A completion.
  ADC0_SEQB_IRQHandler,        // 33: ADC0 sequence B completion.
  ADC0_THCMP_IRQHandler,       // 34: ADC0 threshold compare and error.
  ADC0_OVR_IRQHandler,         // 35: ADC0 overrun
  DMA0_IRQHandler,             // 36: DMA0 interrupt
  I2C2_IRQHandler,             // 37: I2C2 interrupt
  I2C3_IRQHandler,             // 38: I2C3 interrupt
  CTIMER0_IRQHandler,          // 39: Timer interrupt
  PIN_INT0_IRQHandler,         // 40: Pin interrupt 0 or pattern match engine slice 0 interrupt
  PIN_INT1_IRQHandler,         // 41: Pin interrupt 1 or pattern match engine slice 1 interrupt
  PIN_INT2_IRQHandler,         // 42: Pin interrupt 2 or pattern match engine slice 2 interrupt
  PIN_INT3_IRQHandler,         // 43: Pin interrupt 3 or pattern match engine slice 3 interrupt
  PIN_INT4_IRQHandler,         // 44: Pin interrupt 4 or pattern match engine slice 4 interrupt
  PIN_INT5_DAC1_IRQHandler,    // 45: Pin interrupt 5 or pattern match engine slice 5 interrupt or DAC1 interrupt
  PIN_INT6_USART3_IRQHandler,  // 46: Pin interrupt 6 or pattern match engine slice 6 interrupt or UART3 interrupt
  PIN_INT7_USART4_IRQHandler,  // 47: Pin interrupt 7 or pattern match engine slice 7 interrupt or UART4 interrupt
};

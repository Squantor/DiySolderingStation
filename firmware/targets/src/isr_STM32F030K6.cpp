/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#if defined(__cplusplus)
extern "C" {
#endif

void WWDG_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void EXTI0_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void EXTI2_3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void EXTI4_15_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void DMA1_Channel2_3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void DMA1_Channel4_5_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM14_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM15_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM16_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void TIM17_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined(__cplusplus)
}  // extern "C"
#endif

extern void (*const vendor_vector_table[])(void);
void (*const vendor_vector_table[])(void) __attribute__((used, section(".vendor_vectors"))) = {
  WWDG_IRQHandler,
  0,
  RTC_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_1_IRQHandler,
  EXTI2_3_IRQHandler,
  EXTI4_15_IRQHandler,
  0,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_3_IRQHandler,
  DMA1_Channel4_5_IRQHandler,
  ADC1_IRQHandler,
  TIM1_BRK_UP_TRG_COM_IRQHandler,
  TIM1_CC_IRQHandler,
  0,
  TIM3_IRQHandler,
  0,
  0,
  TIM14_IRQHandler,
  TIM15_IRQHandler,
  TIM16_IRQHandler,
  TIM17_IRQHandler,
  I2C1_IRQHandler,
  I2C2_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  0,
  0,
  0,
};

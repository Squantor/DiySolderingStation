/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
@file RP2040 ISR's, based on the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
*/

#if defined(__cplusplus)
extern "C" {
#endif

void timer_0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void timer_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void timer_2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void timer_3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void pwm_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void usbctrl_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void xip_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void pio0_0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void pio0_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void pio1_0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void pio1_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void dma_0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void dma_1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void io_bank0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void io_qspi_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void sio_proc0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void sio_proc1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void clocks_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void spi0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void spi1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void uart0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void uart1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void adc_fifo_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void i2c0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void i2c1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void rtc_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined(__cplusplus)
}  // extern "C"
#endif

extern void (*const vendor_vector_table[])(void);
void (*const vendor_vector_table[])(void) __attribute__((used, section(".vendor_vectors"))) = {
  timer_0_IRQHandler,   /**< Timer 0 IRQ handler*/
  timer_1_IRQHandler,   /**< Timer 1 IRQ handler*/
  timer_2_IRQHandler,   /**< Timer 2 IRQ handler*/
  timer_3_IRQHandler,   /**< Timer 3 IRQ handler*/
  pwm_IRQHandler,       /**< PWM IRQ handler*/
  usbctrl_IRQHandler,   /**< USB IRQ handler*/
  xip_IRQHandler,       /**< XIP IRQ handler*/
  pio0_0_IRQHandler,    /**< PIO0_0 IRQ handler*/
  pio0_1_IRQHandler,    /**< PIO0_1 IRQ handler*/
  pio1_0_IRQHandler,    /**< PIO1_0 IRQ handler*/
  pio1_1_IRQHandler,    /**< PIO1_1 IRQ handler*/
  dma_0_IRQHandler,     /**< DMA 0 IRQ handler*/
  dma_1_IRQHandler,     /**< DMA 1 IRQ handler*/
  io_bank0_IRQHandler,  /**< IO bank 0 IRQ handler*/
  io_qspi_IRQHandler,   /**< IO QSPI IRQ handler*/
  sio_proc0_IRQHandler, /**< SIO CPU 0 IRQ handler*/
  sio_proc1_IRQHandler, /**< SIO CPU 1 IRQ handler*/
  clocks_IRQHandler,    /**< clocks IRQ handler*/
  spi0_IRQHandler,      /**< SPI0 IRQ handler*/
  spi1_IRQHandler,      /**< SPI1 IRQ handler*/
  uart0_IRQHandler,     /**< UART0 IRQ handler*/
  uart1_IRQHandler,     /**< UART1 IRQ handler*/
  adc_fifo_IRQHandler,  /**< ADC FIFO IRQ handler*/
  i2c0_IRQHandler,      /**< I2C0 IRQ handler*/
  i2c1_IRQHandler,      /**< I2C1 IRQ handler*/
  rtc_IRQHandler,       /**< RTC IRQ handler*/
};

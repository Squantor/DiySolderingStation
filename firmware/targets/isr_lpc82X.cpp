/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#if defined (__cplusplus)
extern "C" {
#endif

void SPI0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void SCT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void MRT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void CMP_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WDT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void BOD_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void WKT_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC_SEQA_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC_SEQB_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC_THCMP_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void ADC_OVR_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void DMA_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2C3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT0_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT1_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT2_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT3_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT4_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT5_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT6_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIN_INT7_IRQHandler(void) __attribute__((weak, alias("Dummy_Handler")));

#if defined (__cplusplus)
} // extern "C"
#endif

extern void (* const vendor_vector_table[])(void);
void (* const vendor_vector_table[])(void) __attribute__ ((used,section(".vendor_vectors"))) = {
    SPI0_IRQHandler,                         // SPI0 controller
    SPI1_IRQHandler,                         // SPI1 controller
    0,                                       // Reserved
    UART0_IRQHandler,                        // UART0
    UART1_IRQHandler,                        // UART1
    UART2_IRQHandler,                        // UART2
    0,                                       // Reserved
    I2C1_IRQHandler,                         // I2C1 controller
    I2C0_IRQHandler,                         // I2C0 controller
    SCT_IRQHandler,                          // Smart Counter Timer
    MRT_IRQHandler,                          // Multi-Rate Timer
    CMP_IRQHandler,                          // Comparator
    WDT_IRQHandler,                          // Watchdog
    BOD_IRQHandler,                          // Brown Out Detect
    FLASH_IRQHandler,                        // Flash Interrupt
    WKT_IRQHandler,                          // Wakeup timer
    ADC_SEQA_IRQHandler,                     // ADC sequence A completion
    ADC_SEQB_IRQHandler,                     // ADC sequence B completion
    ADC_THCMP_IRQHandler,                    // ADC threshold compare
    ADC_OVR_IRQHandler,                      // ADC overrun
    DMA_IRQHandler,                          // DMA
    I2C2_IRQHandler,                         // I2C2 controller
    I2C3_IRQHandler,                         // I2C3 controller
    0,                                       // Reserved
    PIN_INT0_IRQHandler,                     // PIO INT0
    PIN_INT1_IRQHandler,                     // PIO INT1
    PIN_INT2_IRQHandler,                     // PIO INT2
    PIN_INT3_IRQHandler,                     // PIO INT3
    PIN_INT4_IRQHandler,                     // PIO INT4
    PIN_INT5_IRQHandler,                     // PIO INT5
    PIN_INT6_IRQHandler,                     // PIO INT6
    PIN_INT7_IRQHandler,                     // PIO INT7
};
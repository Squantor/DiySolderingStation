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
#ifndef BOARD_HPP
#define BOARD_HPP

#define TICKS_PER_S         (100)

#define IOCON_XTAL_IN       IOCON_PIO8
#define IOCON_XTAL_OUT      IOCON_PIO9

#define IOCON_UART_TX       IOCON_PIO13
#define PIN_UART_TX         (13u)
#define IOCON_UART_RX       IOCON_PIO17
#define PIN_UART_RX         (17u)

#define IOCON_ZEROCROSS_DET IOCON_PIO15
#define PIN_ZEROCROSS_DET   (15u)

#define IOCON_SSR_CTRL      IOCON_PIO7
#define PIN_SSR_CTRL        (7u)

#define UART_DEBUG          LPC_USART0
#define UART_BAUD_RATE      (115200u)

#define PININT_ZEROCROSS    (0u)

#define CLOCK_MAIN_SOURCE   SYSCTL_MAINCLKSRC_PLLOUT
#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (30000000u)
#define CLOCK_AHB           (30000000u)
#define CLOCK_MAIN          (60000000u)

void boardInit(void);

#endif
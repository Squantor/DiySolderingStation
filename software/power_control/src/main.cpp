/*
MIT License

Copyright (c) 2020 Bart Bilos

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

/*
Soldering station power control demo
*/

#include <board.hpp>
#include <mcu_ll.h>
#include <stream_uart.hpp>
#include <strings.hpp>
#include <print.h>
#include <time_delay.hpp>
#include <time_interval.hpp>

volatile uint32_t zerocrosses = 0;

extern "C" 
{
    void PININT0_IRQHandler(void)
    {
        PinintClearIntStatus(LPC_PININT, PININTCH(PININT_ZEROCROSS));
        zerocrosses++;
        // clear solid state relay output
    }
}

int main()
{
    uint8_t character;
    uint32_t zerocrossCount = 0;
    uint8_t accumulator = 0;
    uint8_t increment = 7;
    uint8_t endValue = 100;
    uint16_t count = 0;
    timeInterval statusInterval(SEC2TICKS(1));
    boardInit();
    dsPuts(&streamUart, strHello);
    while (1) 
    {
        // did we get a zero crossing?
        if(zerocrossCount != zerocrosses)
        {
            // increment zero cross trigger accumulator
            accumulator += increment;
            // do we need to activate the power controller?
            if(accumulator > endValue)
            {
                // activate for this zero cross 
                count++;
                // reset trigger accumulator
                accumulator -= endValue;
            }
            zerocrossCount = zerocrosses;
        }     

        if((UartGetStatus(UART_DEBUG) & UART_STAT_RXRDY) != 0) 
        {
            character = UartReadByte(UART_DEBUG);
            while((UartGetStatus(UART_DEBUG) & UART_STAT_TXRDY) == 0) 
                ;
            UartSendByte(UART_DEBUG, character);
        }
        if(statusInterval.elapsed())
        {
            dsPuts(&streamUart, strZerocrosses);
            printDecU32(&streamUart, zerocrosses);
            dsPuts(&streamUart, strAccumulator);
            printDecU16(&streamUart, count);
            dsPuts(&streamUart, strCrLf);
            count = 0;
        }
    }
}

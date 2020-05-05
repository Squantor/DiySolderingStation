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
#ifndef TIME_DELAY_HPP
#define TIME_DELAY_HPP

#include <arm_systick.h>
#include <board.hpp>

#if !defined(TICKS_PER_S)
    #warning Ticks per second (TICKS_PER_S) is not defined!
    #define TICKS_PER_S     (100u)
#endif

typedef struct {
    timeTicks timeDelayDuration;
    // at what time to trigger
    timeTicks timeDelayTrigger;
} timeDelay_t;

typedef enum {
    delayNotReached, // we have not reached the delay yet
    delayReached,    // we are at just the right time
    delayExceeded,   // we have exceeded the delay
} resultDelay_t;

#define SEC2TICKS(sec) ((timeTicks)(sec * TICKS_PER_S))

extern volatile timeTicks ticks;

// initialize the time delay structure
void timeDelayInit(timeDelay_t &delayData, timeTicks delay);
// non blocking check if we have a reached a time interval
resultDelay_t timeDelayCheck(timeDelay_t &delayData);
// blocking delay
void timeDelaySimple(timeTicks delay);

#endif
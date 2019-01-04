/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_Spectral3_types.h"

#define __Spectral3_TIMER__

static void spectral3_configTimer()
{


    // Configure Timer
}

void Timer_interrupt()
{
    spectral3_tick();
    // Reset Flag
}
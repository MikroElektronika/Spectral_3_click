/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_Spectral3_types.h"

#define __Spectral3_TIMER__

static void spectral3_configTimer()
{
    T1CON         = 0x8000;
    T1IE_bit = 1;
    T1IF_bit = 0;
    IPC0         = IPC0 | 0x1000;
    PR1                 = 4000;
}
//
void Timer_interrupt() iv IVT_ADDR_T1INTERRUPT
{
    T1IF_bit = 0;
    spectral3_tick();
}
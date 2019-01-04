#include "Click_Spectral3_types.h"

const uint32_t _SPECTRAL3_TIMER_LIMIT      = 5;            // 5 ticks
const uint16_t _SPECTRAL3_BUF_WARNING      = 192;        // 192 bytes activate warning
const uint8_t  _SPECTRAL3_POLL_ENABLE      = 0;         // poll enabled
const uint8_t  _SPECTRAL3_CALLBACK_ENABLE  = 1;            // calback disabled

const uint32_t _SPECTRAL3_UART_CFG[ 4 ] = 
{
        115200,
        _UART_8_BIT_DATA, 
        _UART_NOPARITY, 
        _UART_ONE_STOPBIT
};
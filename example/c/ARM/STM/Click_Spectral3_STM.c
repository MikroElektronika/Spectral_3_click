/*
Example for Spectral3 Click

    Date          : Feb 2018.
    Author        : MikroE Team

Test configuration STM32 :
    
    MCU              : STM32F107VCT6
    Dev. Board       : EasyMx PRO v7 for STM32
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with Spectral and UART used for infromation logging
- Application Initialization - Initializes driver, reset module and sends
command for the default module configuration
- Application Task - Sends the command to start reading data.
   Then logs to USBUART, six read values every 1 second.


*/


#include "Click_Spectral3_types.h"
#include "Click_Spectral3_config.h"
#include "Click_Spectral3_timer.h"


uint16_t readData[6] ;
uint8_t rspBuffer[100]= {0};
char text[100];

uint8_t cmdData[7] = {'A','T','D','A','T','A',0};
uint8_t cmdAT[3] = {'A','T',0};
uint8_t cmdGain[9] = {'A','T','G','A','I','N','=','2',0};
uint8_t cmdMode[10] = {'A','T','T','C','S','M','D','=','2',0};


void spectral3_default_handler( uint8_t *rsp, uint8_t *evArgs )
{
    char *ptr = rsp;
    mikrobus_logWrite( ptr, _LOG_LINE );
    strcpy(rspBuffer,ptr);
}

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_uartInit( _MIKROBUS1, &_SPECTRAL3_UART_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 115200 );

    mikrobus_logWrite( " --- System init --- ", _LOG_LINE );

}

void applicationInit()
{
    spectral3_configTimer();
    spectral3_uartDriverInit((T_SPECTRAL3_P)&_MIKROBUS1_GPIO, (T_SPECTRAL3_P)&_MIKROBUS1_UART);
    RXNEIE_USART3_CR1_bit = 1;
    NVIC_IntEnable( IVT_INT_USART3 );
    EnableInterrupts();
    
    spectral3_coreInit( &spectral3_default_handler, 1500 );
    spectral3_reset();
    Delay_ms( 500 );

    // Settings
    spectral3_cmdSingle(&cmdAT[0]);
    spectral3_cmdSingle(&cmdGain[0]);
    spectral3_cmdSingle(&cmdMode[0]);
    Delay_ms( 1000 );
}


void applicationTask()
{
    spectral3_process();

    spectral3_cmdSingle(&cmdData[0]);
    spectral3_getData(&rspBuffer[0],&readData[0]);
    IntToStr(readData[0],text);
    mikrobus_logWrite( "-- R value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[1],text);
    mikrobus_logWrite( "-- S value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[2],text);
    mikrobus_logWrite( "-- T value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[3],text);
    mikrobus_logWrite( "-- U value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[4],text);
    mikrobus_logWrite( "-- V value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[5],text);
    mikrobus_logWrite( "-- W value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    mikrobus_logWrite( "---------------------", _LOG_LINE );

    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}

/*
 * UART Interrupt
 */
//
void RX_ISR() iv IVT_INT_USART3 ics ICS_AUTO
{
    if( RXNE_USART3_SR_bit )
    {
        char tmp = USART3_DR;
        spectral3_putc( tmp );
    }
}
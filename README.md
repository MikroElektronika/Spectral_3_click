![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Spectral3 Click

- **CIC Prefix**  : SPECTRAL3
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : Feb 2018.

---

### Software Support

We provide a library for the Spectral3 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2356/spectral-3-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library carries generic command parser adopted for AT command based modules. 
Generic parser 

Key functions :

- ``` spectral3_cmdSingle ``` - Sends provided command to the module
- ``` spectral3_setHandler ``` - Handler assignation to the provied command
- ``` spectral3_modulePower ``` - Turn on module

**Examples Description**

The demo application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with Spectral 3 and UART used for infromation logging.
- Application Initialization - Initializes driver, reset module and sends
commands for auto baudrate, GAIN configuration and Mode configuration.
- Application Task (Code Snippet) - Sends the command to start reading data.
Then logs to USBUART, all six values read from Spectral 3 click. Operation 
is repeated every 1 second.

```.c
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
```

Alongside with the demo application timer initialization functions are provided.
Note that timer is configured acording to default develoment system and 
MCUs, changing the system or MCU may require update of timer init and timer ISR 
functions.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2356/spectral-3-click) page.

Other mikroE Libraries used in the example:

- UART Library
- Conversion Library
- C_String Library

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---

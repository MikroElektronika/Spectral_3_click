/*
    __spectral3_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __spectral3_driver.h
@brief    Spectral3 Driver
@mainpage Spectral3 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   SPECTRAL3
@brief      Spectral3 Click Driver
@{

| Global Library Prefix | **SPECTRAL3** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Feb 2018.**      |
| Developer             | **MikroE Team**     |

Command parser core configured for AT command based GSM devices.

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"
#include "stdbool.h"

#ifndef _SPECTRAL3_H_
#define _SPECTRAL3_H_

/**
 * @macro T_SPECTRAL3_P 
 * @brief Global Abstract Macro 
 */
#define T_SPECTRAL3_P    const uint8_t*

/** @defgroup SPECTRAL3_AT_CMDS AT Command Types */                /** @{ */

extern const uint8_t _SPECTRAL3_UNKNOWN ;                                   /**< Unknown command type */
extern const uint8_t _SPECTRAL3_TEST    ;                                   /**< Test command type */
extern const uint8_t _SPECTRAL3_SET     ;                                   /**< Set command type */
extern const uint8_t _SPECTRAL3_GET     ;                                   /**< Get command type */
extern const uint8_t _SPECTRAL3_URC     ;                                   /**< URC */
extern const uint8_t _SPECTRAL3_EXEC    ;                                   /**< Exec command type */
                                                                       /** @} */
/** @defgroup SPECTRAL3_AT_EVARG Spectral3 Event Arguments */   /** @{ */

extern const uint8_t _SPECTRAL3_EVARG_START_T    ;                          /**< Event argument 0 */
extern const uint8_t _SPECTRAL3_EVARG_END_T      ;                          /**< Event argument 1 */
extern const uint8_t _SPECTRAL3_EVARG_EVENT_T    ;                          /**< Event argument 2 */
                          
extern const uint8_t _SPECTRAL3_EVENT_RESPONSE   ;                          /**< Response */
extern const uint8_t _SPECTRAL3_EVENT_TIMEOUT    ;                          /**< Timeout */
extern const uint8_t _SPECTRAL3_EVENT_BUFFER_OUT ;                          /**< Buffer warning */
extern const uint8_t _SPECTRAL3_EVENT_CALLBACK   ;                          /** Callback */

extern const uint8_t _SPECTRAL3_XYZ_FLAG     ;
extern const uint8_t _SPECTRAL3_LUX_FLAG     ;
extern const uint8_t _SPECTRAL3_CCT_FLAG     ;
extern const uint8_t _SPECTRAL3_SMALL_XY_FLAG;
extern const uint8_t _SPECTRAL3_UV_FLAG      ;
extern const uint8_t _SPECTRAL3_DUV_FLAG     ;
extern const uint8_t _SPECTRAL3_XYZR_FLAG    ;
extern const uint8_t _SPECTRAL3_DATA_FLAG    ;
extern const uint8_t _SPECTRAL3_NO_FLAG      ;
                                                                      /** @} */
/**
 * @typedef T_spectral3_handler
 * @brief Handler Prototype
 */
typedef void ( *T_spectral3_handler )( char *buffer, uint8_t *evArgs );

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup SPECTRAL3_INIT Driver Init Functions */              /** @{ */

/**
 * @brief Driver Initialization
 * 
 * @param[in] gpioObj pointer to GPIO object
 * @param[in] uartObj pointer to UART object
 *
 * Default UART driver intializaton function.
 */
void spectral3_uartDriverInit(T_SPECTRAL3_P gpioObj, T_SPECTRAL3_P uartObj);

/**
 * @brief Core Initialization
 *
 * @param[in] defaultHdl        default handler
 * @param[in] defaultWdog       default watchdog
 *
 * Initialization should be executed before any other function. User can
 * execute this function later inside the application to reset AT Engine to
 * the default state.
 */
void spectral3_coreInit( T_spectral3_handler defaultHdl, uint32_t defaultWdog );

                                                                       /** @} */
/** @defgroup SPECTRAL3_FUNC Driver Functions */                   /** @{ */


/**
 * @brief Function returns DRY pin state
 *
 * @return state  DRY state
 */
uint8_t spectral3_getState();
/**
 * @brief Function for reset module
 */
void spectral3_reset();

/**
 * @brief Read calibrated X, Y, and Z color data.
 *
 * @param[in] rsp           pointer to buffer
 * @param[out] xyzData       pointer to the buffer in which will be written
 *
 */
void spectral3_getColor_Data(uint8_t *rsp, uint8_t *);

/**
 * @brief Read raw X, Y, and Z data.
 *
 * @param[in] rsp            pointer to buffer
 * @param[out] xyzrData       pointer to the buffer in which will be written
 */
void spectral3_getXYZ_Data(uint8_t *rsp, uint8_t *xyzrData);

/**
 * @brief Read calibrated x and y for CIE 1931 color gamut.
 *
 * @param[in] rsp            pointer to buffer
 * @param[out] xyData       pointer to the buffer in which will be written
 */
void spectral3_getXYsmall_Data(uint8_t *rsp, uint8_t *xyData);

/**
 * @brief Read the calibrated LUX value from the sensor.
 *
 * @param[in] rsp             pointer to buffer
 *
 * @return lux value
 */
uint8_t spectral3_getLUX_Data(uint8_t *rsp);

/**
 * @brief Read the calibrated CCT value from the sensor.
 *
 * @param[in] rsp             pointer to buffer
 *
 * @return cct value
 */
uint8_t spectral3_getCCT_Data(uint8_t *rsp);

/**
 * @brief Read calibrated u’, v’ and u, v for CIE 1976 color gamut.
 *
 * @param[in] rsp            pointer to buffer
 * @param[out] uvData        pointer to the buffer in which will be written
 */
void spectral3_getUV_Data(uint8_t *rsp, uint16_t *uvData);

/**
 * @brief Read raw X, Y, Z and NIR data as well as two special internal registers D, & C.
 *
 * @param[in] rsp            pointer to buffer
 * @param[out] _Data         pointer to the buffer in which will be written
 */
void spectral3_getData(char *rsp, uint16_t *_Data);

/**
 * @brief Read calibrated Duv for CIE 1976-color gamut.
 *
 * @param[in] rsp             pointer to buffer
 *
 * @return duv value
 */
uint8_t spectral3_getDUV_Data(uint8_t *rsp);



void spectral3_DTE_setState(bool state);
void spectral3_modulePower( bool powerState );



/** 
 * @brief Hardware Flow Control State
 *
 * @param[in] hfcState 
 *
 * Enables or disables Hardware Flow Control.
 */
void spectral3_hfcEnable( bool hfcState );

/**
 * @brief Enables or disables module power
 *
 * @param[in] powerState
 *
 * Turn ON or OFF the module.
 */
void spectral3_modulePower( bool powerState );

/**
 * @brief Receive
 *
 * @param[in] rxInput       char received from the module
 *
 * Function is used to populate response buffer with characters received from
 * the module. This function should be placed inside UART ISR function.It also
 * can be used inside function which constatnly poll the UART RX register.
 */
void spectral3_putc( char rxInput );

/**
 * @brief Engine Tick
 *
 * Function must be placed inside the Timer ISR function which will be called
 * every one millisecond.
 */
void spectral3_tick();

/**
 * @brief Save AT Command to Storage
 *
 * @param[in] pCmd          command string
 * @param[in] timeout       timeout for provided command
 * @param[in] pHandler      handler for provided command
 *
 * Saves handlers and timeout for the particular command.
 */
uint16_t spectral3_setHandler( char *pCmd, uint32_t timeout, T_spectral3_handler pHandler );

/**
 * @brief Simple AT Command
 *
 * @param[in] pCmd          pointer to command string
 *
 * Function should be used in case of simple AT commands which have no
 * additional arguments expected. Most of the AT Commands uses this function.
 */
void spectral3_cmdSingle( char *pCmd );

/**
 * @brief Doble AT Command
 *
 * @param[in] pCmd          pointer to command string
 * @param[in] pArg1         pointer to the string used as additional argument
 *
 * Function should be used with AT commands which expects additional data after
 * the module responses with specific character. In most cases special character
 * is ">" like in example of AT command for SMS sending.
 */
void spectral3_cmdDouble( char *pCmd, char *pArg1 );

/**
 * @brief Triple AT Command
 *
 * @param[in] pCmd          pointer to command string
 * @param[in] pArg1         pointer to the string used as additional argument
 * @param[in] pArg2         pointer to the second additional argument
 *
 * Function should be used with AT command which excepts two additional
 * parameters after the execution of the command. This kind of AT functions are
 * very rare.
 */
void spectral3_cmdTriple( char *pCmd, char *pArg1, char *pArg2 );

/**
 * @brief AT Engine State Machine
 *
 * This function should be placed inside the infinite while loop.
 */
void spectral3_process();
                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Spectral3_STM.c
    @example Click_Spectral3_TIVA.c
    @example Click_Spectral3_CEC.c
    @example Click_Spectral3_KINETIS.c
    @example Click_Spectral3_MSP.c
    @example Click_Spectral3_PIC.c
    @example Click_Spectral3_PIC32.c
    @example Click_Spectral3_DSPIC.c
    @example Click_Spectral3_AVR.c
    @example Click_Spectral3_FT90x.c
    @example Click_Spectral3_STM.mbas
    @example Click_Spectral3_TIVA.mbas
    @example Click_Spectral3_CEC.mbas
    @example Click_Spectral3_KINETIS.mbas
    @example Click_Spectral3_MSP.mbas
    @example Click_Spectral3_PIC.mbas
    @example Click_Spectral3_PIC32.mbas
    @example Click_Spectral3_DSPIC.mbas
    @example Click_Spectral3_AVR.mbas
    @example Click_Spectral3_FT90x.mbas
    @example Click_Spectral3_STM.mpas
    @example Click_Spectral3_TIVA.mpas
    @example Click_Spectral3_CEC.mpas
    @example Click_Spectral3_KINETIS.mpas
    @example Click_Spectral3_MSP.mpas
    @example Click_Spectral3_PIC.mpas
    @example Click_Spectral3_PIC32.mpas
    @example Click_Spectral3_DSPIC.mpas
    @example Click_Spectral3_AVR.mpas
    @example Click_Spectral3_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __spectral3_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */

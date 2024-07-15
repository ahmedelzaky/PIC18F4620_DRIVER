/* 
 * File:   hal_usart.h
 * Author: zekwa
 *
 * Created on July 14, 2024, 11:04 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* ----------------- Includes -----------------*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#if (EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) ||(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#include "../../Queue/queue.h"
#endif

/* ----------------- Macro Declarations -----------------*/

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/* ----------------- Macro Functions Declarations -----------------*/
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE()    (TXSTAbits.TXEN = 1)
#define EUSART_ASYNCHRONOUS_TX_DISABLE()   (TXSTAbits.TXEN = 0)
/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE()    (RCSTAbits.CREN = 1)
#define EUSART_ASYNCHRONOUS_RX_DISABLE()   (RCSTAbits.CREN = 1)
/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE()   (RCSTAbits.SPEN =1)
#define EUSART_MODULE_DISABLE()  (RCSTAbits.SPEN =0)

/* ----------------- Data Type Declarations -----------------*/
typedef enum {
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
} baudrate_gen_t;

typedef struct {
    interrupt_priority_cfg usart_tx_int_priority;
    uint8_t usart_tx_enable : 1;
    uint8_t usart_tx_9bit_enable : 1;
    uint8_t usart_tx_reserved : 6;
} usart_tx_cfg_t;

typedef struct {
    interrupt_priority_cfg usart_rx_int_priority;
    uint8_t usart_rx_enable : 1;
    uint8_t usart_rx_9bit_enable : 1;
    uint8_t usart_rx_reserved : 6;
} usart_rx_cfg_t;

typedef union {

    struct {
        uint8_t usart_tx_reserved : 6;
        uint8_t usart_ferr : 1;
        uint8_t usart_oerr : 1;
    };
    uint8_t status;
} usart_error_status_t;

typedef struct {
    uint32_t baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
#if  EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*EUSART_TxDefaultInterruptHandler)(void);
#endif
#if  EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
#endif
} usart_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
bool EUSART_DATA_AVAILABLE();
Std_ReturnType EUSART_ASYNC_ReadByte(uint8_t *_data);
#else
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8_t *_data);
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8_t *_data);
#endif
Std_ReturnType EUSART_ASYNC_RX_Restart(void);

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8_t _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(string _data);
Std_ReturnType EUSART_ASYNC_WriteLineBlocking(string _data);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8_t _data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(string _data);
#endif


#endif	/* HAL_USART_H */


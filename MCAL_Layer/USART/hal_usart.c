/* 
 * File:   hal_usart.c
 * Author: zekwa
 *
 * Created on July 14, 2024, 11:04 PM
 */

#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TxInterruptHandler)(void) = NULL;
queue_t tx_buffer;
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RxInterruptHandler)(void) = NULL;
static void (*EUSART_FramingErrorHandler)(void) = NULL;
static void (*EUSART_OverrunErrorHandler)(void) = NULL;
queue_t rx_buffer;
#endif

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart) {
    Std_ReturnType ret = E_OK;

    if (NULL == _eusart) {
        ret = E_NOT_OK;
    } else {

        EUSART_MODULE_DISABLE();
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        EUSART_Baud_Rate_Calculation(_eusart);

        if (ENABLE == _eusart->usart_tx_cfg.usart_tx_enable) {
            EUSART_ASYNC_TX_Init(_eusart);
        }

        if (ENABLE == _eusart->usart_rx_cfg.usart_rx_enable) {
            EUSART_ASYNC_RX_Init(_eusart);
        }

        EUSART_MODULE_ENABLE();

    }
    return ret;
}

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart) {

    uint16_t baudrate_temp = 0;

    switch (_eusart->baudrate_gen_gonfig) {
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            baudrate_temp = (uint16_t) (((_XTAL_FREQ / (float) _eusart->baudrate) / (float) 64) - 1);
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            baudrate_temp = (uint16_t) (((_XTAL_FREQ / (float) _eusart->baudrate) / (float) 16) - 1);
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            baudrate_temp = (uint16_t) (((_XTAL_FREQ / (float) _eusart->baudrate) / (float) 16) - 1);
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            baudrate_temp = (uint16_t) (((_XTAL_FREQ / (float) _eusart->baudrate) / (float) 4) - 1);
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            baudrate_temp = (uint16_t) (((_XTAL_FREQ / (float) _eusart->baudrate) / (float) 4) - 1);
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            baudrate_temp = (uint16_t) (((_XTAL_FREQ / (float) _eusart->baudrate) / (float) 4) - 1);
            break;
        default:
            break;
    }
    SPBRG = (uint8_t) baudrate_temp;
    SPBRGH = (uint8_t) (baudrate_temp >> 8);
}

static void EUSART_ASYNC_TX_Init(const usart_t *_eusart) {
    EUSART_ASYNCHRONOUS_TX_ENABLE();

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptDisable();
    EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    EUSART_TX_InterruptEnable();
    queueInit(&tx_buffer);
#endif

    if (EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable) {
        TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
    } else {
        TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    }
}

static void EUSART_ASYNC_RX_Init(const usart_t *_eusart) {
    EUSART_ASYNCHRONOUS_RX_ENABLE();

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_RX_InterruptDisable();
    EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
    EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
    EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    EUSART_RX_InterruptEnable();
    queueInit(&rx_buffer);
#endif

    if (EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable) {
        RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
    } else {
        RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    }
}

Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart) {
    Std_ReturnType ret = E_OK;

    if (NULL == _eusart) {
        ret = E_NOT_OK;
    } else {
        EUSART_MODULE_DISABLE();
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_InterruptDisable();
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_RX_InterruptDisable();
#endif
    }

    return ret;
}
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

bool EUSART_DATA_AVAILABLE() {
    return !isQueueEmpty(&rx_buffer);
}

Std_ReturnType EUSART_ASYNC_ReadByte(uint8_t *_data) {
    Std_ReturnType ret = E_OK;
    if (NULL == _data || isQueueEmpty(&rx_buffer)) {
        ret = E_NOT_OK;
    } else {
        dequeue(&rx_buffer, _data);
    }
    return ret;
}

#else

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8_t *_data) {
    Std_ReturnType ret = E_OK;

    if (NULL == _data) {
        ret = E_NOT_OK;
    } else {
        while (!PIR1bits.RCIF);
        *_data = RCREG;
    }

    return ret;
}

Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8_t *_data) {
    Std_ReturnType ret = E_OK;

    if (NULL == _data) {
        ret = E_NOT_OK;
    } else {
        if (PIR1bits.RCIF) {
            *_data = RCREG;
        } else {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

#endif

Std_ReturnType EUSART_ASYNC_RX_Restart(void) {
    Std_ReturnType ret = E_OK;
    CREN = 0;
    CREN = 1;
    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8_t _data) {
    Std_ReturnType ret = E_OK;
    while (!TRMT);
    TXREG = _data;
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();
#endif

    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteStringBlocking(string _data) {
    Std_ReturnType ret = E_OK;

    if (NULL == _data) {
        ret = E_NOT_OK;
    } else {
        uint16_t i = 0;
        while (_data[i] != '\0') {
            ret |= EUSART_ASYNC_WriteByteBlocking(_data[i++]);
        }
        ret |= EUSART_ASYNC_WriteByteBlocking('\0');
    }

    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteLineBlocking(string _data) {
    Std_ReturnType ret = E_OK;

    if (NULL == _data) {
        ret = E_NOT_OK;
    } else {
        ret |= EUSART_ASYNC_WriteStringBlocking(_data);
        ret |= EUSART_ASYNC_WriteByteBlocking('\r');
    }
    return ret;
}

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8_t _data) {
    Std_ReturnType ret = E_OK;
    if (TRMT && isQueueEmpty(&tx_buffer)) {
        TXREG = _data;
    } else {
        enqueue(&tx_buffer, _data);
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(string _data) {
    Std_ReturnType ret = E_OK;

    if (NULL == _data) {
        ret = E_NOT_OK;
    } else {
        uint16_t i = 0;
        while (_data[i] != '\0') {
            ret |= enqueue(&tx_buffer, _data[i++]);
        }
        ret |= enqueue(&tx_buffer, '\0');
        if (TRMT) {
            uint8_t temp_data;
            dequeue(&tx_buffer, &temp_data);
            TXREG = temp_data;
            EUSART_TX_InterruptEnable();
        }
    }
    return ret;
}
#endif

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void EUSART_TX_ISR(void) {
    EUSART_TX_InterruptDisable();
    if (!isQueueEmpty(&tx_buffer)) {
        if (TXIF) {
            uint8_t temp_data;
            dequeue(&tx_buffer, &temp_data);
            TXREG = temp_data;
            if (!isQueueEmpty(&tx_buffer)) {
                EUSART_TX_InterruptEnable();
            }
        }
    }
    if (EUSART_TxInterruptHandler) {
        EUSART_TxInterruptHandler();
    }
}

#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void EUSART_RX_ISR(void) {
    enqueue(&rx_buffer, RCREG);
    if (EUSART_RxInterruptHandler) {
        EUSART_RxInterruptHandler();
    }

    if (EUSART_FramingErrorHandler && FERR) {
        EUSART_FramingErrorHandler();
        uint8_t temp = RCREG;
    }

    if (EUSART_OverrunErrorHandler && OERR) {
        EUSART_OverrunErrorHandler();
        EUSART_ASYNC_RX_Restart();
    }

}
#endif


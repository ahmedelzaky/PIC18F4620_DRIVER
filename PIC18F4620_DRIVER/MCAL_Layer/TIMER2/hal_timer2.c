
/* 
 * File:   hal_timer2.c
 * Author: zekwa
 *
 * Created on July 6, 2024, 4:00 PM
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TMR2_InterruptHandler)(void) = NULL;
#endif

static uint8_t timer2_preload = 0;

Std_ReturnType Timer2_Init(const timer2_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        timer2_preload = _timer->timer2_preload_value;
        TMR2 = _timer->timer2_preload_value;

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
#endif

        TIMER2_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer2_DeInit(const timer2_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
#endif
    }
    return ret;
}

Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8_t _value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TMR2 = _value;
    }
    return ret;
}

Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8_t *_value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer || NULL == _value) {
        ret = E_NOT_OK;
    } else {
        *_value = TMR2;
    }
    return ret;
}

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

void TMR2_ISR(void) {
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload;
    if (TMR2_InterruptHandler) {
        TMR2_InterruptHandler();
    }
}

#endif

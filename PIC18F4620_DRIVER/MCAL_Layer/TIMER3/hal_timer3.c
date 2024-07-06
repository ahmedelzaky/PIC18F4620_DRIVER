/* 
 * File:   hal_timer3.c
 * Author: zekwa
 *
 * Created on July 6, 2024, 4:04 PM
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TMR3_InterruptHandler)(void) = NULL;
#endif
static uint16_t timer3_preload = 0;

static inline void Timer3_Mode_Select(const timer3_t *_timer);

Std_ReturnType Timer3_Init(const timer3_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        Timer3_Mode_Select(_timer);
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8_t) (_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif      
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer3_DeInit(const timer3_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
#endif
    }
    return ret;
}

Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16_t _value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TMR3H = (_value) >> 8;
        TMR3L = (uint8_t) (_value);
    }
    return ret;
}

Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16_t *_value) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _timer) || (NULL == _value)) {
        ret = E_NOT_OK;
    } else {
        *_value = TMR3L;
        *_value = (uint16_t) (TMR3H << 8);
    }
    return ret;
}

void TMR3_ISR(void) {
    TIMER3_InterruptFlagClear();
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8_t) (timer3_preload);
    if (TMR3_InterruptHandler) {
        TMR3_InterruptHandler();
    }
}

static inline void Timer3_Mode_Select(const timer3_t *_timer) {
    if (TIMER3_TIMER_MODE == _timer->timer3_mode) {
        TIMER3_TIMER_MODE_ENABLE();
    } else {
        TIMER3_COUNTER_MODE_ENABLE();
        if (TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode) {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        } else {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
    }
}

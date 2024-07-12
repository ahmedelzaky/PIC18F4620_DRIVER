/* 
 * File:   hal_timer0.c
 * Author: zekwa
 *
 * Created on June 30, 2024, 3:29 PM
 */
#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TMR0_InterruptHandler)(void) = NULL;
#endif

static uint16_t timer0_preload = 0;

static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);

Std_ReturnType Timer0_Init(const timer0_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TIMER0_MODULE_DISABLE();

        Timer0_Prescaler_Config(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size_Config(_timer);
        Timer0_Write_Value(_timer, _timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
#endif

        TIMER0_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer0_DeInit(const timer0_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        TIMER0_MODULE_DISABLE();
    }
    return ret;
}

Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16_t _value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
    } else {
        TMR0H = (_value >> 8);
        TMR0L = (_value & 0xFF);
    }
    return ret;
}

Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16_t *_value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;
    } else {
        *_value = TMR0L;
        *_value += (uint16_t) (TMR0H << 8);
    }
    return ret;
}

static inline void Timer0_Prescaler_Config(const timer0_t *_timer) {
    if (TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable) {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    } else {
        TIMER0_PRESCALER_DISABLE();
    }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer) {
    if (TIMER0_TIMER_MODE == _timer->timer0_mode) {
        TIMER0_TIMER_MODE_ENABLE();
    } else {
        TIMER0_COUNTER_MODE_ENABLE();
        if (TIMER0_COUNTER_RISING_EDGE_CFG == _timer->timer0_counter_edge) {
            TIMER0_RISING_EDGE_ENABLE();
        } else {
            TIMER0_FALLING_EDGE_ENABLE();
        }
    }
}

static inline void Timer0_Register_Size_Config(const timer0_t *_timer) {
    if (TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size) {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    } else {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
}

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

void TMR0_ISR(void) {
    TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload >> 8);
    TMR0L = (timer0_preload & 0xFF);
    if (TMR0_InterruptHandler) {
        TMR0_InterruptHandler();
    }
}

#endif


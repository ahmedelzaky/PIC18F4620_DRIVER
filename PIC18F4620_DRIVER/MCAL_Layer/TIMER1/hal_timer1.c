
/* 
 * File:   hal_timer1.c
 * Author: zekwa
 *
 * Created on July 5, 2024, 7:38 PM
 */
#include"hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TMR1_InterruptHandler)(void) = NULL;
#endif

static uint16_t timer1_preload = 0;
static inline void Timer1_Mode_Select(const timer1_t *_timer);

Std_ReturnType Timer1_Init(const timer1_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;

    } else {
        TIMER1_MODULE_DISABLE();

        Timer1_Mode_Select(_timer);

        if (_timer->timer1_reg_wr_mode == TIMER1_RW_REG_16Bit_MODE) {
            TIMER1_RW_REG_16BIT_MODE_ENABLE();
        } else {
            TIMER1_RW_REG_8BIT_MODE_ENABLE();
        }

        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8_t) (_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        TMR1_InterruptHandler = _timer->TMR1_InterruptHandler;
#endif

        TIMER1_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer1_DeInit(const timer1_t *_timer) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;

    } else {
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
#endif
    }
    return ret;
}

Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16_t _value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer) {
        ret = E_NOT_OK;

    } else {
        TMR1H = (_value >> 8);
        TMR1L = (uint8_t) (_value);
    }
    return ret;
}

Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16_t *_value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _timer && NULL == _value) {
        ret = E_NOT_OK;

    } else {
        *_value = TMR1L;
        *_value += (uint16_t) (TMR1H << 8);
    }
    return ret;
}

static inline void Timer1_Mode_Select(const timer1_t *_timer) {
    if (_timer->timer1_mode == TIMER1_COUNTER_MODE) {
        TIMER1_COUNTER_MODE_ENABLE();
        if (_timer->timer1_counter_mode == TIMER1_ASYNC_COUNTER_MODE) {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        } else {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
    } else {
        TIMER1_TIMER_MODE_ENABLE();
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        if (_timer->timer1_osc_cfg == TIMER1_OSCILLATOR_ENABLE) {
            TIMER1_OSC_HW_ENABLE();
        } else {

            TIMER1_OSC_HW_DISABLE();
        }

    }
}
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TMR1_ISR(void) {
    TIMER1_InterruptFlagClear();
    TMR1H = (timer1_preload >> 8);
    TMR1L = (uint8_t) (timer1_preload);
    if (TMR1_InterruptHandler) {
        TMR1_InterruptHandler();
    }
}
#endif


/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

void timer1_app_isr(void);
uint16_t frq = 0;

led_t led0 = {
    .port = PORTC_INDEX,
    .pin = PIN0
};

//timer1_t tmr = {
//    .TMR1_InterruptHandler = timer1_app_isr,
//    .timer1_mode = TIMER1_TIMER_MODE,
//    .timer1_osc_cfg = TIMER1_OSCILLATOR_DISABLE,
//    .timer1_reg_wr_mode = TIMER1_RW_REG_16Bit_MODE,
//    .timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_2,
//    .timer1_preload_value = 15536,
//};
timer1_t tmr = {
    .TMR1_InterruptHandler = timer1_app_isr,
    .timer1_mode = TIMER1_COUNTER_MODE,
    .timer1_reg_wr_mode = TIMER1_RW_REG_16Bit_MODE,
    .timer1_counter_mode = TIMER1_ASYNC_COUNTER_MODE,
    .timer1_preload_value = 0,
};

void setup(void) {
    Timer1_Init(&tmr);
    led_initialize(&led0);
}

int main(void) {

    setup();

    while (1) {
        __delay_ms(1000);
        Timer1_Read_Value(&tmr, &frq);
        Timer1_Write_Value(&tmr, 0);

    }
    return (EXIT_SUCCESS);

}

void timer1_app_isr(void) {
    led_turn_toggle(&led0);
}
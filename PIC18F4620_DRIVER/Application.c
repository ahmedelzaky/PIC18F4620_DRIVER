/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

void timer0_app_isr(void);

led_t led0 = {
    .port = PORTC_INDEX,
    .pin = PIN0
};

timer0_t tmr = {
    .TMR0_InterruptHandler = timer0_app_isr,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_4,
    .timer0_preload_value = 63036
};

void setup(void) {
    Timer0_Init(&tmr);
    led_initialize(&led0);
}

int main(void) {

    setup();

    while (1) {

    }
    return (EXIT_SUCCESS);

}

void timer0_app_isr(void) {
    led_turn_toggle(&led0);
}
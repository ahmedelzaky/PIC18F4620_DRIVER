/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"
#include "MCAL_Layer/TIMER2/hal_timer2.h"

void timer1_app_isr(void);
uint16_t frq = 0;

led_t led0 = {
    .port = PORTC_INDEX,
    .pin = PIN0
};

timer2_t tmr = {
    .TMR2_InterruptHandler = timer1_app_isr,
    .timer2_postscaler_value = 0,
    .timer2_preload_value = TIMER2_POSTSCALER_DIV_BY_1,
    .timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_16,

};

void setup(void) {
    Timer2_Init(&tmr);
    led_initialize(&led0);
}

int main(void) {

    setup();

    while (1) {

    }
    return (EXIT_SUCCESS);

}

void timer1_app_isr(void) {
    led_turn_toggle(&led0);
}
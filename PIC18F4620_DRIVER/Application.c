/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"
#include "MCAL_Layer/TIMER2/hal_timer2.h"
#include "MCAL_Layer/TIMER3/hal_timer3.h"

void timer1_app_isr(void);
uint16_t frq = 0;

led_t led0 = {
    .port = PORTC_INDEX,
    .pin = PIN0
};

timer3_t tmr = {
    .TMR3_InterruptHandler = timer1_app_isr,


};

void setup(void) {
    Timer3_Init(&tmr);
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
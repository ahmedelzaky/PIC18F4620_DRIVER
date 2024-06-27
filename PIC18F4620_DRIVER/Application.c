/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h" 



led_t led0 = {
    .led_state = LED_ON,
    .pin = PIN0,
    .port = PORTC_INDEX,
};
led_t led1 = {
    .led_state = LED_ON,
    .pin = PIN1,
    .port = PORTC_INDEX,
};
led_t led2 = {
    .led_state = LED_ON,
    .pin = PIN2,
    .port = PORTC_INDEX,
};
led_t led3 = {
    .led_state = LED_ON,
    .pin = PIN3,
    .port = PORTC_INDEX,
};

void RB4_Int_APP_ISR(void) {
    led_turn_toggle(&led0);
}

interrupt_RBx_t int_obj = {
    .EXT_InterruptHandler = RB4_Int_APP_ISR,
    .priority = 1,
    .mcu_pin.direction = INPUT,
    .mcu_pin.pin = PIN4,
    .mcu_pin.port = PORTB_INDEX,
};

void setup(void) {
    led_initialize(&led0);
    led_initialize(&led1);
    led_initialize(&led2);
    Interrupt_RBx_Init(&int_obj);
}

int main(void) {
    setup();
    while (1) {
    }
    return 0;
}

void int0_app_isr(void) {
    led_turn_toggle(&led0);

}

void int1_app_isr(void) {
    led_turn_toggle(&led1);

}

void int2_app_isr(void) {
    led_turn_toggle(&led2);

}


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

void RB4_Int_APP_ISR_HIGH(void) {
    led_turn_toggle(&led0);
    __delay_ms(250);
}

void RB4_Int_APP_ISR_LOW(void) {
    led_turn_toggle(&led1);
    __delay_ms(250);

}

interrupt_RBx_t int_obj = {
    .EXT_InterruptHandler_HIGH = RB4_Int_APP_ISR_HIGH,
    .EXT_InterruptHandler_LOW = RB4_Int_APP_ISR_LOW,
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


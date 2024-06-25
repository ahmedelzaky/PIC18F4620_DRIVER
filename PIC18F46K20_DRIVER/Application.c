/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h" 

void int0_app_isr(void);
void int1_app_isr(void);
void int2_app_isr(void);

led_t led0 = {
    .led_state = LED_ON,
    .pin = PIN0,
    .port = PORTD_INDEX,
};
led_t led1 = {
    .led_state = LED_ON,
    .pin = PIN1,
    .port = PORTD_INDEX,
};
led_t led2 = {
    .led_state = LED_ON,
    .pin = PIN2,
    .port = PORTD_INDEX,
};

interrupt_INTx_t int0_obj = {
    .EXT_InterruptHandler = int0_app_isr,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN0,
    .mcu_pin.direction = INPUT
};

interrupt_INTx_t int1_obj = {
    .EXT_InterruptHandler = int1_app_isr,
    .edge = INTERRUPT_FALLING_EDGE,
    .priority = INTERRUPT_LOW_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN1,
    .mcu_pin.direction = INPUT
};

interrupt_INTx_t int2_obj = {
    .EXT_InterruptHandler = int2_app_isr,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT2,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN2,
    .mcu_pin.direction = INPUT
};

void setup(void) {
    led_initialize(&led0);
    led_initialize(&led1);
    led_initialize(&led2);
    Interrupt_INTx_Init(&int0_obj);
    Interrupt_INTx_Init(&int1_obj);
    Interrupt_INTx_Init(&int2_obj);
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

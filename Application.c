/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

#define LEDS_COUNT  8

led_t leds[LEDS_COUNT] = {
    {.port = PORTC_INDEX, .pin = PIN0, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN1, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN2, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN3, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN4, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN5, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN6, .led_state = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN7, .led_state = LED_OFF}
};


button_t btn_1 = {
    .port = PORTD_INDEX,
    .pin = PIN0,
    .btn_connection = BUTTON_PULLUP,
};

button_t btn_2 = {
    .port = PORTD_INDEX,
    .pin = PIN1,
    .btn_connection = BUTTON_PULLDOWN,
};

void setup(void)
{
    for (int i = 0; i < LEDS_COUNT; i++)
    {
        led_initialize(&(leds[i]));
    }
    button_initialize(&btn_1);
    button_initialize(&btn_2);
}

int main(void)
{
    setup();
    button_state_t btn_1_state;
    button_state_t btn_2_state;

    while (1)
    {
        button_read_state(&btn_1, &btn_1_state);
        if (btn_1_state)
        {
            led_turn_toggle(&leds[0]);
            while (btn_1_state)
            {
                button_read_state(&btn_1, &btn_1_state);
            }
        }

        button_read_state(&btn_2, &btn_2_state);
        if (btn_2_state)
        {
            led_turn_toggle(&leds[1]);
            while (btn_2_state)
            {
                button_read_state(&btn_2, &btn_2_state);
            }
        }

    }
    return 0;
}


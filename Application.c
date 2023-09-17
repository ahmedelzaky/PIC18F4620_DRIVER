/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

#define LEDS_COUNT  8
#define LEDS_SQUENCE_COUNT  17

led_t leds[LEDS_COUNT] = {
    {.port = PORTC_INDEX, .pin = PIN0, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN1, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN2, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN3, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN4, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN5, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN6, .led_status = LED_OFF},
    {.port = PORTC_INDEX, .pin = PIN7, .led_status = LED_OFF}
};
uint8_t led_squence[][LEDS_SQUENCE_COUNT] = {
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
};


pin_config_t btn_1 = {
    .direction = INPUT,
    .logic = LOW,
    .port = PORTD_INDEX,
    .pin = PIN0
};

void setup(void)
{
    for (int i = 0; i < LEDS_COUNT; i++)
    {
        led_initialize(&(leds[i]));
    }
}

int main(void)
{
    setup();
    while (1)
    {
        for (int i = 0; i < LEDS_SQUENCE_COUNT; i++)
        {
            for (int j = 0; j < LEDS_COUNT; j++)
            {
                led_squence[i][j] ? led_turn_on(&(leds[j])) : led_turn_off(&(leds[j]));
            }
            __delay_ms(500);
        }
    }

    return 0;
}


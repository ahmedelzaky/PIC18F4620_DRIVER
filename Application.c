/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

lcd_4bit_t lcd_4bit = {
    .lcd_rs =
    {.port = PORTC_INDEX, .pin = PIN6},
    .lcd_en =
    {.port = PORTC_INDEX, .pin = PIN7},

    .lcd_data_pins[0].port = PORTC_INDEX,
    .lcd_data_pins[0].pin = PIN2,

    .lcd_data_pins[1].port = PORTC_INDEX,
    .lcd_data_pins[1].pin = PIN3,

    .lcd_data_pins[2].port = PORTC_INDEX,
    .lcd_data_pins[2].pin = PIN4,

    .lcd_data_pins[3].port = PORTC_INDEX,
    .lcd_data_pins[3].pin = PIN5,
};

lcd_8bit_t lcd_8bit = {
    .lcd_rs =
    {.port = PORTC_INDEX, .pin = PIN0},
    .lcd_en =
    {.port = PORTC_INDEX, .pin = PIN1},

    .lcd_data_pins[0].port = PORTD_INDEX,
    .lcd_data_pins[0].pin = PIN0,

    .lcd_data_pins[1].port = PORTD_INDEX,
    .lcd_data_pins[1].pin = PIN1,

    .lcd_data_pins[2].port = PORTD_INDEX,
    .lcd_data_pins[2].pin = PIN2,

    .lcd_data_pins[3].port = PORTD_INDEX,
    .lcd_data_pins[3].pin = PIN3,

    .lcd_data_pins[4].port = PORTD_INDEX,
    .lcd_data_pins[4].pin = PIN4,

    .lcd_data_pins[5].port = PORTD_INDEX,
    .lcd_data_pins[5].pin = PIN5,

    .lcd_data_pins[6].port = PORTD_INDEX,
    .lcd_data_pins[6].pin = PIN6,

    .lcd_data_pins[7].port = PORTD_INDEX,
    .lcd_data_pins[7].pin = PIN7,
};

void setup(void) {
    lcd_4bit_intialize(&lcd_4bit);
    lcd_8bit_intialize(&lcd_8bit);
}

int main(void) {
    setup();

    while (1) {
    }
    return 0;
}


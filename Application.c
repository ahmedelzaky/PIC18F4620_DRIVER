/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"
#include "ECU_Layer/keypad/ecu_keypad.h"

segment_t seg = {
    .segment_type = COMMON_ANODE,
    .pin_A =
    {.port = PORTC_INDEX, .pin = PIN0, .state = HIGH},
    .pin_B =
    {.port = PORTC_INDEX, .pin = PIN1, .state = HIGH},
    .pin_C =
    {.port = PORTC_INDEX, .pin = PIN2, .state = LOW},
    .pin_D =
    {.port = PORTC_INDEX, .pin = PIN3, .state = LOW},

};
keypad_t keypad = {
    .keypad_rows_pins[0].port = PORTD_INDEX,
    .keypad_rows_pins[0].pin = PIN0,
    .keypad_rows_pins[1].port = PORTD_INDEX,
    .keypad_rows_pins[1].pin = PIN1,
    .keypad_rows_pins[2].port = PORTD_INDEX,
    .keypad_rows_pins[2].pin = PIN2,
    .keypad_rows_pins[3].port = PORTD_INDEX,
    .keypad_rows_pins[3].pin = PIN3,

    .keypad_colums_pins[0].port = PORTD_INDEX,
    .keypad_colums_pins[0].pin = PIN4,
    .keypad_colums_pins[1].port = PORTD_INDEX,
    .keypad_colums_pins[1].pin = PIN5,
    .keypad_colums_pins[2].port = PORTD_INDEX,
    .keypad_colums_pins[2].pin = PIN6,
    .keypad_colums_pins[3].port = PORTD_INDEX,
    .keypad_colums_pins[3].pin = PIN7,
};

char keypad_char = '5';

void setup(void)
{
    segment_initialize(&seg);
    keypad_initialize(&keypad);
}

int main(void)
{
    setup();

    while (1)
    {
        keypad_get_value(&keypad, &keypad_char);
        segment_write_number(&seg, (uint8_t) (keypad_char - '0'));
    }
    return 0;
}


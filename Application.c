/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

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

void setup(void)
{
    segment_initialize(&seg);
}
uint8_t x = 0;

int main(void)
{
    setup();

    while (1)
    {
        for (uint8_t i = 0; i <= 9; i++)
        {
            segment_write_number(&seg, i);
            __delay_ms(1000);
        }
    }
    return 0;
}


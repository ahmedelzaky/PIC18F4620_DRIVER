/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

dc_motor_t m1 = {
    .pin_1 =
    {.pin = PIN0, .port = PORTC_INDEX, .state = HIGH},
    .pin_2 =
    {.pin = PIN1, .port = PORTC_INDEX, .state = LOW}
};
dc_motor_t m2 = {
    .pin_1 =
    {.pin = PIN2, .port = PORTC_INDEX, .state = HIGH},
    .pin_2 =
    {.pin = PIN3, .port = PORTC_INDEX, .state = LOW}
};

void setup(void)
{
    motor_initialize(&m1);
    motor_initialize(&m2);
}

int main(void)
{
    setup();

    while (1)
    {
        motor_move_right(&m1);
        motor_move_right(&m2);
        __delay_ms(3000);
        motor_move_left(&m1);
        motor_move_left(&m2);
        __delay_ms(3000);
        motor_stop(&m1);
        motor_stop(&m2);
        __delay_ms(3000);
        motor_move_left(&m1);
        motor_move_right(&m2);
        __delay_ms(3000);
        motor_move_right(&m1);
        motor_move_left(&m2);
        __delay_ms(3000);


    }
    return 0;
}


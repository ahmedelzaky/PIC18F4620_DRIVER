/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "ECU_Layer/relay/ecu_relay.h"

relay_t relay_1 = {
    .pin = PIN0,
    .port = PORTC_INDEX,
    .relay_state = RELAY_OFF,
};

relay_t relay_2 = {
    .pin = PIN1,
    .port = PORTC_INDEX,
    .relay_state = RELAY_OFF,
};

void setup(void)
{
    relay_initialize(&relay_1);
    relay_initialize(&relay_2);
}

int main(void)
{
    setup();

    while (1)
    {
        relay_turn_on(&relay_1);
        relay_turn_off(&relay_2);
        __delay_ms(5000);
        relay_turn_off(&relay_1);
        relay_turn_on(&relay_2);
        __delay_ms(5000);


    }
    return 0;
}


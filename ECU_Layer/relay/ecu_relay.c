/* 
 * File:   ecu_relay.c
 * Author: zekwa
 *
 * Created on September 19, 2023, 11:31 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param btn
 * @return relay pin configuration 
 */

static pin_config_t relay_create_pin(relay_t *relay)
{
    pin_config_t relay_pin = {
        .port = relay->port,
        .pin = relay->pin,
        .direction = OUTPUT,
        .logic = relay->relay_state,
    };
    return relay_pin;
}

Std_ReturnType relay_initialize(relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_pin = relay_create_pin(relay);
        ret = gpio_pin_intialize(&relay_pin);
    }
    return ret;
}

Std_ReturnType relay_turn_on(relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_pin = relay_create_pin(relay);
        gpio_pin_write_logic(&relay_pin, HIGH);
    }
    return ret;
}

Std_ReturnType relay_turn_off(relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_pin = relay_create_pin(relay);
        gpio_pin_write_logic(&relay_pin, LOW);
    }
    return ret;
}
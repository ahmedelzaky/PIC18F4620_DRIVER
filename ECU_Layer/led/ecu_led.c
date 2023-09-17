/* 
 * File:   ecu_led.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:50 PM
 */



#include "ecu_led.h"

/**
 * 
 * @param led
 * @return   led pin configuration
 */
static pin_config_t led_create_pin(led_t *led)
{
    pin_config_t led_pin = {.port = led->port,
        .pin = led->pin,
        .logic = led->led_state,
        .direction = OUTPUT,};

    return led_pin;
}

Std_ReturnType led_initialize(led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin = led_create_pin(led);
        ret = gpio_pin_intialize(&led_pin);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
Std_ReturnType led_turn_on(led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin_value = led_create_pin(led);
        ret = gpio_pin_write_logic(&led_pin_value, HIGH);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
Std_ReturnType led_turn_off(led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin_value = led_create_pin(led);
        ret = gpio_pin_write_logic(&led_pin_value, LOW);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
Std_ReturnType led_turn_toggle(led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin_value = led_create_pin(led);
        ret = gpio_pin_toggle_logic(&led_pin_value);
    }
    return ret;
}
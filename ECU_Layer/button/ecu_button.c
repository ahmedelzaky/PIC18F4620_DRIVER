/* 
 * File:   ecu_button.c
 * Author: zekwa
 *
 * Created on September 17, 2023, 10:26 PM
 */
#include "ecu_button.h"

/**
 * 
 * @param btn
 * @return button pin configuration 
 */
static pin_config_t btton_create_pin(button_t *btn)
{
    pin_config_t btn_pin = {
        .port = btn->port,
        .pin = btn->pin,
        .direction = INPUT,
        .logic = btn->btn_connection ? LOW : HIGH,
    };

    return btn_pin;
}

/**
 * 
 * @param btn
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_initialize(button_t *btn)
{
    Std_ReturnType ret = E_OK;
    if (btn == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t btn_pin = btton_create_pin(btn);
        ret = gpio_pin_direction_intialize(&btn_pin);
    }
    return ret;
}

/**
 * 
 * @param btn
 * @param state
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_read_state(button_t *btn, button_state_t *state)
{
    Std_ReturnType ret = E_OK;
    logic_t pin_logic;
    if (btn == NULL || state == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t btn_pin = btton_create_pin(btn);
        ret = gpio_pin_read_logic(&btn_pin, &pin_logic);
        if (btn->btn_connection == BUTTON_PULLDOWN)
        {
            pin_logic == HIGH ? (*state = BUTTON_PRESSED) : (*state = BUTTON_RELEASED);
        }
        else if (btn->btn_connection == BUTTON_PULLUP)
        {
            pin_logic == LOW ? (*state = BUTTON_PRESSED) : (*state = BUTTON_RELEASED);
        }
        else
        {
            //NOTHING
        }
    }
    return ret;

}
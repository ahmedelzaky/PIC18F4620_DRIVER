/* 
 * File:   ecu_keypad.h
 * Author: zekwa
 *
 * Created on September 28, 2023, 6:51 PM
 */

#include "ecu_keypad.h"

const char keypad_charcters_map[KEYPAD_ROWS][KEYPAD_COLUMS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'},
};

/**
 * 
 * @param keypad
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */

Std_ReturnType keypad_initialize(keypad_t *keypad)
{
    Std_ReturnType ret = E_OK;
    if (keypad == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t keypad_row_pins[KEYPAD_ROWS];
        for (int i = 0; i < KEYPAD_ROWS; i++)
        {
            keypad_row_pins[i].port = keypad->keypad_rows_pins[i].port;
            keypad_row_pins[i].pin = keypad->keypad_rows_pins[i].pin;
            keypad_row_pins[i].direction = OUTPUT;
            keypad_row_pins[i].logic = LOW;
        }
        pin_config_t keypad_col_pins[KEYPAD_COLUMS];
        for (int i = 0; i < KEYPAD_COLUMS; i++)
        {
            keypad_col_pins[i].port = keypad->keypad_colums_pins[i].port;
            keypad_col_pins[i].pin = keypad->keypad_colums_pins[i].pin;
            keypad_col_pins[i].direction = INPUT;
            keypad_col_pins[i].logic = LOW;
        }

        for (int i = 0; i < 4; i++)
        {
            ret = gpio_pin_intialize(&(keypad_row_pins[i]));
            ret = gpio_pin_intialize(&(keypad_col_pins[i]));
        }
    }
    return ret;
}

/**
 * 
 * @param keypad
 * @param c
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
Std_ReturnType keypad_get_value(keypad_t *keypad, char *c)
{
    Std_ReturnType ret = E_OK;
    if (keypad == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t keypad_row_pins[KEYPAD_ROWS];
        for (int i = 0; i < KEYPAD_ROWS; i++)
        {
            keypad_row_pins[i].port = keypad->keypad_rows_pins[i].port;
            keypad_row_pins[i].pin = keypad->keypad_rows_pins[i].pin;
            keypad_row_pins[i].direction = OUTPUT;
            keypad_row_pins[i].logic = LOW;
        }
        pin_config_t keypad_col_pins[KEYPAD_COLUMS];
        for (int i = 0; i < KEYPAD_COLUMS; i++)
        {
            keypad_col_pins[i].port = keypad->keypad_colums_pins[i].port;
            keypad_col_pins[i].pin = keypad->keypad_colums_pins[i].pin;
            keypad_col_pins[i].direction = INPUT;
            keypad_col_pins[i].logic = LOW;
        }

        for (int i = 0; i < KEYPAD_ROWS; i++)
        {
            for (int j = 0; j < KEYPAD_ROWS; j++)
            {
                ret = gpio_pin_write_logic(&(keypad_row_pins[j]), LOW);
            }
            ret = gpio_pin_write_logic(&(keypad_row_pins[i]), HIGH);
            __delay_ms(10);
            logic_t pin_state;
            for (int z = 0; z < KEYPAD_COLUMS; z++)
            {
                gpio_pin_read_logic(&(keypad_col_pins[z]), &pin_state);
                if (pin_state == HIGH)
                {
                    *c = keypad_charcters_map[i][z];
                    break;
                }
            }
        }
    }
    return ret;
}
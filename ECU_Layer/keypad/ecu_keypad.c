/* 
 * File:   ecu_keypad.c
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
 * @param col_pin
 * @return keypad row pin config
 */
static pin_config_t keypad_create_row_pin(keypad_pin_t *row_pin) {
    pin_config_t pin_col_config = {.direction = OUTPUT, .logic = LOW, .pin = row_pin->pin, .port = row_pin->port};

    return pin_col_config;
}

/**
 * 
 * @param col_pin
 * @return keypad colum pin config
 */
static pin_config_t keypad_create_col_pin(keypad_pin_t *col_pin) {
    pin_config_t pin_col_config = {.direction = INPUT, .logic = LOW, .pin = col_pin->pin, .port = col_pin->port};

    return pin_col_config;
}

/**
 * 
 * @param keypad
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */

Std_ReturnType keypad_initialize(keypad_t *keypad) {
    Std_ReturnType ret = E_OK;
    if (keypad == NULL) {
        ret = E_NOT_OK;
    } else {

        for (int i = 0; i < KEYPAD_ROWS; i++) {
            pin_config_t row_pin = keypad_create_row_pin(&(keypad->keypad_rows_pins[i]));
            ret = gpio_pin_intialize(&row_pin);
        }

        for (int i = 0; i < KEYPAD_COLUMS; i++) {
            pin_config_t col_pin = keypad_create_row_pin(&(keypad->keypad_colums_pins[i]));
            ret = gpio_pin_intialize(&col_pin);
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
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(keypad_t *keypad, char *c) {
    Std_ReturnType ret = E_OK;
    if (keypad == NULL || c == NULL) {
        ret = E_NOT_OK;
    } else {

        for (int i = 0; i < KEYPAD_ROWS; i++) {
            for (int j = 0; j < KEYPAD_ROWS; j++) {
                pin_config_t row_pin = keypad_create_row_pin(&(keypad->keypad_rows_pins[j]));
                ret = gpio_pin_write_logic(&row_pin, LOW);
            }

            pin_config_t row_pin = keypad_create_row_pin(&(keypad->keypad_rows_pins[i]));
            ret = gpio_pin_write_logic(&(row_pin), HIGH);

            __delay_ms(10);

            logic_t pin_state;
            for (int z = 0; z < KEYPAD_COLUMS; z++) {
                pin_config_t col_pin = keypad_create_row_pin(&(keypad->keypad_colums_pins[z]));
                gpio_pin_read_logic(&(col_pin), &pin_state);
                if (pin_state == HIGH) {
                    *c = keypad_charcters_map[i][z];
                    break;
                }
            }
        }
    }
    return ret;
}
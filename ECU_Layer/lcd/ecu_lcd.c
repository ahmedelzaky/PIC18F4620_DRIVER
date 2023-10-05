/* 
 * File:   ecu_lcd.c
 * Author: zekwa
 *
 * Created on September 30, 2023, 4:32 PM
 */

#include "ecu_lcd.h"

/**
 * 
 * @param pin
 * @return lcd pin config
 */
static pin_config_t lcd_create_pin_config(lcd_pin_t *pin) {

    pin_config_t pin_config = {.direction = OUTPUT, .logic = LOW, .pin = pin->pin, .port = pin->port};

    return pin_config;

}

Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_en));
        gpio_pin_intialize(&pin);

        pin = lcd_create_pin_config(&(lcd->lcd_rs));
        gpio_pin_intialize(&pin);

        for (int i = 0; i < 4; i++) {
            pin = lcd_create_pin_config(&(lcd->lcd_data_pins[i]));
            gpio_pin_intialize(&pin);
        }
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8_t data) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8_t data, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, char *str) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, char *str, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, char data[], uint8_t mem_pos) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_en));
        gpio_pin_intialize(&pin);

        pin = lcd_create_pin_config(&(lcd->lcd_rs));
        gpio_pin_intialize(&pin);

        for (int i = 0; i < 8; i++) {
            pin = lcd_create_pin_config(&(lcd->lcd_data_pins[i]));
            gpio_pin_intialize(&pin);
        }
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8_t command) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8_t data) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8_t data, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, char *str) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, char *str, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, char data[], uint8_t mem_pos) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

Std_ReturnType convert_uint8_to_string(uint8_t value, char *str) {
}

Std_ReturnType convert_uint16_to_string(uint16_t value, char *str) {
}

Std_ReturnType convert_uint32_to_string(uint32_t value, char *str) {
}

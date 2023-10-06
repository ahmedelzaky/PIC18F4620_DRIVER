/* 
 * File:   ecu_lcd.c
 * Author: zekwa
 *
 * Created on September 30, 2023, 4:32 PM
 */
#include <stdio.h>

#include "ecu_lcd.h"

/**
 * 
 * @param pin
 * @return lcd pin config
 */
static pin_config_t lcd_create_pin_config(const lcd_pin_t *pin) {

    pin_config_t pin_config = {.direction = OUTPUT, .logic = LOW, .pin = pin->pin, .port = pin->port};

    return pin_config;
}

/**
 * 
 * @param lcd
 * @param data
 */
static void lcd_send_4bit(const lcd_4bit_t *lcd, uint8_t data) {
    for (int i = 0; i < 4; i++) {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_data_pins[i]));
        gpio_pin_write_logic(&pin, (data >> i) & 0x01);
    }
}

/**
 * 
 * @param lcd
 * @param data
 */
static void lcd_send_8bit(const lcd_8bit_t *lcd, uint8_t data) {
    for (int i = 0; i < 8; i++) {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_data_pins[i]));
        gpio_pin_write_logic(&pin, (data >> i) & 0x01);
    }
}

/**
 * 
 * @param lcd
 */
static void lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd) {
    pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_en));
    gpio_pin_write_logic(&pin, HIGH);
    __delay_us(5);
    gpio_pin_write_logic(&pin, LOW);
}

/**
 * 
 * @param lcd
 */
static void lcd_8bit_send_enable_signal(const lcd_8bit_t *lcd) {
    pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_en));
    gpio_pin_write_logic(&pin, HIGH);
    __delay_us(5);
    gpio_pin_write_logic(&pin, LOW);
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_en));
        ret = gpio_pin_intialize(&pin);

        pin = lcd_create_pin_config(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&pin);

        for (int i = 0; i < 4; i++) {
            pin = lcd_create_pin_config(&(lcd->lcd_data_pins[i]));
            ret = gpio_pin_intialize(&pin);
        }

        __delay_ms(40);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);

        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);

        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        __delay_ms(2);

        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);

        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_rs));
        ret = gpio_pin_write_logic(&pin, LOW);

        lcd_send_4bit(lcd, command >> 4);
        lcd_4bit_send_enable_signal(lcd);

        lcd_send_4bit(lcd, command);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param ch
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_print_char(const lcd_4bit_t *lcd, char ch) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {

        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_rs));
        ret = gpio_pin_write_logic(&pin, HIGH);

        lcd_send_4bit(lcd, ch >> 4);
        lcd_4bit_send_enable_signal(lcd);

        lcd_send_4bit(lcd, ch);
        lcd_4bit_send_enable_signal(lcd);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param ch
 * @param row
 * @param col
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_print_char_pos(const lcd_4bit_t *lcd, char ch, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        lcd_4bit_set_cursor(lcd, row, col);
        lcd_4bit_print_char(lcd, ch);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_print_string(const lcd_4bit_t *lcd, char *str) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {

        while (*str) {
            ret = lcd_4bit_print_char(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @param row
 * @param col
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_print_string_pos(const lcd_4bit_t *lcd, char *str, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {
        lcd_4bit_set_cursor(lcd, row, col);
        lcd_4bit_print_string(lcd, str);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @param mem_pos
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8_t data[], uint8_t mem_pos, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
        for (int i = 0; i < 8; i++) {
            ret = lcd_4bit_print_char(lcd, data[i]);
        }
        __delay_ms(5);
        ret = lcd_4bit_print_char_pos(lcd, mem_pos, row, col);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        col--;
        switch (row) {
            case ROW1: lcd_4bit_send_command(lcd, (0x80 + col));
                break;
            case ROW2: lcd_4bit_send_command(lcd, (0xc0 + col));
                break;
            case ROW3: lcd_4bit_send_command(lcd, (0x94 + col));
                break;
            case ROW4: lcd_4bit_send_command(lcd, (0xd4 + col));
                break;
        }

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_clear(const lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        lcd_4bit_send_command(lcd, _LCD_CLEAR);
        lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_en));
        ret = gpio_pin_intialize(&pin);

        pin = lcd_create_pin_config(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&pin);

        for (int i = 0; i < 8; i++) {
            pin = lcd_create_pin_config(&(lcd->lcd_data_pins[i]));
            ret = gpio_pin_intialize(&pin);
        }
        __delay_ms(40);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);

        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        __delay_ms(2);

        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8_t command) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_rs));
        ret = gpio_pin_write_logic(&pin, LOW);

        lcd_send_8bit(lcd, command);
        lcd_8bit_send_enable_signal(lcd);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param ch
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_print_char(const lcd_8bit_t *lcd, char ch) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin = lcd_create_pin_config(&(lcd->lcd_rs));
        ret = gpio_pin_write_logic(&pin, HIGH);

        lcd_send_8bit(lcd, ch);
        lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param ch
 * @param row
 * @param col
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_print_char_pos(const lcd_8bit_t *lcd, char ch, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        lcd_8bit_set_cursor(lcd, row, col);
        lcd_8bit_print_char(lcd, ch);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_print_string(const lcd_8bit_t *lcd, char *str) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            ret = lcd_8bit_print_char(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @param row
 * @param col
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_print_string_pos(const lcd_8bit_t *lcd, char *str, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL || str == NULL) {
        ret = E_NOT_OK;
    } else {
        lcd_8bit_set_cursor(lcd, row, col);
        lcd_8bit_print_string(lcd, str);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @param mem_pos
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8_t data[], uint8_t mem_pos, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
        for (int i = 0; i < 8; i++) {
            ret = lcd_8bit_print_char(lcd, data[i]);
        }
        __delay_ms(5);
        ret = lcd_8bit_print_char_pos(lcd, mem_pos, row, col);

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8_t row, uint8_t col) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        col--;
        switch (row) {
            case ROW1: lcd_8bit_send_command(lcd, (0x80 + col));
                break;
            case ROW2: lcd_8bit_send_command(lcd, (0xc0 + col));
                break;
            case ROW3: lcd_8bit_send_command(lcd, (0x94 + col));
                break;
            case ROW4: lcd_8bit_send_command(lcd, (0xd4 + col));
                break;
        }

    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_clear(const lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (lcd == NULL) {
        ret = E_NOT_OK;
    } else {
        lcd_8bit_send_command(lcd, _LCD_CLEAR);
        lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_uint8_to_string(uint8_t value, char *str) {
    Std_ReturnType ret = E_OK;
    if (str == NULL) {
        ret = E_NOT_OK;
    } else {
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_uint16_to_string(uint16_t value, char *str) {
    Std_ReturnType ret = E_OK;
    if (str == NULL) {
        ret = E_NOT_OK;
    } else {
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_uint32_to_string(uint32_t value, char *str) {
    Std_ReturnType ret = E_OK;
    if (str == NULL) {
        ret = E_NOT_OK;
    } else {
        memset(str, '\0', 11);
        sprintf(str, "%lu", value);

    }
    return ret;
}


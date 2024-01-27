/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

lcd_4bit_t lcd_4bit = {
    .lcd_rs =
    {.port = PORTC_INDEX, .pin = PIN0},
    .lcd_en =
    {.port = PORTC_INDEX, .pin = PIN1},

    .lcd_data_pins[0].port = PORTC_INDEX,
    .lcd_data_pins[0].pin = PIN2,

    .lcd_data_pins[1].port = PORTC_INDEX,
    .lcd_data_pins[1].pin = PIN3,

    .lcd_data_pins[2].port = PORTC_INDEX,
    .lcd_data_pins[2].pin = PIN4,

    .lcd_data_pins[3].port = PORTC_INDEX,
    .lcd_data_pins[3].pin = PIN5,
};

lcd_8bit_t lcd_8bit = {
    .lcd_rs =
    {.port = PORTC_INDEX, .pin = PIN6},
    .lcd_en =
    {.port = PORTC_INDEX, .pin = PIN7},

    .lcd_data_pins[0].port = PORTD_INDEX,
    .lcd_data_pins[0].pin = PIN0,

    .lcd_data_pins[1].port = PORTD_INDEX,
    .lcd_data_pins[1].pin = PIN1,

    .lcd_data_pins[2].port = PORTD_INDEX,
    .lcd_data_pins[2].pin = PIN2,

    .lcd_data_pins[3].port = PORTD_INDEX,
    .lcd_data_pins[3].pin = PIN3,

    .lcd_data_pins[4].port = PORTD_INDEX,
    .lcd_data_pins[4].pin = PIN4,

    .lcd_data_pins[5].port = PORTD_INDEX,
    .lcd_data_pins[5].pin = PIN5,

    .lcd_data_pins[6].port = PORTD_INDEX,
    .lcd_data_pins[6].pin = PIN6,

    .lcd_data_pins[7].port = PORTD_INDEX,
    .lcd_data_pins[7].pin = PIN7,
};

uint8_t battry[][8] = {
    {
        0x00,
        0x0E,
        0x1B,
        0x11,
        0x11,
        0x11,
        0x1F,
        0x00
    },
    { 0x00,
        0x0E,
        0x1B,
        0x11,
        0x11,
        0x1F,
        0x1F,
        0x00},
    {
        0x00,
        0x0E,
        0x1B,
        0x11,
        0x1F,
        0x1F,
        0x1F,
        0x00
    },
    {
        0x00,
        0x0E,
        0x1B,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x00
    },
    {
        0x00,
        0x0E,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x00
    }
};

void setup(void) {
    lcd_4bit_intialize(&lcd_4bit);
    lcd_8bit_intialize(&lcd_8bit);

    lcd_8bit_print_string(&lcd_8bit, "AHMED");
    lcd_8bit_print_string_pos(&lcd_8bit, "ELZAKI", 2, 2);
    lcd_8bit_send_custom_char(&lcd_8bit, battry[0], 0, 1, 15);

    lcd_4bit_print_string(&lcd_4bit, "AHMED");
    lcd_4bit_print_string_pos(&lcd_4bit, "ELZAKI", 2, 2);
}

int main(void) {
    setup();

    while (1) {
        lcd_4bit_clear(&lcd_4bit);
        uint8_t battry_counter = 0;
        lcd_4bit_print_string(&lcd_4bit, "Count: ");
        for (uint16_t i = 0; i < 400; i++) {
            char numText[6];
            convert_uint16_to_string(i, numText);
            lcd_4bit_print_string_pos(&lcd_4bit, numText, 1, 7);
            if (i % 100 == 0) {
                lcd_8bit_send_custom_char(&lcd_8bit, battry[battry_counter++], 0, 1, 15);
            }
            __delay_ms(10);
        }

    }
    return 0;
}


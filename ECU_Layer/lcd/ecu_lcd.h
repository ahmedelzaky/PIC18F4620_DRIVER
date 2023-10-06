/* 
 * File:   ecu_lcd.h
 * Author: zekwa
 *
 * Created on September 30, 2023, 4:32 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H


/* Section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include <string.h>


/* Section: Macros */
#define _LCD_CLEAR                                  0X01
#define _LCD_RETURN_HOME                            0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF               0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON                0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF               0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON                0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT                 0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT                0x14
#define _LCD_DISPLAY_SHIFT_LEFT                     0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                    0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF    0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON     0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF     0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON      0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF                 0x08
#define _LCD_8BIT_MODE_2_LINE                       0x38
#define _LCD_4BIT_MODE_2_LINE                       0x28

#define _LCD_CGRAM_START    0x40
#define _LCD_DDRAM_START    0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* Section: Data Type Declaration */

typedef struct {
    uint8_t port : 4;
    uint8_t pin : 4;
} lcd_pin_t;

typedef struct {
    lcd_pin_t lcd_rs;
    lcd_pin_t lcd_en;
    lcd_pin_t lcd_data_pins[4];
} lcd_4bit_t;

typedef struct {
    lcd_pin_t lcd_rs;
    lcd_pin_t lcd_en;
    lcd_pin_t lcd_data_pins[8];
} lcd_8bit_t;

/* Section: Function Declaration */
Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command);
Std_ReturnType lcd_4bit_print_char(const lcd_4bit_t *lcd, char ch);
Std_ReturnType lcd_4bit_print_char_pos(const lcd_4bit_t *lcd, char ch, uint8_t row, uint8_t col);
Std_ReturnType lcd_4bit_print_string(const lcd_4bit_t *lcd, char *str);
Std_ReturnType lcd_4bit_print_string_pos(const lcd_4bit_t *lcd, char *str, uint8_t row, uint8_t col);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8_t data[], uint8_t mem_pos, uint8_t row, uint8_t col);
Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8_t row, uint8_t col);
Std_ReturnType lcd_4bit_clear(const lcd_4bit_t *lcd);

Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8_t command);
Std_ReturnType lcd_8bit_print_char(const lcd_8bit_t *lcd, char ch);
Std_ReturnType lcd_8bit_print_char_pos(const lcd_8bit_t *lcd, char ch, uint8_t row, uint8_t col);
Std_ReturnType lcd_8bit_print_string(const lcd_8bit_t *lcd, char *str);
Std_ReturnType lcd_8bit_print_string_pos(const lcd_8bit_t *lcd, char *str, uint8_t row, uint8_t col);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8_t data[], uint8_t mem_pos, uint8_t row, uint8_t col);
Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8_t row, uint8_t col);
Std_ReturnType lcd_8bit_clear(const lcd_8bit_t *lcd);

Std_ReturnType convert_uint8_to_string(uint8_t value, char *str);
Std_ReturnType convert_uint16_to_string(uint16_t value, char *str);
Std_ReturnType convert_uint32_to_string(uint32_t value, char *str);

#endif	/* ECU_LCD_H */


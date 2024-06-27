/* 
 * File:   ecu_keypad.h
 * Author: zekwa
 *
 * Created on September 28, 2023, 6:51 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H


/* Section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section: Macros */
#define KEYPAD_COLUMS 4
#define KEYPAD_ROWS 4

/* Section: Data Type Declaration */
typedef struct {
    uint8_t port : 4;
    uint8_t pin : 4;
} keypad_pin_t;

typedef struct {
    keypad_pin_t keypad_colums_pins[KEYPAD_COLUMS]; /* @ref keypad_pin_t */
    keypad_pin_t keypad_rows_pins[KEYPAD_ROWS]; /* @ref keypad_pin_t */
} keypad_t;


/* Section: Function Declaration */
Std_ReturnType keypad_initialize(keypad_t *keypad);
Std_ReturnType keypad_get_value(keypad_t *keypad, char *c);

#endif	/* ECU_KEYPAD_H */


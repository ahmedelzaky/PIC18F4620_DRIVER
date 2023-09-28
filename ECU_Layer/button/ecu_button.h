/* 
 * File:   ecu_button.h
 * Author: zekwa
 *
 * Created on September 17, 2023, 10:26 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section: Macros */

/* Section: Macro Functions */

/* Section: Data Type Declaration */

typedef enum {
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED,
} button_state_t;

typedef enum {
    BUTTON_PULLUP = 0,
    BUTTON_PULLDOWN,
} button_connection_t;

typedef struct {
    uint8_t port : 4; /* @ref  port_index_t */
    uint8_t pin : 3; /* @ref  pin_index_t */
    uint8_t btn_connection : 1; /* @ref button_connection_t */
} button_t;


/* Section: Function Declaration */
Std_ReturnType button_initialize(button_t *btn);
Std_ReturnType button_read_state(button_t *btn, button_state_t *state);



#endif	/* ECU_BUTTON_H */


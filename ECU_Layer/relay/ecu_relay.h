/* 
 * File:   ecu_relay.h
 * Author: zekwa
 *
 * Created on September 19, 2023, 11:31 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section: Macros */

/* Section: Data Type Declaration */

typedef enum {
    RELAY_OFF = 0,
    RELAY_ON
} relay_state_t;

typedef struct {
    uint8_t port : 4; /* @ref  port_index_t */
    uint8_t pin : 3; /* @ref  pin_index_t */
    uint8_t relay_state : 1; /* @ref relay_state_t */
} relay_t;


/* Section: Function Declaration */
Std_ReturnType relay_initialize(relay_t *relay);
Std_ReturnType relay_turn_on(relay_t *relay);
Std_ReturnType relay_turn_off(relay_t *relay);




#endif	/* ECU_RELAY_H */


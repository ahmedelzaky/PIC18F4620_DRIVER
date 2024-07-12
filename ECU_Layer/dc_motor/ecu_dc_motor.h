/* 
 * File:   dc_motor.h
 * Author: zekwa
 *
 * Created on September 20, 2023, 10:41 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/* Section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section: Macros */

/* Section: Data Type Declaration */

typedef enum {
    MOTOR_OFF = 0,
    MOTOR_ON
} dc_motor_state_t;

typedef struct {
    uint8_t port : 4; /* @ref  port_index_t */
    uint8_t pin : 3; /* @ref  pin_index_t */
    uint8_t state : 1; /* @ref motor_state_t */
} dc_motor_pin_t;

typedef struct {
    dc_motor_pin_t pin_1; /* @ref motor_pin_t */
    dc_motor_pin_t pin_2; /* @ref motor_pin_t */
} dc_motor_t;


/* Section: Function Declaration */
Std_ReturnType motor_initialize(dc_motor_t *motor);
Std_ReturnType motor_move_left(dc_motor_t *motor);
Std_ReturnType motor_move_right(dc_motor_t *motor);
Std_ReturnType motor_stop(dc_motor_t *motor);


#endif	/* DC_MOTOR_H */


/* 
 * File:   ecu_led.h
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:48 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes */

#include "../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_config.h"


/* Section: Macros */

/* Section: Macro Functions */

/* Section: Data Type Declaration */

typedef enum {
    LED_OFF = 0,
    LED_ON,
} led_status_t;

typedef struct {
    uint8_t port : 4; /* @ref  port_index_t */
    uint8_t pin : 3; /* @ref  pin_index_t */
    uint8_t led_status : 1; /* @ref led_status_t */
} led_t;


/* Section: Function Declaration */
static pin_config_t led_pin(led_t *led);
Std_ReturnType led_initialize(led_t *led);
Std_ReturnType led_turn_on(led_t *led);
Std_ReturnType led_turn_off(led_t *led);
Std_ReturnType led_turn_toggle(led_t *led);

#endif	/* ECU_LED_H */


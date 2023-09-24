/* 
 * File:   ecu_seven_seg.h
 * Author: zekwa
 *
 * Created on September 24, 2023, 1:10 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H


/* Section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Data Type Declaration */
typedef enum {
    COMMON_ANODE = 0,
    COMMON_CATHODE,
} segment_type_t;

typedef struct {
    uint8_t port : 4;
    uint8_t pin : 3;
    uint8_t state : 1;

} segment_pin_t;

typedef struct {
    segment_type_t segment_type; /* @ref segment_type_t */
    segment_pin_t pin_A; /* @ref segment_pin_t */
    segment_pin_t pin_B; /* @ref segment_pin_t */
    segment_pin_t pin_C; /* @ref segment_pin_t */
    segment_pin_t pin_D; /* @ref segment_pin_t */
} segment_t;


/* Section: Function Declaration */
static pin_config_t *segment_create_pins(segment_t *segment);
Std_ReturnType segment_initialize(segment_t *segment);
Std_ReturnType segment_write_number(segment_t *segment, uint8_t number);


#endif	/* ECU_SEVEN_SEG_H */


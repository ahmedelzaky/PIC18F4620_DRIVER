/* 
 * File:   hal_gpio.h
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:38 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section: Includes */
#include "../device_config.h"
#include "../mcal_std_types.h"
#include "hal_gpio_config.h"
#include <pic18f4620.h>

/* Section: Macros */
#define BIT_MASK (uint8_t)1
#define PINS_MAX_COUNT 8
#define PORTS_MAX_COUNT 5
#define PIN_CONFIGRATIONS DISABLE
#define PORT_CONFIGRATIONS ENABLE

/* Section: Macro Functions */
#define HWREG8(_X)  (*((volatile uint8_t *)(_X)))

#define SET_BIT(REG,BIT_POSN)     (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)    (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)  (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG,BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)

/* Section: Data Type Declarations */
typedef enum {
    OUTPUT = 0,
    INPUT,
} direction_t;

typedef enum {
    LOW = 0,
    HIGH,
} logic_t;

typedef enum {
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
} pin_index_t;

typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
} port_index_t;

typedef struct {
    uint8_t port : 3; /* @ref  port_index_t */
    uint8_t pin : 3; /* @ref  pin_index_t */
    uint8_t direction : 1; /* @ref direction_t */
    uint8_t logic : 1; /* @ref  logic_t */
} pin_config_t;

/* Section: Function Declaration */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config, direction_t *direction);
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8_t direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8_t *direction);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8_t logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8_t *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);


#endif	/* HAL_GPIO_H */


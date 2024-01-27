/* 
 * File:   hal_gpio.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:38 PM
 */

#include "hal_gpio.h"

volatile uint8_t *tris_reg[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8_t *lat_reg[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8_t *port_reg[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * 
 * @param _pin_config   @ref pin_config_t
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */

#if PIN_CONFIGRATIONS

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config)
{
    Std_ReturnType ret = E_OK;
    if (_pin_config == NULL || _pin_config->pin >= PINS_MAX_COUNT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (_pin_config->direction)
        {
        case OUTPUT:
            CLEAR_BIT(*tris_reg[_pin_config->port], _pin_config->pin);
            break;
        case INPUT:
            SET_BIT(*tris_reg[_pin_config->port], _pin_config->pin);
            break;
        default:
            ret = E_NOT_OK;
        }
    }
    return ret;
}

#endif

/**
 * 
 * @param _pin_config   @ref pin_config_t
 * @param direction
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PIN_CONFIGRATIONS 

Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config, direction_t *direction)
{
    Std_ReturnType ret = E_OK;
    if (_pin_config == NULL || direction == NULL || _pin_config->pin >= PINS_MAX_COUNT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction = READ_BIT(*tris_reg[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config   @ref pin_config_t
 * @param logic
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PIN_CONFIGRATIONS 

Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config, logic_t logic)
{
    Std_ReturnType ret = E_OK;

    if (_pin_config == NULL || _pin_config->pin >= PINS_MAX_COUNT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
        case HIGH:
            SET_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
            break;
        case LOW:
            CLEAR_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
            break;
        default:
            ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config   @ref pin_config_t
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */

#if PIN_CONFIGRATIONS 

Std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config)
{
    Std_ReturnType ret = E_OK;
    if (_pin_config == NULL || gpio_pin_direction_intialize(_pin_config) || gpio_pin_write_logic(_pin_config, _pin_config->logic))
    {
        ret = E_NOT_OK;
    }
    else
    {
        //NOTHING
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config   @ref pin_config_t
 * @param logic
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */

#if PIN_CONFIGRATIONS 

Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config, logic_t *logic)
{
    Std_ReturnType ret = E_OK;

    if (_pin_config == NULL || logic == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_reg[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config   @ref pin_config_t
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PIN_CONFIGRATIONS 

Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config)
{
    Std_ReturnType ret = E_OK;

    if (_pin_config == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PORT_CONFIGRATIONS 

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8_t direction)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORTS_MAX_COUNT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_reg[port] = direction;
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PORT_CONFIGRATIONS 

Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8_t *direction)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORTS_MAX_COUNT || direction == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction = *tris_reg[port];
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PORT_CONFIGRATIONS 

Std_ReturnType gpio_port_write_logic(port_index_t port, uint8_t logic)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORTS_MAX_COUNT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_reg[port] = logic;
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PORT_CONFIGRATIONS 

Std_ReturnType gpio_port_read_logic(port_index_t port, uint8_t *logic)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORTS_MAX_COUNT || logic == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *port_reg[port];
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @return  Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
#if PORT_CONFIGRATIONS 

Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORTS_MAX_COUNT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_reg[port] = ~(*lat_reg[port]);
    }
    return ret;
}
#endif

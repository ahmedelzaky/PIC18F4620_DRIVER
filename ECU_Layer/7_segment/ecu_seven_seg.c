/* 
 * File:   ecu_seven_seg.c
 * Author: zekwa
 *
 * Created on September 24, 2023, 1:10 PM
 */

#include "ecu_seven_seg.h"

static pin_config_t *segment_create_pins(segment_t *segment)
{
    pin_config_t *segment_pins = malloc(sizeof (pin_config_t) * 4);

    segment_pins[0].direction = OUTPUT;
    segment_pins[0].port = segment->pin_A.port;
    segment_pins[0].pin = segment->pin_A.pin;
    segment_pins[0].logic = segment->pin_A.state;

    segment_pins[1].direction = OUTPUT;
    segment_pins[1].port = segment->pin_B.port;
    segment_pins[1].pin = segment->pin_B.pin;
    segment_pins[1].logic = segment->pin_B.state;

    segment_pins[2].direction = OUTPUT;
    segment_pins[2].port = segment->pin_C.port;
    segment_pins[2].pin = segment->pin_C.pin;
    segment_pins[2].logic = segment->pin_C.state;
    
    segment_pins[3].direction = OUTPUT;
    segment_pins[3].port = segment->pin_D.port;
    segment_pins[3].pin = segment->pin_D.pin;
    segment_pins[3].logic = segment->pin_D.state;

    return segment_pins;
}

/**
 * 
 * @param segment_t
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
Std_ReturnType segment_initialize(segment_t *segment)
{
    Std_ReturnType ret = E_OK;
    if (segment == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t * segment_pins = segment_create_pins(segment);
        for (int i = 0; i < 4; i++)
        {
            ret = gpio_pin_intialize((segment_pins + i));

            if (ret == E_NOT_OK)
                break;
        }
        free(segment_pins);
    }
    return ret;
}

/**
 * 
 * @param segment_t
 * @param state
 * @return Status of the function
 *         (E_OK) : The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this actionn
 */
Std_ReturnType segment_write_number(segment_t *segment, uint8_t number)
{
    Std_ReturnType ret = E_OK;
    if (segment == NULL && number <= 9)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t *segment_pins = segment_create_pins(segment);

        for (int i = 0; i < 4; i++)
        {

            logic_t pin_state = ((number >> i) & 0x01);
            ret = gpio_pin_write_logic((segment_pins + i), pin_state);

            if (ret == E_NOT_OK)
                break;
        }
        free(segment_pins);

    }
    return ret;
}
/* 
 * File:   dc_motor.h
 * Author: zekwa
 *
 * Created on September 20, 2023, 10:41 PM
 */

#include "ecu_dc_motor.h"

static pin_config_t motor_create_pin(dc_motor_pin_t *motor_pin)
{
    pin_config_t motor_pin_config = {
        .port = motor_pin->port,
        .pin = motor_pin->pin,
        .direction = OUTPUT,
        .logic = motor_pin->state,
    };
    return motor_pin_config;
}

Std_ReturnType motor_initialize(dc_motor_t *motor)
{
    Std_ReturnType ret = E_OK;
    if (motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_pin_1 = motor_create_pin(&(motor->pin_1));
        ret = gpio_pin_intialize(&motor_pin_1);
        pin_config_t motor_pin_2 = motor_create_pin(&(motor->pin_2));
        ret = gpio_pin_intialize(&motor_pin_2);
    }
    return ret;
}

Std_ReturnType motor_move_left(dc_motor_t *motor)
{
    Std_ReturnType ret = E_OK;
    if (motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_pin_1 = motor_create_pin(&(motor->pin_1));
        ret = gpio_pin_write_logic(&motor_pin_1, HIGH);
        pin_config_t motor_pin_2 = motor_create_pin(&(motor->pin_2));
        ret = gpio_pin_write_logic(&motor_pin_2, LOW);
    }
    return ret;
}

Std_ReturnType motor_move_right(dc_motor_t *motor)
{
    Std_ReturnType ret = E_OK;
    if (motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_pin_1 = motor_create_pin(&(motor->pin_1));
        ret = gpio_pin_write_logic(&motor_pin_1, LOW);
        pin_config_t motor_pin_2 = motor_create_pin(&(motor->pin_2));
        ret = gpio_pin_write_logic(&motor_pin_2, HIGH);
    }
    return ret;
}

Std_ReturnType motor_stop(dc_motor_t *motor)
{
    Std_ReturnType ret = E_OK;
    if (motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_pin_1 = motor_create_pin(&(motor->pin_1));
        ret = gpio_pin_write_logic(&motor_pin_1, LOW);
        pin_config_t motor_pin_2 = motor_create_pin(&(motor->pin_2));
        ret = gpio_pin_write_logic(&motor_pin_2, LOW);
    }
    return ret;
}


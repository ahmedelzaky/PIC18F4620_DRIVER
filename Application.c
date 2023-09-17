/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

pin_config_t led_1 = {
    .direction = OUTPUT,
    .logic = HIGH,
    .port = PORTC_INDEX,
    .pin = PIN0
};

pin_config_t led_2 = {
    .direction = OUTPUT,
    .logic = HIGH,
    .port = PORTC_INDEX,
    .pin = PIN1
};

pin_config_t led_3 = {
    .direction = OUTPUT,
    .logic = HIGH,
    .port = PORTC_INDEX,
    .pin = PIN2
};

pin_config_t btn_1 = {
    .direction = INPUT,
    .logic = LOW,
    .port = PORTD_INDEX,
    .pin = PIN0
};

void setup(void)
{
    //    gpio_pin_direction_intialize(&led_1);
    //    gpio_pin_direction_intialize(&led_2);
    //    gpio_pin_direction_intialize(&led_3);
    //    gpio_pin_direction_intialize(&btn_1);
    //    gpio_pin_write_logic(&led_1, HIGH);
    //    gpio_pin_write_logic(&led_2, HIGH);
    //    gpio_pin_write_logic(&led_3, HIGH);
    gpio_port_direction_intialize(PORTC_INDEX, 0);
    gpio_port_write_logic(PORTC_INDEX, 0b10101010);
}

int main(void)
{
    setup();
    while (1)
    {
        //        logic_t btn1_status;
        //        gpio_pin_read_logic(&btn_1, &btn1_status);
        //        if (btn1_status)
        //        {
        //            gpio_pin_toggle_logic(&led_1);
        //            while (btn1_status)
        //            {
        //                gpio_pin_read_logic(&btn_1, &btn1_status);
        //            }
        //        }
        __delay_ms(100);
        gpio_port_toggle_logic(PORTC_INDEX);
    }
    return 0;
}


/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"
uint8_t ack = 0;


#define SLAVE_1 0x04
#define SLAVE_2 0x20
#define MASTER  0x111
#define MODE    MASTER

void slave_1_ISR_APP();
void slave_2_ISR_APP();

led_t led = {
    .pin = PIN0,
    .port = PORTD_INDEX

};

#if MODE ==  MASTER
mssp_i2c_t i2c_obj = {
    .i2c_clock = 100000,
    .i2c_cfg.i2c_mode = I2C_MSSP_MASTER_MODE,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
    //    .I2C_DefaultInterruptHandler = NULL,
    //    .I2C_Report_Receive_Overflow = NULL,
    //    .I2C_Report_Write_Collision = NULL,
};
#elif MODE == SLAVE_1
mssp_i2c_t i2c_obj = {
    .i2c_clock = 100000,
    .i2c_cfg.i2c_mode = I2C_MSSP_SLAVE_MODE,
    .i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE,
    .i2c_cfg.i2c_slave_address = SLAVE_1,
    .I2C_DefaultInterruptHandler = slave_1_ISR_APP,
    //    .I2C_Report_Receive_Overflow = NULL,
    //    .I2C_Report_Write_Collision = NULL,
};
#else
mssp_i2c_t i2c_obj = {
    .i2c_clock = 100000,
    .i2c_cfg.i2c_mode = I2C_MSSP_SLAVE_MODE,
    .i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
    .i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE,
    .i2c_cfg.i2c_slave_address = SLAVE_2,
    .I2C_DefaultInterruptHandler = slave_1_ISR_APP,
    //    .I2C_Report_Receive_Overflow = NULL,
    //    .I2C_Report_Write_Collision = NULL,
};
#endif

void setup(void) {
    MSSP_I2C_Init(&i2c_obj);
    led_initialize(&led);
}

int main(void) {

    setup();

    while (1) {
#if MODE ==  MASTER
        MSSP_I2C_Master_Send_Byte_Blocking(&i2c_obj, SLAVE_1, 'a', &ack);
        __delay_ms(1000);
        MSSP_I2C_Master_Send_Byte_Blocking(&i2c_obj, SLAVE_2, 'b', &ack);
        __delay_ms(1000);
        MSSP_I2C_Master_Send_Byte_Blocking(&i2c_obj, SLAVE_1, 'c', &ack);
        __delay_ms(1000);
        MSSP_I2C_Master_Send_Byte_Blocking(&i2c_obj, SLAVE_2, 'd', &ack);
        __delay_ms(1000);
#elif MODE == SLAVE_1
#else
#endif
    }
    return (EXIT_SUCCESS);

}

void slave_1_ISR_APP() {
    I2C_CLOCK_STRETCH_ENABLE();

    if (R_nW == 0 && D_nA == 0) {
        uint8_t data = SSPBUF;
        while (!BF);
        data = SSPBUF;
        if (data == 'a') {
            led_turn_on(&led);
        } else if (data == 'c') {
            led_turn_off(&led);
        }

    } else {

    }



    I2C_CLOCK_STRETCH_DISABLE();
}

void slave_2_ISR_APP() {
    I2C_CLOCK_STRETCH_ENABLE();

    uint8_t data;
    data = SSPBUF;

    if (data == 'b') {
        led_turn_on(&led);
    } else if (data == 'd') {
        led_turn_off(&led);
    }

    I2C_CLOCK_STRETCH_DISABLE();

}
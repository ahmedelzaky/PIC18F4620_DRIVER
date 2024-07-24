/* 
 * File:   Application.h
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:25 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section: Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ECU_Layer/led/ecu_led.h"
#include "ECU_Layer/button/ecu_button.h"
#include "ECU_Layer/relay/ecu_relay.h"
#include "ECU_Layer/dc_motor/ecu_dc_motor.h"
#include "ECU_Layer/7_segment/ecu_seven_seg.h"
#include "ECU_Layer/keypad/ecu_keypad.h"
#include "ECU_Layer/lcd/ecu_lcd.h"
#include "MCAL_Layer/interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/TIMER0/hal_timer0.h"
#include "MCAL_Layer/TIMER1/hal_timer1.h"
#include "MCAL_Layer/TIMER2/hal_timer2.h"
#include "MCAL_Layer/TIMER3/hal_timer3.h"
#include "MCAL_Layer/CCP/hal_ccp.h"
#include "MCAL_Layer/USART/hal_usart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"


/* Section: Macros */

/* Section: Macro Functions */

/* Section: Function Declaration */

void setup(void);


#endif	/* APPLICATION_H */


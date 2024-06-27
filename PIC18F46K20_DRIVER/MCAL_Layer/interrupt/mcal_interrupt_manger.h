/* 
 * File:   mcal_interrupt_manger.h
 * Author: zekwa
 *
 * Created on February 1, 2024, 12:33 AM
 */

#ifndef MCAL_INTERRUPT_MANGER_H
#define	MCAL_INTERRUPT_MANGER_H

#include "mcal_interrupt_config.h"
#include "../GPIO/hal_gpio.h"

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8_t state);
void RB5_ISR(uint8_t state);
void RB6_ISR(uint8_t state);
void RB7_ISR(uint8_t state);

#endif	/* MCAL_INTERRUPT_MANGER_H */


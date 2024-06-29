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

void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);
void MSSP_SPI_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

#endif	/* MCAL_INTERRUPT_MANGER_H */


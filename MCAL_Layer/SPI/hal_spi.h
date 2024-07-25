/* 
 * File:   hal_spi.h
 * Author: Ahmed Abd El-Ghafar
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* ----------------- Includes -----------------*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
/* Master Synchronous Serial Port Mode Select */
#define SPI_MASTER_FOSC_DIV4   0 /* SPI Master mode, clock = FOSC/4 */  
#define SPI_MASTER_FOSC_DIV16  1 /* SPI Master mode, clock = FOSC/16 */
#define SPI_MASTER_FOSC_DIV64  2 /* SPI Master mode, clock = FOSC/64 */ 
#define SPI_MASTER_FOSC_TMR2   3 /* SPI Master mode, clock = TMR2 output/2 */
#define SPI_SLAVE_SS_ENABLE    4 /* SPI Slave mode, clock = SCK pin, SS pin control enabled */
#define SPI_SLAVE_SS_DISABLE   5 /* SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin */

/* Clock Polarity Select */
#define SPI_IDLE_STATE_HIGH_LEVEL   1 /* Idle state for clock is a high level */
#define SPI_IDLE_STATE_LOW_LEVEL    0 /* Idle state for clock is a low level */

/* SPI Sample Select */
#define SPI_DATA_SAMPLE_MIDDLE      0 /* Input data sampled at middle of data output time */
#define SPI_DATA_SAMPLE_END         1 /* Input data sampled at end of data output time */

/* SPI Clock Select */
#define SPI_TRANSMIT_ACTIVE_TO_IDLE 1 /* Transmit occurs on transition from active to Idle clock state */
#define SPI_TRANSMIT_IDLE_TO_ACTIVE 0 /* Transmit occurs on transition from Idle to active clock state */

/* Receive Overflow Indicator */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED      1
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED  0

/* Write Collision Detect */
#define SPI_WRITE_COLLISION_DETECTED             1
#define SPI_WRITE_COLLISION_NOT_DETECTED         0

/* Buffer Full Status bit (Receive mode only) */
#define SPI_BUFFER_FULL_RECEIVE_COMPLETE         1
#define SPI_BUFFER_FULL_RECEIVE_NOT_COMPLETE     0

/* ----------------- Macro Functions Declarations -----------------*/
/* Master Synchronous Serial Port Enable */
#define SPI_ENABLE_MODULE()    (SSPCON1bits.SSPEN = 1) /* Enables serial port and configures SCK, SDO, SDI and SS as serial port pins */
#define SPI_DISABLE_MODULE()   (SSPCON1bits.SSPEN = 0) /*  Disables serial port and configures these pins as I/O port pins */

/* ----------------- Data Type Declarations -----------------*/
typedef struct {
    uint8_t ClockPolarity : 2; /* Clock Polarity Select */
    uint8_t SampleSelect : 2; /* SPI Sample Select */
    uint8_t ClockSelect : 2; /* SPI Clock Select */
    uint8_t Reserved : 2;
} SPI_Control_Config;

typedef struct {
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8_t spi_mode;
    SPI_Control_Config spi_config;
} SPI_Config;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType SPI_Init(const SPI_Config *Config);
Std_ReturnType SPI_DeInit(const SPI_Config *Config);
Std_ReturnType SPI_Send_Byte(const SPI_Config *Config, const uint8_t _data);
Std_ReturnType SPI_Read_Byte(const SPI_Config *Config, uint8_t *_data);

#endif	/* HAL_SPI_H */

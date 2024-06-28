/* 
 * File:   hal_eeprom.h
 * Author: zekwa
 *
 * Created on June 28, 2024, 1:55 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section: Includes */

#include <xc.h>
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"

/* Section: Macros */
#define ACCESS_FLASH_PROGRAM_MEMORY 1
#define ACCESS_EEPROM 0

#define ACCESS_CONFIG_REGISTERS 1
#define ACCESS_EEPROM_OR_FLASH_PROGRAM_MEMORY 0

#define ALLOW_WRITE_CYCLES 1
#define INHIBTS_WRITE_CYCLES 0

#define INIT_WRITE 1
#define DATA_WRITE_COMPLETED 0

#define INIT_READ 1

/* Section: Macro Functions */

/* Section: Variables */

/* Section: Function Declaration */
Std_ReturnType Data_EEPROM_WriteByte(uint16_t add, uint8_t data);
Std_ReturnType Data_EEPROM_ReadByte(uint16_t add, uint8_t *data);
#endif	/* HAL_EEPROM_H */


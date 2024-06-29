/* 
 * File:   mcal_std_types.h
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:34 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section: Includes */

#include "compilar.h"
#include "std_libraries.h"
#include <stdbool.h>

/* Section: Macros */

#define STD_HIGH 0x01
#define STD_LOW 0x00

#define STD_ACTIVE 0x01
#define STD_IDLE 0x00

#define STD_ON 0x01
#define STD_OFF 0x00

#define E_OK 0x00
#define E_NOT_OK 0x01

/* Section: Data Type Declarations */

typedef uint8_t Std_ReturnType;

/* Section: Macro Functions */

/* Section: Variables */

/* Section: Function Declaration */

#endif	/* MCAL_STD_TYPES_H */


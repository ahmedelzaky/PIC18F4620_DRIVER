/* 
 * File:   mcal_interrupt_config.h
 * Author: zekwa
 *
 * Created on February 1, 2024, 12:29 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section: Includes */
#include <xc.h>
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"


/* Section: Macros */
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0
#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0


/* Section: Macro Functions */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This macro will enable priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsEnable()  (RCONbits.IPEN = 1)
/* This macro will disable  priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0)

/* This macro will enable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* This macro will disable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/* This macro will enable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
/* This macro will disable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)
#else
/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE = 1)
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
/* This macro will enable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
#endif

/* ----------------- Data Type Declarations -----------------*/
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
} interrupt_priority_cfg;



#endif	/* MCAL_INTERRUPT_CONFIG_H */


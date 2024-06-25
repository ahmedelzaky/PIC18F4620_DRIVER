/* 
 * File:   mcal_interrupt_manger.c
 * Author: zekwa
 *
 * Created on February 1, 2024, 12:33 AM
 */

#include "mcal_interrupt_manger.h"

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 

void __interrupt() InterruptMAngerHigh(void) {
    if (INTERRUPT_ENABLE == INTCONbits.INT0E && INTERRUPT_OCCUR == INTCONbits.INT0F) {
        INT0_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F) {
        INT1_ISR();
    }
}

void __interrupt(low_priority) InterruptMAngerLow(void) {
    if (INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F) {
        INT1_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT2E && INTERRUPT_OCCUR == INTCON3bits.INT2F) {
        INT2_ISR();
    }
}

#else

void __interrupt() InterruptMAnger(void) {
    if (INTERRUPT_ENABLE == INTCONbits.INT0E && INTERRUPT_OCCUR == INTCONbits.INT0F) {
        INT0_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F) {
        INT1_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT2E && INTERRUPT_OCCUR == INTCON3bits.INT2F) {
        INT2_ISR();
    }
}

#endif
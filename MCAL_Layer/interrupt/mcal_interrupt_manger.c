/* 
 * File:   mcal_interrupt_manger.c
 * Author: zekwa
 *
 * Created on February 1, 2024, 12:33 AM
 */

#include "mcal_interrupt_manger.h"

static volatile uint8_t RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 

void __interrupt() InterruptMAngerHigh(void) {
    if (INTERRUPT_ENABLE == INTCONbits.INT0E && INTERRUPT_OCCUR == INTCONbits.INT0F) {
        INT0_ISR();
    }
    if (INTCON3bits.INT1P == INTERRUPT_HIGH_PRIORITY && INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F) {
        INT1_ISR();
    }
    if (INTCON3bits.INT2P == INTERRUPT_HIGH_PRIORITY && INTERRUPT_ENABLE == INTCON3bits.INT2E && INTERRUPT_OCCUR == INTCON3bits.INT2F) {
        INT2_ISR();
    }
}

void __interrupt(low_priority) InterruptMAngerLow(void) {
    if (INTCON3bits.INT1P == INTERRUPT_LOW_PRIORITY && INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F) {
        INT1_ISR();
    }
    if (INTCON3bits.INT2P == INTERRUPT_LOW_PRIORITY && INTERRUPT_ENABLE == INTCON3bits.INT2E && INTERRUPT_OCCUR == INTCON3bits.INT2F) {
        INT2_ISR();
    }

}

#else

void __interrupt() InterruptMAnger(void) {
    /* ============ INTx External On Change Interrupt Start ============ */
#if (EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)

    if (INTERRUPT_ENABLE == INTCONbits.INT0E && INTERRUPT_OCCUR == INTCONbits.INT0F) {
        INT0_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F) {
        INT1_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT2E && INTERRUPT_OCCUR == INTCON3bits.INT2F) {
        INT2_ISR();
    }

#endif
    /* ============ INTx External Interrupt End ============ */
    /* ============ PortB External On Change Interrupt Start ============ */
#if (EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)

    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB4 == HIGH) && (RB4_Flag == 1)) {
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB4 == LOW) && (RB4_Flag == 0)) {
        RB4_Flag = 1;
        RB4_ISR(1);
    } else
        if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB5 == HIGH) && (RB5_Flag == 1)) {
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB5 == LOW) && (RB5_Flag == 0)) {
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB6 == HIGH) && (RB6_Flag == 1)) {
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB6 == LOW) && (RB6_Flag == 0)) {
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB7 == HIGH) && (RB7_Flag == 1)) {
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (PORTBbits.RB7 == LOW) && (RB7_Flag == 0)) {
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    
#endif
    /* ============ PortB External On Change Interrupt End ============ */

    /* ============ Internal Interrupt Start ============ */
#if (ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)

    if ((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)) {
        ADC_ISR();
    }
    
#endif

#if (TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
    
    if ((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)) {
        TMR0_ISR();
    }
    
#endif
    
#if (TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
    
    if ((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF)) {
        TMR1_ISR();
    }
    
#endif
    
#if (TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
    
    if ((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF)) {
        TMR2_ISR();
    }

#endif
    
#if (TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)

    if ((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF)) {
        TMR3_ISR();
    }

#endif

#if (CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)

    if ((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)) {
        CCP1_ISR();
    }

#endif

#if (CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)

    if ((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)) {
        CCP2_ISR();
    }

#endif


    /* ============ Internal Interrupt End ============ */
}

#endif
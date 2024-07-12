/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"


timer3_t timer3_obj;
ccp_t ccp_obj;
uint8_t cpp_flag = 0;

void CCP1_DefaultInterruptHandler_APP(void) {
    Timer3_Write_Value(&timer3_obj, 0);
    if (cpp_flag == 0) {
        CCP_Compare_Mode_Set_Value(&ccp_obj, 12500);
        cpp_flag++;
    } else {
        CCP_Compare_Mode_Set_Value(&ccp_obj, 37500);
        cpp_flag = 0;
    }
}

void setup(void) {
    Std_ReturnType ret = E_NOT_OK;


    ccp_obj.ccp_inst = CCP1_INST;
    ccp_obj.ccp_mode = CCP_COMPARE_MODE_SELECTED;
    ccp_obj.ccp_mode_variant = CCP_COMPARE_MODE_TOGGLE_ON_MATCH;
    ccp_obj.ccp_capture_timer = CCP1_CCP2_TIMER3;
    ccp_obj.ccp_pin.port = PORTC_INDEX;
    ccp_obj.ccp_pin.pin = PIN2;
    ccp_obj.ccp_pin.direction = OUTPUT;

    ret = CCP_Compare_Mode_Set_Value(&ccp_obj, 12500);

    ret = CCP_Init(&ccp_obj);

    timer3_obj.TMR3_InterruptHandler = NULL;
    timer3_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer3_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer3_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_2;
    timer3_obj.timer3_preload_value = 0;
    timer3_obj.timer3_reg_wr_mode = TIMER3_RW_REG_16Bit_MODE;
    ret = Timer3_Init(&timer3_obj);

}

int main(void) {

    setup();

    while (1) {

    }
    return (EXIT_SUCCESS);

}

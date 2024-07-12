/* 
 * File:   hal_ccp1.c
 * Author: zekwa
 *
 * Created on July 10, 2024, 8:21 PM
 */
#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void (* CCP1_InterruptHandler)(void) = NULL;
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void (* CCP2_InterruptHandler)(void) = NULL;
#endif

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
static Std_ReturnType CCP_PWM_INIT(const ccp_t *_ccp_obj);
#endif

#if (CCP1_CFG_SELECTED_MODE!=CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE!=CCP_CFG_PWM_MODE_SELECTED)
static void CCP_TIMER_SELECT(const ccp_t *_ccp_obj);
#endif

Std_ReturnType CCP_Init(const ccp_t *_ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        } else if (CCP2_INST == _ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }

        gpio_pin_intialize(&(_ccp_obj->ccp_pin));

        CCP_Interrupt_Config(_ccp_obj);

        if (CCP1_INST == _ccp_obj->ccp_inst) {
            CCP1_SET_MODE(_ccp_obj->ccp_mode_variant);
        } else if (CCP2_INST == _ccp_obj->ccp_inst) {
            CCP2_SET_MODE(_ccp_obj->ccp_mode_variant);
        }


#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
        if (_ccp_obj->ccp_mode == CCP_PWM_MODE_SELECTED) {
            ret = CCP_PWM_INIT(_ccp_obj);
        }
#endif
#if (CCP1_CFG_SELECTED_MODE!=CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE!=CCP_CFG_PWM_MODE_SELECTED)
        CCP_TIMER_SELECT(_ccp_obj);
#endif

    }
    return ret;
}

Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
#endif 
        } else {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
#endif  
        }
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)|| (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)

Std_ReturnType CCP_IsCapturedDataReady(const ccp_t *_ccp_obj, uint8_t *_capture_status) {
    Std_ReturnType ret = E_OK;
    if (NULL == _capture_status || NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            if (CCP_CAPTURE_READY == PIR1bits.CCP1IF) {
                *_capture_status = CCP_CAPTURE_READY;
                PIR1bits.CCP1IF = 0;
            } else {
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
        } else {
            if (CCP_CAPTURE_READY == PIR2bits.CCP2IF) {
                *_capture_status = CCP_CAPTURE_READY;
                PIR2bits.CCP2IF = 0;
            } else {
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
    }
    return ret;
}

Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj, uint16_t *capture_value) {
    Std_ReturnType ret = E_OK;
    if (NULL == capture_value || NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        CCP_REG_T capture_value_temp;
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            capture_value_temp.ccpr_low = CCPR1L;
            capture_value_temp.ccpr_high = CCPR1H;
        } else {
            capture_value_temp.ccpr_low = CCPR2L;
            capture_value_temp.ccpr_high = CCPR2H;
        }
        *capture_value = capture_value_temp.ccpr_16Bit;
    }
    return ret;
}



#endif

#if (CCP1_CFG_SELECTED_MODE!=CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE!=CCP_CFG_PWM_MODE_SELECTED)

static void CCP_TIMER_SELECT(const ccp_t *_ccp_obj) {
    if (CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer) {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    } else if (CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer) {
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    } else {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)|| (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)

Std_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj, uint8_t *_compare_status) {
    Std_ReturnType ret = E_OK;
    if (NULL == _compare_status || NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            if (CCP_COMPARE_READY == PIR1bits.CCP1IF) {
                *_compare_status = CCP_COMPARE_READY;
                PIR1bits.CCP1IF = 0;
            } else {
                *_compare_status = CCP_COMPARE_NOT_READY;
            }
        } else {
            if (CCP_COMPARE_READY == PIR2bits.CCP2IF) {
                *_compare_status = CCP_COMPARE_READY;
                PIR2bits.CCP2IF = 0;
            } else {
                *_compare_status = CCP_COMPARE_NOT_READY;
            }
        }
    }
    return ret;
}

Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16_t compare_value) {
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        CCP_REG_T compare_value_temp = {.ccpr_16Bit = compare_value};

        if (_ccp_obj->ccp_inst == CCP1_INST) {
            CCPR1L = compare_value_temp.ccpr_low;
            CCPR1H = compare_value_temp.ccpr_high;
        } else {
            CCPR2L = compare_value_temp.ccpr_low;
            CCPR2H = compare_value_temp.ccpr_high;
        }
    }
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)

Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint16_t _duty) {
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        uint16_t temp_duty = (uint16_t) ((((float) (4 * PR2) / (float) 1020)) *(float) _duty);
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            CCP1CONbits.DC1B = (temp_duty & 0x0003);
            CCPR1L = (uint8_t) (temp_duty >> 2);
        } else if (CCP2_INST == _ccp_obj->ccp_inst) {
            CCP2CONbits.DC2B = (temp_duty & 0x0003);
            CCPR2L = (uint8_t) (temp_duty >> 2);
        }

    }
    return ret;
}

Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_PWM_MODE);
        } else if (CCP2_INST == _ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
    }
    return ret;
}

Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == _ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        } else if (CCP2_INST == _ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
    }
    return ret;
}

static Std_ReturnType CCP_PWM_INIT(const ccp_t * _ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (_ccp_obj->ccp_mode == CCP_PWM_MODE_SELECTED) {
        timer2_t tmr = {
            .timer2_postscaler_value = _ccp_obj->timer2_postscaler_value,
            .timer2_prescaler_value = _ccp_obj->timer2_prescaler_value,
            .timer2_preload_value = 0,
        };
        Timer2_Init(&tmr);


        uint8_t prescaler = 0;
        switch (_ccp_obj->timer2_prescaler_value) {
            case TIMER2_PRESCALER_DIV_BY_1:
                prescaler = 1;
                break;
            case TIMER2_PRESCALER_DIV_BY_4:
                prescaler = 4;
                break;
            case TIMER2_PRESCALER_DIV_BY_16:
                prescaler = 16;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }


        PR2 = (uint8_t) ((_XTAL_FREQ /
                (_ccp_obj->PWM_Frequency * 4.0 * prescaler * (_ccp_obj->timer2_postscaler_value + 1))) - 1
                );

        if (_ccp_obj->ccp_mode_variant == CCP_PWM_MODE) {
            if (CCP1_INST == _ccp_obj->ccp_inst) {
                CCP1_SET_MODE(CCP_PWM_MODE);
            } else {
                CCP2_SET_MODE(CCP_PWM_MODE);
            }
        }
    }

    return ret;
}

#endif

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj) {
    /* CCP1 Interrupt Configurations */
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptEnable();
    CCP1_InterruptFlagClear();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if (INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP1_priority) {
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_HighPrioritySet();
    } else if (INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority) {
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        CCP1_LowPrioritySet();
    } else {
        /* Nothing */
    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif          
#endif    

    /* CCP2 Interrupt Configurations */
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_InterruptEnable();
    CCP2_InterruptFlagClear();
    CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if (INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP2_priority) {
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        CCP2_HighPrioritySet();
    } else if (INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP2_priority) {
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        CCP2_LowPrioritySet();
    } else {
        /* Nothing */
    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif          
#endif 
}

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

void CCP1_ISR(void) {
    CCP1_InterruptFlagClear();
    if (CCP1_InterruptHandler) {
        CCP1_InterruptHandler();
    }
}

#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

void CCP2_ISR(void) {
    CCP2_InterruptFlagClear();
    if (CCP2_InterruptHandler) {
        CCP2_InterruptHandler();
    }
}
#endif

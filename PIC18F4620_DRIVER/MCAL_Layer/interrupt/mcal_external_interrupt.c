/* 
 * File:   mcal_external_interrupt.c
 * Author: zekwa
 *
 * Created on February 1, 2024, 12:34 AM
 */

#include "mcal_external_interrupt.h"

static void (*INT0_interruptHandler)(void) = NULL;
static void (*INT1_interruptHandler)(void) = NULL;
static void (*INT2_interruptHandler)(void) = NULL;

static void (*RBX4_interruptHandler_LOW)(void) = NULL;
static void (*RBX5_interruptHandler_LOW)(void) = NULL;
static void (*RBX6_interruptHandler_LOW)(void) = NULL;
static void (*RBX7_interruptHandler_LOW)(void) = NULL;

static void (*RBX4_interruptHandler_HIGH)(void) = NULL;
static void (*RBX5_interruptHandler_HIGH)(void) = NULL;
static void (*RBX6_interruptHandler_HIGH)(void) = NULL;
static void (*RBX7_interruptHandler_HIGH)(void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType Intx_handler_settetr(const interrupt_INTx_t *int_obj);
static Std_ReturnType rbx_handler_settetr(const interrupt_RBx_t *int_obj);

//static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
//static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
//static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif

        ret += Interrupt_INTx_Disable(int_obj);
        ret += Interrupt_INTx_Clear_Flag(int_obj);

        ret += Interrupt_INTx_Edge_Init(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        ret += Interrupt_INTx_Priority_Init(int_obj);
#endif
        ret += Interrupt_INTx_Pin_Init(int_obj);
        ret += Intx_handler_settetr(int_obj);
        ret += Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

Std_ReturnType Interrupt_INTx_DInit(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptEnable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 

static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT1:
                int_obj->priority == INTERRUPT_HIGH_PRIORITY ? EXT_INT1_HighPrioritySet() : EXT_INT1_LowPrioritySet();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                int_obj->priority == INTERRUPT_HIGH_PRIORITY ? EXT_INT2_HighPrioritySet() : EXT_INT2_LowPrioritySet();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                int_obj->edge == INTERRUPT_RISING_EDGE ? EXT_INT0_RisingEdgeSet() : EXT_INT0_FallingEdgeSet();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                int_obj->edge == INTERRUPT_RISING_EDGE ? EXT_INT1_RisingEdgeSet() : EXT_INT1_FallingEdgeSet();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                int_obj->edge == INTERRUPT_RISING_EDGE ? EXT_INT2_RisingEdgeSet() : EXT_INT2_FallingEdgeSet();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

static Std_ReturnType Intx_handler_settetr(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj || NULL == int_obj->EXT_InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                INT0_interruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                INT1_interruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                INT2_interruptHandler = int_obj->EXT_InterruptHandler;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

void INT0_ISR(void) {
    EXT_INT0_InterruptFlagClear();
    if (INT0_interruptHandler) {
        INT0_interruptHandler();
    }
}

void INT1_ISR(void) {
    EXT_INT1_InterruptFlagClear();
    if (INT1_interruptHandler) {
        INT1_interruptHandler();
    }
}

void INT2_ISR(void) {
    EXT_INT2_InterruptFlagClear();
    if (INT2_interruptHandler) {
        INT2_interruptHandler();
    }
}

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        EXT_RBx_InterruptDisable();
        EXT_RBx_InterruptFlagClear();

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
            EXT_RBx_Priority_Low();
        } else {
            EXT_RBx_Priority_High();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ret += rbx_handler_settetr(int_obj);
        ret += Interrupt_RBx_Pin_Init(int_obj);
        EXT_RBx_InterruptEnable();
    }
    return ret;
}

Std_ReturnType Interrupt_RBx_DInit(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret;
}

static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

static Std_ReturnType rbx_handler_settetr(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj || NULL == int_obj->EXT_InterruptHandler_LOW || NULL == int_obj->EXT_InterruptHandler_HIGH) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->mcu_pin.pin) {
            case PIN4:
                RBX4_interruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RBX4_interruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            case PIN5:
                RBX5_interruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RBX5_interruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            case PIN6:
                RBX6_interruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RBX6_interruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            case PIN7:
                RBX7_interruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RBX7_interruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

void RB4_ISR(uint8_t state) {
    EXT_RBx_InterruptFlagClear();
    if (RBX4_interruptHandler_LOW && state == 1) {
        RBX4_interruptHandler_LOW();
    } else if (RBX4_interruptHandler_HIGH && state == 0) {
        RBX4_interruptHandler_HIGH();
    }
}

void RB5_ISR(uint8_t state) {
    EXT_RBx_InterruptFlagClear();
    if (RBX4_interruptHandler_LOW && state == 1) {
        RBX4_interruptHandler_LOW();
    } else if (RBX4_interruptHandler_HIGH && state == 0) {
        RBX4_interruptHandler_HIGH();
    }
}

void RB6_ISR(uint8_t state) {
    EXT_RBx_InterruptFlagClear();
    if (RBX4_interruptHandler_LOW && state == 1) {
        RBX4_interruptHandler_LOW();
    } else if (RBX4_interruptHandler_HIGH && state == 0) {
        RBX4_interruptHandler_HIGH();
    }
}

void RB7_ISR(uint8_t state) {
    EXT_RBx_InterruptFlagClear();
    if (RBX4_interruptHandler_LOW && state == 1) {
        RBX4_interruptHandler_LOW();
    } else if (RBX4_interruptHandler_HIGH && state == 0) {
        RBX4_interruptHandler_HIGH();
    }
}
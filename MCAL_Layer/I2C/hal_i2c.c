/* 
 * File:   hal_i2c.c
 * Author: zekwa
 *
 * Created on July 23, 2024, 3:27 PM
 */
#include "hal_i2c.h"

static inline void MSSP_I2C_Mode_GPIO_CFG(void);
static inline void I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *i2c_obj);
static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj);

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
static void (*I2C_DefaultInterruptHandle)(void) = NULL;
static void (*I2C_Report_Receive_Overflow_InterruptHandle)(void) = NULL;
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *i2c_obj);
#endif

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj) {
        ret = E_NOT_OK;
    } else {
        MSSP_MODULE_DISABLE_CFG();

        if (I2C_MSSP_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode) {
            I2C_Master_Mode_Clock_Configurations(i2c_obj);
        } else {
            I2C_Slave_Mode_Configurations(i2c_obj);
        }
        MSSP_I2C_Mode_GPIO_CFG();

        if (I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate) {
            I2C_SLEW_RATE_ENABLE_CFG();
        } else {
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        if (I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control) {
            I2C_SMBus_ENABLE_CFG();
        } else {
            I2C_SMBus_DISABLE_CFG();
        }
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        if (SSPCON1bits.SSPM != I2C_MASTER_MODE_DEFINED_CLOCK) {
            MSSP_I2C_Interrupt_Configurations(i2c_obj);
        }
#endif
        MSSP_MODULE_ENABLE_CFG();
    }
    return ret;
}

Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t * i2c_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj) {
        ret = E_NOT_OK;
    } else {
        MSSP_MODULE_DISABLE_CFG();
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_InterruptDisable();
        MSSP_I2C_BUS_COL_InterruptDisable();
#endif
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t * i2c_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj) {
        ret = E_NOT_OK;
    } else {
        SEN = 1;

        while (SEN);

        SSPIF = 0;

        if (I2C_START_BIT_NOT_DETECTED == SSPSTATbits.S) {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t * i2c_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj) {
        ret = E_NOT_OK;
    } else {
        RSEN = 1;

        while (RSEN);

        SSPIF = 0;

    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t * i2c_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj) {
        ret = E_NOT_OK;
    } else {
        PEN = 1;

        while (PEN);

        SSPIF = 0;

        if (I2C_STOP_BIT_NOT_DETECTED == SSPSTATbits.P) {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8_t i2c_data, uint8_t * _ack) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj || NULL == _ack) {
        ret = E_NOT_OK;
    } else {
        SSPBUF = i2c_data;

        while (!SSPIF);


        SSPIF = 0;

        if (I2C_ACK_RECEIVED_FROM_SLAVE == ACKSTAT) {
            *_ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        } else {
            *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Byte_Blocking(const mssp_i2c_t *i2c_obj, uint8_t slave_add, uint8_t i2c_data, uint8_t * _ack) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj || NULL == _ack) {
        ret = E_NOT_OK;
    } else {
        ret |= MSSP_I2C_Master_Send_Start(i2c_obj);
        ret |= MSSP_I2C_Master_Write_Blocking(i2c_obj, slave_add, _ack);
        ret |= MSSP_I2C_Master_Write_Blocking(i2c_obj, i2c_data, _ack);
        ret |= MSSP_I2C_Master_Send_Stop(i2c_obj);
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8_t * i2c_data) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj || NULL == i2c_data) {
        ret = E_NOT_OK;
    } else {
        I2C_MASTER_RECEIVE_ENABLE_CFG();

        while (!BF);

        *i2c_data = SSPBUF;

        ACKDT = 0;
        ACKEN = 1;

    }
    return ret;
}

static inline void MSSP_I2C_Mode_GPIO_CFG(void) {

    TRISCbits.TRISC3 = 1; /* Serial clock (SCL) is Input */
    TRISCbits.TRISC4 = 1; /* Serial data (SDA) is Input */
}

static inline void I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t * i2c_obj) {
    SSPCON1bits.SSPM = I2C_MASTER_MODE_DEFINED_CLOCK;
    SSPADD = (uint8_t) (((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock) - 1);
}

static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t * i2c_obj) {
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
    if (I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call) {
        I2C_GENERAL_CALL_ENABLE_CFG();
    } else {

        I2C_GENERAL_CALL_DISABLE_CFG();
    }
    WCOL = 0;
    SSPOV = 0;
    CKP = 1;

    SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;

}


#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t * i2c_obj) {

    MSSP_I2C_InterruptFlagClear();
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    MSSP_I2C_InterruptEnable();
    MSSP_I2C_BUS_COL_InterruptEnable();
    I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
    I2C_DefaultInterruptHandle = i2c_obj->I2C_DefaultInterruptHandler;
    I2C_Report_Receive_Overflow_InterruptHandle = i2c_obj->I2C_Report_Receive_Overflow;
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if (INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priority) {
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_I2C_HighPrioritySet();
    } else if (INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priority) {
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_I2C_LowPrioritySet();
    } else { /* Nothing */
    }

    if (INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priority) {
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_I2C_BUS_COL_HighPrioritySet();
    } else if (INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priority) {
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_I2C_BUS_COL_LowPrioritySet();
    } else { /* Nothing */
    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif

}

Std_ReturnType MSSP_I2C_Master_Write_NBlocking(const mssp_i2c_t *i2c_obj, uint8_t i2c_data, uint8_t * _ack) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj || NULL == _ack) {
        ret = E_NOT_OK;
    } else {
    }

    return ret;
}

Std_ReturnType MSSP_I2C_Master_Read_NBlocking(const mssp_i2c_t *i2c_obj, uint8_t ack, uint8_t * i2c_data) {
    Std_ReturnType ret = E_OK;
    if (NULL == i2c_obj || NULL == i2c_data) {
        ret = E_NOT_OK;
    } else {
    }

    return ret;
}

void MSSP_I2C_ISR(void) {
    MSSP_I2C_InterruptFlagClear();
    if (I2C_DefaultInterruptHandle) {
        I2C_DefaultInterruptHandle();
    }
}
#endif

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void MSSP_I2C_BC_ISR(void) {
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if (I2C_Report_Write_Collision_InterruptHandler) {
        I2C_Report_Write_Collision_InterruptHandler();
    }

}
#endif
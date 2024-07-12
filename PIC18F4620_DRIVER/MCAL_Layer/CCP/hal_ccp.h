/* 
 * File:   hal_ccp.h
 * Author: zekwa
 *
 * Created on July 10, 2024, 8:21 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* ----------------- Includes -----------------*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../TIMER2/hal_timer2.h"
#include "ccp_cfg.h"

/* ----------------- Macro Declarations -----------------*/
/* CCP1 Module Mode Select  */
#define CCP_MODULE_DISABLE                 ((uint8_t)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8_t)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8_t)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8_t)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8_t)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8_t)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8_t)0x09) 
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8_t)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8_t)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8_t)0x0B)
#define CCP_PWM_MODE                       ((uint8_t)0x0C)

/* CCP1 Capture Mode State  */
#define CCP_CAPTURE_NOT_READY              0X00
#define CCP_CAPTURE_READY                  0X01

/* CCP1 Compare Mode State  */
#define CCP_COMPARE_NOT_READY               0X00
#define CCP_COMPARE_READY                   0X01


/* ----------------- Macro Functions Declarations -----------------*/

/* Set the CCP1 Mode Variant */
#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M = _CONFIG)

/* ----------------- Data Type Declarations -----------------*/

/*
  @Summary      Define the values to select the CCP1 Main mode
 */
typedef enum {
    CCP_CAPTURE_MODE_SELECTED = 0, /* Select CCP1 Capture Mode */
    CCP_COMPARE_MODE_SELECTED, /* Select CCP1 Compare Mode */
    CCP_PWM_MODE_SELECTED /* Select CCP1 PWM Mode */
} ccp1_mode_t;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
 */
typedef union {

    struct {
        uint8_t ccpr_low; /* CCPR1 low register */
        uint8_t ccpr_high; /* CCPR1 high register */
    };

    struct {
        uint16_t ccpr_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
} CCP_REG_T;

typedef enum {
    CCP1_INST = 0,
    CCP2_INST
} ccp_inst_t;

typedef enum {
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
} ccp_capture_timer_t;

/*
  @Summary      CCP Module configurations
  @Description  This data type used to describe the module initialization configuration
 */
typedef struct {
    ccp_inst_t ccp_inst;
    ccp1_mode_t ccp_mode; /* CCP main mode */
    uint8_t ccp_mode_variant; /* CCP selected mode variant */
    pin_config_t ccp_pin; /* CCP Pin I/O configurations */
    ccp_capture_timer_t ccp_capture_timer;
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
    uint32_t PWM_Frequency; /* CCP PWM mode frequency */
    uint8_t timer2_postscaler_value;
    uint8_t timer2_prescaler_value;
#endif
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void); /* Call back used for all CCP1 Modes */
    interrupt_priority_cfg CCP1_priority; /* Configure the CCP1 mode interrupt */
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP2_InterruptHandler)(void); /* Call back used for all CCP2 Modes */
    interrupt_priority_cfg CCP2_priority; /* Configure the CCP1 mode interrupt */
#endif
} ccp_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)|| (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP_IsCapturedDataReady(const ccp_t *_ccp_obj, uint8_t *_capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj, uint16_t *capture_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj, uint8_t *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16_t compare_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint16_t _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj);
#endif

#endif	/* HAL_CCP1_H */


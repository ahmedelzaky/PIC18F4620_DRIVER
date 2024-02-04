/* 
 * File:   mcal_external_interrupt.c
 * Author: zekwa
 *
 * Created on February 1, 2024, 12:34 AM
 */

#include "mcal_external_interrupt.h"

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

Std_ReturnType Interrupt_INTx_DInit(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

Std_ReturnType Interrupt_RBx_DInit(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
    }
    return ret = E_OK;
}
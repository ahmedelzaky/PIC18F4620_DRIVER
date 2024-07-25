/* 
 * File:   hal_spi.c
 * Author: Ahmed Abd El-Ghafar
 */

#include "hal_spi.h"

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*SPI_InterruptHandler)(void) = NULL;
static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config);
#endif

static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);

Std_ReturnType SPI_Init(const SPI_Config *Config) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == Config) {
        ret = E_NOT_OK;
    } else {
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = Config->spi_mode;
        /* GPIO PIN Configurations */
        if ((Config->spi_mode == SPI_MASTER_FOSC_DIV4) || (Config->spi_mode == SPI_MASTER_FOSC_DIV16) ||
                (Config->spi_mode == SPI_MASTER_FOSC_DIV64) || (Config->spi_mode == SPI_MASTER_FOSC_TMR2)) {
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(Config);
        } else if ((Config->spi_mode == SPI_SLAVE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_SS_DISABLE)) {
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP = Config->spi_config.ClockPolarity;
        /* SPI Sample Select */
        SSPSTATbits.SMP = Config->spi_config.SampleSelect;
        /* SPI Clock Select */
        SSPSTATbits.CKE = Config->spi_config.ClockSelect;
        /* MSSP SPI Interrupt Configurations*/
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_Interrupt_Init(Config);
#endif
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
    }

    return ret;
}

Std_ReturnType SPI_DeInit(const SPI_Config *Config) {
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == Config) {
        ret = E_NOT_OK;
    } else {
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* Interrupt Configurations */
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_InterruptDisable();
#endif
    }

    return ret;
}

Std_ReturnType SPI_Send_Byte(const SPI_Config *Config, const uint8_t _data) {
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == Config) {
        ret = E_NOT_OK;
    } else {
        SSPBUF = _data;
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==!INTERRUPT_FEATURE_ENABLE
        while (!SSPIF); /* Waiting to transmit */
        SSPIF = 0;
#endif
    }

    return ret;
}

Std_ReturnType SPI_Read_Byte(const SPI_Config *Config, uint8_t *_data) {
    Std_ReturnType ret = E_NOT_OK;

    if ((NULL == Config) || (NULL == _data)) {
        ret = E_NOT_OK;
    } else {
        while (SSPSTATbits.BF == 0); /* Receive not complete, SSPBUF is empty */
        *_data = SSPBUF;
    }

    return ret;
}
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config) {
    /* Interrupt Configurations */
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptEnable();
    MSSP_SPI_InterruptFlagClear();
    SPI_InterruptHandler = Config->MSSP_SPI_InterruptHandler;
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if (INTERRUPT_HIGH_PRIORITY == Config->priority) {
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_SPI_HighPrioritySet();
    } else if (INTERRUPT_LOW_PRIORITY == Config->priority) {
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_SPI_LowPrioritySet();
    } else {
        /* Nothing */
    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif      
#endif        
}

void MSSP_SPI_ISR(void) {
    MSSP_SPI_InterruptFlagClear();
    if (SPI_InterruptHandler) {
        SPI_InterruptHandler();
    }
}
#endif

static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config) {
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = PIN5, .direction = OUTPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = PIN3, .direction = OUTPUT};

    ret = gpio_pin_direction_intialize(&SPI_SDO);
    ret = gpio_pin_direction_intialize(&SPI_CLK);
}

static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config) {
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = PIN5, .direction = OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = PIN4, .direction = INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = PIN3, .direction = INPUT};
    pin_config_t SPI_SS = {.port = PORTA_INDEX, .pin = PIN5, .direction = INPUT};

    ret = gpio_pin_direction_intialize(&SPI_SDO);
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_CLK);

    if (SPI_SLAVE_SS_ENABLE == Config->spi_mode) {
        ret = gpio_pin_direction_intialize(&SPI_SS);
    }
}
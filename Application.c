/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

SPI_Config spi = {
    .spi_mode = SPI_MASTER_FOSC_DIV4,
    .spi_config.ClockPolarity = SPI_IDLE_STATE_LOW_LEVEL,
    .spi_config.ClockSelect = SPI_TRANSMIT_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SPI_DATA_SAMPLE_MIDDLE,
    //.MSSP_SPI_InterruptHandler = NULL,
};

void setup(void) {

    SPI_Init(&spi);

}

int main(void) {

    setup();

    while (1) {
        SPI_Send_Byte(&spi, 0x30);
        __delay_ms(1000);
        SPI_Send_Byte(&spi, 0x15);
        __delay_ms(1000);
        SPI_Send_Byte(&spi, 0x60);
        __delay_ms(1000);
        SPI_Send_Byte(&spi, 0x80);
        __delay_ms(1000);
    }
    return (EXIT_SUCCESS);

}

/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

uint8_t c;
led_t led = {
    .pin = PIN0,
    .port = PORTC_INDEX,
};

usart_t uart = {

    .baudrate = 9600,
    .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
    .usart_rx_cfg.usart_rx_enable = ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    .usart_tx_cfg.usart_tx_enable = ENABLE,

};

void setup(void) {
    EUSART_ASYNC_Init(&uart);
    led_initialize(&led);
}

int main(void) {

    setup();

    while (1) {
        if (EUSART_DATA_AVAILABLE()) {
            EUSART_ASYNC_ReadByte(&c);
        }
        EUSART_ASYNC_WriteStringNonBlocking("AHMED ELZAKI\r");
        led_turn_toggle(&led);

    }
    return (EXIT_SUCCESS);

}

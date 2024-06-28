/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h" 

void setup(void) {
}
uint8_t temp;

int main(void) {
    setup();
    while (1) {

        Data_EEPROM_WriteByte(0x12, 0x32);
        Data_EEPROM_ReadByte(0x12, &temp);

        __delay_ms(5000);


    }
    return 0;
}


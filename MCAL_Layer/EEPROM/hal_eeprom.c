/* 
 * File:   hal_eeprom.c
 * Author: zekwa
 *
 * Created on June 28, 2024, 1:55 AM
 */

#include "hal_eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16_t add, uint8_t data) {
    Std_ReturnType ret = E_OK;

    uint8_t interrupt_status = INTCONbits.GIE;

    EEADRH = (uint8_t) ((add >> 8) & 0x03);
    EEADR = (uint8_t) (add & 0xff);
    EEDATA = data;

    EECON1bits.EEPGD = ACCESS_EEPROM;
    EECON1bits.CFGS = ACCESS_EEPROM_OR_FLASH_PROGRAM_MEMORY;
    EECON1bits.WREN = ALLOW_WRITE_CYCLES;
    //disable global interrupt
    INTCONbits.GIE = 0;

    EECON2 = 0x55;
    EECON2 = 0xAA;

    EECON1bits.WR = INIT_WRITE;
    //wait until writing data complete
    while (EECON1bits.WR);

    EECON1bits.WREN = INHIBTS_WRITE_CYCLES;

    INTCONbits.GIE = interrupt_status;


    return ret;
}

Std_ReturnType Data_EEPROM_ReadByte(uint16_t add, uint8_t * data) {
    Std_ReturnType ret = E_OK;

    if (NULL == data) {
        ret = E_NOT_OK;
    } else {
        EEADRH = (uint8_t) ((add >> 8) & 0x03);
        EEADR = (uint8_t) (add & 0xff);

        EECON1bits.EEPGD = ACCESS_EEPROM;
        EECON1bits.CFGS = ACCESS_EEPROM_OR_FLASH_PROGRAM_MEMORY;

        EECON1bits.RD = INIT_READ;
        NOP();
        NOP();
        *data = EEDATA;

    }
    return ret;

}

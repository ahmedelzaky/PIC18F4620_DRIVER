/*
 * File:   Application.c
 * Author: zekwa
 *
 * Created on September 9, 2023, 10:01 PM
 */

#include "Application.h"

void ADC_DefaultInterruptHandler(void);

lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = PIN0,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = PIN1,
    .lcd_data_pins[0].port = PORTC_INDEX,
    .lcd_data_pins[0].pin = PIN2,
    .lcd_data_pins[1].port = PORTC_INDEX,
    .lcd_data_pins[1].pin = PIN3,
    .lcd_data_pins[2].port = PORTC_INDEX,
    .lcd_data_pins[2].pin = PIN4,
    .lcd_data_pins[3].port = PORTC_INDEX,
    .lcd_data_pins[3].pin = PIN5,

};

adc_conf_t adc_1 = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};

uint16_t adc_res_1 = 0, adc_res_2 = 0, adc_res_3 = 0, adc_res_4 = 0;
char adc_res_1_txt[6], adc_res_2_txt[6], adc_res_3_txt[6], adc_res_4_txt[6];
uint8_t ADC_Req = 0;

void setup(void) {
    Std_ReturnType ret = E_NOT_OK;
    ret |= ADC_Init(&adc_1);
    ret |= lcd_4bit_intialize(&lcd_1);
    ret |= lcd_4bit_print_string_pos(&lcd_1, "ADC Test", 1, 7);
    __delay_ms(2000);
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);

    ret |= lcd_4bit_print_string_pos(&lcd_1, "Pot0: ", 1, 1);
    ret |= lcd_4bit_print_string_pos(&lcd_1, "Pot1: ", 2, 1);
    ret |= lcd_4bit_print_string_pos(&lcd_1, "Pot2: ", 3, 1);
    ret |= lcd_4bit_print_string_pos(&lcd_1, "Pot3: ", 4, 1);
}

int main(void) {
    Std_ReturnType ret = E_NOT_OK;

    setup();

    while (1) {
        if (0 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
        } else if (1 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN1);
        } else if (2 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN2);
        } else if (3 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN3);
        } else {
            /* Nothing */
        }

        ret |= convert_uint16_to_string(adc_res_1, adc_res_1_txt);
        ret |= convert_uint16_to_string(adc_res_2, adc_res_2_txt);
        ret |= convert_uint16_to_string(adc_res_3, adc_res_3_txt);
        ret |= convert_uint16_to_string(adc_res_4, adc_res_4_txt);
        
        ret |= lcd_4bit_print_string_pos(&lcd_1, adc_res_1_txt, 1, 7);
        ret |= lcd_4bit_print_string_pos(&lcd_1, adc_res_2_txt, 2, 7);
        ret |= lcd_4bit_print_string_pos(&lcd_1, adc_res_3_txt, 3, 7);
        ret |= lcd_4bit_print_string_pos(&lcd_1, adc_res_4_txt, 4, 7);
    }
    return (EXIT_SUCCESS);

}

void ADC_DefaultInterruptHandler(void) {
    Std_ReturnType ret = E_NOT_OK;
    if (0 == ADC_Req) {
        ret = ADC_GetConversionResult(&adc_1, &adc_res_1);
        ADC_Req = 1;
    } else if (1 == ADC_Req) {
        ret = ADC_GetConversionResult(&adc_1, &adc_res_2);
        ADC_Req = 2;
    } else if (2 == ADC_Req) {
        ret = ADC_GetConversionResult(&adc_1, &adc_res_3);
        ADC_Req = 3;
    } else if (3 == ADC_Req) {
        ret = ADC_GetConversionResult(&adc_1, &adc_res_4);
        ADC_Req = 0;
    } else {
        /* Nothing */
    }
}

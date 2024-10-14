#ifndef _ADC_
#define _ADC_
#include "gd32e23x.h"
#define SIG0_H gpio_bit_set(GPIOA,GPIO_PIN_0);
#define SIG1_H gpio_bit_set(GPIOA,GPIO_PIN_1);
#define SIG2_H gpio_bit_set(GPIOA,GPIO_PIN_2);
#define SIG0_L gpio_bit_reset(GPIOA,GPIO_PIN_0);
#define SIG1_L gpio_bit_reset(GPIOA,GPIO_PIN_1);
#define SIG2_L gpio_bit_reset(GPIOA,GPIO_PIN_2);
#define CLK_H  gpio_bit_set(GPIOA,GPIO_PIN_7);
#define CLK_L  gpio_bit_reset(GPIOA,GPIO_PIN_7);
void adc_gpio_init();
void adc_init();
void DMA_init();
void user_adc_init();
uint16_t getadc_value();
extern uint16_t adc_value[2500];
#endif
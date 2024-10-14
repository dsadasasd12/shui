#ifndef _BF2640_
#define _BF2460_
#include "gd32e23x.h"
#include "systick.h"
#define CLK_H gpio_bit_set(GPIOA,GPIO_PIN_7)
#define CLK_L gpio_bit_reset(GPIOA,GPIO_PIN_7)
#define ICG_H gpio_bit_set(GPIOA,GPIO_PIN_6)
#define ICG_L gpio_bit_reset(GPIOA,GPIO_PIN_6)
#define SH_H gpio_bit_set(GPIOA,GPIO_PIN_5)
#define SH_L gpio_bit_reset(GPIOA,GPIO_PIN_5)

#define ICG_H_1 gpio_bit_set(GPIOA,GPIO_PIN_9)
#define ICG_L_1 gpio_bit_reset(GPIOA,GPIO_PIN_9)
#define SH_H_1  gpio_bit_set(GPIOA,GPIO_PIN_10)
#define SH_L_1  gpio_bit_reset(GPIOA,GPIO_PIN_10);
void bf2460_init_user();
void bf2460_init();
void bf2460_gpio();
void ccd_init(uint16_t sh_num);
void bf2460_gpio_1();
void bf2460_init_1();
void bf2460_user_1();
void sh_time(uint16_t num);
extern uint16_t adc_value[2500];
extern uint16_t adc_temp;
#endif
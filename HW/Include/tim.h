#ifndef _TIM_
#define _TIM_
#include "gd32e23x.h"
void tim_gpio_init();
void tim_pwm_init(uint16_t psc,uint16_t arr);
void pwm_clk_init();

void gpio_pwm2();
void tim2_ch2();
void PB0_PWM();

void PB14_gpio();
void PB14_pwm_init(uint8_t psc, uint8_t arr);
void PB14_PWM_init();
#endif
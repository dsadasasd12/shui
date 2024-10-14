#include "tim.h"
void tim_gpio_init()
{
  rcu_periph_clock_enable(RCU_GPIOA);
  gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_7);
  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);
}
void tim_pwm_init(uint16_t psc,uint16_t arr)
{
  timer_parameter_struct tim2;
  timer_oc_parameter_struct pwm1;
  rcu_periph_clock_enable(RCU_TIMER2);
  timer_deinit(TIMER2);
  //TIM2初始化
  tim2.alignedmode = TIMER_COUNTER_EDGE;
  tim2.clockdivision = TIMER_CKDIV_DIV1;
  tim2.counterdirection = TIMER_COUNTER_UP;
  tim2.period = arr;
  tim2.prescaler = psc;
  tim2.repetitioncounter = 0;
  timer_init(TIMER2,&tim2);
  //PWM初始化
  pwm1.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
  pwm1.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
  pwm1.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
  pwm1.ocpolarity = TIMER_OC_POLARITY_LOW;             //低电平为有效电平
  pwm1.outputnstate = TIMER_CCXN_DISABLE;
  pwm1.outputstate = TIMER_CCX_ENABLE;                 //使能PWM输出通道
  timer_channel_output_config(TIMER2,TIMER_CH_1,&pwm1);
  
  timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 2);
  timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
  //timer_primary_output_config(TIMER2,ENABLE);
  timer_auto_reload_shadow_enable(TIMER2);
  timer_enable(TIMER2);
}

void pwm_clk_init()
{
    tim_gpio_init();
    tim_pwm_init(1,8);
}


void gpio_pwm2()
{
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_0);
  gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
  gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_0);
}
void tim2_ch2()
{
  timer_parameter_struct tim_2;
  timer_oc_parameter_struct pwm;
   rcu_periph_clock_enable(RCU_TIMER2);
  tim_2.alignedmode = TIMER_COUNTER_EDGE;
  tim_2.clockdivision = TIMER_CKDIV_DIV1;
  tim_2.counterdirection = TIMER_COUNTER_UP;
  tim_2.period = 799;
  tim_2.prescaler = 99;
  tim_2.repetitioncounter = 0;
  timer_init(TIMER2,&tim_2);
  
  pwm.outputnstate = TIMER_CCX_ENABLE;
  pwm.ocpolarity = TIMER_OC_POLARITY_LOW;
  
  
  timer_channel_output_config(TIMER2,TIMER_CH_2,&pwm);
  
  timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_2,100);
  timer_channel_output_mode_config(TIMER2,TIMER_CH_2,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
  
  timer_auto_reload_shadow_enable(TIMER2);
  timer_enable(TIMER2);
}
void PB0_PWM()
{
  gpio_pwm2();
  tim2_ch2();
}
void PB14_gpio()
{
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_af_set(GPIOB,GPIO_AF_1,GPIO_PIN_14);
  gpio_mode_set(GPIOB,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_14);
  gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_14);
}
void PB14_pwm_init(uint8_t psc, uint8_t arr)
{
   rcu_periph_clock_enable(RCU_TIMER14);
  timer_parameter_struct tim14;
  timer_oc_parameter_struct pwm;
  tim14.alignedmode = TIMER_COUNTER_EDGE;
  tim14.clockdivision = TIMER_CKDIV_DIV1;
  tim14.counterdirection = TIMER_COUNTER_UP;
  tim14.period = arr;
  tim14.prescaler = psc;
  tim14.repetitioncounter = 0;
  timer_init(TIMER14,&tim14);
  
  pwm.ocpolarity = TIMER_OC_POLARITY_LOW;
  pwm.outputstate =  TIMER_CCX_ENABLE;
  timer_channel_output_config(TIMER14,TIMER_CH_0,&pwm);
  
  timer_channel_output_mode_config(TIMER14,TIMER_CH_0,TIMER_OC_MODE_PWM0);
  timer_channel_output_pulse_value_config(TIMER14,TIMER_CH_0,50);
  timer_channel_output_shadow_config(TIMER14, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
  
  timer_auto_reload_shadow_enable(TIMER14);
  timer_enable(TIMER14);
}
void PB14_PWM_init()
{
  PB14_gpio();
  PB14_pwm_init(100,99);
}
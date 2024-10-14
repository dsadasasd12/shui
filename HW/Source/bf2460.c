#include "bf2460.h"
#include "adc.h"
/*
*PA0-PA2 CCD_SIG
*
*PA5     SH
*PA6     ICG
*PA7     CLK
*/
uint16_t temp;
void bf2460_gpio()
{
  
  rcu_periph_clock_enable(RCU_GPIOA);
  //gpio_af_set(GPIOA,GPIO_AF_0,GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5);
  gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_7);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);
  
  gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_6);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
  
  gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_5);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
  
  
}
void bf2460_init()
{
 
  //t1
  SH_L;
  ICG_H;
  delay_10us(5);
  ICG_L;
  delay_10us(4);
  
  SH_H;
  delay_10us(1);
  //t2
  SH_L;
  delay_10us(4);
  ICG_H;
  delay_10us(1);
  delay_10us(1136);
}

void bf2460_init_user()
{
  bf2460_gpio();
  bf2460_init();
  
}

void bf2460_gpio_1()
{
  rcu_periph_clock_enable(RCU_GPIOA);
  gpio_af_set(GPIOA,GPIO_AF_0,GPIO_PIN_9|GPIO_PIN_10);
  gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_9|GPIO_PIN_10);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9|GPIO_PIN_10);
  
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_9);
  gpio_output_options_set(GPIOB,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
}
void bf2460_init_1()
{
  //t1
  SH_L_1;
  ICG_H_1;
  delay_10us(10);
  ICG_L_1;
  delay_10us(4);
  
  SH_H_1;
  delay_10us(10);
  //t2
  SH_L_1;
  delay_10us(11);
  ICG_H_1;
  delay_10us(10);
}
void bf2460_user_1()
{
  bf2460_gpio_1();
  bf2460_init_1();
}


void sh_time(uint16_t num)
{
  uint16_t i;
  for(i=0;i<num;i++)
  {
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
  }
  
}
//clkÊ±Ðò
uint8_t flag;
void ccd_init(uint16_t sh_num)
{
  uint16_t num;
   
  uint16_t temp1;

  ICG_H;
  SH_L;
  delay_10us(2);
  for(uint8_t i = 0; i < 3; i++)
  {
    CLK_H;
    ICG_L;
    delay_10us(1);
    SH_H;
    delay_10us(1);
    SH_L;
    delay_10us(1);
    ICG_H;
    CLK_L;
    CLK_H;
    CLK_L;
    for(uint8_t j = 0; j < 85; j++)
    {
      sh_time(12);
    }
  }
  CLK_L;
  ICG_L;
  delay_10us(1);
  SH_H;
  sh_time(sh_num);
  SH_L;
  delay_10us(2);
  ICG_H;
  CLK_L;
  CLK_H;
  CLK_L;
  
  
//  SH_L;
//  ICG_H;
//  delay_10us(5);
//  ICG_L;
//  delay_10us(10);
//  
//  SH_H;
//  //delay_10us(1);
//  sh_time(sh_num);
//  //t2
//  SH_L;
//  delay_10us(10);
//  CLK_H;
//  ICG_H;
//  delay_10us(1);
//  CLK_L;
//  delay_10us(1);
//  CLK_H;
  for(uint16_t i = 0; i < 32; i++)
  {
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;
    
//    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
//    while(adc_flag_get(ADC_FLAG_EOC) == RESET);
//    adc_value[i]=(uint16_t)ADC_RDATA;  
  }
  
  
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
    while(adc_flag_get(ADC_FLAG_EOC) == RESET);
    temp = (uint16_t)ADC_RDATA;
  
  for(num = 0; num<2500; num++)
  { 
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
    CLK_H;
    delay_10us(1);
    CLK_L;
    delay_10us(1);
    CLK_H;
    delay_10us(1);
    CLK_L;
    delay_10us(1);
    while(adc_flag_get(ADC_FLAG_EOC) == RESET);
    adc_value[num] = ADC_RDATA;
    //printf("%d\n",adc_value[num]);
//    temp1=(uint16_t)ADC_RDATA>>2;
//    
//    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
//    CLK_L;
//    delay_10us(1);
//    CLK_H;
//    delay_10us(1);
//    CLK_L;
//    delay_10us(1);
//    CLK_H;
//    delay_10us(1);
//    adc_value[num] = 1024 - temp1/2;
    
    
    
  }
  
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
    while(adc_flag_get(ADC_FLAG_EOC) == RESET);
    temp = (uint16_t)ADC_RDATA;
  
  for(uint8_t j=0; j<14 ; j++)
  {
    CLK_H;
    CLK_L;
    CLK_H;
    CLK_L;

//    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
//    while(adc_flag_get(ADC_FLAG_EOC) == RESET);
//    adc_value[j]=(uint16_t)ADC_RDATA;
  }
  //adc_disable();
  
}
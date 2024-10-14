#include "ccd_fun.h"
#include "adc.h"
#include "uart.h"
#include "math.h"
uint8_t sun = 0;
float rult_height[4] = 0;
uint8_t flag_num1 = 0;
uint8_t i_num1 = 0;
uint8_t end_flag = 0;
uint8_t start_flag = 0;
/*
* @name:check_i()
* @fun: 进行i角校准
*/
int16_t abs1[2];
int16_t delta;
uint8_t check_i(uint16_t len) //len : 两条码尺的距离
{
  
  memset();
  if(flag_num1 == 0)
  {  
    if((sun == 0)&&(rx_buf[0] == 'e'))
    {
      rult_height[0] = sig_height();
      sun++;
    }
    
    if((sun == 1)&&(rx_buf[0] == 's'))
    {
      rult_height[1] = sig_height();
      sun = 0;
      flag_num1 = 1;
    }
    abs1[0] = rult_height[1] - rult_height[0];
    if(abs1[0] < 0)
    {
      abs1[0] = abs(abs1[0]);
    }
  }
  if(flag_num1 == 1)
  {
    if((sun == 0)&&(rx_buf[0] == 'n'))
    {
      rult_height[2] = sig_height();
      sun++;
    }
    
    if((sun == 1)&&(rx_buf[0] == 'o'))
    {
      rult_height[3] = sig_height();
      sun = 0;
      flag_num1 = 0;
    }
    end_flag = 1;
  }
  if(end_flag == 1)
  { 
    abs1[1] = rult_height[3] - rult_height[2];
    if(abs1[1] < 0)
    {
      abs1[1] = abs(abs1[1]);
    }
    delta = abs1[0] - abs1[1];
    if(delta < 0)
    {
      delta = abs(delta);
    }
    
    i_num1 = delta/10 * 206265 / len;
    end_flag = 0;
  }
    
}
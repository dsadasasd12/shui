#include "Algorithm.h"
#include "ccd.h"



/*灰度重心法*/
uint8_t num1;           //将像素点均匀分格的个数
uint16_t out_buf[250];    //像素点输出值
uint32_t Egi;         //Egi:累加像素坐标  
uint32_t Eui;         //Ugi:累加（像素坐标*像素值）
void barcent(uint16_t *bin,uint16_t *buf)//像素灰度值
{
        
  uint16_t adcv_k;      
            
  float out;
  adcv_k = 4096*K/3.3;
  uint8_t n;            //余数
  n = BIN_NUM%WIDTH;
  
  if(n != 0)
  {
    out = (1500/21);
    num1 = ((uint8_t)out +1);    
  }
  else
  {
    num1 = out;
  }
  for(uint16_t i = 0; i < num1; i++)
  {
    if(i*21 <= 2500)
    {
      for(uint8_t j = i*21; j < (i+1)*21; j++)
      {
        if(bin[j] > adcv_k)
        {
          Egi += j;
          Eui += bin[j];
        } 
        
      }
      buf[i] = (Eui/Egi);//光心位置
      Egi = 0;
      Eui = 0;
    }
  }
            
}

void getgray_value(uint16_t *buf,uint16_t *outbuf)
{
  for(uint8_t i=0; i<120; i++)
  {
    barcent(buf,outbuf);     
  }
  
  
}
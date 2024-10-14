#include "lcd160642.h"
/*****************************
*PA15->LCD_CS(CS)
*PB5 ->LCD_DATA(SI)
*PF1 ->LCD_REG_SL(A0)
*PB3 ->LCD_CLK(SCL)
*A0为高时显示数据



设置page地址 
设置column地址
******************************/
void spi0_gpio_init()
{
  //LCD_CLK & LCD_DATA
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_af_set(GPIOB,GPIO_AF_0,GPIO_PIN_3|GPIO_PIN_5);
  gpio_mode_set(GPIOB,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_3|GPIO_PIN_5);
  gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_3|GPIO_PIN_5);
  //CS
  rcu_periph_clock_enable(RCU_GPIOA);
  gpio_af_set(GPIOA,GPIO_AF_0,GPIO_PIN_15);
  gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_15);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_15);
  
  //AO
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_af_set(GPIOB,GPIO_AF_0,GPIO_PIN_2);
  gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_2);
  gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_2);
  //LCD_BL
  rcu_periph_clock_enable(RCU_GPIOF);
  gpio_af_set(GPIOF,GPIO_AF_0,GPIO_PIN_1);
  gpio_mode_set(GPIOF,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_1);
  gpio_output_options_set(GPIOF,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_1);
  
  //LCD_V4
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_af_set(GPIOB,GPIO_AF_0,GPIO_PIN_10);
  gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_10);
  gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
  
  //LCD_RES
  rcu_periph_clock_enable(RCU_GPIOB);
  gpio_af_set(GPIOB,GPIO_AF_0,GPIO_PIN_11);
  gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_11);
  gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_11);
}
void spi0_init()
{
  rcu_periph_clock_enable(RCU_SPI0);
  spi_parameter_struct spi0;
  spi_i2s_deinit(SPI0);
  spi_struct_para_init(&spi0);
  spi0.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
  spi0.device_mode = SPI_MASTER;
  spi0.endian = SPI_ENDIAN_MSB;
  spi0.frame_size = SPI_FRAMESIZE_8BIT;
  spi0.nss = SPI_NSS_SOFT;
  spi0.prescale = SPI_PSC_8;
  spi0.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
  spi_init(SPI0,&spi0);
  
  spi_enable(SPI0);
   
}
uint8_t spi0_write_read(uint8_t res)
{
  while(spi_i2s_flag_get(SPI0,SPI_FLAG_TBE) == RESET);
  spi_i2s_data_transmit(SPI0,res);
  
  while(spi_i2s_flag_get(SPI0,SPI_STAT_RBNE) == RESET);
  return spi_i2s_data_receive(SPI0);
}
void lcd_start()
{
//  gpio_bit_set(GPIOA,GPIO_PIN_7);
//  gpio_bit_reset(GPIOA,GPIO_PIN_7);
//  gpio_bit_reset(GPIOA,GPIO_PIN_5);
//  gpio_bit_set(GPIOA,GPIO_PIN_5);
  LCD_V4_H;
  
  LCD_RES_L;
  LCD_RES_H;
  AO_L;
  LCD_CS_L;
  spi0_write_read(0x40);  //初始化显示行
  spi0_write_read(0xa0);  //ADC=0
  spi0_write_read(0xa6);  //反转显示
  spi0_write_read(0xa4);  //关闭全屏显示
  spi0_write_read(0xa2);  //lcd电压偏置
  spi0_write_read(0xc0);  //行顺序0-63
  spi0_write_read(0x82);spi0_write_read(0x0e);    //刷频频率
  spi0_write_read(0x11);spi0_write_read(0x00);    //设置列数
  
  spi0_write_read(0xb1); //设置页数
  spi0_write_read(0xb2); 
  spi0_write_read(0xb3); 
  spi0_write_read(0xb4); 
  spi0_write_read(0xb5); 
  
  spi0_write_read(0x30);  //M信号0进行反转 
  spi0_write_read(0x23);  //V0电压电阻比
  spi0_write_read(0x2c);  //打开VC
  delay_10us(50);
  spi0_write_read(0x2e);  //打开VC VR
  delay_10us(50);
  spi0_write_read(0x2f);  //打开 VC VR VF
  delay_10us(50);
  spi0_write_read(0x81);  //对比度调节
  spi0_write_read(0x20);   
  
  spi0_write_read(0xab);  //开启系统时钟
  spi0_write_read(0xaf);  //开显示
  
  

  //spi0_write_read(0xe2);
  LCD_CS_H;
  
  
}
void lcd_init()
{
  spi0_gpio_init();
  spi0_init();
  lcd_start();
  
}
void write_to_lcd(uint8_t *txbuf, uint16_t len)
{ 
  uint8_t i;
  for(i=0;i<len;i++)
  {
     spi0_write_read(txbuf[i]);
     delay_10us(1);
     
  }
}
void read_from_lcd(uint8_t *rxbuf ,uint16_t len)
{
  uint8_t i;
  for(i = 0;i<len;i++)
  {
    rxbuf[i] = spi0_write_read(0xff);
    
  }
}
void display_on(uint8_t *buf)
{
  AO_L;
  LCD_CS_L;
  *buf = spi0_write_read(0xaf);
}
void init_display_line()
{
  AO_L;
  spi0_write_read(0x40);
}
void set_page_addr()
{
  AO_L;
  spi0_write_read(0xb0);
}
void set_column_addr()
{
  AO_L;
  spi0_write_read(0x10);
  spi0_write_read(0x00);
}
void write_display_data(uint8_t *txbuf)
{
  AO_H;
  LCD_CS_L;
  uint8_t  i ;
  for(i=0;i<4; i++);
  {
    spi0_write_read(txbuf[i]);
  }
  LCD_CS_H;
}
void display_lcd_test()
{
  gpio_bit_reset(GPIOA,GPIO_PIN_15);
  uint8_t txbuf[4] = {0x01,0x02,0x03,0x04};
  write_to_lcd(txbuf,4);
  
  //gpio_bit_set(GPIOA,GPIO_PIN_15);
  
}
void cmd(uint8_t num)
{
  AO_L;
  LCD_CS_L;
  spi0_write_read(num);
  LCD_CS_H;
}
void data(uint8_t num)
{
  AO_H;
  LCD_CS_L;
  spi0_write_read(num);
  LCD_CS_H;
}
void clear_ram()
{
  uint8_t i,j;
  for(i=0;i<8;i++)
  {
    cmd(i|0xb0);
    cmd(0x10);
    cmd(0x00);
    for(j = 0;j<160;j++)
    {
      data(0);
    }
  }
}

uint8_t hex_h = 0,hex_e = 0;
uint8_t temp1,temp2;
uint8_t utemp;
uint8_t s_hex_h,s_hex_e;
/* @name:clear_area()
*  @fun:清除矩形区域
*  @parm: x_start:矩形x轴起始，x_end:矩形x轴结束，y_start:矩形y轴开始，矩形y轴结束
*/
void clear_area(uint8_t x_start,uint8_t x_end, uint8_t y_start,uint8_t y_end)
{
  uint8_t start = 0;
  
  
  if(x_start > 16)
  {
    hex_e = x_start%16;
    hex_h = x_start/16;
  }
  else
  {
    hex_e = x_start%16;//得到起始位置
    hex_h = 0;
    s_hex_h = hex_h;
    s_hex_e = hex_e;
  }

//  temp1 = (x_end - x_start)/16;
//  temp2 = (x_end - x_start)%16;
//  if(temp2 == 0)
//  {
//    temp2 = temp1;
//  }
//  for(uint8_t i = 0; i < temp1; i++)
//  {
//    
//    for(uint8_t j = 0; j < temp2; j++)
//    {
//      cmd(y|0xb0);
//      cmd(0x10|hex_h|i);
//      cmd(0x00|hex_e+j);
//      data(0);
//    }
//  }
  for(utemp = y_start; utemp <=y_end; utemp++)
  {
    hex_h = s_hex_h;
    hex_e = s_hex_e;
    for(uint8_t i = 0; i < x_end - x_start; i++)
    {
      
      if(hex_e >= 16)
      {
        hex_h++;
        hex_e = 0;
      }
      else
      {
        hex_e++;
      }
      temp1 = hex_e;
      temp2 = hex_h;
      cmd(utemp|0xb0);
      cmd(0x10|hex_h);
      cmd(0x00|hex_e);
      data(0);
    }
  }
  
}
uint8_t x_y[4] = {3,3,10,10};
uint8_t err,delt_x,delt_y;
 uint8_t k,m,l1;
void draw_point(uint8_t x,uint8_t y)
{
 
  k = (y/8);
  m = y%8;
  cmd(k|0xb0);
  cmd((x>>4)|0x10);
  cmd(x&0x0f);
  switch(m)
  {
    case 0:
     data(0x01);
     break;
    case 1:
     data(0x02);
     break;
    case 2:
     data(0x04);
     break;
    case 3:
     data(0x08);
     break;
    case 4:
     data(0x10);
     break;
    case 5:
     data(0x20);
     break;
    case 6:
     data(0x40);
     break;
    case 7:
     data(0x80);
     break;
  }
    
//    l1 |= 1 << m;
//    if(m != 0)
//    {
//      uint8_t l2 ;
//      l2 |= l1;
//      switch(m)
//      {
//      case 1:
//        
//        break
//      }
//    }
    
}
void draw_point_HZ(uint8_t x,uint8_t y)
{
  uint8_t k,m;
  k = y/8;
  m = y%8;
  cmd(k|0xb0);
  cmd((x>>4)|0x10);
  cmd(x&0x0f);
  data(0x01);
}
void line_write(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
  
//  if(x_y[1] < x_y[3])
//  {
//    
//    temp = x_y[1];
//    x_y[1] = x_y[3];
//    x_y[3] = temp; 
//    temp = x_y[0];
//    x_y[0] = x_y[2];
//    x_y[2] = temp;
//  }
  delt_x = x_y[2] - x_y[0];
  delt_y = x_y[3] - x_y[1];
 
  if(delt_x > 0)          
  {    
      if(delt_y > delt_x)   //斜率>1
      {
          while(x_y[1]>x_y[3])
          {              
                if(err < 0)
                {
                  x_y[2]++;
                  x_y[3]++;
                  err = err + delt_y - delt_x;
                }
                else
                {
                  x_y[3]++;
                  err = err - delt_x;
                 }           
          }
      }
      else if((delt_x>delt_y)&&(delt_y>0))                //1>=斜率>=0
      {
          
          while(x_y[2]>x_y[0])
          {
            if(err<0)
            {
              x_y[2]++;
              x_y[3]++;
              err = err - delt_y + delt_x;
            }
            else
            {
              x_y[2]++;
              err = err - delt_y;
            }
            draw_point(x_y[2],x_y[3]);
          }
      
    }
    else                //delt_y<0
    {
      if((delt_y+delt_x)<0) //-delt_y大于delt_x
      {
        while(x_y[1] > x_y[3])
        {
          if(err<0)
          {
            x_y[2]--;
            x_y[3]++;
            err = err - delt_x - delt_y;
          }
          else
          {
            x_y[3]++;
            err = err - delt_x;
          }
        }
      }
      else               //-delt_y小于delt_x
      {
        while(x_y[2] > x_y[0])
        {
          if(err<0)
          {
            x_y[2]--;
            err = err + delt_y;
          }
          else
          {
            x_y[2]--;
            x_y[3]++;
            err = err - delt_x + delt_y;
          }
         
          
          draw_point(x_y[2],x_y[3]);
        }
      }
      
    }
  }
  else 
  {   
    if(delt_y > delt_x) //k<-1
    {
      while(x_y[1] > x_y[3])
      {
        if(err<0)
        {
          x_y[2]--;
          x_y[3]++;
          err = err - delt_y + delt_x;          
        }
        else
        {
          x_y[3]++;
          err = err - delt_y;
        }
      }
    }
    else 
    {
      while(x_y[0] < x_y[2])
      {
        if(err < 0)
        {
          x_y[2]--;
          x_y[3]++;
          err = err - delt_y - delt_x;
        }
        else
        {
          x_y[2]--;
          err = err - delt_y;
        }
        draw_point(x_y[2],x_y[3]);
      }
      while(x_y[1] != x_y[3])
      {
        if(x_y[1] > x_y[3])
        {
          x_y[3]++;
        }
        else
        {
          x_y[3]--;
        }
        draw_point(x_y[2],x_y[3]);
      }
    }
  }
}

#include "flash.h"
#include "spi.h"
void Sst25_init()
{
  spi_gpio_init();
  spi1_init();
  spi_enable(SPI1);
  CS_L;
}
void ESWR()
{
  CS_L;
  SPI1_WriteRead(0x50);
  CS_H;
  CS_L;
  SPI1_WriteRead(0x01);
  SPI1_WriteRead(0);
  CS_H;
  Sst25_read_status();
}
uint8_t  Sst25_read_status()
{
  uint8_t res;
  CS_L;
  SPI1_WriteRead(0x05);
  res = SPI1_WriteRead(0xff);
  CS_H;
  return res;
  
}
void BUSY()
{
  uint8_t res;
  do
  {
    res = Sst25_read_status();
  }while((res&0x01) == 1);
}
void Ssta_write_enable()
{
  Sst25_read_status();
  CS_L;
  SPI1_WriteRead(0x06);
  CS_H;
}
void Ssta_erase64KB(uint8_t numblock)
{
  uint8_t com_add[4];
  com_add[0] = 0xD8;
  com_add[1] = (numblock*64*1024)>>16;
  com_add[2] = (numblock*64*1024)>>8;
  com_add[3] = (numblock*64*1024)>>0;
  
  ESWR();
  Ssta_write_enable();
  CS_L;
  SPI1_Write(com_add,4);
  CS_H;
  BUSY();
}
void Ssta_Write(uint8_t *wdata,uint8_t numpage)
{
  uint8_t com_add[4];
  com_add[0] = 0x02;
  com_add[1] = (numpage*256)>>16;
  com_add[2] = (numpage*256)>>8;
  com_add[3] = (numpage*256)>>0;
  
  ESWR();
  Ssta_write_enable();
  BUSY();
  CS_L;
  SPI1_Write(com_add,4);
  SPI1_Write(wdata,256);
  
  CS_H;
}
void Ssta_Read(uint8_t *rbuff,uint8_t len,uint32_t addr)
{
  uint8_t com_add[4];
  com_add[0] = 0x03;
  com_add[1] = addr>>16;
  com_add[2] = addr>>8;
  com_add[3] = addr>>0;
  
  
  CS_L;
  SPI1_Write(com_add,4);
  SPI1_Read(rbuff,len);
  CS_H;
}
void Ssta_ReadID(uint8_t *rbuff,uint8_t len)
{
  uint8_t com_add[4];
  com_add[0] = 0x90;
  com_add[1] = 0;
  com_add[2] = 0;
  com_add[3] = 0;
  
  Sst25_read_status();
  CS_L;
  SPI1_Write(com_add,4);
  SPI1_Read(rbuff,len);
  
  CS_H;
}
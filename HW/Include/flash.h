#ifndef _FLASH_
#define _FLASH_
#include "gd32e23x.h"
#define CS_L gpio_bit_reset(GPIOB,GPIO_PIN_12)
#define CS_H gpio_bit_set(GPIOB,GPIO_PIN_12)
void Sst25_init();
uint8_t Sst25_read_status();
void Ssta_write_enable();
void Ssta_erase64KB(uint8_t numblock);
void Ssta_Write(uint8_t *wdata,uint8_t numpage);
void Ssta_Read(uint8_t *rbuff,uint8_t len,uint32_t addr);
void Ssta_ReadID(uint8_t *rbuff,uint8_t len);
void BUSY();
void ESWR();
#endif
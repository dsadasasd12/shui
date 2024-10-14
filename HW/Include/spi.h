#ifndef _SPI_
#define _SPI_
#include "gd32e23x.h"
void spi_gpio_init();
void spi1_init();
uint8_t SPI1_WriteRead(uint8_t txd);
void SPI1_Write(uint8_t *wdata,uint16_t len);
void SPI1_Read(uint8_t *rdata,uint16_t len);
#endif
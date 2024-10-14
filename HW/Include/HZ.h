#ifndef _HZ_
#define _HZ_
#include "gd32e23x.h"
#include "lcd160642.h"
void Write_HZ(uint8_t x,uint8_t y,uint8_t index,uint8_t size,uint8_t **buf);
void write_Hz(uint8_t x,uint8_t y,uint8_t (*buf)[16],uint8_t num);
#define picbit_num 10
void getnum(float n);
#endif
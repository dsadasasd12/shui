#ifndef _ALG_
#define _ALG_
#include "gd32e23x.h"
#define BIN_NUM 2500    //计算像素个数
#define G_MAX   2       //极值点
#define K       0.32     //阈值点
#define WIDTH   21      //将像素数量分为width为一组
#define LEN     ((BIN_NUM/WIDTH)!=0)?(uint8_t)((BIN_NUM/WIDTH)+1):(BIN_NUM/WIDTH)
void barcent(uint16_t *bin,uint16_t *buf);
void getgray_value(uint16_t *buf,uint16_t *outbuf);
#endif
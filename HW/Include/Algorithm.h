#ifndef _ALG_
#define _ALG_
#include "gd32e23x.h"
#define BIN_NUM 2500    //�������ظ���
#define G_MAX   2       //��ֵ��
#define K       0.32     //��ֵ��
#define WIDTH   21      //������������ΪwidthΪһ��
#define LEN     ((BIN_NUM/WIDTH)!=0)?(uint8_t)((BIN_NUM/WIDTH)+1):(BIN_NUM/WIDTH)
void barcent(uint16_t *bin,uint16_t *buf);
void getgray_value(uint16_t *buf,uint16_t *outbuf);
#endif
#ifndef _DECODE_
#define _DECODE_
#include "gd32e23x.h"
uint16_t *Code_bar_length(uint16_t *buf);
extern uint16_t out[42],f_out[42];   //输出结果
extern uint8_t bar_code[15];  //将码条宽度进行编码存储在此数组
extern uint8_t feng_code[15];
extern uint16_t temp_feng_ed[21];
extern uint16_t min_adc[4];
void display_feng(uint16_t *in);
uint16_t match_num(uint8_t *in);
float show_fine_turn(uint16_t *in,uint8_t bit);
void display_feng_buble(uint16_t *in,uint8_t rsln);
float display_len(uint8_t len,float dis);
void adj_min(uint16_t *buf ,uint16_t start1, uint16_t end1, uint16_t start2, uint16_t end2);
float sig_height();
uint8_t show_vis_ran(uint16_t *in);
extern float rel_len;
#endif
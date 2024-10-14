#ifndef _UI_
#define _UI_
#include "gd32e23x.h"
typedef struct ui
{
  uint8_t cur;
  uint8_t up;
  uint8_t down;
  uint8_t enter;
  void (*currnt_index)();
}index_table;
void cg_ui1();
void display_num(float num, uint8_t bit, uint8_t x_s, uint8_t y_s,uint8_t loc);
extern index_table table[40];
void main_ui1();
void main_ui2();
void main_ui3();
void main_ui0();
void stand_meas1();
void stand_meas2();
void stand_meas3();
void stand_meas4();
void stand_meas5();
void stand_meas6();
void height_loft1();
void height_loft2();
void height_loft3();
void height_loft4();
void height_loft5();
void height_loft6();
void height_loft7();
void stand_list1();
void stand_list2();
void stand_list3();
void stand_list4();
void hgt_dif_loft1();
void hgt_dif_loft2();
void view_loft1();
void view_loft2();
void line_mea_main1();
void line_mea_main2();
void line_mea_main3();
void line_mea_start1();
void line_mea_start2();
void line_mea_start3();
void line_mea_start4();
void line_mea_start5();
void line_mea_start6();
void line_mea_start7();
void line_mea_start8();
void line_mea_start9();
void line_mea_start10();
#endif
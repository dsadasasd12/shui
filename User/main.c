#include "main.h"
#include "delay.h"
#include "spi.h"
#include "flash.h"
#include "adc.h"
#include "bf2460.h"
#include "lcd160642.h"
#include "uart.h"
#include "Algorithm.h"
#include <stdio.h>
#include <string.h>
#include "HZ.h"
#include "ccd_decode.h"
#include "ui.h"
//uint8_t buf[64] = {0x06,0x07,0x03,0x03,0x03};
//uint8_t rbuf[50];
//uint8_t res;

//uint32_t clock;
//uint32_t u;
//uint16_t adc;
//uint8_t testbuf[3];
//uint8_t l;
//uint8_t a;
//uint8_t len;
//uint8_t i;
//uint16_t adc_buf[20];
//uint16_t num;
//uint16_t loc;//码条位置

#define clear_ram_  1
#define line_write_ 0

//uint8_t feng_code[15];
extern uint8_t decode_feng[10];
extern uint8_t up_rlt,down_rlt;    //向上相对位置
extern uint16_t up_wid_end; 
extern uint16_t down_wid_end;
extern uint8_t s1[4];
extern uint8_t test[4];

uint8_t num2;    //显示任意四个码条长度
float height1; //显示高度
uint8_t vis_range = 0;
uint8_t buf_f;
//float nnn = 19998;
int main()
{
  //rcu_system_clock_source_config(RCU_CKSYSSRC_IRC8M);
  //clock = rcu_clock_freq_get(CK_SYS);
   systick_config();
   
//  Sst25_init();
//  Ssta_erase64KB(0);
//  Sst25_read_status();
//  Ssta_Write(buf,0);
//  Ssta_Read(buf,4,0);
//  Ssta_Write((uint8_t*)adc_value,0);
//  delay_1ms(50);
//  Ssta_Read(rbuf,6000,0);
  
//PB14_PWM_init();
  
    bf2460_gpio();
    adc_gpio_init();//adc_gpio
    adc_init();
   // rcu_periph_clock_enable(RCU_GPIOA); 
   // gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9|GPIO_PIN_7);
   // gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
   // gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);
    uart0_init(256000);
//  pwm_clk_init();
 // tim_gpio_init();
    //gpio_bit_set(GPIOA,GPIO_PIN_4);
    //gpio_bit_reset(GPIOA,GPIO_PIN_9);
    lcd_init();
    
    gpio_bit_reset(GPIOF,GPIO_PIN_1);
  //page_contioun(2,5); 
#if clear_ram_
    clear_ram();
#endif
  // draw_point(159,1); 
  //set_page_addr();
  // set_column_addr();
  //display_on(testbuf);
  //write_display_data(buf);
  //PB0_PWM();
  //gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_9);
  //gpio_output_options_set(GPIOA,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
#if line_write_
    line_write(30,40,90,100);
#endif 
    
    
  while(1)
  {
//    bf2460_ lcd_test(2);init();  
//    gpio_bit_reset(GPIOA,GPIO_PIN_9);
//    delay_10us(10);
//    gpio_bit_set(GPIOA,GPIO_PIN_9);
//    bf2460_init();  
//    init();
//    getgray_value(adc_value,out_buf);  
//    meas(1);
//    Adj_thd(adc_value,700,1400);
//    Code_bar_length(adc_value);
//   
//    display_feng_buble(f_out,5);
//    vis_range = show_vis_ran(temp_feng_ed);
    Uart0_process_data();
    cg_ui1();
    //write_zm(10,7,14);
    //height1 = 40/(float)show_vis_ran(temp_feng_ed);
    //line_mea_start11();
    
    
    //check_i(60000);   
    ///sig_height();
//    for(uint16_t j = 0; j < 2500; j++)
//    {
//      printf("%d\n",adc_value[j]);
//    }
//    getnum(rel_len);    
//    write_num(10,2,down_rlt);
//    getnum(loc);
//    show_bar_code();
//    write_num(1,6,0);
//    getnum(192);
//    delay_1ms(100);
//    write_Hz(30,4);
//    draw_point(40,40);
//    draw_point(41,39);
//    draw_point(42,38);
//    draw_point(43,37);
//    draw_point(44,36);
//    barcent(adc_value,out_buf);
//    barcent(adc_buf);
//    send_data(0x00);
//    send_data((adc_value[1]>>8));
//    send_data((adc_value[1]));
//    ccd_init(9100);
//    printf("%ld",sizeof(struct a));
//    printf("%d",(adc_value[1]>>8));
//    printf("%f",adc_value[1]);
//    send_data(sizeof(struct a));
//    adc = getadc_value();
//    i++;
//
  };
}
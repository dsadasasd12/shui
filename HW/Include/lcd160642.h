#ifndef _LCD_
#define _LCD_
#include "gd32e23x.h"
#define LCD_CS_H gpio_bit_set(GPIOA,GPIO_PIN_15)
#define LCD_CS_L gpio_bit_reset(GPIOA,GPIO_PIN_15)
#define AO_H gpio_bit_set(GPIOB,GPIO_PIN_2)
#define AO_L gpio_bit_reset(GPIOB,GPIO_PIN_2)
#define LCD_BL_OFF gpio_bit_set(GPIOF,GPIO_PIN_1)
#define LCD_BL_ON gpio_bit_reset(GPIOF,GPIO_PIN_1)
#define LCD_V4_H gpio_bit_set(GPIOB,GPIO_PIN_10)
#define LCD_V4_L gpio_bit_reset(GPIOB,GPIO_PIN_10)
#define LCD_RES_H gpio_bit_set(GPIOB,GPIO_PIN_11)
#define LCD_RES_L gpio_bit_reset(GPIOB,GPIO_PIN_11)
void spi0_gpio_init();
void spi0_init();
void lcd_init();
void write_to_lcd(uint8_t *txbuf, uint16_t len);
void lcd_start();
void read_from_lcd(uint8_t *rxbuf ,uint16_t len);
void display_on(uint8_t *buf);
void init_display_line();
void set_page_addr();
void set_column_addr();
void write_display_data(uint8_t *txbuf);
void display_lcd_test();
void cmd(uint8_t num);
void data(uint8_t num);
void clear_ram();
void draw_point_HZ(uint8_t x,uint8_t y);
#endif
#ifndef _UART_
#define _UART_
#include "gd32e23x.h"
#include <stdio.h>
#include "gd32e230c_eval.h"
void uart0_init();
void send_data(uint16_t data);
int fputc(int ch, FILE *f);
void uart1_init();
void send_data_uart0(uint16_t data);
void uart0_init(uint32_t baud);
extern uint8_t rx_buf[20]; //���յ�����
extern uint8_t rx_len;     //���յ����ݸ���
extern uint8_t tx_buf[20]; //���͵�����
extern uint8_t tx_len;     //���͵����ݸ���
#endif
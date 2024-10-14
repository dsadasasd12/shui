#include "uart.h"
#include <stdio.h>
uint8_t rx_count = 0,tx_count = 0;//一轮串口接收的数据个数
uint8_t rx_buf[20]; //接收的数据
uint8_t rx_len;     //接收的数据个数
uint8_t tx_buf[20]; //发送的数据
uint8_t tx_len;     //发送的数据个数
void uart0_init(uint32_t baud)
{
    //端口初始化
    rcu_periph_clock_enable(RCU_GPIOB);
    
    gpio_af_set(GPIOB, GPIO_AF_0, GPIO_PIN_6|GPIO_PIN_7);

    gpio_mode_set(GPIOB, GPIO_MODE_AF,GPIO_PUPD_PULLUP , GPIO_PIN_6);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_6);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_7);
  
    //UART0初始化
    rcu_periph_clock_enable(RCU_USART0);
    
    usart_deinit(USART0);
    usart_baudrate_set(USART0, baud);
    usart_parity_config(USART0,USART_PM_NONE);
    usart_data_first_config(USART0,USART_MSBF_LSB);
    usart_word_length_set(USART0,USART_WL_8BIT);
    usart_stop_bit_set(USART0,USART_STB_1BIT);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE); 
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    
    usart_enable(USART0);
    
    nvic_irq_enable(USART0_IRQn, 0);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
    usart_interrupt_enable(USART0, USART_INT_IDLE); // 使能“IDLE线检测中断”
    usart_interrupt_enable(USART0, USART_INT_TBE);  // 使能“发送缓冲区空中断”
}

int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t) ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}
void send_data(uint16_t data)
{
  
   usart_data_transmit(USART0, data);
   while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

//void USART0_IRQHandler(void)
//{
//  uint8_t data;
//  if(RESET != usart_interrupt_flag_get(USART0,USART_INT_FLAG_RBNE))
//  {
//    data = usart_data_receive(USART0);
//    usart_data_transmit(USART0,(uint8_t)data);
//    
//    
//    //usart_data_transmit(USART0,0x35);
//     while(RESET == usart_flag_get(USART0,USART_FLAG_TBE));
//    usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);
//  }
//}
void USART0_IRQHandler(void)
{
  if(RESET != usart_interrupt_flag_get(USART0,USART_INT_FLAG_RBNE))
  {
    usart_interrupt_flag_clear(USART0,USART_INT_FLAG_RBNE);
    uint8_t ch = usart_data_receive(USART0);
    if(rx_count < 20)
    {
      rx_buf[rx_count++] = ch; 
    }
    
  }
  if(RESET != usart_interrupt_flag_get(USART0,USART_INT_FLAG_IDLE))
  {
    usart_interrupt_flag_clear(USART0,USART_INT_FLAG_IDLE);
    uint8_t ch = usart_data_receive(USART0);
    if(rx_count > 0)
    {
      usart_receive_config(USART0, USART_RECEIVE_DISABLE);// 关闭串口接收功能，准备处理数据
      rx_len = rx_count;
      rx_count = 0;
      printf("receve byte %d\n", rx_len);
    }
  }
  if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE))
  {
    usart_interrupt_flag_clear(USART0, USART_INT_FLAG_TBE);
    
    // 如果满足以下条件，说明缓存中有数据需要发送
    if(tx_len > 0)
    {
      // 如果满足以下条件，说明缓存中还有数据没发送完
      if(tx_count < tx_len)
      {
        usart_data_transmit(USART0,tx_buf[tx_count++]);
        printf("\n");
        //printf("data_send2\n");
      }
      // 反之，说明缓存中的数据都已经发送完毕
      else
      {
        usart_interrupt_disable(USART0, USART_INT_TBE);
        
        tx_len = 0;
        tx_count = 0;
        //printf("data_send3\n");
      }
    }
    // 反之，说明缓存中没有数据需要发送
    else
    {
      usart_interrupt_disable(USART0, USART_INT_TBE);
      printf("data_send1\n");
    }
  }
}
void Uart0_process_data()
{
  if(rx_len > 0)
  {
    if(!(tx_len > 0))
    {
      printf("process_data\n");
      memcpy(tx_buf,rx_buf,rx_len);
      //memset(rx_buf,0,sizeof(rx_buf));
      tx_len = rx_len;
      rx_len = 0;
      for(uint8_t n = 0; n < tx_len; n++)
      {
        printf("data: %c\n",tx_buf[n]);
      }
      //usart_interrupt_enable(USART0, USART_INT_TBE);
      usart_receive_config(USART0, USART_RECEIVE_ENABLE);  
      usart_interrupt_enable(USART0, USART_INT_RBNE);       
      usart_interrupt_enable(USART0, USART_INT_IDLE);       
      usart_interrupt_enable(USART0, USART_INT_TBE); 
      printf("Process data over!\n");
      printf("\n");
    }
  }
}
void uart1_init()
{
    //端口初始化
    
    rcu_periph_clock_enable(RCU_GPIOA);
    
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9|GPIO_PIN_10);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);
  
    //UART1初始化
    rcu_periph_clock_enable(RCU_USART0);
    
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 9600U);
    usart_parity_config(USART0,USART_PM_NONE);
    usart_data_first_config(USART0,USART_MSBF_MSB);
    usart_word_length_set(USART0,USART_WL_8BIT);
    usart_stop_bit_set(USART0,USART_STB_1BIT);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE); 
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    
    usart_enable(USART0);
    
//    nvic_irq_enable(USART1_IRQn, 1);
//    usart_interrupt_enable(USART1, USART_INT_RBNE);
}
void send_data_uart0(uint16_t data)
{
  
   usart_data_transmit(USART0, data);
   while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}
void USART_IRQHandler(void)
{
  uint8_t data;
  if(RESET != usart_interrupt_flag_get(USART1,USART_INT_FLAG_RBNE))
  {
    data = usart_data_receive(USART1);
    usart_data_transmit(USART1,(uint8_t)data);
    while(RESET == usart_flag_get(USART1,USART_FLAG_TBE));
  }
}
#include "spi.h"
/******************************
*PB12->SPI1_NSS
*PB13->SPI1_SCK
*PB14->SPI1_MISO
*PB15->SPI1_MOSI
*所有指令都在CE由高电平转换为低电平时启动，
*字节传输先传高位，
*在SCK上升沿传输，
*******************************/
void spi_gpio_init()
{
	rcu_periph_clock_enable(RCU_SPI1);
	rcu_periph_clock_enable(RCU_GPIOB);
//	gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_PIN_12);
//	gpio_mode_set(GPIOB,GPIO_MODE_AF,GPIO_PUPD_PULLDOWN,GPIO_PIN_13);
//	gpio_mode_set(GPIOB,GPIO_MODE_INPUT,GPIO_PUPD_NONE,GPIO_PIN_14);
//	gpio_mode_set(GPIOB,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_15
//         gpio_deinit(GPIOB);
         gpio_af_set(GPIOB, GPIO_AF_0, GPIO_PIN_13 |GPIO_PIN_14 | GPIO_PIN_15);
         gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE,  GPIO_PIN_13 | GPIO_PIN_14 |GPIO_PIN_15);         
         gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_14 |  GPIO_PIN_15);
         gpio_bit_reset(GPIOB,GPIO_PIN_13 | GPIO_PIN_14 |  GPIO_PIN_15);
         
         gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
         gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);       
         gpio_bit_set(GPIOB,GPIO_PIN_12);
         
}
void spi1_init()
{
	spi_parameter_struct SPI1_Init;
	spi_i2s_deinit(SPI1);
        spi_struct_para_init(&SPI1_Init);
	SPI1_Init.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
	SPI1_Init.device_mode = SPI_MASTER;
	SPI1_Init.endian = SPI_ENDIAN_MSB;
	SPI1_Init.frame_size = SPI_FRAMESIZE_8BIT;
	SPI1_Init.nss = SPI_NSS_HARD;
	SPI1_Init.prescale = SPI_PSC_4;
	SPI1_Init.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
        spi_init(SPI1,&SPI1_Init);
        spi_fifo_access_size_config(SPI1,SPI_BYTE_ACCESS);
        
	
}
uint8_t SPI1_WriteRead(uint8_t txd)
{
	while(spi_i2s_flag_get(SPI1,SPI_FLAG_TBE) == RESET);
	spi_i2s_data_transmit(SPI1,txd);	
	while(spi_i2s_flag_get(SPI1,SPI_FLAG_RBNE) == RESET);
	return (spi_i2s_data_receive(SPI1));
}
void SPI1_Write(uint8_t *wdata,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		SPI1_WriteRead(wdata[i]);
	}
}
void SPI1_Read(uint8_t *rdata,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		rdata[i]=SPI1_WriteRead(0xfe);
	}
}
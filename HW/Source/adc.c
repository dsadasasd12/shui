#include "adc.h"
#include "bf2460.h"
/*
*PA0-PA2 CCD_SIG
*PA3     CCD_SHIFT_GATE
*PA5     SH
*PA6     ICG
*PA7     CLK
*/
uint16_t adc_value[2500];
void adc_gpio_init()
{
  
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
  //gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_0);
  gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_4);
  //gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_2);
 
}
void adc_init()
{
    rcu_periph_clock_enable(RCU_ADC);
    
    adc_special_function_config(ADC_SCAN_MODE,DISABLE);      //É¨Ãè
    adc_special_function_config(ADC_CONTINUOUS_MODE,DISABLE);//Á¬Ðø
    //DMA_init();
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL,ADC_EXTTRIG_REGULAR_NONE);
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);          //ÓÒ¶ÔÆë
    adc_resolution_config(ADC_RESOLUTION_12B);
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 4);
    adc_regular_channel_config(0, ADC_CHANNEL_4, ADC_SAMPLETIME_1POINT5);
    //adc_regular_channel_config(1, ADC_CHANNEL_2, ADC_SAMPLETIME_55POINT5);
    //adc_regular_channel_config(2, ADC_CHANNEL_2, ADC_SAMPLETIME_55POINT5);
    //adc_regular_channel_config(3, ADC_CHANNEL_3, ADC_SAMPLETIME_55POINT5);
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    
    adc_enable();
    delay_10us(1U);
    adc_calibration_enable();   
    adc_dma_mode_disable();
    
    
   
    
}
void DMA_init()
{
    dma_parameter_struct dma_data_parameter;

    rcu_periph_clock_enable(RCU_DMA);
	    
    dma_deinit(DMA_CH0);
    
    
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA);
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr  = (uint32_t)(&adc_value);
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;  
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number       = 2546U;
    dma_data_parameter.priority     = DMA_PRIORITY_HIGH;
    dma_init(DMA_CH0, &dma_data_parameter);

    //dma_circulation_enable(DMA_CH0);
    dma_memory_to_memory_disable(DMA_CH0);

    dma_channel_enable(DMA_CH0);

}
void user_adc_init()
{
  gpio_init();
  
  adc_init();
  //adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
 
 // memset(adc_value,0,sizeof(adc_value));
  
}
uint16_t getadc_value()
{
  adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
  
    return (adc_regular_data_read());
   
}
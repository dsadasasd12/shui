#include "ccd.h"
#include "bf2460.h"
#include "stdlib.h"
#define MAX_DIS 2
#define MAX_CHN 4
static uint8_t ccd_num;
static uint8_t ccd_type[2];
uint8_t turning;
uint16_t ccdback[MAX_DIS][MAX_CHN*64];
uint8_t lines,ccderr[MAX_DIS][MAX_CHN];
uint32_t angle,realagl[4];
uint8_t sh_tim[MAX_DIS][MAX_CHN];
void speed_ccd(uint8_t codedisc,uint8_t channel)
{
  uint8_t spd_nmb;
  uint32_t sqd_lct;
  turning = 0;
  sqd_lct = channel*64;
  for(spd_nmb = 0;spd_nmb < 64;spd_nmb++)
  {
    
    if(abs(ccdback[codedisc][sqd_lct + spd_nmb] - adc_value[spd_nmb])>50)
    {
      turning = 1;
    }
    ccdback[codedisc][sqd_lct+spd_nmb] = adc_value[spd_nmb];
  }
}

/*CCD测角*/
//积分时间范围 0 - 10
void meas(uint8_t sh_time)
{
  ccd_init(sh_time);
}

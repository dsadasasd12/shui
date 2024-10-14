#include"tcd1254.h"
extern unsigned short ccdbuf[];

//SH
static void ccd_sh_set(void)
{
//    GPIO_SetBits(GPIOA, GPIO_Pin_7);
   GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}

static void ccd_sh_reset(void)
{
  //  GPIO_ResetBits(GPIOA, GPIO_Pin_7);
   GPIO_SetBits(GPIOA, GPIO_Pin_7);
}

//CS
static void ccd_cs_set(void)
{
  //  GPIO_SetBits(GPIOA, GPIO_Pin_1);
  GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

static void ccd_cs_reset(void)
{
 //   GPIO_ResetBits(GPIOA, GPIO_Pin_1);
  GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

//CK
static void ccd_ck_set(void)
{
   // GPIO_SetBits(GPIOA, GPIO_Pin_5);
  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
static void ccd_ck_reset(void)
{
  //  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
  GPIO_SetBits(GPIOA, GPIO_Pin_5);
}
/*����ѡ��*/
static void ccd_disc_select(unsigned char disc)
{
    if(disc == 0) //��ֱ����V
    {
     GPIO_ResetBits(GPIOA, GPIO_Pin_0); //v
     GPIO_SetBits(GPIOA, GPIO_Pin_6);   // h
    }
    else     //ˮƽ����H
    {
      GPIO_SetBits(GPIOA, GPIO_Pin_0);  // v
      GPIO_ResetBits(GPIOA, GPIO_Pin_6); //h
    }
}
/*ͨ��ѡ��*/
static void ccd_ccdch_select(unsigned char ch,unsigned char disc)
{

    if(disc == 0) //��ֱ����V
    {
      if(ch == 0)
      {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);//SL1
      }
      else if(ch == 1)
      {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_SetBits(GPIOB, GPIO_Pin_14);//SL1
      }
      else if(ch == 2)
      {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);//SL1
      }
      else if(ch ==3)
      {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_SetBits(GPIOB, GPIO_Pin_14);//SL1
      }
    }
    else
    {
      if(ch == 0)
      {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);//SL1
      }
      else if(ch == 1)
      {         
         GPIO_ResetBits(GPIOB, GPIO_Pin_15);//SL0
         GPIO_SetBits(GPIOB, GPIO_Pin_14);//SL1
      }
      else if(ch == 2)
      {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);//SL1
      }
      else if(ch ==3)
      {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);//SL0
        GPIO_SetBits(GPIOB, GPIO_Pin_14);//SL1
      }
    }
}
/*���ٻ���*/
#pragma optimize=none
static void fast30p(void)
{
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
  ccd_ck_set();
  ccd_ck_reset();
}
//us��ʱ
static void nsdelay(void)
{
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
}
/*������ccd*/
void tcd1254_read(unsigned char codedisc,unsigned char ccdch,int shtime)
{
    unsigned short int temp;
    int i, j; 
    ccd_disc_select(codedisc);
    ccd_ccdch_select (ccdch,codedisc);
    ccd_cs_set();//ICGHIGH;
    ccd_sh_reset();//SHOFF;
    nsdelay(); 
    nsdelay();
    for(i=0;i<10;i++) //�ն�10��
    {	
     ccd_ck_set();
     ccd_cs_reset();//ICGLOW
     nsdelay();  //500ns
     ccd_sh_set();//SHON;
     nsdelay();
     nsdelay();
     ccd_sh_reset();//SHOFF;
     nsdelay();
     nsdelay();
     ccd_cs_set();//ICGHIGH;
     ccd_ck_reset();//CKLOW;                  //T4 (typ  20)
     ccd_ck_set();//CKHIGH;
     ccd_ck_reset();//CKLOW;
      for(j=0;j<85;j++)  //2550
      {
        fast30p();
        fast30p();
      } 
    }
    ccd_ck_reset();
    ccd_cs_reset();//ICGLOW
    nsdelay();  //500ns
    ccd_sh_set();//SHON;
    while(shtime!=0)	         //����ʱ�� T3>1000ns
    {
      fast30p();
      shtime--;
    }
    ccd_sh_reset();//SHOFF;  
    nsdelay(); //500ns
    nsdelay(); //500ns
    nsdelay(); //500ns
    ccd_cs_set();//ICGHIGH;                     //T4 (typ  20)
    ccd_ck_reset();//CKLOW;
    ccd_ck_set();//CKHIGH;
    ccd_ck_reset();//CKLOW;
    //�ܹ�2500�����ء�x=(2500-1024*2)/2
    for(i=0;i<32+226;i++)        //DUMMY DARK��32��+x(226)
    {
      ccd_ck_set();//CKHIGH;
      ccd_ck_reset();//CKLOW;
      ccd_ck_set();//CKHIGH;
      ccd_ck_reset();//CKLOW;
    } 
    nsdelay();
    temp=ADC1->SR;
    temp=ADC1->DR; //�ն�1��
    ADC_Cmd(ADC1, ENABLE);    
    for (j = 0; j < 1024; j++) //��1024�������㣬ÿ�����������2����Ԫ�� ������β��������
    {
      temp=0;
      while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
      ccd_ck_set();
      ccd_ck_reset(); //Ӧ�øߵ�ƽ���� ����mck����
      ccd_ck_set();
      ccd_ck_reset(); //Ӧ�øߵ�ƽ���� ����mck����
      temp = ADC_GetConversionValue(ADC1)>>2;
      //nsdelay();
      //nsdelay();
      ADC_Cmd(ADC1, ENABLE);
      nsdelay();
      nsdelay();
      while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
      ccd_ck_set();
      ccd_ck_reset(); //Ӧ�øߵ�ƽ���� ����mck����
      ccd_ck_set();
      ccd_ck_reset(); //Ӧ�øߵ�ƽ���� ����mck����
      temp += ADC_GetConversionValue(ADC1)>>2;
      // nsdelay();
      // nsdelay();
      ADC_Cmd(ADC1, ENABLE);
      ccdbuf[j] =1024-temp/2;
      nsdelay();
      nsdelay();
    }
    for( i=0;i<14+226;i++)   
    { 
      ccd_ck_set();
      ccd_ck_reset(); 
      ccd_ck_set();
      ccd_ck_reset(); 
    }
   // while ((ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) == 0);
   // ccd_cs_set();
    /*CCD�����ص㴦��*/
}
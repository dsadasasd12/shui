#include "ccd_decode.h"
#include "HZ.h"
#include "adc.h"
uint16_t feng_start,feng_end,feng_num,feng_end_flag,feng_start_flag = 0;//波峰
uint16_t code_bar_start,code_bar_num,code_bar_end,code_bar_flag;//码条

uint8_t nor_num;  //滤除ccd开启后信号计数值
uint8_t flag_bar_end;
uint16_t out[42],f_out[42];   //码条宽度输出结果
uint16_t bar_round;  //码条轮数
uint16_t temp_n;
uint16_t min_level = 2300;
uint16_t bar_len[132] = {2,1,0,1, 0,0,1,0, 3,2,0,0, 2,2,0,1,  2,1,2,1,  3,3,0,1  ,3,1,1,3 , 2,3,2,3,  3,0,3,2,  0,2,0,0,  3,1,0,3, 1,1,2,3, 1,2,3,3, 2,3,2,1,  1,2,0,2,  2,0,3,0,  3,1,1,0,  1,3,1,3,  1,0,0,2,  1,1,3,1,  2,0,3,3,  0,1,2,0, 3,3,2,3,  0,3,3,1,  0,0,0,3,  3,0,3,0, 2,0,3,0,  1,3,3,3,  1,1,3,0,  1,0,0,3, 2,1,1,0, 2,0,1,0, 1,2,0,2};//将码尺以四个为一组分为33个千位数
uint16_t bar_length[33] = {1995,1932,1876,1815,1755,1695,1636,1575,1516,1452,1397,1330,1270,1212,1151,1092,1033,970,911,850,792,730,673,610,550,493,432,370,310,250,192,121,60};
uint8_t flag_num = 0;
uint8_t bar_len_test[133] = {1,2,0,2,1,0,1,0,2,0,1,1,2,3,0,0,1,0,3,1,1,3,3,3,1,0,3,0,2,0,3,0,3, 3,0,0,0, 1,3,3,0, 3,2,3,3, 0,2,1,0, 3,3,0,2, 3,3,1,1, 2,0,0,1, 3,1,3,1, 0,1,1,3, 0,3,0,2, 2,0,2,1, 1,2,3,2, 3,3,2,1, 3,2,1,1, 3,0,1,3, 0,0,2,0, 2,3,0,3, 3,2,3,2, 3,1,1,3, 1,0,3,2, 1,2,1,2, 1,0,2,2, 0,0,2,3, 0,1,0,0, 1,0,1,2,
};
uint16_t *Code_bar_length(uint16_t *buf)
{
  static uint8_t flag_f_start = 0; 
  uint16_t feng_round = 0; //波峰轮数
  uint16_t n;
  //nor_num++;
  memset(f_out,0,sizeof(f_out));  
      for(n = 50;n < /*1800*/ 2250; n++)
      {
//        if(n >= 0)
//        {
          if(buf[n] >= min_level)
          {
                   
            if(((buf[n+1] < min_level )||((buf[n+2] <min_level))||(buf[n+3]<min_level)||(buf[n+4]<min_level)))//码条中出现>1000的像素
            {
              code_bar_num++;
              
            }
            if(((buf[n-4] < min_level)&&(buf[n-2] < min_level)&&(buf[n+2]>min_level)&&(buf[n+4]>min_level)&&(buf[n+2] - buf[n-4] > 70)&&(buf[n+4] - buf[n-2] > 70)))
            {
             
              code_bar_end = n - 1;
              code_bar_start = code_bar_end  - code_bar_num + 1;
              flag_bar_end = 1;
              bar_round += 1;                 
            }
//            if(((buf[n+1]>2000)&&(buf[n+2]>2000)&&(buf[n+3]>2000))/*||((temp_ccd > min_dc)&&(buf[n+1] < min_dc))*/)
//            {
//              feng_num++;//波峰数量
////              if(feng_num > 200)
////              {
////                memset(buf,0,sizeof(buf));
////                return 0;
////              }
//              feng_start_flag = 1;
//              
//            }
            feng_start_flag = 1;
            feng_num++;
            if(feng_start_flag&&(flag_num==0))
            {
              feng_start = n;
              flag_num+=1;
            }
            if((buf[n-3]<min_level)&&(buf[n+3] > min_level)&&(buf[n+3] - buf[n-3] > 100)&&(buf[n-2] < min_level)&&(buf[n+4] > min_level)&&(buf[n+4] - buf[n-2] > 100))
            {
              
              
              
            }
            
//            if((feng_start_flag == 1)&&(buf[n+1] > min_level))
//            {
//              
//            }
          }
          
           if(buf[n] < min_level)
          {
            code_bar_num++;
            code_bar_flag = 1;
            
//            if((buf[n-2] > 2000)&&(temp_ccd > 2000)&&(buf[n+1] < 2000)&&(buf[n+2] < 2000)&&(buf[n+3] < 2000)&&(buf[n+4] < 2000)&&( buf[n-2]-buf[n+4] >70))
//            {
//              feng_flag = 1;
//              feng_end = n ;
//              feng_start = feng_end - feng_num ;
//              feng_round++;
//              feng_start_flag = 0;
//            }
            
            if((feng_start_flag == 1)&&(((buf[n-3] > min_level)&&(buf[n+3] < min_level)&&(buf[n-3]-buf[n+3] >60))&&((buf[n-2] > min_level)&&(buf[n+4] < min_level)&&( buf[n-2]-buf[n+4] >60))))//&&(buf[n+5] < min_level)&&(buf[n-1]-buf[n+5] >50))
            {
              feng_end_flag = 1;
              feng_end = n ;
              //feng_start = feng_end - feng_num ;
              feng_round++;
              feng_start_flag = 0;
//              if(feng_end - feng_start < 40)
//              {
//                feng_round--;
//              }
            }
           
//            if((temp_ccd > 1000)&&((buf[n+1]) < 1000)&&(buf[n+2] < 1000)&&(buf[n+3] < 1000))
//            {
//              code_bar_start = n;
//            }
//            
            
          }
         
          
          if(flag_bar_end)//将结果输出
          { 
//            out[i+feng_round] = code_bar_start;
//            out[i+feng_round] = code_bar_end;
//            out[i+feng_round] = code_bar_num;
          if(code_bar_num >= 50)
          {
            switch(bar_round)
            {
            case 1:
              out[0] = code_bar_start;
              out[1] = code_bar_end;
              out[2] = code_bar_num;
              break;
            case 2:
              out[3] = code_bar_start;
              out[4] = code_bar_end;
              out[5] = code_bar_num;
              break;
            case 3:
              out[6] = code_bar_start;
              out[7] = code_bar_end;
              out[8] = code_bar_num;
              break;
            case 4:
              out[9] = code_bar_start;
              out[10] = code_bar_end;
              out[11] = code_bar_num;
              break;
            case 5:
              out[12] = code_bar_start;
              out[13] = code_bar_end;
              out[14] = code_bar_num;
              break;
            case 6:
              out[15] = code_bar_start;
              out[16] = code_bar_end;
              out[17] = code_bar_num;
              break;
            case 7:
              out[18] = code_bar_start;
              out[19] = code_bar_end;
              out[20] = code_bar_num;
              break;
            case 8:
              out[21] = code_bar_start;
              out[22] = code_bar_end;
              out[23] = code_bar_num;
              break;
            case 9:
              out[24] = code_bar_start;
              out[25] = code_bar_end;
              out[26] = code_bar_num;
              break;
            case 10:
              out[27] = code_bar_start;
              out[28] = code_bar_end;
              out[29] = code_bar_num;
              break;
            case 11:
              out[30] = code_bar_start;
              out[31] = code_bar_end;
              out[32] = code_bar_num;
              break;
            case 12:
              out[33] = code_bar_start;
              out[34] = code_bar_end;
              out[35] = code_bar_num;
              break;  
            case 13:
              out[26] = code_bar_start;
              out[37] = code_bar_end;
              out[38] = code_bar_num;
              break;
            case 14:
              out[39] = code_bar_start;
              out[40] = code_bar_end;
              out[41] = code_bar_num;
              break;
            }
          }
          
          
          flag_bar_end = 0;
          code_bar_start = 0;
          code_bar_num = 0;
          code_bar_end = 0;
          code_bar_flag = 0;
          
        }
        if(feng_end_flag)
        {
//          out[27] = feng_start;
//          out[28] = feng_end;
//          out[29] = feng_num;
//          if(feng_num > 250)
//          {
//            feng_round = 0;
//            bar_round = 0;
//            code_bar_num = 0;
//            code_bar_start = 0;    
//            code_bar_end = 0;
//            feng_start = 0;
//            feng_end = 0;
//            feng_num = 0;
//            feng_round = 0;
//            return 0;
//          }
          if(feng_num > 50)
          {
            switch(feng_round)
            {
              
            case 1:
              f_out[0] = feng_start;
              f_out[1] = feng_end;
              f_out[2] = feng_num;
              
              break;
            case 2:
              f_out[3] = feng_start;
              f_out[4] = feng_end;
              f_out[5] = feng_num;
             
              break;
            case 3:
              f_out[6] = feng_start;
              f_out[7] = feng_end;
              f_out[8] = feng_num;
              
              break;
            case 4:
              f_out[9] = feng_start;
              f_out[10] = feng_end;
              f_out[11] = feng_num;
               
              break;
            case 5:
              f_out[12] = feng_start;
              f_out[13] = feng_end;
              f_out[14] = feng_num;
               
              break;
            case 6:
              f_out[15] = feng_start;
              f_out[16] = feng_end;
              f_out[17] = feng_num;
               
              break;
            case 7:
              f_out[18] = feng_start;
              f_out[19] = feng_end;
              f_out[20] = feng_num;
              
              break;
            case 8:
              f_out[21] = feng_start;
              f_out[22] = feng_end;
              f_out[23] = feng_num;
              
              break;
            case 9:
              f_out[24] = feng_start;
              f_out[25] = feng_end;
              f_out[26] = feng_num;
              
              break;  
            case 10:
              f_out[27] = feng_start;
              f_out[28] = feng_end;
              f_out[29] = feng_num;
              
              break;
//            case 11:
//              f_out[30] = feng_start;
//              f_out[31] = feng_end;
//              f_out[32] = feng_num;
//              break;
//            case 12:
//              f_out[33] = feng_start;
//              f_out[34] = feng_end;
//              f_out[35] = feng_num;
//              break;
//            case 13:
//              f_out[36] = feng_start;
//              f_out[37] = feng_end;
//              f_out[38] = feng_num;
//              break;
            }
            feng_end_flag = 0;
            feng_start = 0;
            feng_end = 0;
            feng_num = 0;
            flag_num = 0;
          }
        }

      }
      //        if(n == 2000)
//        {
          feng_round = 0;
          bar_round = 0;
          code_bar_num = 0;
          code_bar_start = 0;    
          code_bar_end = 0;
          feng_start = 0;
          feng_end = 0;
          feng_num = 0;
          feng_round = 0;
          //return f_out;
        //}
        
}

/*显示码条宽度*/
uint8_t bar_code[15];  //将码条宽度进行编码存储在此数组

//void display_bar(uint16_t *in)
//{
//  uint8_t i;
//  uint8_t src_n,j = 0;
//  while(in[j++] != 0)
//  {
//    src_n++;
//  }
////  if(in[41] != 0)
////  {
////    src_n = 14;
////  }
////  else
////  {
////    src_n = 13;
////  }
//  for(i = 0; i < src_n; i++)
//  {
//    if(in[2+i*3] > 130)
//    {
//      bar_code[i] = 3;
//    }
//     if((in[2+i*3] < 130)&&(in[2+i*3] > 110))
//    {
//      bar_code[i] = 2;
//    }
//     if( (in[2+i*3] < 110)&&(in[2+i*3]>85))
//    {
//      bar_code[i] = 1;
//    }
//    if(in[2+i*3] <= 85)
//    {
//      bar_code[i] = 0;
//    }
//  }
//  src_n = 0;
//  j = 0;
//}
void display_feng(uint16_t *in)
{
  uint8_t i = 0;
  uint8_t src_feng = 0;
  while(in[i++] != 0)
  {
    src_feng++;
  }
  for(uint8_t j = 0; j < (src_feng/3)+1; j++)
  {
    if(in[2 + 3*j] > 130)
    {
      feng_code[j] = 3;
    }
    if((in[2 + 3*j] >=100) && (in[2 + 3*j] < 130))
    {
      feng_code[j] = 2;
    }
    if((in[ 2+ 3*j] >=70) && ((in[2+3*j]) < 100))
    {
      feng_code[j] = 1;
    }
    if(in[2+3*j] < 70)
    {
      feng_code[j] = 0;
    }
  }
  
}

uint16_t temp_buble[40];
uint16_t temp_feng_ed[21];

float protion;
uint8_t decode_feng[10];
uint8_t  min_decode_width;
uint8_t  sig_pix ;
uint8_t sig_pix_num = 5;
uint8_t way = 1;
/*@name:dispaly_feng_buble()
* @fun: 找出码条所在位置
* @parm: in:   ccd数据（码条起始位置，码条结束位置，码条宽度）
*        rsln: 计算多少码条宽度（分辨率）
*/
void display_feng_buble(uint16_t *in,uint8_t rsln)
{
  uint8_t i = 1;
  uint8_t src_feng = 0;
  uint16_t temp;
  while(in[i++] != 0)
  {
    src_feng++;
  }
  if((src_feng + 1 )%3 == 0)
  { 
    if(in[src_feng - 1] < 2200)
  {
    if((src_feng + 1)/3 - rsln >= 2)
    {
       for(uint8_t n = 0; n < rsln * 3; n++)
      {
        *(temp_buble+n) = *(in+src_feng+1-3-rsln*3+n);
        temp_feng_ed[n] = temp_buble[n];
      }
      
    }
    if((src_feng + 1)/3 - rsln <= 1)
    {
      for(uint8_t n = 0; n <= rsln * 3; n++)
      {
        *(temp_buble+n) = *(in+src_feng+1-rsln*3+n);
        temp_feng_ed[n] = temp_buble[n];
      }
    }
  }
    
    
  }
  
  
  for(uint8_t j = 0; j < rsln - 1; j++)
  {
    for(uint8_t k = 0; k < (rsln- 1) - j; k++ )
    {
      if(temp_buble[2+k*3] > temp_buble[2+(k+1)*3])
      {
        temp = temp_buble[2+k*3];
        temp_buble[2+k*3] = temp_buble[2+(k+1)*3];
        temp_buble[2+(k+1)*3] = temp;
      }
      
    }
  }
  sig_pix = show_vis_ran(temp_feng_ed);
  min_decode_width = sig_pix * 4;
//  for(uint8_t k = 0; k < rsln; k++)
//  {
//    if((temp_buble[2] > 70)&&(temp_buble[2] < 80))
//    {
//      protion = (float)temp_feng_ed[2+k*3]/temp_buble[2];
//      if(protion > 2.65)//3
//      {
//        decode_feng[k] = 3;
//      }
//      if((protion > 1.8)&&(protion < 2.65))//2
//      {
//        decode_feng[k] = 2;
//      }
//      if((protion > 1.3)&&(protion < 1.8))//1
//      {
//        decode_feng[k] = 1;
//      }
//      if(protion < 1.3 ) //0
//      {
//        decode_feng[k] = 0;
//      }
//    }
//    if(temp_buble[2] > 80)
//    {
//      protion = (float)temp_feng_ed[2+k*3]/70;
//      if(protion > 2.45)//3
//      {
//        decode_feng[k] = 3;
//      }
//      if((protion > 1.6)&&(protion < 2.45))//2
//      {
//        decode_feng[k] = 2;
//      }
//      if((protion > 1.3)&&(protion < 1.6))//1
//      {
//        decode_feng[k] = 1;
//      }
//      if(protion < 1.3 ) //0
//      {
//        decode_feng[k] = 0;
//      }
//    }
//  }
  if(way == 0)
  {
    if(sig_pix >= sig_pix_num)  //表示1mm所需要的像素数量
    {
      for(uint8_t n = 0; n < rsln ; n++)
      {
        if((temp_buble[2] > sig_pix * 2.6)&&(temp_buble[2] < sig_pix * 4.1))
        {
          if((temp_feng_ed[2+3*n] - temp_buble[2] >=0)&&(temp_feng_ed[2+3*n] - temp_buble[2] <= sig_pix * 0.5))
          {
            decode_feng[n] = 0;
          }
          if((temp_feng_ed[2+3*n] - temp_buble[2] >=sig_pix * 0.5)&&(temp_feng_ed[2+3*n] - temp_buble[2] <=sig_pix * 3))
          {
            decode_feng[n] = 1;
          }
          if((temp_feng_ed[2+3*n] - temp_buble[2] >=sig_pix * 3)&&(temp_feng_ed[2+3*n] - temp_buble[2] <=sig_pix * 5.8))
          {
            decode_feng[n] = 2;
          }
          if((temp_feng_ed[2+3*n] - temp_buble[2] >sig_pix * 5.8))
          {
            decode_feng[n] = 3;
          }
        }
        if(temp_buble[2] > sig_pix * 4)
        {
          if((temp_feng_ed[2+3*n] - min_decode_width >=0)&&(temp_feng_ed[2+3*n] - min_decode_width <=sig_pix * 0.5))
          {
            decode_feng[n] = 0;
          }
          if((temp_feng_ed[2+3*n] - min_decode_width >=sig_pix * 0.5)&&(temp_feng_ed[2+3*n] - min_decode_width <=sig_pix * 3))
          {
            decode_feng[n] = 1;
          }
          if((temp_feng_ed[2+3*n] - min_decode_width >=sig_pix * 3)&&(temp_feng_ed[2+3*n] - min_decode_width<=sig_pix *5.1))
          {
            
            decode_feng[n] = 2;
          }
          if((temp_feng_ed[2+3*n] - min_decode_width >=sig_pix *5.1))
          {
            decode_feng[n] = 3;
          }
        }
      }
    }
  }
   
  //比例区分 
   if(sig_pix >= sig_pix_num)  //表示1mm所需要的像素数量
   {
     for(uint8_t n = 0; n < rsln ; n++)
     {
       if((temp_buble[2] > sig_pix * 3)&&(temp_buble[2] < sig_pix * 4.2))
       {
         if(((float)temp_feng_ed[2+3*n] / temp_buble[2] >=0.75)&&((float)temp_feng_ed[2+3*n] / temp_buble[2] <= 1.25))
         {
           decode_feng[n] = 0;
         }
         if(((float)temp_feng_ed[2+3*n]/temp_buble[2] >= 1.25)&&((float)temp_feng_ed[2+3*n]/temp_buble[2] <=1.75))
         {
           decode_feng[n] = 1;
         }
         if(((float)temp_feng_ed[2+3*n]/temp_buble[2] >= 2)&&((float)temp_feng_ed[2+3*n]/temp_buble[2] <=2.5))
         {
           
           decode_feng[n] = 2;
         }
         if(((float)temp_feng_ed[2+3*n] / (float)temp_buble[2] >2.6))
         {
           decode_feng[n] = 3;
         }
       }
       if(temp_buble[2] > sig_pix * 4.2)
       {
         if(((float)temp_feng_ed[2+3*n] / min_decode_width >=0.75)&&((float)temp_feng_ed[2+3*n] / min_decode_width <=1.25))
         {
           decode_feng[n] = 0;
         }
         if(((float)temp_feng_ed[2+3*n] / min_decode_width >=1.25)&&((float)temp_feng_ed[2+3*n] / min_decode_width <=1.75))
         {
           decode_feng[n] = 1;
         }
         if(((float)temp_feng_ed[2+3*n] / min_decode_width >=2)&&((float)temp_feng_ed[2+3*n] / min_decode_width<=2.5))
         {
           decode_feng[n] = 2;
         }
         if(((float)temp_feng_ed[2+3*n] / min_decode_width >=2.6))
         {
           decode_feng[n] = 3;
         }
       }
     }
   }
   
}

//void decode_feng_width(uint16_t *in , uint8_t rsln)
//{
// 
//  while(in[i++] != 0)
//  {
//    src_feng++;
//  }
//  if(src_feng + 1 == 21)
//  {
//    for(uint8_t n = 0; n < rsln * 3; n++)
//    {
//      *(temp_buble+n) = *(in+src_feng+1-3-rsln*3+n);
//      temp_feng_ed[n] = temp_buble[n];
//    }
//  }
//  
//  for(uint8_t num = 0; num < rsln ; num++)
//  {
//    temp_buble[2+rsln*3] 
//  }
//}
/*
* @name:match_num
* @fun ：找出固定四组的码条高度
*/
uint8_t mt_num = 0;
uint16_t match_num(uint8_t *in)
{
  for(uint8_t i = 0; i < 33; i++)
  {
    for(uint8_t j = 0; j < 4; j++)
    {
      if(bar_len[4*i+j] == in[j])
      {
        mt_num++;
        if(mt_num == 4)
        {
          mt_num = 0;
          return bar_length[i];
        }
      }
      
    }
    mt_num = 0;
  }
}

//uint8_t up_rlt,down_rlt;    //向上相对位置
//uint16_t rlt_start,rlt_end,rlt_mid,rlt_width,rlt_width2;//rlt_width:码条宽度
//uint8_t rlt_width_up,rlt_width_down;
//void show_rlt_width(uint16_t *in)
//{
//
//  rlt_start = in[6];
//  rlt_end = in[7];
//  rlt_width = in[8];
//  rlt_width2 = rlt_width/2;
//  rlt_mid = 1250;
//  rlt_width = rlt_width2/18;  //将码条宽度的一半取出
//  rlt_width_up = rlt_mid - rlt_start;
//  rlt_width_down = rlt_end - rlt_mid;   
//  if((rlt_width_up < rlt_width2)&&(rlt_width_up > 0)&&(rlt_width_up/18 <= 5<=rlt_width))
//  {
//    up_rlt = rlt_width - rlt_width_up/18;
//  }
//  if((rlt_width_down < rlt_width2)&&(rlt_width_down > 0)&&(rlt_width_up/18<=rlt_width))
//  {
//    down_rlt =   rlt_width - rlt_width_down/18;
//  }
//
//}

float up_len = 0;
float down_len = 0;
float tmp_mid = 1230;
float up_wid = 0;   //上一个码条距离中心距离
float down_wid = 0; //下一个码条距离中心距离
float up_wid_end = 0; //上一个码条的长度
float down_wid_end = 0;//下一个码条的长度
float mid_len = 0;  //马条的一半
float  subed_num = 0;  //需要减去的长度
uint8_t loc_mid[2] = 0;
/*
* @fun :得到 中心上半部分距离
* @parm : in : temp_feng_ed        bit: 1 mm占多少像素
*/
float show_fine_turn(uint16_t *in,uint8_t bit)
{
  uint8_t i = 1;
  uint8_t j = 0;
  uint8_t num3 = 1;
  while(in[i++] != 0)
  {
    num3++;
  }
  for(j = 0 ; j < num3/3 ; j++)
  {
    if((in[1+j*3] < 1200 )&&(in[3+j*3] < 1300)&&(in[3+j*3] - in[1+j*3]) < 250)
    {
      loc_mid[0] = j*3;
      loc_mid[1] = 2+j*3;
    }
  }
  up_len = in[loc_mid[1]]/2 + in[loc_mid[0]];//上一个码条中心像素坐标
 // down_len = in[11]/2 + in[9];//下一个码条中心像素坐标
 // mid_len = (down_len - up_len)/2;
  up_wid = tmp_mid - up_len;    //在十字心上第一个码条宽度
 // down_wid = down_len - tmp_mid;
  up_wid_end = up_wid/bit;       //离十字中心的距离
  subed_num = up_wid_end;
  return subed_num;
//  if((up_wid > 0)&&(down_wid > 0))
//  {
//    if(up_wid == down_wid)
//    {
//      up_wid_end = 0;
//      down_wid_end = 0;
//    }
//    if(up_wid > mid_len)
//    {
//      down_wid_end = 0;
//      up_wid_end = 7.5-up_wid/18;
//      
//    }
//    if(down_wid < mid_len)
//    {
//      
//      up_wid_end = 0;
//      down_wid_end = 7.5-down_wid/18;
//      
//    }

//  }
  
  
}
/*
* @name: show_vis_ran();
* @fun : 测量1mm所需要的像素数量
*/
uint8_t vis_n = 0;
uint8_t i_vis = 1;
uint8_t n_round = 0;
uint16_t tep_buf[10];
uint16_t end_buf1[10];
uint16_t uuu[10];
uint8_t start = 0,end = 0;

uint8_t round_d = 0;
uint8_t show_vis_ran(uint16_t *in)
{
  uint8_t round = 0;
  uint8_t to_vis_ran = 0;
  
  while(in[i_vis++] != 0)
  {
    
  }
  vis_n = i_vis - 1;
  
  vis_n/=3;
  end = (vis_n - 1);
  start = (vis_n - 3);
  round_d = (end - start - 1);
  
  
  for(uint8_t n = start ; n < end ; n++)
  {
    tep_buf[n-start] = ((in[n*3+1] - in[n*3])/2 + in[n*3]);
  }
  
  for(uint8_t i = round_d; i > 0; --i)
  {
    uint8_t ii = i - 1;
    uuu[ii] = tep_buf[i] - tep_buf[i-1];
  }
  for(uint8_t n = 0; n < round_d; n++)
  {
    
    to_vis_ran += uuu[n]/15;
    
  }
  to_vis_ran /= round_d;
  
  i_vis = 1;
  vis_n = 0;
  return to_vis_ran;
}
//提取任意rsln个码条
uint8_t num1 = 0; //符合的个数
uint8_t n1 = 0;       //整个码条的数量

uint8_t test[4] = {1,2,1,2};
uint8_t end_n;
uint8_t loc_m[2];
uint8_t bar_rad(uint8_t * in,uint8_t rsln,uint16_t *ni)//返回当前码条位置
{
  uint8_t i = 1;
  uint8_t j = 0;
  uint8_t u = 0;       //采样的四个码条
  while(ni[i++] != 0)
  {
    
  }
  for(j = 0; j < i/3; j++)
  {
    if((ni[3*j + 1] < 1200 ) && (ni[3*j + 3] < 1300) &&(ni[3*j + 3] - ni[3*j + 1] < 250))
    {
      loc_m[0] = 3*j + 3;
      loc_m[1] = loc_m[0]/3;
    }
  }
  
  
  num1 = 0;
  for(n1 = 132; n1 >= 0; n1-- )
  {
    for(u = 0; u < rsln; u++)
    {
      if((in[u] == bar_len_test[n1-u])&&(n1>=5))
      {
        num1++;
      }
      if(num1 == rsln)
      {
        end_n = n1+1  - loc_m[1];
        return end_n;
      }
    }
    num1 = 0;
    if(n1 == 0)
    {
      return 0;
    }
  }
  return 0;
}
uint16_t bar_num_4[5]; 
float rel_len = 0;     //得到任意四条码条所在高度
         
float display_len(uint8_t len,float dis)//计算最终高度
{
  
  memset(bar_num_4,0,sizeof(bar_num_4));
  rel_len = len*15;
  rel_len = rel_len - dis;

  
  
  
}
/*查找范围内最大值*/
uint16_t max_adc;
void Adj_thd(uint16_t *buf,uint16_t start,uint16_t end)
{
  uint16_t n;
  uint16_t temp;
  temp = buf[start];
  for(n = start; n < end ; n++)
  {
    if(buf[n] > temp)
    {
      temp = buf[n];
    }
  }
  max_adc = temp;
  max_adc /= 100;
  
  min_level = (max_adc-1) * 100;
}
/*寻找范围内最小值*/
uint16_t min_adc[4];
void adj_min(uint16_t *buf ,uint16_t start1, uint16_t end1, uint16_t start2, uint16_t end2)
{
  uint16_t temp,temp1,temp2,temp3;
  uint16_t n = 0;
  uint16_t u = 0;
  temp = buf[start1];
  temp1 = buf[start2];
  temp2 = buf[start1];
  temp3 = buf[start2];
  for( n = start1; n < end1; n++)
  {
    if(temp > buf[n])
    {
      temp = buf[n];
    }
    if(buf[n] > temp2)
    {
      temp2 = buf[n];
    }
  }
  for(u = start2; u < end2; u++)
  {
    if(temp1 > buf[u])
    {
      temp1 = buf[u];
    }
  }
  min_adc[0] = temp;
  min_adc[1] = temp1;
  min_adc[2] = temp2;
}
float sig_height()
{
    meas(1);
    Adj_thd(adc_value,700,1400);
    Code_bar_length(adc_value);
    display_feng_buble(f_out,5);    
    display_len(bar_rad(decode_feng,5,temp_feng_ed),show_fine_turn(temp_feng_ed,show_vis_ran(temp_feng_ed)));
    return rel_len;
}
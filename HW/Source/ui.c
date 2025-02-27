#include "ui.h"
#include "HZ.h"
#include "uart.h"
#include "ccd_decode.h"
#include "math.h"
static uint8_t  H_Z[46][16] = {
  {0x00,0x10,0x10,0x10,0x10,0x10,0x90,0x5F,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00},
  {0x02,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x02,0x00},/*"主",0*/
  
  {0x20,0x20,0x22,0x23,0xF2,0x22,0x22,0x23,0x24,0x24,0xF4,0x2D,0x24,0x20,0x20,0x00},
  {0x02,0x22,0x24,0x24,0xA8,0x30,0x20,0x7F,0x20,0x30,0xA8,0x24,0x24,0x22,0x02,0x00},/*"菜",1*/

  {0x00,0x00,0x1F,0x92,0x52,0x32,0x12,0x1F,0x12,0x32,0x52,0x92,0x1F,0x00,0x00,0x00},
  {0x08,0x08,0xC8,0x48,0x48,0x48,0x48,0xFF,0x48,0x48,0x48,0x48,0xC8,0x08,0x08,0x00},/*"单",2*/
  
  {0x08,0x08,0x0B,0xFF,0x09,0x08,0x04,0x44,0x44,0x44,0x47,0x44,0x44,0x44,0x04,0x00},
  {0x20,0xC0,0x00,0xFF,0x00,0xC8,0x30,0xC0,0x02,0x01,0xFE,0x00,0x80,0x60,0x18,0x00},/*"标",3*/

  {0x00,0x40,0x30,0x07,0x02,0x04,0x1F,0xF2,0x12,0x92,0x7F,0x12,0x12,0x12,0x10,0x00},
  {0x20,0x20,0xFE,0x00,0x00,0x00,0xFF,0x44,0x44,0x44,0xFC,0x44,0x44,0x44,0x04,0x00},/*"准",4*/

  {0x08,0x06,0x40,0x31,0x00,0x7F,0x40,0x4F,0x40,0x7F,0x00,0x1F,0x00,0xFF,0x00,0x00},
  {0x20,0x20,0x7E,0x80,0x01,0xE2,0x0C,0xF0,0x08,0xE4,0x00,0xE2,0x01,0xFE,0x00,0x00},/*"测",5*/

  {0x04,0x04,0x04,0x7D,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7D,0x04,0x04,0x04,0x00},
  {0x00,0x01,0x01,0xF5,0x55,0x55,0x55,0xFF,0x55,0x55,0x55,0xF5,0x01,0x01,0x00,0x00},/*"量",6*/

  {0x08,0x08,0x0B,0xFF,0x09,0x28,0x27,0xF5,0x25,0x25,0x25,0xF5,0x27,0x20,0x00,0x00},
  {0x20,0xC0,0x00,0xFF,0x00,0x91,0xD2,0x54,0x58,0x70,0x58,0x54,0xD2,0x11,0x01,0x00},/*"模",7*/

  {0x08,0x08,0x09,0x09,0x09,0x09,0x09,0x08,0x08,0xFF,0x08,0x08,0x88,0x68,0x08,0x00},
  {0x00,0x04,0x06,0x04,0xFC,0x08,0x08,0x08,0x00,0xC0,0x30,0x08,0x04,0x02,0x1F,0x00},/*"式",8*/

//  {0x04,0x0C,0x35,0xC6,0x04,0x18,0x01,0x09,0x09,0xFF,0x09,0x92,0x52,0x12,0x02,0x00},
//  {0x44,0xE6,0x44,0x48,0x48,0x48,0x02,0x02,0x04,0xC8,0x30,0x28,0x44,0x82,0x1F,0x00},/*"线",9*/
//
//  {0x00,0x7C,0x44,0x47,0x44,0x7C,0x00,0x08,0x11,0xEA,0x24,0x2A,0x31,0x00,0x00,0x00},
//  {0x02,0x7E,0x02,0xFC,0x44,0x44,0x00,0x80,0x7F,0x42,0x42,0x42,0x7F,0x80,0x80,0x00},/*"路",10*/
//
//  {0x08,0x08,0x0B,0xFF,0x09,0x08,0x01,0x12,0x14,0x90,0x70,0x10,0x14,0x12,0x11,0x00},
//  {0x20,0xC0,0x00,0xFF,0x00,0x80,0x01,0x01,0xC2,0x34,0x08,0x34,0xC2,0x01,0x01,0x00},/*"校",11*/
//
//  {0x08,0x08,0x0B,0xFF,0x09,0x0A,0x04,0x0A,0x32,0xC2,0x32,0x0A,0x04,0x02,0x02,0x00},
//  {0x20,0xC0,0x00,0xFF,0x00,0x82,0x22,0x1A,0x82,0x72,0x06,0x1A,0xE2,0x02,0x02,0x00},/*"检",12*/
//  
//  {0x00,0x00,0x1C,0x2C,0x40,0x41,0x43,0x3E,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//  {0x00,0x00,0x00,0x00,0x00,0xEC,0xEC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"？",9*/
//
//  {0x08,0x08,0x08,0xFF,0x09,0x04,0x19,0x11,0x11,0x97,0x71,0x11,0x11,0x15,0x19,0x00},
//  {0x40,0x42,0x81,0xFE,0x00,0x00,0x01,0x21,0xD2,0x14,0x08,0x14,0xE2,0x01,0x00,0x00},/*"按",10*/

  {0x01,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x01,0x00},
  {0x00,0x01,0x02,0x0C,0xF0,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00},/*"开",9*/

  {0x08,0x08,0x0F,0xF8,0x08,0x0F,0x00,0x02,0x07,0x1A,0xE2,0x02,0x0A,0x06,0x03,0x00},
  {0x02,0x44,0xA8,0x10,0x68,0x84,0x00,0x00,0x7F,0x42,0x42,0x42,0x42,0x7F,0x00,0x00},/*"始",10*/
  
  {0x00,0x00,0x00,0x7F,0x42,0x42,0x42,0x42,0x43,0x42,0x42,0x42,0x7E,0x00,0x00,0x00},
  {0x01,0x02,0x0C,0xF0,0x00,0x00,0x00,0x00,0xC0,0x30,0x08,0x04,0x02,0x01,0x01,0x00},/*"尺",11*/
  
  {0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x08,0x32,0xD1,0x10,0x10,0x10,0x1F,0x00,0x00},
  {0x08,0x0C,0x08,0xF0,0x10,0x10,0x00,0x08,0x08,0x90,0x22,0x41,0x02,0xFC,0x00,0x00},/*"均",12*/
  
  {0x00,0x01,0x06,0x1F,0xE0,0x20,0x27,0x25,0x25,0xFD,0x25,0x25,0x27,0x20,0x00,0x00},
  {0x80,0x00,0x00,0xFF,0x02,0x02,0xFE,0x52,0x52,0x52,0x52,0x52,0xFE,0x02,0x02,0x00},/*"值",13*/
  
  {0x10,0x10,0x91,0x77,0x19,0x00,0x00,0x7F,0x40,0x40,0x4F,0x40,0x40,0x7F,0x00,0x00},
  {0x40,0x80,0x00,0xFF,0x00,0xC1,0x02,0xC4,0x18,0x60,0x80,0x7E,0x01,0xC1,0x07,0x00},/*"视",14*/

  {0x00,0x7C,0x44,0x47,0x44,0x7C,0x00,0x7F,0x44,0x44,0x44,0x44,0x44,0x47,0x40,0x00},
  {0x04,0xFC,0x04,0xF8,0x88,0x88,0x00,0xFE,0x22,0x22,0x22,0x22,0x22,0xE2,0x02,0x00},/*"距",15*/
  
  {0x00,0x01,0x06,0x1F,0xE0,0x02,0x0C,0xF0,0x1F,0x11,0x11,0x11,0x11,0x10,0x10,0x00},
  {0x80,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x10,0x10,0x10,0x10,0x10,0x00,0x00},/*"作",16*/

  {0x00,0x08,0x06,0x01,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x03,0x0C,0x00,0x00},
  {0x02,0x02,0x02,0xC2,0x02,0xFE,0x02,0x02,0x02,0xFE,0x42,0x82,0x02,0x02,0x02,0x00},/*"业",17*/

  {0x01,0x01,0x01,0x7D,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x7D,0x01,0x01,0x01,0x00},
  {0x00,0x00,0x00,0x60,0xA0,0x20,0x20,0x20,0x22,0x21,0x22,0x3C,0x00,0x00,0x00,0x00},/*"号",18*/

  {0x00,0x00,0x03,0x02,0x02,0x02,0xFE,0x12,0x12,0x12,0x12,0x13,0x10,0x10,0x00,0x00},
  {0x01,0x02,0xEC,0x20,0x20,0x28,0x26,0x20,0x28,0x26,0x20,0xE0,0x08,0x07,0x00,0x00},/*"点",19*/

  {0x08,0x06,0x40,0x31,0x00,0x10,0x10,0x10,0x90,0x5F,0x10,0x10,0x10,0x10,0x00,0x00},
  {0x20,0x20,0x7E,0x80,0x02,0x02,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x02,0x00},/*"注",20*/

  {0x02,0x02,0x42,0x33,0x00,0x00,0x00,0x21,0x21,0x21,0x21,0x21,0x3F,0x00,0x00,0x00},
  {0x00,0x00,0x00,0xFE,0x04,0x08,0x00,0xFC,0x02,0x02,0x02,0x02,0x82,0x02,0x0E,0x00},/*"记",21*/
  
  {0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x14,0x13,0x11,0x08,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00,0x3C,0x7E,0xC2,0x82,0x04,0xFC,0x70,0x00,0x00,0x00,0x00,0x00},/*"δ",22*/

//  {0x20,0x20,0x20,0x20,0x2F,0x29,0xA9,0x69,0x29,0x29,0x2F,0x20,0x20,0x20,0x20,0x00},
//  {0x00,0x7F,0x40,0x40,0x5E,0x52,0x52,0x52,0x52,0x52,0x5E,0x40,0x41,0x7F,0x00,0x00},/*"高",34*/
//
//  {0x24,0x24,0x25,0x7F,0xC4,0x44,0x00,0x7C,0x44,0x44,0x44,0x44,0x44,0x7C,0x00,0x00},
//  {0x10,0x60,0x80,0xFF,0x80,0x60,0x02,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0x82,0x00},/*"程",35*/
//
//  {0x10,0x10,0x9F,0x52,0x12,0x13,0x12,0x04,0x1B,0xE8,0x08,0x08,0x0F,0x08,0x08,0x00},
//  {0x02,0x0C,0xF0,0x04,0x02,0xFC,0x01,0x02,0x84,0x68,0x10,0x68,0x84,0x02,0x01,0x00},/*"放",36*/
//
//  {0x08,0x08,0x0B,0xFF,0x09,0x00,0x08,0x89,0x69,0x09,0x0F,0x09,0x29,0xC9,0x08,0x00},
//  {0x20,0xC0,0x00,0xFF,0x00,0x80,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0x00},/*"样",37*/
//  
//  {0x11,0x16,0xF8,0x13,0x10,0x08,0x13,0x2A,0x4A,0x8B,0x48,0x29,0x10,0x0B,0x08,0x00},
//  {0x90,0x98,0x90,0xFF,0xA0,0x00,0xFF,0x48,0x49,0xFF,0x00,0xFA,0x01,0xFE,0x00,0x00},/*"输",38*/
//
//  {0x00,0x00,0x00,0x00,0x00,0x80,0x47,0x38,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//  {0x01,0x02,0x04,0x08,0x30,0xC0,0x00,0x00,0x00,0xC0,0x30,0x0C,0x02,0x01,0x01,0x00},/*"入",39*/
//
//  {0x00,0x00,0x00,0x3F,0x24,0x24,0x24,0x24,0x44,0x44,0x44,0xC4,0x44,0x04,0x04,0x00},
//  {0x02,0x04,0x18,0xE0,0x00,0x7F,0x42,0x42,0x42,0x42,0x42,0x42,0x7F,0x00,0x00,0x00},/*"后",40*/
//
//  {0x10,0x10,0x91,0x77,0x19,0x00,0x00,0x7F,0x40,0x40,0x4F,0x40,0x40,0x7F,0x00,0x00},
//  {0x40,0x80,0x00,0xFF,0x00,0xC1,0x02,0xC4,0x18,0x60,0x80,0x7E,0x01,0xC1,0x07,0x00},/*"视",41*/
//
//  
//  {0x02,0x22,0x2A,0xA6,0x63,0x26,0x2A,0x22,0x00,0x3F,0x22,0x22,0x23,0x42,0x02,0x00},
//  {0x04,0x48,0x52,0x41,0xFE,0x40,0x50,0x49,0x06,0xF8,0x00,0x00,0xFF,0x00,0x00,0x00},/*"新",42*/
//  
//  {0x00,0x1F,0x30,0xD0,0x10,0x10,0x1F,0x02,0x0C,0xF1,0x10,0x10,0x10,0x1F,0x00,0x00},
//  {0x00,0xFE,0x84,0x84,0x84,0x84,0xFE,0x00,0x00,0x00,0xC2,0x01,0x02,0xFC,0x00,0x00},/*"的",43*/
//  
//  {0x04,0x0C,0x35,0xC6,0x08,0x00,0x7F,0x12,0x0A,0x02,0xFF,0x02,0x0A,0x12,0x00,0x00},
//  {0x44,0xE6,0x44,0x48,0x48,0x00,0xFE,0x22,0x42,0x82,0xFE,0x82,0x42,0x22,0x02,0x00},/*"继",44*/
//  
//  {0x04,0x0C,0x35,0xC6,0x04,0x18,0x04,0x24,0x25,0x24,0xFC,0x25,0x24,0x25,0x06,0x00},
//  {0x44,0xE6,0x44,0x48,0x48,0x48,0x11,0x51,0x32,0x94,0x18,0xF0,0x18,0x14,0x13,0x00},/*"续",45*/
//  
//  {0x02,0x02,0x42,0x33,0x00,0x00,0xFF,0x92,0x92,0x93,0x92,0x92,0xFE,0x01,0x00,0x00},
//  {0x00,0x02,0x04,0xF8,0x04,0x02,0xFA,0x12,0x22,0x02,0x82,0x42,0xA2,0x1A,0x02,0x00},/*"退",46*/
//  
//  {0x00,0x00,0x3E,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x3F,0x00,0x00,0x00},
//  {0x00,0x3E,0x02,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x02,0x02,0x02,0x3F,0x00,0x00},/*"出",47*/
//  
//  
//  {0x04,0x0C,0x35,0xC6,0x08,0x00,0x7F,0x12,0x0A,0x02,0xFF,0x02,0x0A,0x12,0x00,0x00},
//  {0x44,0xE6,0x44,0x48,0x48,0x00,0xFE,0x22,0x42,0x82,0xFE,0x82,0x42,0x22,0x02,0x00},/*"继",48*/
//  
//  {0x04,0x0C,0x35,0xC6,0x04,0x18,0x04,0x24,0x25,0x24,0xFC,0x25,0x24,0x25,0x06,0x00},
//  {0x44,0xE6,0x44,0x48,0x48,0x48,0x11,0x51,0x32,0x94,0x18,0xF0,0x18,0x14,0x13,0x00},/*"续",49*/
//
//  
//
//  {0x02,0x02,0x42,0x33,0x00,0x00,0xFF,0x92,0x92,0x93,0x92,0x92,0xFE,0x01,0x00,0x00},
//  {0x00,0x02,0x04,0xF8,0x04,0x02,0xFA,0x12,0x22,0x02,0x82,0x42,0xA2,0x1A,0x02,0x00},/*"退",50*/
//  
//  {0x00,0x00,0x3E,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x3F,0x00,0x00,0x00},
//  {0x00,0x3E,0x02,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x02,0x02,0x02,0x3F,0x00,0x00},/*"出",51*/
//
//  
//  {0x00,0x20,0x24,0x24,0xA4,0x64,0x27,0x3C,0x24,0x64,0xA4,0x24,0x24,0x20,0x00,0x00},
//  {0x82,0x84,0x88,0x91,0xA1,0xD1,0x91,0x91,0x9F,0x91,0x91,0x91,0x91,0x81,0x80,0x00},/*"差",52*/
//
//  {0x00,0x20,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x20,0x00,0x00},
//  {0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00},/*"三",53*/
//
//  
//  {0x10,0x20,0xC4,0x44,0x64,0x54,0x44,0x5F,0x24,0xC4,0x44,0x64,0x54,0x40,0x40,0x00},
//  {0x80,0x90,0x90,0x90,0x98,0x96,0x90,0x90,0x92,0x91,0xBE,0x90,0x90,0x90,0x80,0x00},/*"等",54*/
//  
//  {0x00,0x04,0x04,0x04,0x05,0x06,0x00,0xFF,0x06,0x01,0x02,0x04,0x18,0x00,0x00,0x00},
//  {0x04,0x08,0x10,0x60,0x80,0x02,0x01,0xFE,0x00,0x80,0x40,0x20,0x10,0x08,0x08,0x00},/*"水",55*/
//
//  {0x00,0x00,0x00,0x00,0x02,0x0C,0x38,0xFF,0x38,0x0C,0x02,0x00,0x00,0x00,0x00,0x00},
//  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"↑",56*/
//  
//  
//  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//  {0x00,0x00,0x00,0x00,0x40,0x30,0x1C,0xFF,0x1C,0x30,0x40,0x00,0x00,0x00,0x00,0x00},/*"↓",57*/
//  
//  {0x00,0x3F,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x3F,0x00,0x00},
//  {0x00,0xFE,0x14,0x24,0xC4,0x04,0x04,0x04,0x04,0x84,0x44,0x44,0x44,0xFE,0x00,0x00},/*"四",58*/
//
//  {0x10,0x10,0x17,0x94,0x74,0x14,0x17,0x10,0x10,0x13,0x30,0xD0,0x17,0x10,0x10,0x00},
//  {0x00,0x00,0xFF,0x90,0x92,0x91,0xFE,0x00,0x00,0xF0,0x02,0x01,0xFE,0x00,0x00,0x00},/*"前",59*/
//  
//  {0x00,0x00,0x0F,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00},
//  {0x00,0x00,0xF0,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0xF0,0x00,0x00,0x00},/*"中",60*/
//
//  {0x00,0x00,0x1C,0x2C,0x40,0x41,0x43,0x3E,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//  {0x00,0x00,0x00,0x00,0x00,0xEC,0xEC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"？",61*/
//
//  
//  {0x00,0x00,0x03,0x02,0x02,0x02,0xFE,0x12,0x12,0x12,0x12,0x13,0x10,0x10,0x00,0x00},
//  {0x01,0x02,0xEC,0x20,0x20,0x28,0x26,0x20,0x28,0x26,0x20,0xE0,0x08,0x07,0x00,0x00},/*"点",62*/
//  
//  
//  {0x02,0x42,0x33,0x00,0x00,0x7F,0x41,0x49,0x49,0x7F,0x49,0x49,0x41,0x7F,0x00,0x00},
//  {0x00,0x00,0xFC,0x08,0x11,0xFE,0x00,0x78,0x48,0x48,0x48,0x7A,0x01,0xFE,0x00,0x00},/*"调",63*/
//  
//  {0x00,0x00,0x7F,0x44,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x44,0x7F,0x00,0x00,0x00},
//  {0x01,0x06,0xF8,0x40,0x40,0x40,0x40,0xFE,0x40,0x40,0x42,0x41,0xFE,0x00,0x00,0x00},/*"用",64*/
//  
//  {0x00,0x00,0x47,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
//  {0x00,0x00,0xFC,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x1E,0x00,0x00},/*"已",65*/
//  
//  {0x20,0x20,0x21,0x27,0x38,0xE0,0x24,0x24,0x24,0x24,0x25,0x26,0x24,0x20,0x20,0x00},
//  {0x40,0x80,0x00,0xFF,0x00,0x40,0x40,0x42,0x41,0xFE,0x40,0x40,0x40,0x40,0x40,0x00},/*"存",66*/



};
uint8_t cur_index = 0;
uint8_t last_index = 0;
void  (*fun_index)();
void  (*eq_dun_index)();
uint8_t flag_l = 0;
uint16_t dsp_num[6] = {0};
uint8_t num_flag[2] = 0;
index_table table[40] = 
{
  //主菜单
  {0,2,1,7,(*main_ui1)},
  {1,0,2,24,(*main_ui2)},
  {2,1,0,1,(*main_ui3)},
  //标准测量模式
  {3,0,4,7, (*stand_list1)},
  {4,3,5,13,(*stand_list2)},
  {5,4,6,20,(*stand_list3)},
  {6,5,3,22,(*stand_list4)},
  
  //标准测量
  {7,3,8,8,(*stand_meas1)},
  {8,7,9,9,(*stand_meas2)},
  {9,8,10,10,(*stand_meas3)},
  {10,9,11,11,(*stand_meas4)},
  {11,10,11,12,(*stand_meas5)},
  {12,11,12,7,(*stand_meas6)},
  
  //高程放样模式
  {13,4,14,14,(*height_loft1)},
  {14,13,15,15,(*height_loft3)},
  {15,14,16,16,(*height_loft2)},
  {16,15,17,17,(*height_loft4)},
  {17,16,18,18,(*height_loft5)},
  {18,17,18,19,(*height_loft6)},
  {19,18,19,19,(*height_loft7)},
  
  //高差放样
  {20,5,21,21, (*hgt_dif_loft1)},
  {21,20,21,21,(*hgt_dif_loft2)},
  //视距放样
  {22,6,23,23, (*view_loft1)},
  {23,22,23,23,(*view_loft2)},
  //线路测量菜单
  {24,1,25,27, (*line_mea_main1)},
  {25,24,26,26,(*line_mea_main2)},
  {26,25,24,27,(*line_mea_main3)},
  //线路测量模式选择
  {27,26,27,28,(*line_mea_start1)},
  {28,27,29,31,(*line_mea_start2)},
  {29,28,30,29,(*line_mea_start3)},
  {30,29,31,29,(*line_mea_start4)},
  {31,29,31,33,(*line_mea_start5)},
  {32,31,32,33,(*line_mea_start6)},
  {33,32,33,34,(*line_mea_start7)},
  {34,33,35,35,(*line_mea_start8)},
  {35,34,36,36,(*line_mea_start9)},
  {36,35,37,37,(*line_mea_start10)},
};
uint8_t num_cml[10] = 0;
uint8_t sum_num[3] = 0;
uint8_t hln = 0;

void cg_ui1()
{
  
  
  if(rx_buf[0] == '1')
  {
    cur_index = table[cur_index].up;
    rx_buf[0] = 0;
  }
  if(rx_buf[0] == '2')
  {
    cur_index = table[cur_index].down;
    rx_buf[0] = 0;
  }
  if(rx_buf[0] == '3')
  {
    cur_index = table[cur_index].enter;
    rx_buf[0] = 0;
  }
  
  if(cur_index != last_index)
  {
    fun_index = table[cur_index].currnt_index;
    eq_dun_index = fun_index;
    clear_ram();
    (*fun_index)();
    last_index = cur_index;
  }
  if(cur_index == last_index)
  {
    if(flag_l == 0)
    {
      eq_dun_index = main_ui1;
      (*eq_dun_index)(); 
    }
    (*eq_dun_index)(); 
    flag_l = 1;
  }
  
}
void main_ui0()          //主菜单ui0
{
 
  write_Hz(10,8,H_Z,0);  //主
  write_Hz(26,8,H_Z,1);  //菜
  write_Hz(42,8,H_Z,2);  //单
  
  
  write_Hz(26,6,H_Z,3);  //标
  write_Hz(42,6,H_Z,4);  //准
  write_Hz(58,6,H_Z,5);  //测
  write_Hz(74,6,H_Z,6);  //量
  write_Hz(90,6,H_Z,7);  //模
  write_Hz(106,6,H_Z,8); //式
  
//  write_Hz(26,4,H_Z,9);  //线
//  write_Hz(42,4,H_Z,10); //路
//  write_Hz(58,4,H_Z,5);  //测
//  write_Hz(74,4,H_Z,6);  //量
//  write_Hz(90,4,H_Z,7);  //模
//  write_Hz(106,4,H_Z,8); //式
//  
//  write_Hz(26,2,H_Z,12); //校
//  write_Hz(42,2,H_Z,11); //检
//  write_Hz(58,2,H_Z,7);  //模
//  write_Hz(74,2,H_Z,8);  //式

  write_zm(10,5,2);
  write_zm(18,5,3);
    
  
}
void main_ui1()          //主菜单ui1
{
 
  write_Hz(10,8,H_Z,0);  //主
  write_Hz(26,8,H_Z,1);  //菜
  write_Hz(42,8,H_Z,2);  //单
  
  
  write_Hz(26,6,H_Z,3);  //标
  write_Hz(42,6,H_Z,4);  //准
  write_Hz(58,6,H_Z,5);  //测
  write_Hz(74,6,H_Z,6);  //量
  write_Hz(90,6,H_Z,7);  //模
  write_Hz(106,6,H_Z,8); //式
  
//  write_Hz(26,4,H_Z,9);  //线
//  write_Hz(42,4,H_Z,10); //路
//  write_Hz(58,4,H_Z,5);  //测
//  write_Hz(74,4,H_Z,6);  //量
//  write_Hz(90,4,H_Z,7);  //模
//  write_Hz(106,4,H_Z,8); //式
//  
//  write_Hz(26,2,H_Z,12); //校
//  write_Hz(42,2,H_Z,11); //检
//  write_Hz(58,2,H_Z,7);  //模
//  write_Hz(74,2,H_Z,8);  //式

  write_zm(10,5,0);
  write_zm(18,5,1);
    
  
}
void main_ui2()          //主菜单ui2
{
  
  write_Hz(10,8,H_Z,0);  //主
  write_Hz(26,8,H_Z,1);  //菜
  write_Hz(42,8,H_Z,2);  //单
  
  
  write_Hz(26,6,H_Z,3);  //标
  write_Hz(42,6,H_Z,4);  //准
  write_Hz(58,6,H_Z,5);  //测
  write_Hz(74,6,H_Z,6);  //量
  write_Hz(90,6,H_Z,7);  //模
  write_Hz(106,6,H_Z,8); //式
  
  write_Hz(26,4,H_Z,9);  //线
  write_Hz(42,4,H_Z,10); //路
  write_Hz(58,4,H_Z,5);  //测
  write_Hz(74,4,H_Z,6);  //量
  write_Hz(90,4,H_Z,7);  //模
  write_Hz(106,4,H_Z,8); //式
  
  write_Hz(26,2,H_Z,12); //校
  write_Hz(42,2,H_Z,11); //检
  write_Hz(58,2,H_Z,7);  //模
  write_Hz(74,2,H_Z,8);  //式
 
  write_zm(10,3,2);
  write_zm(18,3,3);
    
  
}
void main_ui3()          //主菜单ui3
{
  
  write_Hz(10,8,H_Z,0);  //主
  write_Hz(26,8,H_Z,1);  //菜
  write_Hz(42,8,H_Z,2);  //单
  
  
  write_Hz(26,6,H_Z,3);  //标
  write_Hz(42,6,H_Z,4);  //准
  write_Hz(58,6,H_Z,5);  //测
  write_Hz(74,6,H_Z,6);  //量
  write_Hz(90,6,H_Z,7);  //模
  write_Hz(106,6,H_Z,8); //式
  
  write_Hz(26,4,H_Z,9);  //线
  write_Hz(42,4,H_Z,10); //路
  write_Hz(58,4,H_Z,5);  //测
  write_Hz(74,4,H_Z,6);  //量
  write_Hz(90,4,H_Z,7);  //模
  write_Hz(106,4,H_Z,8); //式
  
  write_Hz(26,2,H_Z,12); //校
  write_Hz(42,2,H_Z,11); //检
  write_Hz(58,2,H_Z,7);  //模
  write_Hz(74,2,H_Z,8);  //式
 
  write_zm(10,1,2);
  write_zm(18,1,3);
    
  
}
/*
* @name : write_num11()
* @fun  : 显示按键输入的数字
*/
void write_num111(uint8_t index,uint8_t s, uint8_t y)
{
  
  if(cur_index == index)
  {    
    switch(rx_buf[0])
    {
    case 0x34:
      write_zm(8*(num_cml[0]+1)+s,y,6);    //4
      num_cml[0]++;
      sum_num[num_cml[0]] = 30;
      rx_buf[0] = 0;
      
      break;
    case 0x35:
      write_zm(8*(num_cml[0]+1)+s,y,7);    //5
      num_cml[0]++;
      sum_num[num_cml[0]] = 31;
      rx_buf[0] = 0;
      break;
    case 0x36:
      write_zm(8*(num_cml[0]+1)+s,y,8);    //6
      num_cml[0]++;
      sum_num[num_cml[0]] = 32;
      rx_buf[0] = 0;
      break;
    case 0x37:
      write_zm(8*(num_cml[0]+1)+s,y,9);    //7
      num_cml[0]++;
      sum_num[num_cml[0]] = 33;
      rx_buf[0] = 0;
      break;
    case 0x38:
      write_zm(8*(num_cml[0]+1)+s,y,10);    //8
      num_cml[0]++;
      sum_num[num_cml[0]] = 34;
      rx_buf[0] = 0;
      break;
    case 0x39:
      write_zm(8*(num_cml[0]+1)+s,y,11);    //9
      num_cml[0]++;
      sum_num[num_cml[0]] = 35;
      rx_buf[0] = 0;
      break;
//    case 0x33:
//      write_zm(8*(num_cml[0]+1)+s,y,29);    //3
//      num_cml[0]++;
//      rx_buf[0] = 0;
//      break;
//    case 0x32:
//      write_zm(8*(num_cml[0]+1)+s,y,28);    //2
//      num_cml[0]++;
//      rx_buf[0] = 0;
//      break;
//    case 0x31:
//      write_zm(8*(num_cml[0]+1)+s,y,27);    //1
//      num_cml[0]++;
//      rx_buf[0] = 0;
//      break;
    case 0x42:
      write_zm(8*(num_cml[0]+1)+s,y,2);    //0
      num_cml[0]++;
      sum_num[num_cml[0]] = 36;
      rx_buf[0] = 0;
      break;                    
    }
    if(num_cml[0] == 3)
    {
      num_cml[0] = 0;
    }
  }
}
void write_num11(uint8_t index,uint8_t s, uint8_t y)
{
  
  if(cur_index == index)
  {    
    switch(rx_buf[0])
    {
    case 0x34:
      write_zm(8*(num_cml[0]+1)+s,y,6);    //4
      num_cml[0]++;
      num_flag[num_cml[0]] = 4;
      rx_buf[0] = 0;
      break;
    case 0x35:
      write_zm(8*(num_cml[0]+1)+s,y,7);    //5
      num_cml[0]++;
      num_flag[num_cml[0]] = 5;
      rx_buf[0] = 0;
      break;
    case 0x36:
      write_zm(8*(num_cml[0]+1)+s,y,8);    //6
      num_cml[0]++;
      num_flag[num_cml[0]] = 6;
      rx_buf[0] = 0;
      break;
    case 0x37:
      write_zm(8*(num_cml[0]+1)+s,y,9);    //7
      num_cml[0]++;
      num_flag[num_cml[0]] = 7;
      rx_buf[0] = 0;
      break;
    case 0x38:
      write_zm(8*(num_cml[0]+1)+s,y,10);    //8
      num_cml[0]++;
      num_flag[num_cml[0]] = 8;
      rx_buf[0] = 0;
      break;
    case 0x39:
      write_zm(8*(num_cml[0]+1)+s,y,11);    //9
      num_cml[0]++;
      num_flag[num_cml[0]] = 9;
      rx_buf[0] = 0;
      break;
//    case 0x33:
//      write_zm(8*(num_cml[0]+1)+s,y,29);    //3
//      num_cml[0]++;
//      rx_buf[0] = 0;
//      break;
//    case 0x32:
//      write_zm(8*(num_cml[0]+1)+s,y,28);    //2
//      num_cml[0]++;
//      rx_buf[0] = 0;
//      break;
//    case 0x31:
//      write_zm(8*(num_cml[0]+1)+s,y,27);    //1
//      num_cml[0]++;
//      rx_buf[0] = 0;
//      break;
    case 0x42:
      write_zm(8*(num_cml[0]+1)+s,y,2);    //0
      num_cml[0]++;
      num_flag[num_cml[0]] = 0;
      rx_buf[0] = 0;
      break;  
    case 0x41:
      write_zm(8*(num_cml[0]+1)+s,y,36);    //B
      num_cml[0]++;
      rx_buf[0] = 0;
      break;
    }
    if(num_cml[0] == 2)
    {
      num_cml[0] = 0;
    }
  }
}
/*
* @parm loc: 小数点位置
*/
void display_num(float num, uint8_t bit, uint8_t x_s, uint8_t y_s,uint8_t loc)
{
  uint8_t nu = 0;
  uint8_t un = 0;
  uint16_t temp_f  = 0, tep_f = 0;
  float temp;
  temp = num;
  
  if(num  >= 1000)
  {
    for(nu = 0; nu < bit; nu++)
    {
      switch(nu)
      {
      case 0:
        if(loc == 1)
        {
          dsp_num[0] = (uint16_t)num/1000%10;
        }
        if(loc == 2)
        {
          dsp_num[0] = (uint16_t)num/10000%10;
        }
        num = temp;
        break;
      case 1:
        if(loc == 1)
        {
          dsp_num[1] = 0x2e;
        }
        if(loc == 2)
        {
          dsp_num[1] = (uint16_t)num/1000%10;
        }
        num = temp;
        break;
      case 2:
        if(loc == 1)
        {
          dsp_num[2] = (uint16_t)num/100%10;
        }
        if(loc == 2)
        {
          dsp_num[2] = 0x2e;
        }
        num = temp;
        break;
      case 3:
        if(loc == 1)
        {
          dsp_num[3] = (uint16_t)num/10%10; 
        }
        if(loc == 2)
        {
          dsp_num[3] = (uint16_t)num/100%10;
          
        }
        num = temp;
        break;
      case 4:
        if(loc == 1)
        {
          dsp_num[4] = (uint16_t)num%10;
        }
        if(loc == 2)
        {
          
          dsp_num[4] = (uint16_t)num/10%10;
          
        }
        num = temp;
        break;
      case 5:
        if(loc == 1)
        {
          temp_f = num*10;
          dsp_num[5] = (uint16_t)temp_f%10;
        }
        if(loc == 2)
        {
          
          dsp_num[5] = (uint16_t)num%10;
        }
        break;
      }
    }
  }
  else
  {
    for(nu = 0; nu < bit ; nu++)
    {
      switch(nu)
      {
      case 0:
        dsp_num[0] = 0;
        num = temp;
        break;
      case 1:
        dsp_num[1] = 0x2E;
        num = temp;
        break;
      case 2:
        dsp_num[2] = (uint16_t)num/100%10; 
        num = temp;
        break;
      case 3:
        dsp_num[3] = (uint16_t)num/10%10;
        num = temp;
        break;
      case 4:    
        dsp_num[4] = (uint16_t)num%10;
        num = temp;
        break;
      case 5:
        tep_f = num * 10;
        dsp_num[5] = (uint16_t)tep_f%10;
        break;
      }
    }
  }
  
  if(1)
  {
    for(un = 0; un < 6; un++)
    {
      switch(dsp_num[un])
      {
      case 1:
        write_zm(x_s+un*8,y_s,3);
        break;
      case 2:
        write_zm(x_s+un*8,y_s,4);
        break;
      case 3:
        write_zm(x_s+un*8,y_s,5);
        break;
      case 4:
        write_zm(x_s+un*8,y_s,6);
        break;
      case 5:
        write_zm(x_s+un*8,y_s,7);
        break;
      case 6:
        write_zm(x_s+un*8,y_s,8);
        break;
      case 7:
        write_zm(x_s+un*8,y_s,9);
        break;
      case 8:
        write_zm(x_s+un*8,y_s,10);
        break;
      case 9:
        write_zm(x_s+un*8,y_s,11);
        break;
      case 0:
        write_zm(x_s+un*8,y_s,2);
        break;
      case 0x2E:
        write_zm(x_s+un*8,y_s,12);
     
      }
    }
  }
  
  //write_zm(x_s,y_s,);
  
  
}
void stand_list1()        //标准测量模式1
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,4,H_Z,34);  //高
  write_Hz(42,4,H_Z,35);  //程
  write_Hz(58,4,H_Z,36);  //放
  write_Hz(74,4,H_Z,37);  //样
  
  write_Hz(26,6,H_Z,3);   //标
  write_Hz(42,6,H_Z,4);   //准
  write_Hz(58,6,H_Z,5);   //测
  write_Hz(74,6,H_Z,6);   //量
  
  
  write_Hz(26,2,H_Z,34);  //高
  write_Hz(42,2,H_Z,52);  //差
  write_Hz(58,2,H_Z,36);  //放
  write_Hz(74,2,H_Z,37);  //样
  
  write_zm(10,5,2);       //=
  write_zm(18,5,3);       //>
}
void stand_list2()
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,4,H_Z,34);  //高
  write_Hz(42,4,H_Z,35);  //程
  write_Hz(58,4,H_Z,36);  //放
  write_Hz(74,4,H_Z,37);  //样
  
  write_Hz(26,6,H_Z,3);   //标
  write_Hz(42,6,H_Z,4);   //准
  write_Hz(58,6,H_Z,5);   //测
  write_Hz(74,6,H_Z,6);   //量
  
  
  write_Hz(26,2,H_Z,34);  //高
  write_Hz(42,2,H_Z,52);  //差
  write_Hz(58,2,H_Z,36);  //放
  write_Hz(74,2,H_Z,37);  //样
  
  write_zm(10,3,0);       //=
  write_zm(18,3,1);       //>
}
void stand_list3()
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,4,H_Z,34);  //高
  write_Hz(42,4,H_Z,35);  //程
  write_Hz(58,4,H_Z,36);  //放
  write_Hz(74,4,H_Z,37);  //样
  
  write_Hz(26,6,H_Z,3);   //标
  write_Hz(42,6,H_Z,4);   //准
  write_Hz(58,6,H_Z,5);   //测
  write_Hz(74,6,H_Z,6);   //量

  
  write_Hz(26,2,H_Z,34);  //高
  write_Hz(42,2,H_Z,52);  //差
  write_Hz(58,2,H_Z,36);  //放
  write_Hz(74,2,H_Z,37);  //样
  
  write_zm(10,1,0);       //=
  write_zm(18,1,1);       //>
}
void stand_list4()
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_zm(10,5,0);       //=
  write_zm(18,5,1);       //>
  
  write_Hz(26,6,H_Z,20);  //视
  write_Hz(42,6,H_Z,21);  //距
  write_Hz(58,6,H_Z,36);  //放
  write_Hz(72,6,H_Z,37);  //样
}
void stand_meas1() 
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量

  write_Hz(10,6,H_Z,16);  //作
  write_Hz(26,6,H_Z,17);  //业
  //write_Hz(42,6,H_Z,13);  //?
  
  write_zm(10,3,0);       //=
  write_zm(18,3,1);       //>
  
  write_zm(26,3,12);      //J
  write_num11(7,26,3);
  
}
void stand_meas2()
{
  
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  
  write_Hz(26,6,H_Z,5);   //测
  write_Hz(42,6,H_Z,6);   //量
  write_Hz(58,6,H_Z,18);  //号
  
  write_zm(10,3,0);       //=
  write_zm(18,3,1);       //>
  write_num11(8,18,3);
}
void stand_meas3()
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  
  write_Hz(26,6,H_Z,20);  //注
  write_Hz(42,6,H_Z,21);  //记
  
//  write_zm(58,5,4);       //#
//  write_num(66,5,1);      //1
//  write_Hz(74,6,H_Z,13);  //?
  
  write_zm(10,3,0);        //=
  write_zm(18,3,1);        //>
  write_num11(9,18,3);
}
void stand_meas4()
{
  
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  
  write_Hz(10,6,H_Z,19);  //点
  write_Hz(26,6,H_Z,18);  //号
  
  write_zm(10,3,0);       //=
  write_zm(18,3,1);       //>
  //write_zm(26,3,11);      //p
  write_num11(10,26,3);
}
void stand_meas5()
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  
//  write_Hz(10,6,H_Z,14);  //按
//  write_zm(26,5,5);       //[
//  write_zm(34,5,6);       //M
//  write_zm(42,5,7);       //E
//  write_zm(50,5,8);       //A
//  write_zm(58,5,9);       //S
//  write_zm(66,5,10);      //]
  write_Hz(42,6,H_Z,9);  //开
  write_Hz(58,6,H_Z,10);  //始
  write_Hz(74,6,H_Z,5);  //测
  write_Hz(90,6,H_Z,6);  //量
  
  write_Hz(10,2,H_Z,5);   //测
  write_Hz(26,2,H_Z,6);   //量
  write_Hz(42,2,H_Z,18);  //号
//  write_zm(58,1,13);      //:
//  
  write_zm(66,1,(num_flag[1]+2));
//  
  write_zm(74,1,(num_flag[2]+2));    
}
 float num_trr[3] = 0;
uint8_t mea_flag = 0;
float num_trrr = 0;
void stand_meas6()
{
  write_Hz(10,8,H_Z,3);   //标
  write_Hz(26,8,H_Z,4);   //准
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量

//  write_zm(90,7,25);      //p
//  write_zm(100,7,27);     //1
//  write_zm(108,7,26);     ///   
//  write_zm(116,7,28);     //2
  
  write_Hz(10,6,H_Z,3);   //标
  write_Hz(26,6,H_Z,11);  //尺
  write_Hz(42,6,H_Z,12);  //均
  write_Hz(58,6,H_Z,13);  //值
  //write_zm(74,5,13);      //:
 
 
  
  write_Hz(10,4,H_Z,14);  //视
  write_Hz(26,4,H_Z,15);  //距
  write_Hz(42,4,H_Z,12);  //均
  write_Hz(58,4,H_Z,13);  //值
  //write_zm(74,3,13);      //:
      //m
//  write_zm(10,1,14);      //N
//  write_zm(18,1,13);      //:
//  
//  write_Hz(90,2,H_Z,33);  //δ
//  write_zm(106,1,13);     //:
   
  if(mea_flag == 0)
  {
    mea_flag = 1;
    for(uint8_t i = 0; i < 3; i++)
    {
      num_trr[i]= sig_height();
    }
    if((abs(num_trr[0] - num_trr[1] )< 1)&&(abs(num_trr[1] - num_trr[2]) < 1)&&(abs(num_trr[0] - num_trr[1] )< 1))
    {
      num_trrr = (num_trr[0] + num_trr[1] + num_trr[2])/3;
    }
    
  }
  if(rx_buf[0] == 0x35)
  {
    mea_flag = 0;
    rx_buf[0] = 0;
  }
  display_num(num_trrr,6,82,5,1);
  write_zm(130,5,13);      //m
  display_num(38853/show_vis_ran(temp_feng_ed),6,82,3,2);
  write_zm(130,3,13);  
}
void height_loft1()
{
  write_Hz(10,8,H_Z,34);  //高
  write_Hz(26,8,H_Z,35);  //程
  write_Hz(42,8,H_Z,36);  //放
  write_Hz(58,8,H_Z,37);  //样
  
    
  write_Hz(10,6,H_Z,38); //输
  write_Hz(26,6,H_Z,39); //入
  write_Hz(42,6,H_Z,40); //后
  write_Hz(58,6,H_Z,41); //视
  write_Hz(74,6,H_Z,34); //高
  write_Hz(90,6,H_Z,35); //程
  write_zm(10,3,2);      //=
  write_num11(13,10,3);
  write_zm(90,3,0);      //m
    
}
void height_loft2()
{
  write_Hz(10,8,H_Z,34);  //高
  write_Hz(26,8,H_Z,35);  //程
  write_Hz(42,8,H_Z,36);  //放
  write_Hz(58,8,H_Z,37);  //样
  write_Hz(10,6,H_Z,38);  //输
  write_Hz(26,6,H_Z,39);  //入
  write_Hz(42,6,H_Z,36);  //放
  write_Hz(58,6,H_Z,37);  //样
  write_Hz(74,6,H_Z,34);  //高
  write_Hz(90,6,H_Z,35);  //程
  write_zm(10,3,2);//=
  write_num11(15,10,3);
  write_zm(90,3,0);//m
}
void height_loft3()
{
  write_Hz(10,8,H_Z,34);  //高
  write_Hz(26,8,H_Z,35);  //程
  write_Hz(42,8,H_Z,36);  //放
  write_Hz(58,8,H_Z,37);  //样

  write_Hz(10,5,H_Z,5);   //测
  write_Hz(26,5,H_Z,6);   //量
  write_Hz(42,5,H_Z,40);  //后
  write_Hz(58,5,H_Z,41);  //视
  write_Hz(74,5,H_Z,25);  //点
  
  write_Hz(10,2,H_Z,14);  //按
  write_zm(26,1,5);       //[
  write_zm(34,1,6);       //M
  write_zm(42,1,7);       //E
  write_zm(50,1,8);       //A
  write_zm(58,1,9);       //S
  write_zm(66,1,10);      //]
  write_Hz(74,2,H_Z,15);  //开
  write_Hz(90,2,H_Z,16);  //始
  write_Hz(106,2,H_Z,5);  //测
  write_Hz(122,2,H_Z,6);  //量
}
void height_loft4()
{
    write_Hz(10,8,H_Z,34);  //高
    write_Hz(26,8,H_Z,35);  //程
    write_Hz(42,8,H_Z,36);  //放
    write_Hz(58,8,H_Z,37);  //样
    write_Hz(10,2,H_Z,14);  //按
    write_zm(26,1,5);       //[
    write_zm(34,1,6);       //M
    write_zm(42,1,7);       //E
    write_zm(50,1,8);       //A
    write_zm(58,1,9);       //S
    write_zm(66,1,10);      //]
    write_Hz(74,2,H_Z,15);  //开
    write_Hz(90,2,H_Z,16);  //始
    write_Hz(106,2,H_Z,5);  //测
    write_Hz(122,2,H_Z,6);  //量
    
    write_Hz(10,5,H_Z,5);   //测
    write_Hz(26,5,H_Z,6);   //量
    write_Hz(42,5,H_Z,36);  //放
    write_Hz(58,5,H_Z,37);  //样
    write_Hz(74,5,H_Z,25);  //点
}
void  height_loft5()
{
    write_Hz(10,8,H_Z,34);  //高
    write_Hz(26,8,H_Z,35);  //程
    write_Hz(42,8,H_Z,36);  //放
    write_Hz(58,8,H_Z,37);  //样
    
    write_zm(10,5,15);       //S
    write_Hz(30,6,H_Z,3);    //标
    write_Hz(46,6,H_Z,28);   //尺
    write_zm(62,5,13);      //:
    write_zm(120,5,0);      //m
    write_Hz(30,4,H_Z,36);  //放
    write_Hz(46,4,H_Z,37);  //样
    write_zm(62,3,13);      //:
    write_zm(120,3,0);      //m
    
    write_zm(10,1,14);      //N
    write_zm(18,1,13);      //:
    
    
    write_Hz(90,2,H_Z,33);   //δ
    write_zm(106,1,13);     //:
    write_zm(140,1,0);      //m
    write_zm(148,1,0);      //m
}
void height_loft6()
{
    write_Hz(10,8,H_Z,34);  //高
    write_Hz(26,8,H_Z,35);  //程
    write_Hz(42,8,H_Z,36);  //放
    write_Hz(58,8,H_Z,37);  //样
    
    write_zm(10,5,15);      //S
    write_Hz(30,6,H_Z,20);  //视
    write_Hz(50,6,H_Z,21);  //距
    write_zm(66,5,13);     //:
    
    
    write_Hz(30,4,H_Z,34); //高
    write_Hz(46,4,H_Z,35); //差
    write_zm(66,3,13);    //:
}
void height_loft7()
{
    write_Hz(10,8,H_Z,34); //高
    write_Hz(26,8,H_Z,35); //程
    write_Hz(42,8,H_Z,36); //放
    write_Hz(58,8,H_Z,37); //样
    
    write_zm(10,5,16);    //R
    write_zm(18,5,17);    //E
    write_zm(26,5,18);    //P
    write_zm(34,5,13);    //:
    
    write_Hz(42,6,H_Z,42);//新
    write_Hz(58,6,H_Z,43);//的
    write_Hz(74,6,H_Z,5); //测
    write_Hz(90,6,H_Z,6); //量
    
    write_zm(10,3,19);    //E
    write_zm(18,3,20);    //N
    write_zm(26,3,21);    //T
    write_zm(34,3,13);    //:
    
    write_Hz(42,4,H_Z,44);//继
    write_Hz(58,4,H_Z,45);//续
    
    write_zm(10,1,22);    //E
    write_zm(18,1,23);    //S
    write_zm(26,1,24);    //C
    write_zm(34,1,13);    //:
    
    write_Hz(42,2,H_Z,50);//退
    write_Hz(58,2,H_Z,51);//出
    write_Hz(74,2,H_Z,5); //测
    write_Hz(90,2,H_Z,6); //量
}
void hgt_dif_loft1()      //高差放样
{
  write_Hz(10,8,H_Z,34);//高
  write_Hz(26,8,H_Z,52);//差
  write_Hz(42,8,H_Z,36);//放
  write_Hz(58,8,H_Z,37);//样
  
  write_zm(10,5,15);    //S
  write_Hz(30,6,H_Z,3); //标
  write_Hz(50,6,H_Z,28);//尺
  write_zm(66,5,13);    //:
  write_zm(130,5,0);    //m
  
  write_Hz(30,4,H_Z,36);//放
  write_Hz(46,4,H_Z,37);//样
  write_zm(66,3,13);    //:
  write_zm(130,3,0);    //m
  
  write_zm(10,1,14);    //N
  write_zm(18,1,13);    //:
  
  write_Hz(90,2,H_Z,33);//δ
  write_zm(106,1,13);   //:
  write_zm(130,1,0);    //m
  write_zm(138,1,0);    //m
}
void hgt_dif_loft2()
{
  write_Hz(10,8,H_Z,34);//高
  write_Hz(26,8,H_Z,52);//差
  write_Hz(42,8,H_Z,36);//放
  write_Hz(58,8,H_Z,37);//样
  
  write_zm(10,5,15);    //S
  write_Hz(30,6,H_Z,20);//视
  write_Hz(50,6,H_Z,21);//距
  write_zm(66,5,13);    //:
  write_zm(130,4,0);    //m
  
  write_Hz(30,4,H_Z,34);//高
  write_Hz(46,4,H_Z,52);//差
  write_zm(66,3,13);    //:
  write_zm(130,2,0);    //m
}
void view_loft1()
{
  write_Hz(10,8,H_Z,20);  //视
  write_Hz(26,8,H_Z,21);  //距
  write_Hz(42,8,H_Z,36);  //放
  write_Hz(58,8,H_Z,37);  //样
  
  write_zm(10,5,15);      //S
  write_Hz(30,6,H_Z,20);  //视
  write_Hz(46,6,H_Z,21);  //距
  write_zm(62,5,13);      //:
  write_zm(130,4,0);      //m
  write_Hz(30,4,H_Z,36);  //放
  write_Hz(46,4,H_Z,37);  //样
  write_zm(62,3,13);      //:
  write_zm(130,2,0);      //m
}
void view_loft2()
{
  write_Hz(10,8,H_Z,20);  //视
  write_Hz(26,8,H_Z,21);  //距
  write_Hz(42,8,H_Z,36);  //放
  write_Hz(58,8,H_Z,37);  //样
  
  write_zm(10,5,15);    //S
  write_Hz(30,6,H_Z,3); //标
  write_Hz(46,6,H_Z,28);//尺
  write_zm(62,5,13);    //:
  write_zm(130,4,0);    //m
  
  write_Hz(30,4,H_Z,38);//输
  write_Hz(46,4,H_Z,39);//入
  write_zm(62,3,13);    //:
  write_zm(130,2,0);    //m
}
void line_mea_main1()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,15);  //开
  write_Hz(42,6,H_Z,16);  //始
  write_Hz(58,6,H_Z,9);   //线
  write_Hz(74,6,H_Z,10);  //路
  write_Hz(90,6,H_Z,5);   //测
  write_Hz(106,6,H_Z,6);  //量
  
  write_Hz(26,4,H_Z,44);  //继
  write_Hz(42,4,H_Z,45);  //续
  write_Hz(58,4,H_Z,9);   //线
  write_Hz(74,4,H_Z,10);  //路
  write_Hz(90,4,H_Z,5);   //测
  write_Hz(106,4,H_Z,6);  //量
  
  write_Hz(26,2,H_Z,46);  //结
  write_Hz(42,2,H_Z,47);  //束
  write_Hz(58,2,H_Z,9);   //线
  write_Hz(74,2,H_Z,10);  //路
  write_Hz(90,2,H_Z,5);   //测
  write_Hz(106,2,H_Z,6);  //量
  
  write_zm(10,5,2);     //=
  write_zm(18,5,3);     //>
}
void line_mea_main2()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,15);  //开
  write_Hz(42,6,H_Z,16);  //始
  write_Hz(58,6,H_Z,9);   //线
  write_Hz(74,6,H_Z,10);  //路
  write_Hz(90,6,H_Z,5);   //测
  write_Hz(106,6,H_Z,6);  //量
  
  write_Hz(26,4,H_Z,44);  //继
  write_Hz(42,4,H_Z,45);  //续
  write_Hz(58,4,H_Z,9);   //线
  write_Hz(74,4,H_Z,10);  //路
  write_Hz(90,4,H_Z,5);   //测
  write_Hz(106,4,H_Z,6);  //量
  
  write_Hz(26,2,H_Z,46);  //结
  write_Hz(42,2,H_Z,47);  //束
  write_Hz(58,2,H_Z,9);   //线
  write_Hz(74,2,H_Z,10);  //路
  write_Hz(90,2,H_Z,5);   //测
  write_Hz(106,2,H_Z,6);  //量
  
  write_zm(10,3,2);     //=
  write_zm(18,3,3);     //>
}
void line_mea_main3()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,15);  //开
  write_Hz(42,6,H_Z,16);  //始
  write_Hz(58,6,H_Z,9);   //线
  write_Hz(74,6,H_Z,10);  //路
  write_Hz(90,6,H_Z,5);   //测
  write_Hz(106,6,H_Z,6);  //量
  
  write_Hz(26,4,H_Z,44);  //继
  write_Hz(42,4,H_Z,45);  //续
  write_Hz(58,4,H_Z,9);   //线
  write_Hz(74,4,H_Z,10);  //路
  write_Hz(90,4,H_Z,5);   //测
  write_Hz(106,4,H_Z,6);  //量
  
  write_Hz(26,2,H_Z,46);  //结
  write_Hz(42,2,H_Z,47);  //束
  write_Hz(58,2,H_Z,9);   //线
  write_Hz(74,2,H_Z,10);  //路
  write_Hz(90,2,H_Z,5);   //测
  write_Hz(106,2,H_Z,6);  //量
  
  write_zm(10,1,2);       //=
  write_zm(18,1,3);       //>
}
void line_mea_start1()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(10,6,H_Z,22);  //作
  write_Hz(26,6,H_Z,23);  //业
  write_Hz(42,6,H_Z,13);  //?
  
  write_zm(10,3,2);       //=
  write_zm(18,3,3);       //>
  
  write_zm(26,3,12);      //J
}
void line_mea_start2()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,53);  //三
  write_Hz(42,6,H_Z,54);  //等
  write_Hz(58,6,H_Z,55);  //水
  write_Hz(74,6,H_Z,4);   //准
  write_Hz(90,6,H_Z,5);   //测
  write_Hz(106,6,H_Z,6);  //量
  write_zm(122,5,38);     //B
  write_zm(130,5,39);     //F
  write_zm(138,5,39);     //F
  write_zm(146,5,38);     //B
  write_zm(10,5,2);       //=
  write_zm(18,5,3);       //>
  
  write_Hz(26,4,H_Z,58);  //四
  write_Hz(42,4,H_Z,54);  //等
  write_Hz(58,4,H_Z,55);  //水
  write_Hz(74,4,H_Z,4);   //准
  write_Hz(90,4,H_Z,5);   //测
  write_Hz(106,4,H_Z,6);  //量
  write_zm(122,3,38);     //B
  write_zm(130,3,38);     //B
  write_zm(138,3,39);     //F
  write_zm(146,3,39);     //F
  
  write_Hz(26,2,H_Z,40);  //后
  write_Hz(42,2,H_Z,59);  //前
  write_zm(58,1,26);      // /
  write_Hz(66,2,H_Z,40);  //后
  write_Hz(82,2,H_Z,60);  //中
  write_Hz(98,2,H_Z,59);  //前
  write_zm(114,1,38);     //B
  write_zm(122,1,39);     //F
  write_zm(130,1,26);     // /
  write_zm(138,1,38);     // B
  write_zm(146,1,40);     // I
  write_zm(154,1,39);     // F
}
void line_mea_start3()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,53);  //三
  write_Hz(42,6,H_Z,54);  //等
  write_Hz(58,6,H_Z,55);  //水
  write_Hz(74,6,H_Z,4);   //准
  write_Hz(90,6,H_Z,5);   //测
  write_Hz(106,6,H_Z,6);  //量
  write_zm(122,5,38);     //B
  write_zm(130,5,39);     //F
  write_zm(138,5,39);     //F
  write_zm(146,5,38);     //B
  write_zm(10,3,2);       //=
  write_zm(18,3,3);       //>
  
  write_Hz(26,4,H_Z,58);  //四
  write_Hz(42,4,H_Z,54);  //等
  write_Hz(58,4,H_Z,55);  //水
  write_Hz(74,4,H_Z,4);   //准
  write_Hz(90,4,H_Z,5);   //测
  write_Hz(106,4,H_Z,6);  //量
  write_zm(122,3,38);     //B
  write_zm(130,3,38);     //B
  write_zm(138,3,39);     //F
  write_zm(146,3,39);     //F
  
  write_Hz(26,2,H_Z,40);  //后
  write_Hz(42,2,H_Z,59);  //前
  write_zm(58,1,26);      // /
  write_Hz(66,2,H_Z,40);  //后
  write_Hz(82,2,H_Z,60);  //中
  write_Hz(98,2,H_Z,59);  //前
  write_zm(114,1,38);     //B
  write_zm(122,1,39);     //F
  write_zm(130,1,26);     // /
  write_zm(138,1,38);     // B
  write_zm(146,1,40);     // I
  write_zm(154,1,39);     // F
}
void line_mea_start4()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,53);  //三
  write_Hz(42,6,H_Z,54);  //等
  write_Hz(58,6,H_Z,55);  //水
  write_Hz(74,6,H_Z,4);   //准
  write_Hz(90,6,H_Z,5);   //测
  write_Hz(106,6,H_Z,6);  //量
  write_zm(122,5,38);     //B
  write_zm(130,5,39);     //F
  write_zm(138,5,39);     //F
  write_zm(146,5,38);     //B
  write_zm(10,1,2);       //=
  write_zm(18,1,3);       //>
  
  
  write_Hz(26,4,H_Z,58);  //四
  write_Hz(42,4,H_Z,54);  //等
  write_Hz(58,4,H_Z,55);  //水
  write_Hz(74,4,H_Z,4);   //准
  write_Hz(90,4,H_Z,5);   //测
  write_Hz(106,4,H_Z,6);  //量
  write_zm(122,3,38);     //B
  write_zm(130,3,38);     //B
  write_zm(138,3,39);     //F
  write_zm(146,3,39);     //F
  
  write_Hz(26,2,H_Z,40);  //后
  write_Hz(42,2,H_Z,59);  //前
  write_zm(58,1,26);      // /
  write_Hz(66,2,H_Z,40);  // 后
  write_Hz(82,2,H_Z,60);  // 中
  write_Hz(98,2,H_Z,59);  // 前
  write_zm(114,1,38);     //B
  write_zm(122,1,39);     //F
  write_zm(130,1,26);     // /
  write_zm(138,1,38);     // B
  write_zm(146,1,40);     // I
  write_zm(154,1,39);     // F
}
void  line_mea_start5()
{
  write_Hz(10,8,H_Z,9);   //线
  write_Hz(26,8,H_Z,10);  //路
  write_Hz(42,8,H_Z,5);   //测
  write_Hz(58,8,H_Z,6);   //量
  write_Hz(74,8,H_Z,7);   //模
  write_Hz(90,8,H_Z,8);   //式
  
  write_Hz(26,6,H_Z,38);   //输
  write_Hz(42,6,H_Z,39);   //入
  write_Hz(58,6,H_Z,40);   //后
  write_Hz(74,6,H_Z,41);   //视
  write_Hz(90,6,H_Z,62);   //点
 
  write_zm(10,5,2);        //=
  write_zm(18,5,3);        //>
  
  write_Hz(26,4,H_Z,63);   //输
  write_Hz(42,4,H_Z,64);   //入
  write_Hz(58,4,H_Z,65);   //后
  write_Hz(74,4,H_Z,66);   //视
  write_Hz(90,4,H_Z,62);   //点

  
}
void  line_mea_start6()
{
  write_Hz(10,8,H_Z,9);    //线
  write_Hz(26,8,H_Z,10);   //路
  write_Hz(42,8,H_Z,5);    //测
  write_Hz(58,8,H_Z,6);    //量
  write_Hz(74,8,H_Z,7);    //模
  write_Hz(90,8,H_Z,8);    //式
  
  write_Hz(26,6,H_Z,38);   //输
  write_Hz(42,6,H_Z,39);   //入
  write_Hz(58,6,H_Z,40);   //后
  write_Hz(74,6,H_Z,41);   //视
  write_Hz(90,6,H_Z,62);   //点
 
  write_zm(10,3,2);        //=
  write_zm(18,3,3);        //>
  
  write_Hz(26,4,H_Z,63);   //输
  write_Hz(42,4,H_Z,64);   //入
  write_Hz(58,4,H_Z,65);   //后
  write_Hz(74,4,H_Z,66);   //视
  write_Hz(90,4,H_Z,62);   //点

  
}
void line_mea_start7()
{
  write_Hz(10,8,H_Z,9);    //线
  write_Hz(26,8,H_Z,10);   //路
  write_Hz(42,8,H_Z,5);    //测
  write_Hz(58,8,H_Z,6);    //量
  write_Hz(74,8,H_Z,7);    //模
  write_Hz(90,8,H_Z,8);    //式
  
  write_zm(10,5,38);       //B
  write_zm(18,5,43);       //M
  write_zm(26,5,43);       //#
  write_Hz(42,6,H_Z,61);   //?
  
  write_zm(10,3,2);        //=
  write_zm(18,3,3);        //>
  
  write_num111(33,18,3);
}
void line_mea_start8()
{
  write_Hz(10,8,H_Z,9);    //线
  write_Hz(26,8,H_Z,10);   //路
  write_Hz(42,8,H_Z,5);    //测
  write_Hz(58,8,H_Z,6);    //量
  write_Hz(74,8,H_Z,7);    //模
  write_Hz(90,8,H_Z,8);    //式
  
  write_Hz(10,6,H_Z,26);   //注
  write_Hz(26,6,H_Z,27);   //记
  write_zm(42,5,43);       //#
  write_Hz(50,6,H_Z,61);   //?
  
  write_zm(10,3,2);        //=
  write_zm(18,3,3);        //>
  
}
void line_mea_start9()
{
  write_Hz(10,8,H_Z,9);    //线
  write_Hz(26,8,H_Z,10);   //路
  write_Hz(42,8,H_Z,5);    //测
  write_Hz(58,8,H_Z,6);    //量
  write_Hz(74,8,H_Z,7);    //模
  write_Hz(90,8,H_Z,8);    //式
  
  write_Hz(10,6,H_Z,38);   //输
  write_Hz(26,6,H_Z,39);   //入
  write_Hz(42,6,H_Z,40);   //后
  write_Hz(58,6,H_Z,41);   //视
  write_Hz(74,6,H_Z,34);   //高
  write_Hz(90,6,H_Z,35);   //程
  
  write_zm(10,3,2);        //=
  write_num111(35,10,3);   //<
}
void line_mea_start10()
{
  write_Hz(10,8,H_Z,9);    //线
  write_Hz(26,8,H_Z,10);   //路
  
  write_zm(60,7,38);       //B
  write_zm(68,7,39);       //F
  write_zm(76,7,39);       //F
  write_zm(84,7,38);       //B
  
  write_zm(10,5,38);       //B
  write_zm(18,5,44);       //k
  write_zm(26,5,27);       //1
  
  write_zm(10,3,38);       //B
  write_zm(18,3,43);       //M
  write_zm(26,3,4);        //#
  write_zm(34,3,13);       //:
  
  write_Hz(10,2,H_Z,14);   //按
  write_zm(26,1,5);        //[
  write_zm(34,1,6);        //M
  write_zm(42,1,7);        //E
  write_zm(50,1,8);        //A
  write_zm(58,1,9);        //S
  write_zm(66,1,10);       //]
  write_Hz(74,2,H_Z,15);   //开
  write_Hz(90,2,H_Z,16);   //始
  write_Hz(106,2,H_Z,5);   //测
  write_Hz(122,2,H_Z,6);   //量
}
void line_mea_start11()
{
  write_Hz(10,8,H_Z,9);    //线
  write_Hz(26,8,H_Z,10);   //路
  
  write_zm(60,7,38);       //B
  write_zm(68,7,39);       //F
  write_zm(76,7,39);       //F
  write_zm(84,7,38);       //B
  write_zm(94,7,27);       //1
  write_zm(102,7,26);       // /
  write_zm(110,7,28);       //2  
  
  write_zm(10,5,38);       //B
  write_zm(18,5,27);       //1
  
  write_Hz(26,6,H_Z,3);   //标
  write_Hz(42,6,H_Z,28);  //尺
  write_Hz(58,6,H_Z,29);  //均
  write_Hz(74,6,H_Z,30);  //值
  
  
  write_zm(10,3,38);       //B
  write_zm(18,3,27);       //1
  
  write_Hz(26,4,H_Z,20);  //视
  write_Hz(42,4,H_Z,21);  //距
  write_Hz(58,4,H_Z,29);  //均
  write_Hz(74,4,H_Z,30);  //值
}
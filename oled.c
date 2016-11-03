/*硬件连接*/
//PB4--SCL   PB5--SDA 
#include"global.h"  //使用其中delay函数
#include"oled.h"
#include"iic.h"
#include"iostm8s103f3.h"
#include"stdbool.h"
#include"stdint.h"

#define  Write_CMD_TO_OLED12864(byte)  I2C_WriteOneByteDataToSlave(0x78,0x00,byte)
#define  Write_DAT_TO_OLED12864(byte)  I2C_WriteOneByteDataToSlave(0x78,0x40,byte)

/************************************6*8的点阵************************************/
const uint8_t ASCII_6X8[92][6] =           //水平寻址
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};
uint8_t Hzk2[]=   //本数据有PCtoLCD取模软件产生,
{
  0x84,0x45,0xF6,0x4C,0x80,0x7E,0xC2,0x42,0xC2,0x7E,0x00,0x00,

  0x84,0x64,0xFF,0x24,0xFA,0x0A,0x5A,0xEF,0x5A,0x0A,0xFA,0x00,

  0x84,0x64,0xFF,0x24,0xFA,0x0A,0x5A,0xEF,0x5A,0x0A,0xFA,0x00,

  0x40,0x20,0x18,0x07,0xC0,0x30,0x00,0x07,0x18,0x20,0x40,0x00,

  0x40,0x42,0x42,0xFE,0x42,0x42,0x42,0xFE,0x42,0x42,0x40,0x00,

  0x11,0xF2,0x40,0x5F,0x55,0x55,0xFF,0x55,0x55,0x5F,0x40,0x00,

  0xFF,0x01,0xC1,0x5D,0x55,0xD5,0x55,0x5D,0xC1,0x01,0xFF,0x00,

  0x22,0x44,0xD2,0x52,0x57,0xF2,0x52,0xF2,0x57,0x52,0xD2,0x00,

  0xFE,0x00,0xFC,0x00,0xFF,0x00,0xF9,0x0D,0xEB,0x09,0xF9,0x00,
 
  0x10,0x92,0x52,0xFE,0x51,0x91,0x10,0xFC,0x00,0x00,0xFF,0x00,
  
  0x00,0x00,0x7C,0x00,0x00,0x00,
  
  0x00,0x00,0x0F,0x00,0x08,0x04,0x03,0x00,0x07,0x08,0x0C,0x00,/*"祝",0*/
  0x00,0x00,0x0F,0x00,0x0F,0x01,0x01,0x07,0x01,0x09,0x0F,0x00,/*"楠",1*/
  0x00,0x00,0x0F,0x00,0x0F,0x01,0x01,0x07,0x01,0x09,0x0F,0x00,/*"楠",2*/
  0x00,0x04,0x06,0x05,0x04,0x04,0x04,0x05,0x06,0x0C,0x00,0x00,/*"公",3*/
  0x00,0x08,0x06,0x01,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,/*"开",4*/
  0x00,0x07,0x02,0x04,0x02,0x01,0x0F,0x01,0x02,0x04,0x04,0x00,/*"课",5*/
  0x0F,0x08,0x09,0x0C,0x0A,0x09,0x0A,0x0C,0x09,0x08,0x0F,0x00,/*"圆",6*/
  0x04,0x02,0x0F,0x00,0x02,0x01,0x02,0x01,0x02,0x08,0x0F,0x00,/*"满",7*/
  0x07,0x00,0x03,0x00,0x0F,0x00,0x09,0x04,0x03,0x04,0x09,0x00,/*"顺",8*/
  0x01,0x00,0x00,0x0F,0x00,0x00,0x00,0x01,0x08,0x08,0x0F,0x00,/*"利",9*/

  0x00,0x00,0x02,0x00,0x00,0x00/*"!",10*/
};


//汉字 “楠楠，我爱你！”先扫描汉字的上半部分，再扫描下半部分
uint8_t Hzk1[]=   //本数据由PCtoLCD取模软件产生,手动改了一下汉字下半部分数据位置
{
   //楠楠,我爱你! 
  0x84,0x64,0xFF,0x24,0xFA,0x0A,0x5A,0xEF,0x5A,0x0A,0xFA,0x00,/*"楠",0up*/
  0x84,0x64,0xFF,0x24,0xFA,0x0A,0x5A,0xEF,0x5A,0x0A,0xFA,0x00,/*"楠",1up*/
  0x00,0x00,0x00,0x00,0x00,0x00,/*",",2up*/
  0x10,0x12,0x12,0xFF,0x91,0x10,0xFF,0x10,0x90,0x52,0x14,0x00,/*"我",3up*/
  0x32,0x56,0x5A,0xD2,0x76,0x5A,0x51,0x51,0x59,0x55,0x31,0x00,/*"爱",4up*/
  0x20,0x10,0xFC,0x03,0x10,0xCF,0x04,0xF4,0x04,0x54,0x8C,0x00,/*"你",5up*/
  0x00,0x00,0x7C,0x00,0x00,0x00,/*"!",6up*/
  0x00,0x00,0x0F,0x00,0x0F,0x01,0x01,0x07,0x01,0x09,0x0F,0x00,/*"楠",0*/
  0x00,0x00,0x0F,0x00,0x0F,0x01,0x01,0x07,0x01,0x09,0x0F,0x00,/*"楠",1*/
  0x04,0x03,0x00,0x00,0x00,0x00,/*",",2*/
  0x02,0x02,0x09,0x0F,0x00,0x04,0x02,0x03,0x04,0x08,0x0E,0x00,/*"我",3*/
  0x08,0x04,0x0A,0x09,0x0B,0x05,0x05,0x05,0x0B,0x08,0x08,0x00,/*"爱",4*/
  0x00,0x00,0x0F,0x00,0x02,0x01,0x08,0x0F,0x00,0x00,0x03,0x00,/*"你",5*/
  0x00,0x00,0x02,0x00,0x00,0x00/*"!",6*/
};

//手机界面图片
//const uint8_t show1[]=
//{
//    0x00,0x06,0x0A,0xFE,0x0A,0xC6,0x00,0xE0,0x00,0xF0,0x00,0xF8,0x00,0x00,0x00,0x00,
//    0x00,0x00,0xFE,0x7D,0xBB,0xC7,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xC7,0xBB,0x7D,
//    0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
//    0x0C,0xFE,0xFE,0x0C,0x08,0x20,0x60,0xFE,0xFE,0x60,0x20,0x00,0x00,0x00,0x78,0x48,
//    0xFE,0x82,0xBA,0xBA,0x82,0xBA,0xBA,0x82,0xBA,0xBA,0x82,0xBA,0xBA,0x82,0xFE,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,
//    0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0x00,0x00,0xFE,0xFF,0x03,
//    0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFE,0x00,0x00,0x00,0x00,0xC0,0xC0,
//    0xC0,0x00,0x00,0x00,0x00,0xFE,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
//    0xFF,0xFE,0x00,0x00,0xFE,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,
//    0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x0C,
//    0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFF,0xFF,0x00,0x00,0x00,0x00,0xE1,0xE1,
//    0xE1,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFF,
//    0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,
//    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x0F,0x1F,0x18,
//    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
//    0x1F,0x0F,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,
//    0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0xE2,0x92,0x8A,0x86,0x00,0x00,0x7C,0x82,0x82,0x82,0x7C,
//    0x00,0xFE,0x00,0x82,0x92,0xAA,0xC6,0x00,0x00,0xC0,0xC0,0x00,0x7C,0x82,0x82,0x82,
//    0x7C,0x00,0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0xC0,0xC0,0x00,0x7C,0x82,0x82,0x82,
//    0x7C,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x24,0xA4,0x2E,0x24,0xE4,0x24,0x2E,0xA4,0x24,0x00,0x00,0x00,0xF8,0x4A,0x4C,
//    0x48,0xF8,0x48,0x4C,0x4A,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x20,0x10,0x10,
//    0x10,0x10,0x20,0xC0,0x00,0x00,0xC0,0x20,0x10,0x10,0x10,0x10,0x20,0xC0,0x00,0x00,
//    0x00,0x12,0x0A,0x07,0x02,0x7F,0x02,0x07,0x0A,0x12,0x00,0x00,0x00,0x0B,0x0A,0x0A,
//    0x0A,0x7F,0x0A,0x0A,0x0A,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x40,0x40,
//    0x40,0x50,0x20,0x5F,0x80,0x00,0x1F,0x20,0x40,0x40,0x40,0x50,0x20,0x5F,0x80,0x00,
//};
/******************************************************************************************************
* 功    能：清屏
* 入口函数:
* 出口函数：
* 说    明：
* 范    例：
* 日    期:2016年11月1日
******************************************************************************************************/
void OLED12864_Clear(void)
{
  uint8_t x,y;
  for(y=0;y<8;y++)
  {
    Write_CMD_TO_OLED12864(0xB0+y);
    Write_CMD_TO_OLED12864(0x00);
    Write_CMD_TO_OLED12864(0x10);
    for(x=0;x<128;x++)
    {
      Write_DAT_TO_OLED12864(0x00);         
    }
  }
}
/******************************************************************************************************
* 功    能：OLED12864初始化配置
* 入口函数:
* 出口函数：
* 说   明：设置显示坐标
* 作   者：茗风
* 日   期:2016年11月1日
******************************************************************************************************/
void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 
	Write_CMD_TO_OLED12864(0xB0+y);
	Write_CMD_TO_OLED12864(((x&0xF0)>>4)|0x10);
	Write_CMD_TO_OLED12864((x&0x0F)|0x01); 
}
///******************************************************************************************************
//* 功    能	：向OLED12864写一串字符函数
//* 入口参数	：x  x轴坐标，取值范围（0~15）
//*             y  y轴坐标，取值范围（0~1），一共两行
//*             *s 一串字符
//* 出口参数	：无 
//* 说    明	：显示6*8一组标准ASCII字符串，显示的坐标（x,y），y为页范围0～7
//* 编写日期  ：2016年11月1日
//* 作    者  ：茗风
//******************************************************************************************************/
uint8_t OLED12864_Display_Char(uint8_t _char)
{
  uint8_t  i=0;
   
  _char -= 32;//计算ASCII字符在F6x8[][]数组中的位置
     
  for(i=0; i<6; i++)
  {
    Write_DAT_TO_OLED12864(ASCII_6X8[_char][i]);  
  }   
  return 0;
}

///******************************************************************************************************
//* 功    能	：向OLED12864写一串字符函数
//* 入口参数	：x  x轴坐标，取值范围（0~15）
//*             y  y轴坐标，取值范围（0~1），一共两行
//*             *s 一串字符
//* 出口参数	：无 
//* 说    明	：显示6*8一组标准ASCII字符串，显示的坐标（x,y），y为页范围0～7
//* 编写日期  ：2016年11月1日
//* 作    者  ：茗风
//******************************************************************************************************/
uint8_t OLED12864_Display_String(uint8_t x,uint8_t y,uint8_t *s)
{
//  uint8_t c=0, i=0;
  OLED_Set_Pos(x,y);   
  while (*s != '\0') 
  {    
//    c = *s-32;//计算ASCII字符在F6x8[][]数组中的位置
//    if(x>126) {x=0; y++;}   
    OLED12864_Display_Char(*s++);  
//    x += 6;
//    s++;//指向字符串的指针自增,指向下一个字符
  }  
  return 0;
}
///******************************************************************************************************
//* 功    能	：OLED12864显示一个uint16_t类型的数据
//* 入口参数	：x  x轴坐标，取值范围（0~128）
//*             y  y轴坐标，取值范围（0~8），一共两行
//*             number 写入的字符
//* 出口参数	：无 
//* 说    明	：
//* 编写日期  ：2016年10月22日
//* 作    者  ：茗风
//******************************************************************************************************/
void LCD1602_Display_Number(uint8_t x,uint8_t y,uint32_t _number)
{
//  uint8_t tmp=0;
  OLED_Set_Pos(x,y);  
  
  if(_number<10)  //9
  { 
     OLED12864_Display_Char(_number%10+48);
  }
  else if(_number<100) //98
  {
     OLED12864_Display_Char(_number/10+48);
     OLED12864_Display_Char(_number%10+48);
  }
  else if(_number<1000) //988
  {
     OLED12864_Display_Char(_number/100+48);
     OLED12864_Display_Char(_number%100/10+48);
     OLED12864_Display_Char(_number%10+48);
  }
  else if(_number<10000) //9999
  {
     OLED12864_Display_Char(_number/1000+48);
     OLED12864_Display_Char(_number%1000/100+48);
     OLED12864_Display_Char(_number%100/10+48);
     OLED12864_Display_Char(_number%10+48);
  }
  else if(_number<100000) //99999
  {
     OLED12864_Display_Char(_number/10000+48);
     OLED12864_Display_Char(_number%10000/1000+48);
     OLED12864_Display_Char(_number%1000/100+48);
     OLED12864_Display_Char(_number%100/10+48);
     OLED12864_Display_Char(_number%10+48);
  } 
  else if(_number<1000000) //999999
  {
     OLED12864_Display_Char(_number/100000+48);
     OLED12864_Display_Char(_number%100000/10000+48);
     OLED12864_Display_Char(_number%10000/1000+48);
     OLED12864_Display_Char(_number%1000/100+48);
     OLED12864_Display_Char(_number%100/10+48);
     OLED12864_Display_Char(_number%10+48);
  }
  else if(_number<10000000) //999999
  {
     OLED12864_Display_Char(_number/1000000+48);
     OLED12864_Display_Char(_number%1000000/100000+48);
     OLED12864_Display_Char(_number%100000/10000+48);
     OLED12864_Display_Char(_number%10000/1000+48);
     OLED12864_Display_Char(_number%1000/100+48);
     OLED12864_Display_Char(_number%100/10+48);
     OLED12864_Display_Char(_number%10+48);
  }
}
///******************************************************************************************************
//*  功  能   ：显示一行汉字
//*  入口参数 ：无
//*  出口参数 ： 0:写字串成功     1：坐标越界      2：字符越界
//*  说  明   ：注意,本函数暂时只能一次写小于一行的汉字,多行需要分开写
//*  范  例   ：无
//* 日     期:2016年10月31日
//******************************************************************************************************/
uint8_t OLED12864_Display_SimplifiedChinese(uint8_t x,uint8_t y,uint8_t *s,uint16_t len)
{
    static uint8_t i=0;
  
    len=len/2;
    
    OLED_Set_Pos(x,y); 
    for(i=0;i<len;i++)
    {      
      Write_DAT_TO_OLED12864(*s++);
    }
    OLED_Set_Pos(x,y+1); 
    for(i=0;i<len;i++)
    {
      Write_DAT_TO_OLED12864(*s++);
    }
    return 0;
}
/******************************************************************************************************
* 功    能：draw one picture
* 入口函数:
* 出口函数：
* 说    明：
* 范    例：
* 日    期:2016年10月31日
******************************************************************************************************/
//void OLED12864_Draw_One_Picture(void)
//{
//  uint8_t x,y;
//  uint16_t i=0;
//  for(y=0;y<8;y++)
//  {
//    Write_CMD_TO_OLED12864(0xb0+y);
//    Write_CMD_TO_OLED12864(0x00);
//    Write_CMD_TO_OLED12864(0x10);
//    for(x=0;x<128;x++)
//    {
//      Write_DAT_TO_OLED12864(0x00);         
//    }
//  }
//  for(y=0;y<8;y++)
//  {
//    Write_CMD_TO_OLED12864(0xb0+y);
//    Write_CMD_TO_OLED12864(0x00);
//    Write_CMD_TO_OLED12864(0x10);
//    for(x=0;x<128;x++)
//    {
//      Write_DAT_TO_OLED12864(show1[i++]);
//      delay_100us(1000);         
//    }
//  }
//}
/******************************************************************************************************
* 功    能：OLED12864初始化配置
* 入口函数:
* 出口函数：
* 说    明：
* 范    例：
* 日    期:2016年10月31日
******************************************************************************************************/
void OLED12864_Config(void)
{
  delay_100us(100);
	Write_CMD_TO_OLED12864(0xAE);   //display off
	Write_CMD_TO_OLED12864(0x20);	//Set Memory Addressing Mode	
	Write_CMD_TO_OLED12864(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_CMD_TO_OLED12864(0xB0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_CMD_TO_OLED12864(0xC8);	//Set COM Output Scan Direction
	Write_CMD_TO_OLED12864(0x00);//---set low column address
	Write_CMD_TO_OLED12864(0x10);//---set high column address
	Write_CMD_TO_OLED12864(0x40);//--set start line address
	Write_CMD_TO_OLED12864(0x81);//--set contrast control register
	Write_CMD_TO_OLED12864(0x7F);
	Write_CMD_TO_OLED12864(0xA1);//--set segment re-map 0 to 127
	Write_CMD_TO_OLED12864(0xA6);//--set normal display
	Write_CMD_TO_OLED12864(0xA8);//--set multiplex ratio(1 to 64)
	Write_CMD_TO_OLED12864(0x3F);//
	Write_CMD_TO_OLED12864(0xA4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_CMD_TO_OLED12864(0xD3);//-set display offset
	Write_CMD_TO_OLED12864(0x00);//-not offset
	Write_CMD_TO_OLED12864(0xD5);//--set display clock divide ratio/oscillator frequency
	Write_CMD_TO_OLED12864(0xF0);//--set divide ratio
	Write_CMD_TO_OLED12864(0xD9);//--set pre-charge period
	Write_CMD_TO_OLED12864(0x22); //
	Write_CMD_TO_OLED12864(0xDA);//--set com pins hardware configuration
	Write_CMD_TO_OLED12864(0x12);
	Write_CMD_TO_OLED12864(0xDB);//--set vcomh
	Write_CMD_TO_OLED12864(0x20);//0x20,0.77xVcc
	Write_CMD_TO_OLED12864(0x8D);//--set DC-DC enable
	Write_CMD_TO_OLED12864(0x14);//
	Write_CMD_TO_OLED12864(0xAF);//--turn on oled panel
  OLED12864_Clear();//清屏操作
  OLED12864_Display_String(0,3,"nan nan 5201314!");
//  OLED12864_Display_SimplifiedChinese(0, 0,Hzk2,sizeof(Hzk2));//祝楠楠公开课，圆满顺利！
//  OLED12864_Display_SimplifiedChinese(30,3,Hzk1,sizeof(Hzk1));//楠楠，我爱你!
//  LCD1602_Display_Number(30,5,5201314);
}




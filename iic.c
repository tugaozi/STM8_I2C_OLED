/*硬件连接*/
// PB4--SCL   PB5--SDA 
/****************************************************************************************
*开发环境:IAR for stm8 v6.5.3
*硬件平台:STM8L-DISCOVERY
*功能说明:通过硬件I2C等待的方法,
*作    者：茗风
****************************************************************************************/
#include"iic.h"
#include"iostm8s103f3.h"
#include"stdbool.h"


/******************************************************************************************************
* 名 称： uint8_t I2C_ReadOneByteDataFromSlave(uint8_t address)
* 功 能：从I2C从设备中读取一字节的数据
* 入口参数：address:读取数据的寄存器地址
* 出口参数：返回一个从I2C从设备指定地址读到的数据
* 说 明：
* 范 例：无
******************************************************************************************************/
uint8_t I2C_ReadOneByteDataFromSlave(uint8_t address)
{
  volatile uint8_t t;
  //----------I2C起始信号--------------
  I2C_CR2_START=1;//产生一个起始条件
  while(!(I2C_SR1_SB==1));//读SR1寄存器，清除SB标志位
//  _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  
  //-------发送写I2C从器件地址--------- 
  I2C_DR=0xD0;//发送从设备地址
  while(!(I2C_SR1_ADDR==1));//读SR1寄存器，清除ADDR标志位
 // _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  if(I2C_SR3_TRA==0)return 1;//读SR3寄存器，清除ADDR标志位
  //  0: Data bytes received
  //  1: Data bytes transmitted
  
  //-----写I2C从器件寄存器地址-------- 
  I2C_DR=address;
  while(!(I2C_SR1_BTF==1));//等待地址发送完成
//  _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  
  //--------I2C重复起始信号-----------
  I2C_CR2_START=1;//重复产生一个起始条件
  while(!(I2C_SR1_SB==1));//读SR1寄存器，清除SB标志位
//  _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  
  //-------发送读I2C从器件地址--------- 
  I2C_DR=0xD1;//发送从设备地址
  while(!(I2C_SR1_ADDR==1));//读SR1寄存器，清除ADDR标志位
//  _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  if(I2C_SR3_TRA==1)return 1;//读SR3寄存器，清除ADDR标志位
  
  //-------------停止信号-------------
  I2C_CR2_ACK=0;//ACK位控制着ACK信号,此位为0可以产生一个NOACK信号
  I2C_CR2_STOP=1;
  
  //-------------等待接收到数据-------------
  while(!(I2C_SR1_RXNE==1));//等待地址发送完成
  
  //-------------读取数据-------------
  t=I2C_DR;
  
  return t;
}
/******************************************************************************************************
* 名 称：void I2C_WriteOneByteDataToSlave(uint8_t slave_address,uint8_t address,uint8_t dat)
* 功 能：写入一字节的数据到I2C设备中
* 入口参数：slave_address: I2C从设备硬件地址     address:写入的数据存储地址    dat:待写入的数据
* 出口参数：无
* 说 明： 通过MSTM8的I2C硬件写入I2C设备一个字节的数据
* 范 例：无
******************************************************************************************************/
uint8_t I2C_WriteOneByteDataToSlave(uint8_t slave_address,uint8_t address,uint8_t dat)
{
  volatile uint8_t t;
  I2C_CR2_ACK=1;
  //----------I2C起始信号--------------
  I2C_CR2_START=1;//产生一个起始条件
  while(!(I2C_SR1_SB==1));
 // _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  I2C_DR=slave_address;
  
  //--------写I2C从器件地址----------- 
  while(!(I2C_SR1_ADDR==1));
//  _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  if(I2C_SR3_TRA==0)return 1;//读SR3寄存器，清除ADDR标志位
  
  //-----写I2C从器件寄存器地址-------- 
  while(!(I2C_SR1_TXE==1));
  I2C_DR=address;
  
  //-------写I2C数据到寄存器中--------
  while(!(I2C_SR1_TXE==1));
  I2C_DR=dat;
  while(!(I2C_SR1_TXE==1));
  while(!(I2C_SR1_BTF==1));
 // _5NOPS;//根据数据手册,检测到标志位后,需插入5个NOP进行延时
  
  //-------------停止信号-------------
  I2C_CR2_STOP=1;
  return 0;
}
/******************************************************************************************************
* 功    能：从I2C从设备读取多个字节数据
* 入口函数:
* 出口函数：
* 说    明：
* 范    例：
* 日    期：
******************************************************************************************************/
uint8_t I2C_ReadMultiBytesFromSlave(uint8_t address,uint8_t *rxbuf,uint8_t len)
{
  volatile uint8_t i=0;
  
  if(len==0)return 1;//如果写入字节长度为0退出
  
  I2C_CR2_ACK=1;
  //----------I2C起始信号--------------
  I2C_CR2_START=1;//产生一个起始条件
  while(!(I2C_SR1_SB==1));//读SR1寄存器，清除SB标志位
  
  //-------发送写I2C从器件地址--------- 
  I2C_DR=0xD0;//发送从设备地址
  while(!(I2C_SR1_ADDR==1));//读SR1寄存器，清除ADDR标志位
  if(I2C_SR3_TRA==0)return 1;//读SR3寄存器，清除ADDR标志位
  //  0: Data bytes received
  //  1: Data bytes transmitted
  
  //-----写I2C从器件寄存器地址-------- 
  I2C_DR=address;
  while(!(I2C_SR1_BTF==1));//等待地址发送完成
  
  //--------I2C重复起始信号-----------
  I2C_CR2_START=1;//重复产生一个起始条件
  while(!(I2C_SR1_SB==1));//读SR1寄存器，清除SB标志位
  
  //-------发送读I2C从器件地址--------- 
  I2C_DR=0xD1;//发送从设备地址
  while(!(I2C_SR1_ADDR==1));//读SR1寄存器，清除ADDR标志位
  if(I2C_SR3_TRA==1)return 1;//读SR3寄存器，清除ADDR标志位
  //-------------读取数据-------------
  if(len>1)
  {
      for( i=len;i>1;i-- )
      {
        while(!(I2C_SR1_RXNE==1));//等待I2C1_DR接收到数
        *rxbuf++ = I2C_DR;  
      }
  }

  //-------------停止信号-------------
  I2C_CR2_ACK=0;//ACK位控制着ACK信号,此位为0可以产生一个NOACK信号
  I2C_CR2_STOP=1;
  
  while(!(I2C_SR1_RXNE==1));//等待I2C1_DR接收到数
  *rxbuf++ = I2C_DR; 
  
  return 0;
}
/******************************************************************************************************
* 名 称： IIC_init()
* 功 能：初始化IIC
* 入口参数：无
* 出口参数：无
* 说 明：PB4--SCL   PB5--SDA 
* 范 例：无
******************************************************************************************************/
void I2C_Init(void)
{ 
  //----打开IIC外设时钟----
//  CLK_PCKENR1_PCKEN13=1;//
  I2C_CR1_PE=0;
  I2C_CR2_ACK=1;
  
  //----I2C输入时钟频率选择----
  I2C_FREQR_FREQ=0x02;//2MHz
  /*  The allowed range is between 1 MHz and 16 MHz
  000000: not allowed
  000001: 1 MHz
  000010: 2 MHz
  ...
  010000: 16 MHz                                 */
  
  //----配置时钟控制寄存器----
  I2C_CCRH=0;
//  I2C1_CCRH_F_S=0; //Standard mode I2C
//  I2C1_CCRH_DUTY=0; 
  I2C_CCRL=10;    //SCL高电平时间配置
  //I2C的SCK时钟设置为100KHz,则SCK周期为10us
  //因为I2C1_FREQR_FREQ=0x02,即I2C输入时钟频率为2M,周期为0.5us
  //CCR=10时,SCK的低电平时间为tlow=10*0.5us=5us,SCk高电平时间为thigh=10*0.5us=5us
  //所以CCR=10时,SCK输出频率为100KHz
  
  //----配置上升时间寄存器----
  I2C_TRISER_TRISE=1;//in standard mode, the maximum allowed SCL rise time is 1000 ns.
  //1 us / 0.5 us = 2 + 1

  I2C_CR1_PE=1;//
}



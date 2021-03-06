#include"iostm8s103f3.h"
#include"stdbool.h"
#include"stdint.h"
#include"oled.h"
#include"iic.h"
/******************************************************************************************************
*  名    称：void delay_100us(uint8_t x_us)
*  功    能：延时100us
*  入口参数：无
*  出口参数：无
*  说    明：
*  范    例：无
******************************************************************************************************/
void delay_100us(uint16_t x_us)
{
  uint8_t j;
  while(x_us--)
  {
    for(j=0;j<33;j++);//2*40个指令周期
  }
  //delay_10ms共消耗 x_ms*2*255+2*x_ms个指令周期  
  //*2*40+2*x_ms=80us+
  //16M/8/2=1M 一个指令周期为1us
}
///******************************************************************************************************
//* 功    能	：按键GPIO初始化配置
//* 入口参数	：无
//* 出口参数	：无 
//* 说    明	：
//* 编写日期    ：2016年10月21日
//* 作    者    ：茗风
//******************************************************************************************************/
void GPIO_Config(void)
{
  //PD3 LED控制引脚
  PB_DDR_DDR5 =1;//输出
  PB_CR1_C15 =1;//推挽输出
  PB_CR2_C25 =1;//输出速率10M
  
//  //PE7 LED控制引脚
//  PE_DDR_DDR7 =1;//输出
//  PE_CR1_C17 =1;//推挽输出
//  PE_CR2_C27 =1;//输出速率10M
//  
//  //配置阀门到位检测引脚PD6，PD7
//  PD_DDR_DDR6 =0;
//  PD_CR1_C16 =1;//带上拉电阻输入
//  PD_CR2_C26 =0;//使能外部中断 
//  
//  PD_DDR_DDR7 =0;
//  PD_CR1_C17 =1;//带上拉电阻输入
//  PD_CR2_C27 =0;//使能外部中断 
  
//  EXTI_CR3_PDIS =2;//PD口上升沿中断
/*00: Falling edge and low level
  01: Rising edge only
  10: Falling edge only
  11: Rising and falling edge*/  
//  EXTI_CONF_PDHIS =1;//PD[7:4] are used for EXTID interrupt generation
  
 //设置中断
 //CPU_CCR |=MASK_CPU_CCR_I1+MASK_CPU_CCR_I0;//启用硬件优先级，禁用软件优先级
}
/******************************************************************************************************
* 名  	   称：WM_Initialize()
* 功 	   能：初始化系统
* 入口    参数：无
* 出口    参数：无
* 说       明：调用各个模块的初始化配置函数，进行系统初始化
* 范       例：无
******************************************************************************************************/
void WM_Initialize(void)
{
//  GPIO_Config();
  I2C_Init();
  OLED12864_Config();
}

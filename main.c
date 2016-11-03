/*硬件连接*/
/****************************************************************************************
*开发环境:IAR for stm8 v6.5.3
*硬件平台:STM8S103F3
*功能说明:
*作    者：茗风
****************************************************************************************/
#include"global.h"
#include"iostm8s103f3.h"
#include"stdint.h"
#include"stdbool.h"
void main(void)
{ 
//  uint8_t i;
  WM_Initialize();
//  asm("rim");               //enable interrupts
  while(1)
  {
//    for(i=0;i<8;i++)
//    {
//      PB_ODR_ODR5 ^=1;
//      delay_100us(500);//50ms延时
//    }
//    PB_ODR_ODR5 =1;
//    delay_100us(2000);//100ms延时
    asm("wfi");
    //delay_100us(10000);
  }
}


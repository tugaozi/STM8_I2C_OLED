/*Ӳ������*/
/****************************************************************************************
*��������:IAR for stm8 v6.5.3
*Ӳ��ƽ̨:STM8L-DISCOVERY
*����˵��:LCD1602�����������ƣ����æ��־λ
*��    �ߣ�����
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
//      delay_100us(500);//50ms��ʱ
//    }
//    PB_ODR_ODR5 =1;
//    delay_100us(2000);//100ms��ʱ
    asm("wfi");
    //delay_100us(10000);
  }
}


#ifndef   __OLED_H
#define   __OLDE_H
extern void OLED12864_Config(void);
extern void LCD1602_Display_Number(uint8_t x,uint8_t y,uint32_t _number);
extern uint8_t OLED12864_Display_SimplifiedChinese(uint8_t x,uint8_t y,uint8_t *s,uint16_t len);
extern void OLED12864_Draw_One_Picture(void);
#endif
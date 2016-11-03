#ifndef   __IIC_H
#define   __IIC_H
#include"stdint.h"
extern void I2C_Init(void);
extern uint8_t I2C_ReadOneByteDataFromSlave(uint8_t address);
extern uint8_t I2C_WriteOneByteDataToSlave(uint8_t slave_address,uint8_t address,uint8_t dat);
extern uint8_t I2C_ReadMultiBytesFromSlave(uint8_t address,uint8_t *rxbuf,uint8_t len);
#endif
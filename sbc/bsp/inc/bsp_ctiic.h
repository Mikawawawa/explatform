#ifndef _BSP_CT_IIC_H
#define _BSP_CT_IIC_H

#include "stm32f4xx.h"

#define SET_SDA_IN()  {GPIOF->MODER&=~(3<<(2*9));GPIOF->MODER|=0<<2*9;}
#define SET_SDA_OUT() {GPIOF->MODER&=~(3<<(2*9));GPIOF->MODER|=1<<2*9;}

#define IIC_SCL					PBout(1)
#define IIC_SDA_IN			PFin(9)
#define IIC_SDA_OUT			PFout(9)

void CT_IIC_Init(void);
void CT_IIC_Start(void);
void CT_IIC_Stop(void);
void CT_IIC_Send_Byte(uint8_t byte);
uint8_t CT_IIC_Read_Byte(uint8_t ack);
uint8_t CT_IIC_Wait_Ack(void);
void CT_IIC_Ack(void);
void CT_IIC_NAck(void);

#endif








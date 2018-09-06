#include <stdio.h>
#include "bsp_ft5206.h"
#include "bsp_ctiic.h"
#include "bsp_systick.h"


const uint16_t FT5206_TPX_TBL[5] = {FT_TP1_REG, FT_TP2_REG, FT_TP3_REG, FT_TP4_REG, FT_TP5_REG};

uint8_t FT5206_WriteREG(uint16_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t no_respons;

	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_WR);
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg & 0xFF);
	CT_IIC_Wait_Ack();
	for(i = 0; i < len; i++)
	{
		CT_IIC_Send_Byte(buf[i]);
		no_respons = CT_IIC_Wait_Ack();
		if(no_respons)
		{
			break;
		}
	}
	CT_IIC_Stop();
	return no_respons;
}

void FT5206_ReadREG(uint16_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_WR);
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg & 0XFF);
	CT_IIC_Wait_Ack();
	CT_IIC_Start();
	CT_IIC_Send_Byte(FT_CMD_RD);
	CT_IIC_Wait_Ack();
	for(i = 0; i < len; i++)
	{
		buf[i] = CT_IIC_Read_Byte(1);
	}
	CT_IIC_Stop();
}

uint8_t bsp_InitFT5206(void)
{
	uint8_t temp[2];
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	CT_IIC_Init();
	FT_RST = 0;
	bsp_DelayMs(1);
	FT_RST = 1;
	bsp_DelayMs(5);
	 	
	temp[0] = 0;
	FT5206_WriteREG(FT_DEVIDE_MODE, temp, 1);
	FT5206_WriteREG(FT_ID_G_MODE, temp, 1);
	temp[0] = 22;
	FT5206_WriteREG(FT_ID_G_THGROUP, temp, 1);
	temp[0] = 12;
	FT5206_WriteREG(FT_ID_G_PERIODACTIVE,temp,1);
	
	FT5206_ReadREG(FT_ID_G_LIB_VERSION,&temp[0],2);
	if(temp[0] == 0x30 && temp[1] == 0x03)
	{
//		printf("CTP ID:%x\r\n",((u16)temp[0]<<8)+temp[1]);
		return 0;
	}
	return 1;
}

uint8_t FT5206_TouchScan(void)
{
//	uint8_t TouchStatus = 0;
//	uint8_t xyCoord[4];
//	uint16_t temp;
//	
//	/* ¶ÁÈ¡´¥ÃþµãµÄ×´Ì¬ */
//	FT5206_ReadREG(FT_REG_NUM_FINGER, &TouchStatus, 1);
//	TouchStatus &= 0x0F;
//	
//	if(TouchStatus < 6)
//	{
//		if(TouchStatus != 0)
//		{
//			FT5206_ReadREG(FT5206_TPX_TBL[0], xyCoord, 4);
//			if(*(uint32_t *)xyCoord == 0xFFFFFFFF)
//			{
//				return 0;
//			}
//			State.x = ((uint16_t)(xyCoord[0] & 0x0F) << 8) | (uint16_t)xyCoord[1];
//			State.y = ((uint16_t)(xyCoord[2] & 0x0F) << 8) | (uint16_t)xyCoord[3];
//			temp = State.x;
//			State.x = State.y;
//			State.y = temp;
//			State.Pressed = 1;
//			GUI_PID_StoreState(&State);
//			return 1;
//		}
//		else
//		{
//			if (State.Pressed)
//			{
//				State.Pressed = 0;
//			}
//			else
//			{
//				GUI_PID_StoreState(&State);
//			}
//		}
//	}
	
	
	return 0;
}

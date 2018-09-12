#ifndef __BSP_FT5206_H
#define __BSP_FT5206_H	
 
#include "stm32f4xx.h"

#define FT_RST    		PCout(13)
#define FT_INT    		PBin(1)

/* IIC ��д���� */
#define FT_CMD_WR 		0x70
#define FT_CMD_RD 		0x71
  
/* FT5206 ���ּĴ������� */
#define FT_DEVIDE_MODE 			0x00   	//FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER       0x02	//����״̬�Ĵ���

#define FT_TP1_REG 				0X03	//��һ�����������ݵ�ַ
#define FT_TP2_REG 				0X09	//�ڶ������������ݵ�ַ
#define FT_TP3_REG 				0X0F	//���������������ݵ�ַ
#define FT_TP4_REG 				0X15	//���ĸ����������ݵ�ַ
#define FT_TP5_REG 				0X1B	//��������������ݵ�ַ  
 

#define	FT_ID_G_LIB_VERSION		0xA1	//�汾		
#define FT_ID_G_MODE 			0xA4	//FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP			0x80	//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE	0x88	//����״̬�������üĴ���

#define TP_PRES_DOWN					0x80
#define TP_CATH_PRES					0x40

extern const uint16_t FT5206_TPX_TBL[5];

uint8_t bsp_InitFT5206(void);
uint8_t FT5206_WriteREG(uint16_t reg, uint8_t *buf, uint8_t len);
void FT5206_ReadREG(uint16_t reg, uint8_t *buf, uint8_t len);
uint8_t FT5206_TouchScan(void);

#endif

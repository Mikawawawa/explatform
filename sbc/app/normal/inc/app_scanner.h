#ifndef __QR_H
#define __QR_H	

#include "stm32f4xx.h"  

extern u8 readData[30];

u8 QR_On(void);//��ά��ɨ��ģ�鿪��ɨ�躯��
u8 QR_RX_Data(u8 rxDat[],char* check);  //��ά���ȡ����


#endif



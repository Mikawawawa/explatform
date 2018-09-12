#include "systask.h"

u8 k;
u8 voice_Com[4]={0xFD,0x00,0x01};  	     			//ģ��ָ��ͷ
char voice_Dat[100];            					//�������� ���25�������ַ�

const u8 voiceWelcome[] = "��ӭʹ�á����������繤����ʵ��̨";

const u8 voiceShowQrCode[] = "��ɨ�����Ķ�ά��";

const u8 voiceSignInSuccess[] = "ǩ���ɹ�";

const u8 voiceSignInFail[] = "ǩ��ʧ��";

const u8 voiceSignInOverTime[] = "ǩ���ϴ���ʱ";

const u8 voiceIdentifySuccess[] = "�����֤�ɹ�";
	
const u8 voiceIdentifyFail[] = "�����֤ʧ��";

const u8 voiceIdentifyOverTime[] = "�����֤��ʱ";

const u8 voiceMarkLoadSuccess[] = "�ɼ��ϴ��ɹ�";

const u8 voiceMarkLoadFail[] = "�ɼ��ϴ�ʧ��";

const u8 voiceMarkLoadOverTime[] = "�ɼ��ϴ���ʱ";
	
const u8 voiceEndExp[] = "����ʵ�鵽�˽���";

/******************************************
�ж��ϵ��ʼ���Ƿ�ɹ�����
����ֵ��0��ʧ��
		1���ɹ�
********************************************/
u8 voice_Init_check(void)
{
	u8 i=0;
	if(uart.uart_5->rx_status&0x8000)   //�ȴ�����ģ�鷵����Ϣ
	{
		if(uart.uart_5->pRx_buffer[0]==init_succeed)
		{
			i=1;
		}
		uart.uart_5->rx_status=0;
	}
	return i;
}

/*********************************************
���������
���룺	com:����
		res:��Ӧ
����ֵ��0:��Ӧ��ʱ;
		1:��Ӧ��ȷ;
		����:��Ӧ������������Ӧ
**********************************************/
u8 voice_Send_Command(u8 com,u8 res)
{
	u8 j=0;
	u8 i=0;
	u8 waittime=30;
	uart.uart_5->rx_status=0;
	voice_Com[3]=com;		//�ϲ�����
	for(j=0;j<4;j++)		//ѭ����������
	{
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������
		USART_SendData(UART5,voice_Com[j]);  
	}
	while(--waittime)
	{
		bsp_delay_ms(10);
		if(uart.uart_5->rx_status&0x8000)   //�ȴ�����ģ�鷵����Ϣ
		{
			if(uart.uart_5->pRx_buffer[0]!=res)
			{
				i=uart.uart_5->pRx_buffer[0];
			}
			else
			{
				i=1;
			}
			uart.uart_5->rx_status=0;
			break;
		}
	}	
	return i;          
}

/****************************************
�������ݺ���
���룺	len:�ַ������ȣ�ת��Ϊ�ֽڣ�
		data:����
����ֵ��0:�ϳɳ�ʱ
		1:�ϳɳɹ�
*****************************************/
u8 voice_Send_Data(u16 len,const char* data)
{
	u8 i = 0;
	u8 waittime=10;
	voice_Dat[0]=0xfd;
	voice_Dat[1]=len>>8;
	voice_Dat[2]=len;
	voice_Dat[3]=0x01;
	voice_Dat[4]=0x00;
//	while(voice_Send_Command(state_check,free_now)!=1&&waittime>0)		//�ȴ�ģ�����
//	{
//		bsp_delay_ms(10);
//		waittime--;
//	}
	waittime=10;
	sprintf(&voice_Dat[5],data);	//�����ı�����������ֵ���
	uart.oop(uart.uart_5).write_raw((u8 *)voice_Dat,len+5);	
	while(--waittime)
	{
		bsp_delay_ms(10);
		if(uart.uart_5->rx_status&0x8000)   //�ȴ�����ģ�鷵����Ϣ
		{
			if(uart.uart_5->pRx_buffer[0]==free_now)
			{
				i=1;
			}
			uart.uart_5->rx_status=0;
			break;
		}
	}	
	return i;
}

u8 voiceDispString(const u8* str)
{
	if(app_state.voice_state == STATE_VOICE_ON)
	{
		if(voice_Send_Data(strlen((const char *)str)+2, (const char *)str))
			return 1;
		else
			return 0;
	}
	else 
		return 1;
}

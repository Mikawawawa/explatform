#include "ep_app.h"

u8 QR_On_key[9]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};  //����ɨ��ָ��
u8 QR_On_res[7]={0x02,0x00,0x00,0x01,0x00,0x33,0x31};            //ģ�鷵����Ϣ

//��ά��ɨ��ģ�鿪��ɨ�躯��
//����ֵ��0,�����ɹ�;1,�������ݴ���;2,���ճ�ʱ
u8 QR_On(void)
{
	u8 res=0;
	u8 waittime=30;
	u8 strx=0;
	uart.uart_4->rx_status=0;
	uart.oop(uart.uart_4).write_raw(QR_On_key,10);
//	for(j=0;j<9;j++)//ѭ����������
//	{
//		 while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������
//		USART_SendData(UART4,QR_On_key[j]);  
//	}
	while(--waittime)
	{
		bsp_delay_ms(10);
		if(uart.uart_4->rx_status&0x8000)   //�ȴ�ɨ��ģ�鷵����Ϣ
		{
			strx=memcmp(uart.uart_4->pRx_buffer,QR_On_res,7);
			if(strx!=0)          
			{
				res=1;        //����ʧ��
				//printf("����ʧ��\r\n");
			}
			else
			{
				//printf("�����ɹ�\r\n");
			}
			uart.uart_4->rx_status=0;
			break;
		}
	}
	if(waittime==0)
	{
		res=2;           //���ճ�ʱ
	}		
	return res;          
}


//��ά���ȡ����
//rxDat:�������飻check:�����Ӧ
//����ֵ��1��   ��Ӧƥ�䣻
//		  0��   ��Ӧ��ƥ����ȡʧ��
//		  0xff���ȴ�ɨ�賬ʱ
u8 QR_RX_Data(u8 rxDat[],char* check)
{
	u8 res,count = 0;
	char *strx = 0;
	uart.uart_4->rx_status = 0;
	while(!(uart.uart_4->rx_status&0x8000) && count <= 5)   //�ȴ�ɨ��ģ�鷵����Ϣ
	{
		bsp_delay_ms(1000);
		count ++;
	}
	if(count >= 5)
	{
		count = 0;
		return 0xff;
	}
	if(uart.uart_4->rx_status&0x8000)   
	{
		uart.uart_4->pRx_buffer[uart.uart_4->rx_status&0X3FFF]=0;//��ӽ�����
		strx=strstr((const char*)uart.uart_4->pRx_buffer,"FAIL");
		if(strx)
		{
			uart.uart_4->rx_status=0;           //��ȡʧ��          
		}
		else                          //��ȡ�ɹ�
		{
			uart.uart_4->rx_status=0; 
			strx=strstr((const char*)uart.uart_4->pRx_buffer,check);
			if(strx)
			{
				strcpy((char*)rxDat,strx+4);           //��ӦΪsid:��tid: ���ȡ��󲿷�����
				rxDat[strlen(strx+4)-1] = 0;		   //�����β0X0D������Ӱ�����HTTP����
//				printf("%s\r\n",uart.uart_4->pRx_buffer);
				res=1;
			}
		}
	}
	return res;
}


#include "ep_app.h"

u8 nLink = 1;                             //nLink����״̬Ĭ�ϸߵ�ƽ

const u8* wifista_ip="101.132.116.211";   //���ӵķ�����IP��ַ
const u8* portnum="80";	

void usr_c322_at_response(u8 mode)
{
	if(uart.uart_3->rx_status&0X8000)		//���յ�һ��������
	{ 
		uart.uart_3->pRx_buffer[uart.uart_3->rx_status&0X3FFF]=0;//��ӽ�����
		//printf("%s",uart.uart_3->pRx_buffer);	//���͵�����
		uart.oop(uart.uart_1).write("%s",uart.uart_3->pRx_buffer);
		if(mode)uart.uart_3->rx_status=0;
	} 
}

//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* usr_c322_check_cmd(u8 *str)
{
	char *strx=NULL;
	if(uart.uart_3->rx_status&0X8000)		//���յ�һ��������
	{ 
		uart.uart_3->pRx_buffer[uart.uart_3->rx_status&0X3FFF]=0;//��ӽ�����
		strx=strstr((const char*)uart.uart_3->pRx_buffer,(const char*)str);
	} 
	return (u8*)strx;
}

//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 usr_c322_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	uart.uart_3->rx_status=0;
	uart.oop(uart.uart_3).write("%s",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			bsp_delay_ms(10);
			if(uart.uart_3->rx_status&0X8000)//���յ��ڴ���Ӧ����
			{
				usr_c322_at_response(0);   //��ӡATָ�����Ϣ
				if(usr_c322_check_cmd(ack))
				{
					break;//�õ���Ч���� 
				}
				uart.uart_3->rx_status=0;
			}
		}
		if(waittime==0)res=1; 
	}
	return res;
} 

//�˳�͸��ģʽ
//����ֵ:1,�˳��ɹ�;
//       0,�˳�ʧ��
u8 usr_c322_quit_trans(void)
{
	u8  tem;  
	tem = usr_c322_send_cmd("+++","a",20);
	if(!tem)
	{
		tem = usr_c322_send_cmd("a","+OK",20);
		if(tem)
		{
			//printf("Quit trans second error\r\n");
			return 0;
		}
	}
	else
	{
		tem = strcmp((const char*)uart.uart_3->pRx_buffer,"+++");
		if(tem)
		{
			//printf("Quit trans first error\r\n");
			return 0;
		}
		else
			usr_c322_send_cmd("\r\n","",20);
	}
	return 1;
}

void usr_c322_led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12; //nready,nlink��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	GPIO_SetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12);
}

u8 usr_c322_waiting_restart(void)
{
	u8 i = 0;
	while(!nLink && i < 3)  		   //�ȴ�WIFI������������
	{
		bsp_delay_ms(1000);
		uart.oop(uart.uart_1).write_line("1");
		i ++;
	}
	
	i = 0;
	while(nLink && i < 10)  		   //�ȴ�WIFI������������
	{
		bsp_delay_ms(1000);
		uart.oop(uart.uart_1).write_line("2");
		i ++;
	}
	if(0 == i)
	{
//		printf("�޷����ӵ��������\r\n");
		return 0;
	}
	return 1;
}

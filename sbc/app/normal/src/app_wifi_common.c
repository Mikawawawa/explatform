#include "ep_app.h"

u8 nLink = 1;                             //nLink引脚状态默认高电平

const u8* wifista_ip="101.132.116.211";   //连接的服务器IP地址
const u8* portnum="80";	

void usr_c322_at_response(u8 mode)
{
	if(uart.uart_3->rx_status&0X8000)		//接收到一次数据了
	{ 
		uart.uart_3->pRx_buffer[uart.uart_3->rx_status&0X3FFF]=0;//添加结束符
		//printf("%s",uart.uart_3->pRx_buffer);	//发送到串口
		uart.oop(uart.uart_1).write("%s",uart.uart_3->pRx_buffer);
		if(mode)uart.uart_3->rx_status=0;
	} 
}

//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//    其他,期待应答结果的位置(str的位置)
u8* usr_c322_check_cmd(u8 *str)
{
	char *strx=NULL;
	if(uart.uart_3->rx_status&0X8000)		//接收到一次数据了
	{ 
		uart.uart_3->pRx_buffer[uart.uart_3->rx_status&0X3FFF]=0;//添加结束符
		strx=strstr((const char*)uart.uart_3->pRx_buffer,(const char*)str);
	} 
	return (u8*)strx;
}

//cmd:发送的命令字符串
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 usr_c322_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	uart.uart_3->rx_status=0;
	uart.oop(uart.uart_3).write("%s",cmd);	//发送命令
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{
			bsp_delay_ms(10);
			if(uart.uart_3->rx_status&0X8000)//接收到期待的应答结果
			{
				usr_c322_at_response(0);   //打印AT指令返回信息
				if(usr_c322_check_cmd(ack))
				{
					break;//得到有效数据 
				}
				uart.uart_3->rx_status=0;
			}
		}
		if(waittime==0)res=1; 
	}
	return res;
} 

//退出透传模式
//返回值:1,退出成功;
//       0,退出失败
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

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12; //nready,nlink对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	GPIO_SetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12);
}

u8 usr_c322_waiting_restart(void)
{
	u8 i = 0;
	while(!nLink && i < 3)  		   //等待WIFI连接引脚拉高
	{
		bsp_delay_ms(1000);
		uart.oop(uart.uart_1).write_line("1");
		i ++;
	}
	
	i = 0;
	while(nLink && i < 10)  		   //等待WIFI连接引脚拉低
	{
		bsp_delay_ms(1000);
		uart.oop(uart.uart_1).write_line("2");
		i ++;
	}
	if(0 == i)
	{
//		printf("无法连接到这个网络\r\n");
		return 0;
	}
	return 1;
}

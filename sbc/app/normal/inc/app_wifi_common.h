#ifndef __COMMON_H__
#define __COMMON_H__	 

#include "bsp.h"

#define Nready 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) //PA11
#define Nlink		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) //PA12

extern u8 nLink;
extern u8 AppointmentInfo[2][10];
extern u8 macAddress[16];

void usr_c322_led_init(void);
void usr_c322_at_response(u8 mode);
u8* usr_c322_check_cmd(u8 *str);
u8 usr_c322_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8 usr_c322_quit_trans(void);
u8 usr_c322_waiting_restart(void);

u8 usr_c322_init(void);	        									 //初始化WIFI模块函数
u8 usr_c322_hdu_login(void);                                         //登录函数
u8 usr_c322_wifista_connect(u8* wifista_ssid,u8* wifista_password);  //更改WIFI函数
u8 usr_c322_wifista_HTTP_request(u8* request,u8* parameter);         //发送HTTP请求函数
u8 usr_c322_wifista_HTTP_appointment(u8* room,u8* table);            //通过HTTP请求获取预约信息函数
void usr_c322_wifista_parse(void);                                       //解析WIFI扫描函数

//用户配置参数
extern const u8* portnum;			//连接端口
extern const u8* wifista_ip;        //连接的服务器IP地址

extern u8 Wifi_List[20][20];
#endif






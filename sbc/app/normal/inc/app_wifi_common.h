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

u8 usr_c322_init(void);	        									 //��ʼ��WIFIģ�麯��
u8 usr_c322_hdu_login(void);                                         //��¼����
u8 usr_c322_wifista_connect(u8* wifista_ssid,u8* wifista_password);  //����WIFI����
u8 usr_c322_wifista_HTTP_request(u8* request,u8* parameter);         //����HTTP������
u8 usr_c322_wifista_HTTP_appointment(u8* room,u8* table);            //ͨ��HTTP�����ȡԤԼ��Ϣ����
void usr_c322_wifista_parse(void);                                       //����WIFIɨ�躯��

//�û����ò���
extern const u8* portnum;			//���Ӷ˿�
extern const u8* wifista_ip;        //���ӵķ�����IP��ַ

extern u8 Wifi_List[20][20];
#endif






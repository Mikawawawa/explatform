#ifndef __VOICE_H
#define __VOICE_H

#include "stm32f4xx.h"

//�ϳ�ָ��
#define 	state_check					(u8)0x21		//״̬���
#define 	power_saving_mode			(u8)0x88		//ʡ��ģʽ
#define 	wake_up						(u8)0xff		//����оƬ
#define 	stop_combine				(u8)0x02		//ֹͣ�ϳ�
#define 	pause_combine				(u8)0x03		//��ͣ�ϳ�
#define 	start_over_combine			(u8)0x04		//�ָ��ϳ�

//��Ӧ
#define		init_succeed				(u8)0x4a		//��ʼ���ɹ�
#define		receive_right_com			(u8)0x41		//�յ���ȷָ��
#define		receive_wrong_com			(u8)0x45		//�յ�����ָ��
#define		busy_now					(u8)0x4e		//��ǰ��æ
#define		free_now					(u8)0x4f		//��ǰ����

extern const u8 voiceSetting[];

extern const u8 voiceWelcome[];

extern const u8 voiceShowQrCode[];

extern const u8 voiceSignInSuccess[];

extern const u8 voiceSignInFail[];

extern const u8 voiceSignInOverTime[];

extern const u8 voiceIdentifySuccess[];
	
extern const u8 voiceIdentifyFail[];

extern const u8 voiceIdentifyOverTime[];

extern const u8 voiceMarkLoadSuccess[];

extern const u8 voiceMarkLoadFail[];

extern const u8 voiceMarkLoadOverTime[];
	
extern const u8 voiceEndExp[];

u8 voice_Init_check(void);
u8 voice_Send_Command(u8 com,u8 res);
u8 voice_Send_Data(u16 len,const char* data);
u8 voiceDispString(const u8* str);

#endif


#ifndef __VOICE_H
#define __VOICE_H

#include "stm32f4xx.h"

//合成指令
#define 	state_check					(u8)0x21		//状态检测
#define 	power_saving_mode			(u8)0x88		//省电模式
#define 	wake_up						(u8)0xff		//唤醒芯片
#define 	stop_combine				(u8)0x02		//停止合成
#define 	pause_combine				(u8)0x03		//暂停合成
#define 	start_over_combine			(u8)0x04		//恢复合成

//响应
#define		init_succeed				(u8)0x4a		//初始化成功
#define		receive_right_com			(u8)0x41		//收到正确指令
#define		receive_wrong_com			(u8)0x45		//收到错误指令
#define		busy_now					(u8)0x4e		//当前繁忙
#define		free_now					(u8)0x4f		//当前空闲

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


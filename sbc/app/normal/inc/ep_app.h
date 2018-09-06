#ifndef __EP_APP_H
#define __EP_APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "bsp.h"

#include "app_wifi_common.h"
#include "app_scanner.h"	
#include "app_voice.h"
#include "app_localdb.h"

typedef struct{
	u16  VolumeSwitch;
	u16  VolumeLevel;
	u8*   WifiSSID;
	u8*   WifiPassword;
} SettingData;

typedef struct
{
	u8   MacAddress[16];
	u16  VolumeSwitch;
	u16  VolumeLevel;
}HistorySettingData;

extern u8 Wifi_List[20][20];
extern SettingData NowData;
extern HistorySettingData HistData;

#endif


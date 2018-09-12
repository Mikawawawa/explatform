#ifndef __SYSTASK
#define __SYSTASK

#include "ep_app.h"
#include "uiBuild.h"

typedef enum
{
	
	STATE_RUNNING_IDLE								= 0x00,
	STATE_RUNNING_WIFI_CONNECTED 					= 0x80,
	
	STATE_RUNNING_STUDENT	 						= STATE_RUNNING_WIFI_CONNECTED | 0x40,
	STATE_RUNNING_TEACHER_IDENTIFY 					= STATE_RUNNING_WIFI_CONNECTED | 0x20,
	STATE_RUNNING_TEACHER_MARK	 					= STATE_RUNNING_WIFI_CONNECTED | 0x10,
	STATE_RUNNING_PRIVILIGED						= STATE_RUNNING_WIFI_CONNECTED | 0x08,
	
	STATE_RUNNING_STUDENT_WITHOUT_WIFI				= 0x40,
	STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI		= 0x20,
	STATE_RUNNING_TEACHER_MARK_WITHOUT_WIFI			= 0x10,
	STATE_RUNNING_PRIVILIGED_WITHOUT_WIFI			= 0x08
	
}RUNNING_STATE;

typedef enum
{
	
	STATE_WIFI_WAIT						= 0x00,
	STATE_WIFI_SCAN,				
	STATE_WIFI_CONNECTING,			
	STATE_WIFI_HTTP_REQUESTING,	
	STATE_WIFI_HTTP_REQUEST_OVERTIME,
	STATE_WIFI_CONNECTED,
	STATE_WIFI_HTTP_REQUEST_RIGHT,
	STATE_WIFI_HTTP_REQUEST_WRONG,
	STATE_WIFI_ERROR_COUNTING, 	 	   
	STATE_WIFI_CONNECT_ERROR			= STATE_WIFI_CONNECTING | 0x80,   
	STATE_WIFI_HTTP_REQUEST_ERROR		= STATE_WIFI_HTTP_REQUESTING | 0x80,  
	
}WIFI_STATE;

typedef enum
{
	
	STATE_QR_SCANNER_WAIT				= 0x00,
	STATE_QR_SCANNER_ON,
	STATE_QR_SCANNER_SCANNING,
	STATE_QR_SCANNER_SCAN_OVERTIME,
	STATE_QR_SCANNER_ERROR_COUNTING,
	STATE_QR_SCANNER_ON_ERROR			= STATE_QR_SCANNER_ON | 0x80,
	STATE_QR_SCANNER_SCAN_ERROR			= STATE_QR_SCANNER_SCAN_OVERTIME | 0x80
	
}QR_SCANNER_STATE;

typedef enum
{
	
	STATE_VOICE_ON				= 0x00,
	STATE_VOICE_OFF				= 0xff
	
}VOICE_STATE;

typedef enum
{
	
	STATE_STANDBY_ON				= 0x00,
	STATE_STANDBY_OFF			
	
}STANDBY_STATE;

typedef struct {

	WIFI_STATE			current_state;
	WIFI_STATE			next_state;
	
}wifiStateStructTypedef;

typedef struct {

	QR_SCANNER_STATE			current_state;
	QR_SCANNER_STATE			next_state;
	
}QRScannerStateStructTypedef;

typedef struct {
	
	VOICE_STATE							voice_state;
	STANDBY_STATE						standby_state;
	
	QRScannerStateStructTypedef			scanner_state;							
	wifiStateStructTypedef				wifi_state;

}app_state_type_struct;

enum ulWifiTaskNotifiedValue
{
	bitWifiScan 				= 0x00000001UL,
	bitWifiConnecting 			= 0x00000002UL,
	bitWifiHttpRequesting 		= 0x00000004UL,
	bitWifiConnected		    = 0x00000008UL,
	bitWifiConnectError		    = 0x00000010UL,
	bitWifiHttpRequestRight     = 0x00000020UL,
	bitWifiHttpRequestWrong     = 0x00000040UL,
	bitWifiHttpRequestError	    = 0x00000080UL,
};

enum ulQRScannerTaskNotifiedValue
{
	bitQRScannerOn 				= 0x00000100UL,
	bitQRScannerScanRight		= 0x00000200UL,
	bitQRScannerOnError 		= 0x00000400UL,
	bitQRScannerScanOvertime    = 0x00000800UL,
	bitQRScannerScanError		= 0x00001000UL,
};

enum ulInitTaskNotifiedValue
{
	bitFlashReadID				= 0x00002000UL,
	bitFlashReadFont 			= 0x00004000UL,
	bitWifiInit		 			= 0x00008000UL,
	bitFatfsInit	 			= 0x00010000UL,
	bitVoiceInit	 			= 0x00020000UL,
	bitCompeletlyInit	 		= 0x00040000UL,
};

typedef struct {
	void		(*init0)(void);
}system_struct_type;

extern u8 studentMark[2];

extern system_struct_type os; 
extern app_state_type_struct app_state;
extern RUNNING_STATE running_state;

extern TaskHandle_t xHandleTaskMain;
extern TaskHandle_t xHandleTaskWifi;
extern TaskHandle_t xHandleTaskSettingwin;
extern TaskHandle_t xHandleTaskQRScanner;
extern TaskHandle_t xHandleTaskStudentwin;
extern TaskHandle_t xHandleTaskTeacherwin;
extern TaskHandle_t xHandleTaskWifiConnectwin;
extern TaskHandle_t xHandleTaskTimer;
extern TaskHandle_t xHandleTaskConsole;
extern TaskHandle_t xHandleTaskInit;

#endif

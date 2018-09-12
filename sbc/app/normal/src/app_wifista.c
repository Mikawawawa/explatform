#include "ep_app.h"

u8 macAddress[16];
u8 AppointmentInfo[2][10];

SettingData NowData;
HistorySettingData HistData;
u8 Wifi_List[20][20];

//У԰����¼����
//����ֵ��0����¼�ɹ�
//		  1����¼ʧ��
u8 usr_c322_hdu_login(void)
{
	u8 tem = 0;
	u8 res = 0;
	usr_c322_send_cmd("AT+SOCKA=TCPC,2.2.2.2,80\r\n","+OK",20);
	usr_c322_send_cmd("AT+Z\r\n","+OK",20);
	usr_c322_waiting_restart();
	usr_c322_quit_trans();
	bsp_delay_ms(1000);	        		 //�ȴ����ӵ�������
	tem = usr_c322_send_cmd("AT+SOCKLKA\r\n","DISCONNECTED",20);
	if(tem)
	{
		usr_c322_send_cmd("AT+ENTM\r\n","+OK",20);
		usr_c322_send_cmd("POST /ac_portal/login.php HTTP/1.1\r\n","",20);
		usr_c322_send_cmd("Host: 2.2.2.2\r\n","",20);
		usr_c322_send_cmd("Connection: keep-alive\r\n","",20);
		usr_c322_send_cmd("Content-Length: 61\r\n","",20);
		usr_c322_send_cmd("Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n","",20);
		usr_c322_send_cmd("\r\n","",20);
		res = usr_c322_send_cmd("opr=pwdLogin&userName=16041538&pwd=990404GZXWAN&rememberPwd=0\r\n","success",20);
		usr_c322_quit_trans();
	}
	else;
	return res;
}

//WIFI��ʼ������
//����ֵ��0��
u8 usr_c322_init(void)
{
	u8 i = 0;
	u8 p[75];
	while(Nready && i < 3)  		//�ȴ�Nready��������
	{
		bsp_delay_ms(1000);	
		i ++;
	}
	memset(p,0,sizeof(p));
	usr_c322_quit_trans();
	
	usr_c322_send_cmd("AT+MAC\r\n","+OK",20);
	strcpy((char*)macAddress, (const char*)usr_c322_check_cmd("=")+1);        //��ȡMAC��ַ
	macAddress[12] = '\0';
	strcpy((char*)HistData.MacAddress, (const char*)macAddress);        //��ȡMAC��ַ
	
	usr_c322_send_cmd("AT+WMODE=STA\r\n","+OK",20);
	usr_c322_send_cmd("AT+WKMOD=TRANS\r\n","+OK",20);
	usr_c322_send_cmd("AT+Z\r\n","+OK",20);
	i = 0;
	while(!Nready && i < 3)  		//�ȴ�Nready��������
	{
		bsp_delay_ms(1000);	
		i ++;
	}
	i = 0;
	while(Nready && i < 3)  		//�ȴ�Nready��������
	{
		bsp_delay_ms(1000);	
		i ++;
	}
	if(0 == i)
		return 0;
	return 1;
}

//WIFI���Ӻ���
//����ֵ:1,���ӳɹ�;
//       0,����ʧ��
u8 usr_c322_wifista_connect(u8* wifista_ssid,u8* wifista_password)
{
//	u8 i = 3;
	u8 p[75];
	usr_c322_quit_trans();
	memset(p,0,sizeof(p));
	
	sprintf((char*)p,"AT+WSTA=%s,%s\r\n",wifista_ssid,wifista_password);
	usr_c322_send_cmd(p,"+OK",20);
	
//	while(usr_c322_hdu_login() && i --);
	
	memset(p,0,sizeof(p));
	sprintf((char*)p,"AT+SOCKA=TCPC,%s,%s\r\n",wifista_ip,portnum);
	usr_c322_send_cmd(p,"+OK",20);
	usr_c322_send_cmd("AT+Z\r\n","+OK",20);
	
	if(!usr_c322_waiting_restart())
		return 0;
	bsp_delay_ms(1000);	   			//�ȴ����ӵ�������
	return 1;
}

//����HTTP������
//����ֵ��0��1��ûͨ����ͨ����2������ʧ��
u8 usr_c322_wifista_HTTP_request(u8* request,u8* parameter)               
{
	u8 *strx=0;
	u8 status=2;
	u8 p[75];
	if(!Nlink)
	{
		memset(p,0,sizeof(p));
		sprintf((char*)p,"GET /api/%s/?%s HTTP/1.1\r\n",request,parameter);    //����Ŀ��TCP������
		if(!usr_c322_send_cmd(p,"+ERR=-1",20))   
		{
			usr_c322_send_cmd("AT+ENTM\r\n","+OK",20);
			usr_c322_send_cmd(p,"",0);
		}
		usr_c322_send_cmd("Host: zx.mcfhq.com\r\n","",0);
		usr_c322_send_cmd("Connection: keep-alive\r\n","",0);
		usr_c322_send_cmd("\r\n","status",200);                  //��������ͷ����������
		strx=usr_c322_check_cmd("status");  //�ڶ�λ��ָ���ַ���֮ǰ���������㴮�ڽ��ձ�־�Ĵ����������޷���λ
		if(strx)
		{
			status=*(strx+7)-'0';                 //ȷ������ֵλ�� ȡ�÷���ֵ
			uart.uart_3->rx_status=0;
		}
		else
		{
			uart.uart_3->rx_status=0;
			status=2;
		}
	}
	return status;
}

//ͨ��HTTP�����ȡԤԼ��Ϣ����
//����ֵ��0����ȡʧ��
//		  1����ȡ�ɹ�
u8 usr_c322_wifista_HTTP_appointment(u8* room,u8* table)                 
{
	u8* appointID = NULL;
	u8* appointName = NULL;
	u8 i = 0;
	u8 p[75];
	if(!Nlink)
	{
		memset(p,0,sizeof(p));
		sprintf((char*)p,"GET /api/appointment/?room=%s&table=%s&mac=%s HTTP/1.1\r\n",room,table,macAddress);    //����Ŀ��TCP������
		if(!usr_c322_send_cmd(p,"+ERR=-1",20))              //��ʼ����HTTP����
		{
			usr_c322_send_cmd("AT+ENTM\r\n","+OK",20);
			usr_c322_send_cmd(p,"",0);
		}                      
		memset(p,0,sizeof(p));
		usr_c322_send_cmd("Host: zx.mcfhq.com\r\n","",0);
		usr_c322_send_cmd("Connection: keep-alive\r\n","",0);
		usr_c322_send_cmd("\r\n","\"sid\"",200);                  //��������ͷ����������
		appointID=usr_c322_check_cmd("\"sid\""); //�ڶ�λ��ָ���ַ���֮ǰ���������㴮�ڽ��ձ�־�Ĵ����������޷���λ
		if(appointID)
		{
			appointID+=6;      //��λ��ԤԼ��ѧ��
			for(i=0; i<10 && appointID[i]!= '"'; i++)
				AppointmentInfo[0][i] = appointID[i];
		}
		
		else
		{
			appointID=NULL;
			uart.uart_3->rx_status=0;
			return 0;
		}
		
		appointName=usr_c322_check_cmd("name"); //�ڶ�λ��ָ���ַ���֮ǰ���������㴮�ڽ��ձ�־�Ĵ����������޷���λ
		if(appointName)
		{
			appointName+=7;      //��λ��ԤԼ��ѧ��
			uart.uart_3->rx_status=0;
			for(i=0; i<10 && appointName[i]!= '\"'; i++)
				AppointmentInfo[1][i] = appointName[i];
		}
		
		else
		{
			appointName=NULL;
			uart.uart_3->rx_status=0;
			return 0;
		}
		return 1;
	}
	else
		return 0;
}

void usr_c322_wifista_parse()
{
	u8 times;
	u8 *str = NULL;
	u8 WifiNameIndex = 1;
	u8 WifiNumber = 0;
	str = usr_c322_check_cmd("INDICATOR")+9;
	
	while('\r' != *str)
	{
		if('\n' == *str)
		{
			str += 2;
			while(',' != *str && WifiNameIndex <20)
			{
				Wifi_List[WifiNumber][WifiNameIndex] = *str;
				str ++;
				WifiNameIndex ++;
			}
			str ++;
			while(',' != *str)
				str ++;
			str ++;
			if('O' != *str)							//�жϼ��ܷ�ʽ
				Wifi_List[WifiNumber][0] = '1';     //����
			else
				Wifi_List[WifiNumber][0] = '0';     //OPEN��������
			
			for(times=0;times<WifiNumber;times++)						//�޳���ͬ��WIFI
			{
				if(!strcmp((const char *)&Wifi_List[WifiNumber][1],(const char *)&Wifi_List[times][1]))
				{
					memset(Wifi_List[WifiNumber],0,sizeof(Wifi_List[WifiNumber]));
					WifiNumber --;
				}
			}
			
			WifiNumber ++;
			WifiNameIndex = 1;
		}
		if(WifiNumber >20)
			return;
		str ++;
	}
}


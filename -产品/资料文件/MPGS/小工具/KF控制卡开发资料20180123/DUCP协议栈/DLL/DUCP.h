/*
****************************************************************************************************
*                                                DUCP
*                      				Displayer universal control protocal
*                                      	   Master Head File
*
*                          			(c) Copyright 2016-2017, KF 
*                                        All Rights Reserved
*
* File : DUCP.h
* By   : Lyon 
* Date : 2016-1-1
* Email: yangzhonglai@163.com
****************************************************************************************************
*/
#ifndef _DUCP_H_
#define _DUCP_H_

#define DUCP_PATH_LEN_MAX		(125)


#define DUCP_FM_READ			(0X01)
#define DUCP_FM_WRITE			(0X02)
#define DUCP_FM_OPEN_ALWAYS		(0X10)
#define DUCP_FM_FLLOW_PATH		(0X80)


#define SEND_MSG_OVERTIME_DEF		(100)
#define READ_MSG_OVERTIME_DEF		(100)


#define DUCP_TTS_PLAY_OPT_A			(0x00)	/*��ӵ��������е��ǲ���ʼ����*/
#define DUCP_TTS_PLAY_OPT_AS		(0x01)	/*��ӵ��������в��ҿ�ʼ����*/
#define DUCP_TTS_PLAY_OPT_CAS		(0x02)	/*��������У�����������������У�Ȼ��ʼ����*/

/*��������*/
#define DUCP_ERR_NONE				(0x00) /*�޴���*/
typedef uint8_t DUCP_ERR_T;

/*-------------------------UDCPָ�----------------------------*/
#define DUCP_CMD_SYS_BASE		(0)
#define DUCP_CMD_FM_BASE		(0X20)
#define DUCP_CMD_TTS_BASE		(0X30)
#define DUCP_CMD_2D_BASE		(0X38)
#define DUCP_CMD_WM_BASE		(0X50)
#define DUCP_CMD_TWIN_BASE		(0X60)
#define DUCP_CMD_PIC_BASE		(0X80)

typedef enum {
			/*--------------------ϵͳ����------------------------------*/
			DUCP_CMD_SYS_CONNECT = DUCP_CMD_SYS_BASE, /*0��¼������UDCP������ OK*/		
			DUCP_CMD_SYS_SYN_PN,			/*1ͬ�������� OK*/		
			DUCP_CMD_SYS_SET_PASSWAORD,		/*2�޸ĵ�¼���� NOTEST*/
			DUCP_CMD_SYS_GET_PASSWAORD,		/*3��ȡ��¼���� NOTEST*/
			DUCP_CMD_SYS_GET_FIRMWARE,		/*4��ȡ�̼���ϢOK*/
			DUCP_CMD_SYS_UPTIME,			/*5����ʱ��OK*/
			DUCP_CMD_SYS_RESET,				/*6����ϵͳ OK*/

			DUCP_CMD_SYS_SET_ADDR,			/*7����485��ַ OK*/
			DUCP_CMD_SYS_SET_IP,			/*8����IP��ַ OK*/
			DUCP_CMD_SYS_SET_PORT,			/*9���ö˿� OK*/
			DUCP_CMD_SYS_SET_BAUD,			/*10���ò�����OK*/
			DUCP_CMD_SYS_SET_SCAN_FRE,		/*11����ɨ��Ƶ��OK*/
			DUCP_CMD_SYS_SET_LIGHT,	 		/*12��������OK*/
			DUCP_CMD_SYS_SET_VOL,		 	/*13��������OK*/
			
			DUCP_CMD_SYS_CFG_IO,			/*14����IO�ڹ���OK*/
			DUCP_CMD_SYS_SET_IO,			/*15����IO��״̬OK*/
			DUCP_CMD_SYS_READ_IO,			/*16��ȡIO��״̬OK*/

			DUCP_CMD_SYS_SET_DRV,			/*17����LED����OK*/
			DUCP_CMD_SYS_SET_OEP,			/*18����OE����OK*/
			DUCP_CMD_SYS_SET_DP,			/*19�������ݼ���OK*/
			DUCP_CMD_SYS_SET_LE,			/*20����LE�ź���ʱOK*/
			DUCP_CMD_SYS_SET_GW_AND_MASK,	/*21�������غ�����OK*/
			DUCP_CMD_SYS_SET_SAF_MODE,		/*22���밲ȫģʽOK*/
			DUCP_CMD_SYS_CLIC,				/*23Passport OK*/
			DUCP_CMD_SYS_SET_DIS_SIZE,		/*24������ʾ�ߴ�OK*/
			DUCP_CMD_SYS_SET_XYMIR,			/*25������ʾ����OK*/
			DUCP_CMD_SYS_SET_485MODE,		/*26����485����ģʽOK*/
			DUCP_CMD_SYS_GET_ALL,			/*27��ȡ���в���OK*/
			DUCP_CMD_SYS_SET_ALL,			/*28�������в���OK*/
			DUCP_CMD_SYS_SET_TTSEN,			/*29ʹ�ܲ��������ı�OK*/
			DUCP_CMD_SYS_FACTORY,			/*30�ָ���������*/
			DUCP_CMD_SYS_SET_OFFLINE,		/*31��������ģʽ*/
			
			/*--------------------�ļ�����------------------------------*/
			DUCP_CMD_FM_MOUNT = DUCP_CMD_FM_BASE,/*����Ŀ¼ INVOLID*/
			DUCP_CMD_FM_OPEN,				/*�򿪻򴴽��ļ� INVOLID*/
			DUCP_CMD_FM_SEEK,				/*�����ļ���дλ�� INVOLID*/
			DUCP_CMD_FM_WRITE,				/*д�ļ� INVOLID*/
			DUCP_CMD_FM_READ,				/*���ļ� INVOLID*/
			DUCP_CMD_FM_SYNBUFF,			/*ͬ���ļ����� INVOLID*/
			DUCP_CMD_FM_COLOSE,				/*�ر��ļ� INVOLID*/
			DUCP_CMD_FM_DEL,				/*ɾ���ļ� INVOLID*/
			DUCP_CMD_FM_COPY,				/*�����ļ� INVOLID*/
			DUCP_CMD_FM_FDISK,				/*��ʽ������ INVOLID*/
			DUCP_CMD_FM_WLIC,				/*д��Ȩ�ļ�*/
			DUCP_CMD_FM_RLIC,				/*����Ȩ�ļ�*/
			DUCP_CMD_FM_CULIC,				/*У���û���Ȩ�ļ�*/

			/*-------------------TTS�����ӿ�----------------------------*/
			DUCP_CMD_TTS_PLAY = DUCP_CMD_TTS_BASE,/*��������OK*/
			DUCP_CMD_TTS_STOP,				/*ֹͣ��������OK*/


			/*-------------------2Dͼ�νӿ�-----------------------------*/
			DUCP_CMD_2D_DRAW_POINT = DUCP_CMD_2D_BASE,/*���� OK*/
			DUCP_CMD_2D_DRAW_LINE,			/*���� OK*/
			DUCP_CMD_2D_DRAW_RECT,			/*������ OK*/
			DUCP_CMD_2D_FILL_RECT,			/*������ OK*/
			DUCP_CMD_2D_DRAW_CICLE,			/*��Բ OK*/
			DUCP_CMD_2D_FILL_CICLE,			/*���Բ OK*/
			DUCP_CMD_2D_DRAW_BITMAP,		/*����λͼ*/
			DUCP_CMD_2D_DIS_TEXT,			/*��ʾ�ı� OK*/
			DUCP_CMD_2D_SET_TCOLOR,	 		/*�����ı���ɫ OK*/
			DUCP_CMD_2D_SET_BCOLOR,			/*���ñ�����ɫ OK*/
			DUCP_CMD_2D_SET_FONT,			/*�������� OK*/
			DUCP_CMD_2D_DRAW_SYSICON,		/*����ϵͳ�Դ���ͼ��OK*/
			
			/*----------------------���ڹ���---------------------------*/
			DUCP_CMD_WIN_SHOW = DUCP_CMD_WM_BASE,/*��ʾ���� OK*/
			DUCP_CMD_WIN_HIDLE,				/*���ش��� OK*/
			DUCP_CMD_WIN_DEL,				/*ɾ������ OK*/
			DUCP_CMD_WIN_AUTO_SYN,			/*�Զ�ͬ��������ʾ OK*/
			
			/*----------------------�ı��ؼ�---------------------------*/
			DUCP_CMD_TWIN_CREATE = DUCP_CMD_TWIN_BASE,/*�����ı����� OK*/
			DUCP_CMD_TWIN_DEL,				/*ɾ���ı����� OK*/
			DUCP_CMD_TWIN_DIS_TEXT,			/*��ʾ��ʱ�ı� OK*/
			DUCP_CMD_TWIN_SET_FONT,	 		/*�������� OK*/
			DUCP_CMD_TWIN_SET_TCOLOR,		/*�����ı���ɫ OK*/
			DUCP_CMD_TWIN_SET_BCOLOR,		/*���ñ�����ɫ OK*/
			DUCP_CMD_TWIN_STOP_DIS,			/*ֹͣ��ʾ OK*/
			DUCP_CMD_TWIN_DOWN_TFILE,		/*�����ı��ļ� OK*/
			DUCP_CMD_TWIN_DIS_TFILE,		/*��ʾ�ı��ļ� OK*/
			DUCP_CMD_TWIN_OPEN_TFILE,		/*���ı��ļ� OK*/
			DUCP_CMD_TWIN_CLOSE_TFILE,		/*�ر��ı��ļ� OK*/
			DUCP_CMD_TWIN_DEL_TFILE,		/*ɾ���ı��ļ� OK*/
			DUCP_CMD_TWIN_SYN_DIS,			/*ͬ����ʾ����ı��ؼ�*/
			DUCP_CMD_TWIN_SYN_DISEX,		/*������ʾ,ͬʱ��������*/

			/*----------------------ͼƬ�ؼ�---------------------------*/
			DUCP_CMD_PIC_CREATE = DUCP_CMD_PIC_BASE,/*����ͼƬ���� OK*/
			DUCP_CMD_PIC_DEL,
			DUCP_CMD_PIC_ADD,
			DUCP_CMD_PIC_CLR,
			DUCP_CMD_PIC_QR, //171030
			DUCP_CMD_SwitchContoll,//171103
			DUCP_CMD_Secret_Key,

} DUCP_CMD_E;


typedef struct {
	char			DevName[8];/*�豸����*/
	char			SVR[8];		/*����汾X.YZ*/
	uint32_t		XSize;		/*X�ߴ�*/
	uint32_t		YSize;		/*Y�ߴ�*/
	uint32_t		LstUpTime;	/*������ʱ��*/
	uint8_t			SN[12];		/*���к�*/
}DEVICE_FRAMWARE_T;

/*IO���ű�ʶ*/
typedef enum {
	IO_PIN_1 = 0,
	IO_PIN_2,
	IO_PIN_3,
	IO_PIN_4,
	IO_PIN_ALL = 0XF0, /*������IO�ڽ��и�ֵ����*/
	IO_PIN_OR,/*������IO�ڽ��� �� ����*/
	IO_PIN_AND,/*������IO�ڽ��� �� ����*/
	IO_PIN_NOT/*������IO�ڽ��� �� ����*/
} IO_PIN_ID_E;

/*IO ����ö��*/
typedef enum {
	IO_FUN_IN = 0, 	/*����*/
	IO_FUN_PP,		/*�������*/
	IO_FUN_OD,		/*��©���*/
} IO_PIN_FUN_E;


/*ϵͳ����������*/
typedef struct {
	uint32_t 	Baud;	/*������ ���115200*/
	uint8_t  	_485Addr;/*485��ַ*/
	uint8_t  	_485CM;/*485����ģʽ 0:��˫�� 1:�빤*/
	uint8_t  	IP[4];/*IP��ַ*/
	uint32_t  	Port;/*�˿ں�*/
	uint8_t	 	GW[4];/*���ص�ַ*/
	uint8_t	 	Mask[4];/*��������*/
	uint16_t 	Fre;/*ɨ��Ƶ�� 30Hz ~ 960Hz*/
	uint8_t  	LightLevel;/*���ȼ��� 10~100 ��Ӧ10% ~ 100%*/
	uint8_t  	VoiceLevel;/*�������� 10~100 ��Ӧ10% ~ 100%*/
	uint8_t	 	OEP;/*OE���ԣ�0:������ 1:������*/
	uint8_t  	DP;/*���ݼ��ԣ�0:������ 1:������*/
	uint8_t  	LEDey;/*LE�ź���ʱ��0:�ر� 1:��*/
	uint8_t  	LEDDrv;/*LED�������� 0:08˫ɫ16��֮һɨ�� 1:12˫ɫ4��֮һɨ�� 2:12˫ɫ8��֮һɨ��*/
	uint16_t 	XSize;/*��ʾ�����ȳߴ� ����*/
	uint16_t 	YSize;/*��ʾ���߶ȳߴ� ����*/
	uint8_t	 	Orientation;/*XY����ʹ�� 0:ԭ�����������Ͻ� 1:ԭ�����������½�*/
	uint8_t		TTSAEn;/*0:����������1:���Բ�����������(��Ҫ�����ⲿTTS����ģ��)*/
	//uint8_t 	RLEn; // 0 RL disable  1 enable    
	//uint8_t 	RLPlace;// 0 out  1 in
	//uint8_t 	RLDis; // 0 two line  1  four line
	//uint8_t 	RLColor; //0 onecolor 1 doublecolor
} SysSettings_t;
typedef struct _SYSTEMTIME {
	uint16_t 	wYear;
	uint8_t  	wMonth;
	uint8_t 	wDayOfWeek;
	uint8_t 	wDay;
	uint8_t 	wHour;
	uint8_t 	wMinute;
	uint8_t 	wSecond;
	uint16_t 	wMilliseconds;
} SYSTEMTIME;
typedef struct
{
	uint32_t                RemotCount;
	uint32_t                ManualCount;
	SYSTEMTIME              pSYSTEMTIME;
}SwitchControll_t;
#endif


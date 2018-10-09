/*
 *****************************************************************************************************************
 *													  LED SDK 6.0
 *
 *														 ��ΰ
 *	
 *
 *										(C) Copyright 2010 - 2015, LISTEN VISION
 *												   All Rights Reserved
 *														  
 *****************************************************************************************************************
 */

#pragma once

typedef LPVOID				HPROGRAM;	//��Ŀ�������

#define COLOR_RED			0xff		//��ɫ
#define COLOR_GREEN			0xff00		//��ɫ
#define COLOR_YELLOW		0Xffff		//��ɫ


#define ADDTYPE_STRING		0			//�������Ϊ�ִ�
#define ADDTYPE_FILE		1			//��ӵ�����Ϊ�ļ�


#define OK					0			//�������سɹ�

//******��Ŀ��ʱ��������ʱ�����ڵı�־��***************************************************************************
#define ENABLE_DATE			0x01		
#define ENABLE_TIME			0x02
#define ENABLE_WEEK			0x04
//*****************************************************************************************************************

//******��Ŀ��ʱ������ĳ�����ú�***********************************************************
#define WEEK_MON			0x01
#define WEEK_TUES			0x02
#define WEEK_WEN			0x04
#define WEEK_THUR			0x08
#define WEEK_FRI			0x10
#define WEEK_SAT			0x20
#define WEEK_SUN			0x40
//*****************************************************************************


//**ͨѶ���ýṹ��*********************************************************
typedef struct COMMUNICATIONINFO
{
	int		LEDType;				//LED����	0.Ϊ����6����ɫ��˫ɫ���߲ʿ�,		1.Ϊ����6��ȫ�ʿ�
	int		SendType;				//ͨѶ��ʽ	0.ΪTcp���ͣ��ֳƹ̶�IPͨѶ��,		1.�㲥���ͣ��ֳƵ���ֱ����		2.����ͨѶ		3.���̱���
	TCHAR	IpStr[16];				//LED����IP��ַ��ֻ��ͨѶ��ʽΪ0ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
	int		Commport;				//���ںţ�ֻ��ͨѶ��ʽΪ2ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
	int		Baud;					//�����ʣ�ֻ��ͨѶ��ʽΪ2ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ,   0.9600   1.57600   2.115200  ֱ�Ӹ�ֵ 9600��19200��38400��57600��115200���
	int		LedNumber;				//LED�����ţ�ֻ��ͨѶ��ʽΪ2ʱ������485ͨѶʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
	TCHAR	OutputDir[MAX_PATH];	//���̱����Ŀ¼��ֻ��ͨѶ��ʽΪ3ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
}*LPCOMMUNICATIONINFO;
//***********************************************************************

//**��������ṹ��*********************************************************
typedef struct AREARECT
{
	int			left;	//�������ϽǺ�����
	int			top;	//�������Ͻ�������
	int			width;	//����Ŀ��
	int			height;	//����ĸ߶�
}*LPAREARECT;
//****************************************************************************

//***�������Խṹ��**********************************************************
struct FONTPROP
{
	TCHAR		FontName[32];		//������
	int			FontSize;			//�ֺ�(��λ��)
	COLORREF	FontColor;			//������ɫ
	BOOL		FontBold;			//�Ƿ�Ӵ�
	BOOL		FontItalic;			//�Ƿ�б��
	BOOL		FontUnderLine;		//ʱ���»���
};
//****************************************************************************


//**ҳ����ʾ�����Խṹ��****************************************************
struct PLAYPROP 
{
	int			InStyle;	//�볡�ؼ�ֵ��ȡֵ��Χ 0-39��
	int			OutStyle;	//�˳��ؼ�ֵ������Ч��Ԥ������0��
	int			Speed;		//�ؼ���ʾ�ٶ�(ȡֵ��Χ1-255)
	int			DelayTime;	//ҳ����ͣʱ��(1-65535)
};
      /*  �ؼ�ֵ��Ӧ
            0=������ʾ
            1=���
            2=����
            3=����
            4=����
            5=����
            6=��������
            7=��������
            8=��������
            9=��������
            10=��˸
            11=������(����)
            12=������(����)
            13=������(����)
            14=������(����)
            15=ˮƽ������Ļ
            16=���½�����Ļ
            17=��������
            18=��������
            19=�󸲸�
            20=�Ҹ���
            21=�ϸ���
            22=�¸���
            23=ˮƽ��Ҷ(����)
            24=ˮƽ��Ҷ(����)
            25=��ֱ��Ҷ(����)
            26=��ֱ��Ҷ(����)
            27=���ҶԿ�
            28=���¶Կ�
            29=���ұպ�
            30=���±պ�
            31=��������
            32=��������
            33=��������
            34=��������
            35=��ɢ��������
            36=��ɢ��������
            37=ð��
            38=��ѩ
         */
//*******************************************************************************

//**���ý�Ŀ��ʱ���Խṹ��****************************************************
typedef struct PROGRAMTIME
{
	int				EnableFlag;		//���ö�ʱ�ı�ǣ�ENABLE_DATEΪ��������,ENABLE_TIMEΪ����ʱ��,ENABLE_WEEKΪ��������,���û����������ϣ��� ENABLE_DATE | ENABLE_TIME | ENABLE_WEEK
	int				WeekValue;		//�������ں�ѡ��Ҫ��ʱ���������ĳЩ�죬�ú� WEEK_MON,WEEK_TUES,WEEK_WEN,WEEK_THUR,WEEK_FRI,WEEK_SAT,WEEK_SUN ͨ��������������
	int				StartYear;		//��ʼ��
	int				StartMonth;		//��ʼ��
	int				StartDay;		//��ʼ��
	int				StartHour;		//���ʱ
	int				StartMinute;	//��ʼ��
	int				StartSecond;	//��ʼ��
	int				EndYear;		//������
	int				EndMonth;		//������
	int				EndDay;			//������
	int				EndHour;		//����ʱ
	int				EndMinute;		//������
	int				EndSecond;		//������
}*LPPROGRAMTIME;
//**********************************************************************************

//����ʱ�����Խṹ��*********************************************************************************
typedef struct DIGITALCLOCKAREAINFO
{
	TCHAR		ShowStr[128];			//�Զ�����ʾ�ַ���
	FONTPROP	ShowStrFont;			//�Զ�����ʾ�ַ����Լ���������ʱ����������ԣ�ע��������������FontColorֻ���Զ�����ʾ������Ч�����������ɫ�е�������ɫ���ԣ����Եĸ�ֵ��FONTPROP�ṹ��˵��
	int			TimeLagType;			//ʱ������ 0Ϊ��ǰ��1Ϊ�ͺ�
	int			HourNum;				//ʱ��Сʱ��	
	int			MiniteNum;				//ʱ�������
	int			DateFormat;				//���ڸ�ʽ 0.YYYY��MM��DD��  1.YY��MM��DD��  2.MM/DD/YYYY  3.YYYY/MM/DD  4.YYYY-MM-DD  5.YYYY.MM.DD  6.MM.DD.YYYY  7.DD.MM.YYYY
	COLORREF	DateColor;				//����������ɫ
	int			WeekFormat;				//���ڸ�ʽ 0.����X  1.Monday  2.Mon.
	COLORREF	WeekColor;				//����������ɫ
	int			TimeFormat;				//ʱ���ʽ 0.HHʱmm��ss��  1.HH�rmm��ss��  2.HH:mm:ss  3.���� HH:mm:ss  4.AM HH:mm:ss  5.HH:mm:ss ����  6.HH:mm:ss AM
	COLORREF	TimeColor;				//ʱ��������ɫ
	BOOL		IsShowYear;				//�Ƿ���ʾ�� TRUEΪ��ʾ FALSE����ʾ ��ͬ
	BOOL		IsShowWeek;				//�Ƿ���ʾ����
	BOOL		IsShowMonth;			//�Ƿ���ʾ��
	BOOL		IsShowDay;				//�Ƿ���ʾ��
	BOOL		IsShowHour;				//�Ƿ���ʾʱ
	BOOL		IsShowMinute;			//�Ƿ���ʾ��
	BOOL		IsShowSecond;			//�Ƿ���ʾ��
	BOOL		IsMutleLineShow;		//�Ƿ������ʾ
}*LPDIGITALCLOCKAREAINFO;
//******************************************************************************

//**ģ��ʱ�����Խṹ��*********************************************************
typedef struct CLOCKAREAINFO
{
	TCHAR		ShowStr[64];			//�Զ�����ʾ�ַ���
	FONTPROP	ShowStrFont;			//�Զ�����ʾ�ַ�����������
	int			TimeLagType;			//ʱ������ 0Ϊ��ǰ��1Ϊ�ͺ�
	int			HourNum;				//ʱ��Сʱ��
	int			MiniteNum;				//ʱ�������
	int			ClockType;				//��������  0.Բ��  1.������
	COLORREF	HourMarkColor;			//ʱ����ɫ	
	int			HourMarkType;			//ʱ������	0.Բ��  1.������
	int			HourMarkWidth;			//ʱ����	1~16
	COLORREF	MiniteMarkColor;		//�ֱ���ɫ
	int			MiniteMarkType;			//�ֱ�����	0.Բ��  1.������
	int			MiniteMarkWidth;		//�ֱ���  1~16
	COLORREF	HourPointerColor;		//ʱ����ɫ
	COLORREF	MinutePointerColor;		//������ɫ
	COLORREF	SecondPointerColor;		//������ɫ
	int			HourPointerWidth;		//ʱ��Ŀ��  1~5
	int			MinutePointerWidth;		//����Ŀ��  1~5
	int			SecondPointerWidth;		//����Ŀ��  1~5
	BOOL		IsShowDate;				//�Ƿ���ʾ����	
	int			DateFormat;				//���ڸ�ʽ 0.YYYY��MM��DD��  1.YY��MM��DD��  2.MM/DD/YYYY  3.YYYY/MM/DD  4.YYYY-MM-DD  5.YYYY.MM.DD  6.MM.DD.YYYY  7.DD.MM.YYYY
	FONTPROP	DateFont;				//������������
	BOOL		IsShowWeek;				//�Ƿ���ʾ����
	int			WeekFormat;				//���ڸ�ʽ 0.����X  1.Monday  2.Mon.
	FONTPROP	WeekFont;				//������������
}*LPCLOCKAREAINFO;
//**************************************************************************************

//**��ʱ���Խṹ��**********************************************************************
typedef struct TIMEAREAINFO
{
	int			ShowFormat;				//��ʾ��ʽ	0.xx��xxʱxx��xx��  1.xx��xx�rxx��xx��  2.xxDayxxHourxxMinxxSec  3.XXdXXhXXmXXs  4.xx:xx:xx:xx
	int			nYear;					//������
	int			nMonth;					//������
	int			nDay;					//������
	int			nHour;					//����ʱ
	int			nMinute;				//������
	int			nSecond;				//������
	BOOL		IsShowDay;				//�Ƿ���ʾ��
	BOOL		IsShowHour;				//�Ƿ���ʾʱ
	BOOL		IsShowMinute;			//�Ƿ���ʾ��
	BOOL		IsShowSecond;			//�Ƿ���ʾ��
	BOOL		IsMutleLineShow;		//�Ƿ������ʾ��ָ�����Զ����������ʱ�����Ƿ������ʾ
	TCHAR		ShowStr[128];			//�Զ��������ַ���
	COLORREF	TimeStrColor;			//��ʱ���ֵ���ɫ
	FONTPROP	ShowFont;				//�Զ������ּ���ʱ������ɫ������FontColorֻ���Ķ���������Ч����ʱ������ɫΪTimeStrColor
}* LPTIMEAREAINFO;
//****************************************************************************************



//**LEDͨѶ�����޸Ľṹ��*****************************************************************
typedef struct LEDCOMMUNICATIONPARAMETER
{
	DWORD	dwMask;				//Ҫ�޸���ı��  0.�޸�����ͨѶ����  1.�޸Ĵ���ͨѶ����  2.�޸����ںʹ���ͨѶ����
	TCHAR	IpStr[16];			//�µ�IP��ַ��ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ����ʽ���� 192.168.1.100
	TCHAR	NetMaskStr[16];		//�µ��������룬ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ����ʽ���� 255.255.255.0
	TCHAR	GatewayStr[16];		//�µ����أ�ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ,��ʽ���� 192.168.1.1
	TCHAR	MacStr[18];			//�µ�MAC��ַ��ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ����ʽ���� 12-34-56-78-9a-bc,�������޸�����Ϊ ff-ff-ff-ff-ff-ff
	int		Baud;				//�����ʣ�ֻ��dwMaskΪ1��2ʱ���踳ֵ������ֵ���踳ֵ��0.9600  1.57600  2.115200
	int		LedNumber;			//LED���� 1~255,����ͨѶ��232ͨѶ��ֵ 1 ���ɣ�485����Ϳ��ƿ���ʾ��������ͬ�ſ�ͨѶ
}*LPLEDCOMMUNICATIONPARAMETER;
//*****************************************************************************************


//**��ˮ�߿����Խṹ��************************************************************************
typedef struct WATERBORDERINFO
{
	int			Flag;							//��ˮ�߿�������ͱ�־��0.Ϊ��̬��Ԥ�õı߿�  1.Ϊ���ļ����صı߿�
	int			BorderType;						//�߿�����ͣ�FlagΪ0����Ч��0.��ɫ�߿�  1.˫��ɫ�߿�  2.ȫ�ʱ߿�
	int			BorderValue;					//�߿��ֵ��FlagΪ0����Ч����ɫ�߿�ȡֵ��Χ��0~39,˫��ɫ�߿�ȡֵ��Χ��0~34,ȫ�ʱ߿�ȡֵ��Χ��0~21
	COLORREF	BorderColor;					//�߿�����ɫ,FlagΪ0����BorderTypeΪ0�ǲ���Ч
	int			BorderStyle;					//�߿���ʾ����ʽ  0.�̶�  1.˳ʱ��  2.��ʱ��  3.��˸
	int			BorderSpeed;					//�߿��������ٶ�
	TCHAR		WaterBorderBmpPath[MAX_PATH];	//�߿�ͼƬ�ļ���·����ע��ֻ����bmpͼƬ��ͼƬ��С�����ǿ��Ϊ32�㣬ȡ�߶�С�ڵ���8
}*LPWATERBORDERINFO;
//*********************************************************************************************



//**��ʱ��������������************************************************************************
typedef	struct ONOFFTIMEINFO
{
	BOOL	TimeFlag[3];
	int		StartHour[3];
	int		StartMinute[3];
	int		EndHour[3];
	int		EndMinute[3];	
}*LPONOFFTIMEINFO;
//********************************************************************************************

//**��ʱ������������**************************************************************************
typedef struct BRIGHTNESSTIMEINFO
{
	BOOL	TimeFlag[3];
	int		StartHour[3];
	int		StartMinute[3];
	int		EndHour[3];
	int		EndMinute[3];
	int		BrightnessValue[3];
}*LPBRIGHTNESSTIMEINFO;
//*******************************************************************************************

/********************************************************************************************
 *	LV_CreateProgram			������Ŀ���󣬷�������Ϊ HPROGRAM
 *
 *	����˵��
 *				LedWidth		���Ŀ��
 *				LedHeight		���ĸ߶�
 *				ColorType		������ɫ 1.��ɫ  2.˫��ɫ  3.�߲�  4.ȫ��
 *	����ֵ
 *				0				������Ŀ����ʧ��
 *				��0				������Ŀ����ɹ�
 ********************************************************************************************/
typedef	HPROGRAM	(__stdcall *_LV_CreateProgram)(int LedWidth,int LedHeight,int ColorType);


/*********************************************************************************************
 *	LV_AddProgram				���һ����Ŀ
 *	
 *	����˵��
 *				hProgram		��Ŀ������
 *				ProgramNo		��Ŀ��
 *				ProgramTime		��Ŀ����ʱ�� 0.��Ŀ����ʱ��  ��0.ָ������ʱ��
 *				LoopCount		ѭ�����Ŵ���
 *	����ֵ
 *				0				�ɹ�
 *				��0				ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddProgram)(HPROGRAM hProgram,int ProgramNo,int ProgramTime,int LoopCount);

/*********************************************************************************************
 *	LV_SetProgramTime			���ý�Ŀ��ʱ
 *	
 *	����˵��
 *				hProgram		��Ŀ������
 *				ProgramNo		��Ŀ��
 *				pProgramTime	��Ŀ��ʱ���ԣ����÷�ʽ��PROGRAMTIME�ṹ��עʾ
 *	����ֵ
 *				0				�ɹ�
 *				��0				ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_SetProgramTime)(HPROGRAM hProgram,int ProgramNo,LPPROGRAMTIME pProgramTime);

/*********************************************************************************************
 *	LV_AddImageTextArea				���һ��ͼ������
 *	
 *	����˵��
 *				hProgram			��Ŀ������
 *				ProgramNo			��Ŀ��
 *				AreaNo				�����
 *				pAreaRect			�����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
 *				IsBackgroundArea	�Ƿ�Ϊ��������0.ǰ������Ĭ�ϣ� 1.������
 *	����ֵ
 *				0					�ɹ�
 *				��0					ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddImageTextArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPAREARECT pAreaRect,BOOL IsBackgroundArea);


/*********************************************************************************************
 *	LV_AddFileToImageTextArea			���һ���ļ���ͼ����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				FilePath				�ļ�·����֧�ֵ��ļ������� txt  rtf  bmp  gif  png  jpg jpeg tiff
 *				pPlayProp				��ʾ�����ԣ����÷�ʽ��PLAYPROP�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddFileToImageTextArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPCTSTR FilePath,PLAYPROP *pPlayProp);

/*********************************************************************************************
 *	LV_AddSingleLineTextToImageTextArea	���һ�������ı���ͼ����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				AddType					��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
 *				AddStr					AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
 *				pFontProp				���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
 *				pPlayProp				��ʾ�����ԣ����÷�ʽ��PLAYPROP�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddSingleLineTextToImageTextArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,int AddType,LPCTSTR AddStr,FONTPROP *pFontProp,PLAYPROP *pPlayProp);

/*********************************************************************************************
 *	LV_AddMultiLineTextToImageTextArea	���һ�������ı���ͼ����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				AddType					��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
 *				AddStr					AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
 *				pFontProp				���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
 *				pPlayProp				��ʾ�����ԣ����÷�ʽ��PLAYPROP�ṹ��עʾ
 *				nAlignment				ˮƽ������ʽ��0.�����  1.�Ҷ���  2.ˮƽ����  ��ע�⣺ֻ���ַ�����txt�ļ���Ч��
 *				IsVCenter				�Ƿ�ֱ����  0.�ö���Ĭ�ϣ� 1.��ֱ����
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddMultiLineTextToImageTextArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,int AddType,LPCTSTR AddStr,FONTPROP *pFontProp,PLAYPROP *pPlayProp,int nAlignment,BOOL IsVCenter);

/*********************************************************************************************
 *	LV_AddStaticTextToImageTextArea		���һ����ֹ�ı���ͼ����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				AddType					��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
 *				AddStr					AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
 *				pFontProp				���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
 *				DelayTime				��ʾ��ʱ�� 1~65535
 *				nAlignment				ˮƽ������ʽ��0.�����  1.�Ҷ���  2.ˮƽ����  ��ע�⣺ֻ���ַ�����txt�ļ���Ч��
 *				IsVCenter				�Ƿ�ֱ����  0.�ö���Ĭ�ϣ� 1.��ֱ����
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddStaticTextToImageTextArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,int AddType,LPCTSTR AddStr,FONTPROP *pFontProp,int DelayTime,int nAlignment,BOOL IsVCenter);

/*********************************************************************************************
 *	LV_QuickAddSingleLineTextArea		�������һ�������ı�����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				pAreaRect				�����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
 *				AddType					��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
 *				AddStr					AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
 *				pFontProp				���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
 *				nSpeed					�����ٶ� 1~255
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_QuickAddSingleLineTextArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPAREARECT pAreaRect,int AddType,LPCTSTR AddStr,FONTPROP *pFontProp,int nSpeed);

/*********************************************************************************************
 *	LV_AddDigitalClockArea				���һ������ʱ������
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				pAreaRect				�����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
 *				pDigitalClockAreaInfo	����ʱ�����ԣ���DIGITALCLOCKAREAINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddDigitalClockArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPAREARECT pAreaRect,LPDIGITALCLOCKAREAINFO pDigitalClockAreaInfo);

/*********************************************************************************************
 *	LV_AddTimeArea						���һ����ʱ����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				pAreaRect				�����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
 *				pTimeAreaInfo			��ʱ���ԣ���TIMEAREAINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddTimeArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPAREARECT pAreaRect,LPTIMEAREAINFO pTimeAreaInfo);

/*********************************************************************************************
 *	LV_AddClockArea						���һ��ģ��ʱ������
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				pAreaRect				�����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
 *				pClockAreaInfo			ģ��ʱ�����ԣ���CLOCKAREAINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddClockArea)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPAREARECT pAreaRect,LPCLOCKAREAINFO pClockAreaInfo);

/*********************************************************************************************
 *	LV_AddWaterBorder					���һ����ˮ�߿�����
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 *				ProgramNo				��Ŀ��
 *				AreaNo					�����
 *				pAreaRect				�����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
 *				pWaterBorderInfo		��ˮ�߿����ԣ���WATERBORDERINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AddWaterBorder)(HPROGRAM hProgram,int ProgramNo,int AreaNo,LPAREARECT pAreaRect,LPWATERBORDERINFO pWaterBorderInfo);

/*********************************************************************************************
 *	LV_DeleteProgram					���ٽ�Ŀ����(ע�⣺����˽�Ŀ������ʹ�ã�����ô˺������٣����������ڴ�й¶)
 *	
 *	����˵��
 *				hProgram				��Ŀ������
 ********************************************************************************************/
typedef	void		(__stdcall *_LV_DeleteProgram)(HPROGRAM hProgram);


/*********************************************************************************************
 *	LV_Send								���ͽ�Ŀ���˷���Ϊһ��һ����
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				hProgram				��Ŀ������
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_Send)(LPCOMMUNICATIONINFO pCommunicationInfo,HPROGRAM hProgram);

/*********************************************************************************************
 *	LV_MultiSendOne						���ͽ�Ŀ���˷���Ϊ���������һ����Ŀ�����з���
 *	
 *	����˵��
 *				pCommunicationInfoArray	ͨѶ������Ϊһ���飬��ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				hProgram				��Ŀ������
 *				pResultArray			���ͷ��صĽ������,�������غ�ͨ����ֵ�жϷ����Ƿ�ɹ���0Ϊ�ɹ�����0ʧ�ܣ�����LV_GetError����ȡ������Ϣ��	
 *				LedCount				Ҫ���͵����ĸ�������ΪpCommunicationInfoArray��pResultArray������ϱ���
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_MultiSendOne)(LPCOMMUNICATIONINFO pCommunicationInfoArray,HPROGRAM hProgram,OUT int* pResultArray,int LedCount);

/*********************************************************************************************
 *	LV_MultiSend						���ͽ�Ŀ���˷���Ϊ��������Ͳ�ͬ�Ľ�Ŀ�����з���
 *	
 *	����˵��
 *				pCommunicationInfoArray	ͨѶ������Ϊһ���飬��ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				phProgramArray			��Ŀ����������
 *				pResultArray			���ͷ��صĽ������,�������غ�ͨ����ֵ�жϷ����Ƿ�ɹ���0Ϊ�ɹ�����0ʧ�ܣ�����LV_GetError����ȡ������Ϣ��	
 *				LedCount				Ҫ���͵����ĸ�������ΪpCommunicationInfoArray��phProgramArray��pResultArray������ϱ���
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_MultiSend)(LPCOMMUNICATIONINFO pCommunicationInfoArray,HPROGRAM *phProgramArray,OUT int* pResultArray,int LedCount);


/*********************************************************************************************
 *	LV_TestOnline						����LED���Ƿ��������
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_TestOnline)(LPCOMMUNICATIONINFO pCommunicationInfo);


/*********************************************************************************************
 *	LV_SetBasicInfo						���û�������
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				ColorType				������ɫ 1.��ɫ  2.˫��ɫ  3.�߲�  4.ȫ��
 *				LedWidth				���Ŀ�ȵ���
 *				LedHeight				���ĸ߶ȵ���
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_SetBasicInfo)(LPCOMMUNICATIONINFO pCommunicationInfo,int ColorType,int LedWidth,int LedHeight);


/*********************************************************************************************
 *	LV_SetOEDA							����OE DA
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				Oe						OE  0.����Ч  1.����Ч
 *				Da						DA  0.������  1.������
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_SetOEDA)(LPCOMMUNICATIONINFO pCommunicationInfo,int Oe,int Da);


/*********************************************************************************************
 *	LV_AdjustTime						Уʱ
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_AdjustTime)(LPCOMMUNICATIONINFO pCommunicationInfo);


/*********************************************************************************************
 *	LV_PowerOnOff						������
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				OnOff					����ֵ  0.����  1.����
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_PowerOnOff)(LPCOMMUNICATIONINFO pCommunicationInfo,int OnOff);

/*********************************************************************************************
 *	LV_TimePowerOnOff					��ʱ������
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				pTimeInfo				��ʱ���������ԣ����ONOFFTIMEINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_TimePowerOnOff)(LPCOMMUNICATIONINFO pCommunicationInfo,LPONOFFTIMEINFO pTimeInfo);

/*********************************************************************************************
 *	LV_SetBrightness					��������
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				BrightnessValue			����ֵ 0~15
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_SetBrightness)(LPCOMMUNICATIONINFO pCommunicationInfo,int BrightnessValue);

/*********************************************************************************************
 *	LV_TimeBrightness					��ʱ����
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				pBrightnessTimeInfo		��ʱ�������ԣ����BRIGHTNESSTIMEINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_TimeBrightness)(LPCOMMUNICATIONINFO pCommunicationInfo,LPBRIGHTNESSTIMEINFO pBrightnessTimeInfo);

/*********************************************************************************************
 *	LV_SetLanguage						����LED��ʾ������
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				LanguageValue			����ֵ  0.���ģ�Ĭ�ϣ� 1.Ӣ��
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_SetLanguage)(LPCOMMUNICATIONINFO pCommunicationInfo,int LanguageValue);

/*********************************************************************************************
 *	LV_LedTest							LED����
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				TestValue				����ֵ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_LedTest)(LPCOMMUNICATIONINFO pCommunicationInfo,int TestValue);

/*********************************************************************************************
 *	LV_TimeLocker						LED��ʱ����
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				LockerYear				������
 *				LockerMonth				������
 *				LockerDay				������
 *				LockerHour				����ʱ
 *				LockerMinute			������
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_TimeLocker)(LPCOMMUNICATIONINFO pCommunicationInfo,int LockerYear,int LockerMonth,int LockerDay,int LockerHour,int LockerMinute);

/*********************************************************************************************
 *	LV_CancelLocker						ȡ����ʱ����
 *	
 *	����˵��
 *				pCommunicationInfo		ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_CancelLocker)(LPCOMMUNICATIONINFO pCommunicationInfo);

/*********************************************************************************************
 *	LV_SetLedCommunicationParameter			����LEDͨѶ����
 *	
 *	����˵��
 *				pCommunicationInfo			ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
 *				pLedCommunicationParameter	���LEDCOMMUNICATIONPARAMETER�ṹ��עʾ
 *	����ֵ
 *				0						�ɹ�
 *				��0						ʧ�ܣ�����LV_GetError����ȡ������Ϣ	
 ********************************************************************************************/
typedef	int			(__stdcall *_LV_SetLedCommunicationParameter)(LPCOMMUNICATIONINFO pCommunicationInfo,LPLEDCOMMUNICATIONPARAMETER pLedCommunicationParameter);



/*********************************************************************************************
 *	LV_GetError								��ȡ������Ϣ��ֻ֧�����ģ�
 *	
 *	����˵��
 *				nErrCode					����ִ�з��صĴ������
 *				nMaxCount					pErrStr�ַ����������Ĵ�С��Ϊ�ַ��ĸ��������ֽ�����
 *				pErrStr						����ȡ������Ϣ���ַ�����ַ
 ********************************************************************************************/
typedef void		(__stdcall *_LV_GetError)(int nErrCode,int nMaxCount,OUT LPTSTR pErrStr);


class CLedDll
{
private:
	HMODULE m_hDll;
public:
	CLedDll();
	~CLedDll();


	_LV_CreateProgram						LV_CreateProgram;
	_LV_AddProgram							LV_AddProgram;
	_LV_SetProgramTime						LV_SetProgramTime;
	_LV_AddImageTextArea					LV_AddImageTextArea;
	_LV_AddFileToImageTextArea				LV_AddFileToImageTextArea;
	_LV_AddSingleLineTextToImageTextArea	LV_AddSingleLineTextToImageTextArea;
	_LV_AddMultiLineTextToImageTextArea		LV_AddMultiLineTextToImageTextArea;
	_LV_AddStaticTextToImageTextArea		LV_AddStaticTextToImageTextArea;
	_LV_QuickAddSingleLineTextArea			LV_QuickAddSingleLineTextArea;
	_LV_AddDigitalClockArea					LV_AddDigitalClockArea;
	_LV_AddTimeArea							LV_AddTimeArea;
	_LV_AddClockArea						LV_AddClockArea;
	_LV_AddWaterBorder						LV_AddWaterBorder;
	_LV_DeleteProgram						LV_DeleteProgram;
	
	_LV_Send								LV_Send;
	_LV_MultiSendOne						LV_MultiSendOne;
	_LV_MultiSend							LV_MultiSend;
	
	
	_LV_TestOnline							LV_TestOnline;
	_LV_SetBasicInfo						LV_SetBasicInfo;
	_LV_SetOEDA								LV_SetOEDA;
	_LV_AdjustTime							LV_AdjustTime;
	_LV_PowerOnOff							LV_PowerOnOff;
	_LV_TimePowerOnOff						LV_TimePowerOnOff;
	_LV_SetBrightness						LV_SetBrightness;
	_LV_TimeBrightness						LV_TimeBrightness;
	_LV_SetLanguage							LV_SetLanguage;
	_LV_LedTest								LV_LedTest;
	
	_LV_TimeLocker							LV_TimeLocker;
	_LV_CancelLocker						LV_CancelLocker;
	
	_LV_SetLedCommunicationParameter		LV_SetLedCommunicationParameter;

	_LV_GetError							LV_GetError;
	
	BOOL InitDll();
};


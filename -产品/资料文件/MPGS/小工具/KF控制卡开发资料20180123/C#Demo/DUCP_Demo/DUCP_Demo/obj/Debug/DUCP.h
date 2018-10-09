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


#define DUCP_TTS_PLAY_OPT_A			(0x00)	/*添加到语音队列但是不开始播放*/
#define DUCP_TTS_PLAY_OPT_AS		(0x01)	/*添加到语音队列并且开始播放*/
#define DUCP_TTS_PLAY_OPT_CAS		(0x02)	/*先清除队列，再添加新语音到队列，然后开始播放*/

/*错误类型*/
#define DUCP_ERR_NONE				(0x00) /*无错误*/
typedef uint8_t DUCP_ERR_T;

/*-------------------------UDCP指令集----------------------------*/
#define DUCP_CMD_SYS_BASE		(0)
#define DUCP_CMD_FM_BASE		(0X20)
#define DUCP_CMD_TTS_BASE		(0X30)
#define DUCP_CMD_2D_BASE		(0X38)
#define DUCP_CMD_WM_BASE		(0X50)
#define DUCP_CMD_TWIN_BASE		(0X60)
#define DUCP_CMD_PIC_BASE		(0X80)

typedef enum {
			/*--------------------系统管理------------------------------*/
			DUCP_CMD_SYS_CONNECT = DUCP_CMD_SYS_BASE, /*0登录并连接UDCP服务器 OK*/		
			DUCP_CMD_SYS_SYN_PN,			/*1同步包序列 OK*/		
			DUCP_CMD_SYS_SET_PASSWAORD,		/*2修改登录密码 NOTEST*/
			DUCP_CMD_SYS_GET_PASSWAORD,		/*3获取登录密码 NOTEST*/
			DUCP_CMD_SYS_GET_FIRMWARE,		/*4获取固件信息OK*/
			DUCP_CMD_SYS_UPTIME,			/*5更新时间OK*/
			DUCP_CMD_SYS_RESET,				/*6重启系统 OK*/

			DUCP_CMD_SYS_SET_ADDR,			/*7设置485地址 OK*/
			DUCP_CMD_SYS_SET_IP,			/*8设置IP地址 OK*/
			DUCP_CMD_SYS_SET_PORT,			/*9设置端口 OK*/
			DUCP_CMD_SYS_SET_BAUD,			/*10设置波特率OK*/
			DUCP_CMD_SYS_SET_SCAN_FRE,		/*11设置扫描频率OK*/
			DUCP_CMD_SYS_SET_LIGHT,	 		/*12调整亮度OK*/
			DUCP_CMD_SYS_SET_VOL,		 	/*13设置音量OK*/
			
			DUCP_CMD_SYS_CFG_IO,			/*14配置IO口功能OK*/
			DUCP_CMD_SYS_SET_IO,			/*15设置IO口状态OK*/
			DUCP_CMD_SYS_READ_IO,			/*16读取IO口状态OK*/

			DUCP_CMD_SYS_SET_DRV,			/*17设置LED驱动OK*/
			DUCP_CMD_SYS_SET_OEP,			/*18设置OE极性OK*/
			DUCP_CMD_SYS_SET_DP,			/*19设置数据极性OK*/
			DUCP_CMD_SYS_SET_LE,			/*20设置LE信号延时OK*/
			DUCP_CMD_SYS_SET_GW_AND_MASK,	/*21设置网关和掩码OK*/
			DUCP_CMD_SYS_SET_SAF_MODE,		/*22进入安全模式OK*/
			DUCP_CMD_SYS_CLIC,				/*23Passport OK*/
			DUCP_CMD_SYS_SET_DIS_SIZE,		/*24设置显示尺寸OK*/
			DUCP_CMD_SYS_SET_XYMIR,			/*25设置显示镜像OK*/
			DUCP_CMD_SYS_SET_485MODE,		/*26设置485工作模式OK*/
			DUCP_CMD_SYS_GET_ALL,			/*27获取所有参数OK*/
			DUCP_CMD_SYS_SET_ALL,			/*28设置所有参数OK*/
			DUCP_CMD_SYS_SET_TTSEN,			/*29使能播报所有文本OK*/
			DUCP_CMD_SYS_FACTORY,			/*30恢复出厂设置*/
			DUCP_CMD_SYS_SET_OFFLINE,		/*31设置离线模式*/
			
			/*--------------------文件管理------------------------------*/
			DUCP_CMD_FM_MOUNT = DUCP_CMD_FM_BASE,/*挂载目录 INVOLID*/
			DUCP_CMD_FM_OPEN,				/*打开或创建文件 INVOLID*/
			DUCP_CMD_FM_SEEK,				/*设置文件读写位置 INVOLID*/
			DUCP_CMD_FM_WRITE,				/*写文件 INVOLID*/
			DUCP_CMD_FM_READ,				/*读文件 INVOLID*/
			DUCP_CMD_FM_SYNBUFF,			/*同步文件缓存 INVOLID*/
			DUCP_CMD_FM_COLOSE,				/*关闭文件 INVOLID*/
			DUCP_CMD_FM_DEL,				/*删除文件 INVOLID*/
			DUCP_CMD_FM_COPY,				/*复制文件 INVOLID*/
			DUCP_CMD_FM_FDISK,				/*格式化磁盘 INVOLID*/
			DUCP_CMD_FM_WLIC,				/*写授权文件*/
			DUCP_CMD_FM_RLIC,				/*读授权文件*/
			DUCP_CMD_FM_CULIC,				/*校验用户授权文件*/

			/*-------------------TTS语音接口----------------------------*/
			DUCP_CMD_TTS_PLAY = DUCP_CMD_TTS_BASE,/*播放语音OK*/
			DUCP_CMD_TTS_STOP,				/*停止播放语音OK*/


			/*-------------------2D图形接口-----------------------------*/
			DUCP_CMD_2D_DRAW_POINT = DUCP_CMD_2D_BASE,/*画点 OK*/
			DUCP_CMD_2D_DRAW_LINE,			/*画线 OK*/
			DUCP_CMD_2D_DRAW_RECT,			/*画矩形 OK*/
			DUCP_CMD_2D_FILL_RECT,			/*填充矩形 OK*/
			DUCP_CMD_2D_DRAW_CICLE,			/*画圆 OK*/
			DUCP_CMD_2D_FILL_CICLE,			/*填充圆 OK*/
			DUCP_CMD_2D_DRAW_BITMAP,		/*绘制位图*/
			DUCP_CMD_2D_DIS_TEXT,			/*显示文本 OK*/
			DUCP_CMD_2D_SET_TCOLOR,	 		/*设置文本颜色 OK*/
			DUCP_CMD_2D_SET_BCOLOR,			/*设置背景颜色 OK*/
			DUCP_CMD_2D_SET_FONT,			/*设置字体 OK*/
			DUCP_CMD_2D_DRAW_SYSICON,		/*绘制系统自带的图标OK*/
			
			/*----------------------窗口管理---------------------------*/
			DUCP_CMD_WIN_SHOW = DUCP_CMD_WM_BASE,/*显示窗口 OK*/
			DUCP_CMD_WIN_HIDLE,				/*隐藏窗口 OK*/
			DUCP_CMD_WIN_DEL,				/*删除窗口 OK*/
			DUCP_CMD_WIN_AUTO_SYN,			/*自动同步窗口显示 OK*/
			
			/*----------------------文本控件---------------------------*/
			DUCP_CMD_TWIN_CREATE = DUCP_CMD_TWIN_BASE,/*创建文本窗口 OK*/
			DUCP_CMD_TWIN_DEL,				/*删除文本窗口 OK*/
			DUCP_CMD_TWIN_DIS_TEXT,			/*显示临时文本 OK*/
			DUCP_CMD_TWIN_SET_FONT,	 		/*设置字体 OK*/
			DUCP_CMD_TWIN_SET_TCOLOR,		/*设置文本颜色 OK*/
			DUCP_CMD_TWIN_SET_BCOLOR,		/*设置背景颜色 OK*/
			DUCP_CMD_TWIN_STOP_DIS,			/*停止显示 OK*/
			DUCP_CMD_TWIN_DOWN_TFILE,		/*下载文本文件 OK*/
			DUCP_CMD_TWIN_DIS_TFILE,		/*显示文本文件 OK*/
			DUCP_CMD_TWIN_OPEN_TFILE,		/*打开文本文件 OK*/
			DUCP_CMD_TWIN_CLOSE_TFILE,		/*关闭文本文件 OK*/
			DUCP_CMD_TWIN_DEL_TFILE,		/*删除文本文件 OK*/
			DUCP_CMD_TWIN_SYN_DIS,			/*同步显示多个文本控件*/
			DUCP_CMD_TWIN_SYN_DISEX,		/*多行显示,同时播报语音*/

			/*----------------------图片控件---------------------------*/
			DUCP_CMD_PIC_CREATE = DUCP_CMD_PIC_BASE,/*创建图片窗口 OK*/
			DUCP_CMD_PIC_DEL,
			DUCP_CMD_PIC_ADD,
			DUCP_CMD_PIC_CLR,
			DUCP_CMD_PIC_QR, //171030
			DUCP_CMD_SwitchContoll,//171103
			DUCP_CMD_Secret_Key,

} DUCP_CMD_E;


typedef struct {
	char			DevName[8];/*设备名称*/
	char			SVR[8];		/*软件版本X.YZ*/
	uint32_t		XSize;		/*X尺寸*/
	uint32_t		YSize;		/*Y尺寸*/
	uint32_t		LstUpTime;	/*最后更新时间*/
	uint8_t			SN[12];		/*序列号*/
}DEVICE_FRAMWARE_T;

/*IO引脚标识*/
typedef enum {
	IO_PIN_1 = 0,
	IO_PIN_2,
	IO_PIN_3,
	IO_PIN_4,
	IO_PIN_ALL = 0XF0, /*对所以IO口进行赋值操作*/
	IO_PIN_OR,/*对所有IO口进行 或 操作*/
	IO_PIN_AND,/*对所有IO口进行 与 操作*/
	IO_PIN_NOT/*对所有IO口进行 非 操作*/
} IO_PIN_ID_E;

/*IO 功能枚举*/
typedef enum {
	IO_FUN_IN = 0, 	/*输入*/
	IO_FUN_PP,		/*推挽输出*/
	IO_FUN_OD,		/*开漏输出*/
} IO_PIN_FUN_E;


/*系统参数描述符*/
typedef struct {
	uint32_t 	Baud;	/*波特率 最高115200*/
	uint8_t  	_485Addr;/*485地址*/
	uint8_t  	_485CM;/*485工作模式 0:半双工 1:半工*/
	uint8_t  	IP[4];/*IP地址*/
	uint32_t  	Port;/*端口号*/
	uint8_t	 	GW[4];/*网关地址*/
	uint8_t	 	Mask[4];/*子网掩码*/
	uint16_t 	Fre;/*扫描频率 30Hz ~ 960Hz*/
	uint8_t  	LightLevel;/*亮度级别 10~100 对应10% ~ 100%*/
	uint8_t  	VoiceLevel;/*声音级别 10~100 对应10% ~ 100%*/
	uint8_t	 	OEP;/*OE极性，0:正极性 1:负极性*/
	uint8_t  	DP;/*数据极性，0:正极性 1:负极性*/
	uint8_t  	LEDey;/*LE信号延时，0:关闭 1:打开*/
	uint8_t  	LEDDrv;/*LED驱动程序 0:08双色16分之一扫描 1:12双色4分之一扫描 2:12双色8分之一扫描*/
	uint16_t 	XSize;/*显示屏长度尺寸 像素*/
	uint16_t 	YSize;/*显示屏高度尺寸 像素*/
	uint8_t	 	Orientation;/*XY镜像使能 0:原点坐标在左上角 1:原点坐标在右下角*/
	uint8_t		TTSAEn;/*0:定制语音。1:可以播报所有文字(需要配置外部TTS解码模块)*/
	uint8_t 	RLEn; // 0 RL disable  1 enable    
	uint8_t 	RLPlace;// 0 out  1 in
	uint8_t 	RLDis; // 0 two line  1  four line
	uint8_t 	RLColor; //0 onecolor 1 doublecolor
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


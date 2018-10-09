/*
****************************************************************************************************
*                                             DUCP HOST
*                      			Displayer universal control protocal for host
*                                      	   Master Head File
*
*                          			(c) Copyright 2016-2017, KF 
*                                        All Rights Reserved
*
* File : DUCP_Host.h
* By   : Lyon 
* Date : 2016-1-1
* Email: yangzhonglai@163.com
****************************************************************************************************
*/
#ifndef _DUCP_DEVICE_H_
#define _DUCP_DEVICE_H_

#include "MBmsg.h"
#include "DUCP.H"


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*
登录和连接DUCP服务器
*/
DUCP_ERR_T	DUCP_HOST_SYS_Connet(const char * Password);

/*
同步包序列
*/
DUCP_ERR_T	DUCP_HOST_SYS_SYNPN(int PN);

/*
更改登录密码
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetPassword(const char * Password);

/*
获取登录密码
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetPassword(char * Password);

/*
获取固件信息
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetFirmware(DEVICE_FRAMWARE_T * pFirmware);

/*
更新本地时间
*/
DUCP_ERR_T	DUCP_HOST_SYS_UpdateTime(uint16_t Year,
									uint8_t Month,
									uint8_t Day,
									uint8_t Week,
									uint8_t Hour,
									uint8_t Minute,
									uint8_t Second);

/*
设置地址
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetAddr(uint8_t Addr);

/*
设置IP地址
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetIP(const char * IP);
/*
设置端口
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetPort(uint32_t Port);

/*
设置波特率
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetBaud(uint32_t Baud);

/*
设置扫描频率
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetScanFre(uint16_t Fre);

/*
设置亮度
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetLight(uint8_t Light);

/*
设置音量
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetVol(uint8_t Vol);

/*
重启系统
*/
DUCP_ERR_T	DUCP_HOST_SYS_Reset(void);

/*
	配置IO口功能
*/
DUCP_ERR_T	DUCP_HOST_SYS_CfgIO(IO_PIN_ID_E Pin,IO_PIN_FUN_E Fun);

/*
	设置IO口输出状态
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetOutState(IO_PIN_ID_E Pin,int OnOff);

/*
	读取IO口输入状态
*/
DUCP_ERR_T	DUCP_HOST_SYS_ReadInputState(IO_PIN_ID_E Pin,int * pRetState);

/*
	设置LED驱动程序
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDrv(int v);

/*
	设置OE极性
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetOEPolarity(int v);

/*
	设置数据极性
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDataPolarity(int v);

/*
	设置LE信号延时
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetLEDelay(int En);

/*
	设置网关和掩码
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetGWAndMask(const char * GW,const char * Mask);

/*
	进入安全模式
*/
DUCP_ERR_T	DUCP_HOST_SYS_EnterSafMode(const char * pswd);

/*
	计算验证码
	
	Msg: 消息地址
	MsgLen: 消息长度，最多255个字节,如果大于255，只会计算前255个字节。
	pOutResult:返回的32位结果
*/
DUCP_ERR_T	DUCP_HOST_SYS_Clic(const char * Msg,int MsgLen,int * pOutResult);

/*
	设置显示尺寸
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDisSize(int XSize,int YSize);

/*
	设置显示镜像
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetXYMIR(int Flag);

/*
	设置485工作模式
*/
DUCP_ERR_T	DUCP_HOST_SYS_Set485Mode(int ModeIndex);

/*
	获取所有参数
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetAll(SysSettings_t * pSet);

/*
	设置所有参数
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetAll(SysSettings_t * pSet);

/*
	设置脱机
*/
DUCP_ERR_T	DUCP_HOST_SYS_Offline(int Mode, int Place, int Line, int Color);

/*
	恢复出厂设置
*/
DUCP_ERR_T	DUCP_HOST_SYS_Factory(void);

/*
	使能TTS播放所有文字(需要配置外部TTS硬件解码模块)
*/
DUCP_ERR_T	DUCP_HOST_SYS_TTSEn(int Enable);

/*
	挂载目录
*/
DUCP_ERR_T	DUCP_HOST_FM_Mount(const char * Path);

/*
	打开文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Open(const char * Path,int Opt);

/*
	设置文件的读写位置
*/
DUCP_ERR_T	DUCP_HOST_FM_Seek(int Offset);

/*
	写文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Write(const uint8_t * pData,uint32_t Size);

/*
	读文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Read(uint8_t * pData,uint32_t Size,uint32_t * pRetSize);

/*
	同步文件缓存数据
*/
DUCP_ERR_T	DUCP_HOST_FM_SynBuff(void);

/*
	关闭当前文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Close(void);

/*
	删除当前文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Del(const char * Path);

/*
	复制文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Copy(const char * DesPath,const char * SrcPath,int Opt);

/*
	格式化磁盘
*/
DUCP_ERR_T	DUCP_HOST_FM_FDisk(void);

/*
播放语音
*/
DUCP_ERR_T	DUCP_HOST_TTS_Play(const char * pText, uint8_t Opt);

/*
停止播放语音
*/
DUCP_ERR_T	DUCP_HOST_TTS_Stop(void);

/*
绘制点
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawPoint(int x0, int y0);

/*
绘制线
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawLine(int x0, int y0, int x1, int y1);

/*
绘制矩形
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawRect(int x0, int y0, int x1, int y1);

/*
填充矩形
*/
DUCP_ERR_T	DUCP_HOST_2D_FillRect(int x0, int y0, int x1, int y1);

/*
绘制圆
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawCircle(int x0, int y0, int r);

/*
填充圆
*/
DUCP_ERR_T	DUCP_HOST_2D_FillCircle(int x0, int y0, int r);

/*
绘制位图
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawBitmap(int x0, int y0, int xSize, int ySize,
									int BitsPerPixle, int BytesPerLine,
									int DataSize, int ColorTabelSize,
									const uint8_t * pData);

/*
显示文本
*/
DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText);

/*
设置绘图颜色
*/
DUCP_ERR_T	DUCP_HOST_2D_SetColor(int Color);

/*
设置背景颜色
*/
DUCP_ERR_T	DUCP_HOST_2D_SetBkColor(int Color);

/*
设置字体
*/
DUCP_ERR_T	DUCP_HOST_2D_SetFont(int FontIndex);

/*
绘制系统自带的位图
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawSysIcon(int x0, int y0, int Num,int Denom,int IconIndex);

/*
显示所有窗口
*/
DUCP_ERR_T	DUCP_HOST_WM_ShowWindow(int WinID);

/*
隐藏所有窗口
*/
DUCP_ERR_T	DUCP_HOST_WM_HideWindow(int WinID);

/*
删除所有窗口
*/
DUCP_ERR_T	DUCP_HOST_WM_DelWindow(int WinID);

/*
	设置窗口自动同步显示
*/
DUCP_ERR_T	DUCP_HOST_WM_AutoSyn(int En);


/*
创建文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_Create(int WinID, int Stile, int x0, int y0, int xSize, int ySize);

/*
删除文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_Del(int WinID);


/*
在文本控件上显示文本。这个接口下载的文字掉电后不能保存。推荐使用这个接口显示经常更改的内容。
*/
DUCP_ERR_T DUCP_HOST_TWIN_DisText(	int WinID,
									const char * pText,
									int EnterMode,
									int EnterSpeed,
									int DelayMode,
									int DelayTime,
									int EixtMode,
									int EixtSpeed,
									int FontIndex,
									int TextColor,
									int BkColor,
									int DisTimes);

/*
设置文本控件的字体
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetFont(int WinID, int FontIndex);

/*
设置文本控件的文本颜色
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetTextColor(int WinID, int Color);

/*
设置文本控件的背景颜色
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetBkColor(int WinID, int Color);

/*
停止显示文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_StopDis(int WinID);

/*
下载文本文件与文本控件关联。这个接口下载的文字会保存在磁盘中，掉电会保存。
不建议频繁使用这个接口，这样会对降低FLASH的使用寿命。
建议对不经常更改的内容下载到磁盘中。例如 广告语等。
*/
DUCP_ERR_T DUCP_HOST_TWIN_DownTextFile(	int WinID,
										int FileID,
										const char * pText,
										int EnterMode,
										int EnterSpeed,
										int DelayMode,
										int DelayTime,
										int EixtMode,
										int EixtSpeed,
										int FontIndex,
										int TextColor,
										int BkColor);
/*
显示文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_DisFile(int WinID, int FileID);

/*
打开文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_OpenFile(int WinID, int FileID);

/*
关闭文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_CloseFile(int WinID, int FileID);

/*
删除文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_DelFile(int WinID, int FileID);

/*
	同步显示多个文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_SynDis(char * pList,int NumBytes);

/*
	多行显示并且播报语音
*/
DUCP_ERR_T DUCP_HOST_TWIN_SYN_DisEx(	int StartWinID,
													const char * pText,
													int EnterMode,
													int EnterSpeed,
													int DelayMode,
													int DelayTime,
													int EixtMode,
													int EixtSpeed,
													int FontIndex,
													int TextColor,
													int BkColor,
													int DisTimes,
													const char * pVoice);

/*
创建图片控件
*/
DUCP_ERR_T DUCP_HOST_PIC_Create(int WinID,int x0, int y0, int xSize, int ySize);

/*
删除图片控件
*/
DUCP_ERR_T DUCP_HOST_PIC_Del(int WinID);

/*
向图片控件追加图片
*/
DUCP_ERR_T DUCP_HOST_PIC_Add(int WinID,int FID,uint8_t EnterMode,uint8_t EnterSpeed,
							uint8_t StopMode,uint8_t StopTime,uint8_t ExitMode,uint8_t ExitSpeed);

/*
删除所有图片
*/
DUCP_ERR_T DUCP_HOST_PIC_Clr(int WinID);

DUCP_ERR_T	 DUCP_HOST_PIC_DrawQR(int x0, int y0, uint8_t option, uint8_t time, const char * pText);
DUCP_ERR_T	DUCP_HOST_SwtichCount_Controll(uint8_t option, SwitchControll_t *swcnr);
DUCP_ERR_T	DUCP_HOST_Secret_Key(uint8_t option, uint32_t * key);
typedef struct {
	uint8_t 	DA;
	uint8_t 	SP;
	uint8_t 	PN[2];
	uint8_t  	MsgId;
	uint8_t 	DLen;
	uint8_t  	Data[MB_MSG_SIZE_MAX];
} rMB_MSG_T;

rMB_MSG_T*	DUCP_HOST_PIC_DrawQR0(int x0, int y0, uint8_t option, uint8_t time, const char * pText);
rMB_MSG_T*	DUCP_HOST_SYS_UpdateTime0(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Week, uint8_t Hour, uint8_t Minute, uint8_t Second);
rMB_MSG_T*	DUCP_HOST_SYS_SetVol0(uint8_t Vol);
rMB_MSG_T*	DUCP_HOST_SYS_SetOutState0(IO_PIN_ID_E Pin, int OnOff);
rMB_MSG_T*	DUCP_HOST_TTS_Play0(const char * pText, uint8_t Opt);
rMB_MSG_T*   DUCP_HOST_TWIN_DisText0(int WinID,
	const char * pText,
	int EnterMode,
	int EnterSpeed,
	int DelayMode,
	int DelayTime,
	int EixtMode,
	int EixtSpeed,
	int FontIndex,
	int TextColor,
	int BkColor,
	int DisTimes);
rMB_MSG_T*  DUCP_HOST_TWIN_DownTextFile0(int WinID,
	int FileID,
	const char * pText,
	int EnterMode,
	int EnterSpeed,
	int DelayMode,
	int DelayTime,
	int EixtMode,
	int EixtSpeed,
	int FontIndex,
	int TextColor,
	int BkColor);

#if defined(__cplusplus)
}
#endif

#endif



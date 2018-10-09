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

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DUCP_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DUCP_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DUCP_EXPORTS
#define DUCP_API __declspec(dllexport)
#else
#define DUCP_API __declspec(dllimport)
#endif


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*
登录和连接DUCP服务器
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Connet(const char * Password);

/*
同步包序列
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SYNPN(int PN);

/*
更改登录密码
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetPassword(const char * Password);

/*
获取登录密码
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_GetPassword(char * Password);

/*
获取固件信息
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_GetFirmware(DEVICE_FRAMWARE_T * pFirmware);

/*
更新本地时间
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_UpdateTime(uint16_t Year,
									uint8_t Month,
									uint8_t Day,
									uint8_t Week,
									uint8_t Hour,
									uint8_t Minute,
									uint8_t Second);

/*
设置地址
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetAddr(uint8_t Addr);

/*
设置IP地址
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetIP(const char * IP);
/*
设置端口
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetPort(uint32_t Port);

/*
设置波特率
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetBaud(uint32_t Baud);

/*
设置扫描频率
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetScanFre(uint16_t Fre);

/*
设置亮度
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetLight(uint8_t Light);

/*
设置音量
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetVol(uint8_t Vol);

/*
重启系统
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Reset(void);

/*
	配置IO口功能
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_CfgIO(IO_PIN_ID_E Pin,IO_PIN_FUN_E Fun);

/*
	设置IO口输出状态
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetOutState(IO_PIN_ID_E Pin,int OnOff);

/*
	读取IO口输入状态
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_ReadInputState(IO_PIN_ID_E Pin,int * pRetState);

/*
	设置LED驱动程序
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetDrv(int v);

/*
	设置OE极性
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetOEPolarity(int v);

/*
	设置数据极性
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetDataPolarity(int v);

/*
	设置LE信号延时
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetLEDelay(int En);

/*
	设置网关和掩码
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetGWAndMask(const char * GW,const char * Mask);

/*
	进入安全模式
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_EnterSafMode(const char * pswd);

/*
	计算验证码
	
	Msg: 消息地址
	MsgLen: 消息长度，最多255个字节,如果大于255，只会计算前255个字节。
	pOutResult:返回的32位结果
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Clic(const char * Msg,int MsgLen,int * pOutResult);

/*
	设置显示尺寸
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetDisSize(int XSize,int YSize);

/*
	设置显示镜像
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetXYMIR(int Flag);

/*
	设置485工作模式
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Set485Mode(int ModeIndex);

/*
	获取所有参数
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_GetAll(SysSettings_t * pSet);

/*
	设置所有参数
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetAll(SysSettings_t * pSet);

/*
	使能TTS播放所有文字(需要配置外部TTS硬件解码模块)
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_TTSEn(int Enable);

/*
	挂载目录
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Mount(const char * Path);

/*
	打开文件
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Open(const char * Path,int Opt);

/*
	设置文件的读写位置
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Seek(int Offset);

/*
	写文件
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Write(const uint8_t * pData,uint32_t Size);

/*
	读文件
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Read(uint8_t * pData,uint32_t Size,uint32_t * pRetSize);

/*
	同步文件缓存数据
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_SynBuff(void);

/*
	关闭当前文件
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Close(void);

/*
	删除当前文件
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Del(const char * Path);

/*
	复制文件
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Copy(const char * DesPath,const char * SrcPath,int Opt);

/*
	格式化磁盘
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_FDisk(void);

/*
播放语音
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_TTS_Play(const char * pText, uint8_t Opt);

/*
停止播放语音
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_TTS_Stop(void);

/*
绘制点
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawPoint(int x0, int y0);

/*
绘制线
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawLine(int x0, int y0, int x1, int y1);

/*
绘制矩形
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawRect(int x0, int y0, int x1, int y1);

/*
填充矩形
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_FillRect(int x0, int y0, int x1, int y1);

/*
绘制圆
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawCircle(int x0, int y0, int r);

/*
填充圆
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_FillCircle(int x0, int y0, int r);

/*
绘制位图
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawBitmap(int x0, int y0, int xSize, int ySize,
									int BitsPerPixle, int BytesPerLine,
									int DataSize, int ColorTabelSize,
									const uint8_t * pData);

/*
显示文本
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText);

/*
设置绘图颜色
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_SetColor(int Color);

/*
设置背景颜色
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_SetBkColor(int Color);

/*
设置字体
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_SetFont(int FontIndex);

/*
绘制系统自带的位图
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawSysIcon(int x0, int y0, int Num,int Denom,int IconIndex);

/*
显示所有窗口
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_ShowWindow(int WinID);

/*
隐藏所有窗口
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_HideWindow(int WinID);

/*
删除所有窗口
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_DelWindow(int WinID);

/*
	设置窗口自动同步显示
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_AutoSyn(int En);


/*
创建文本控件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_Create(int WinID, int Stile, int x0, int y0, int xSize, int ySize);

/*
删除文本控件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_Del(int WinID);


/*
在文本控件上显示文本。这个接口下载的文字掉电后不能保存。推荐使用这个接口显示经常更改的内容。
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_DisText(	int WinID,
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
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SetFont(int WinID, int FontIndex);

/*
设置文本控件的文本颜色
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SetTextColor(int WinID, int Color);

/*
设置文本控件的背景颜色
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SetBkColor(int WinID, int Color);

/*
停止显示文本控件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_StopDis(int WinID);

/*
下载文本文件与文本控件关联。这个接口下载的文字会保存在磁盘中，掉电会保存。
不建议频繁使用这个接口，这样会对降低FLASH的使用寿命。
建议对不经常更改的内容下载到磁盘中。例如 广告语等。
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_DownTextFile(	int WinID,
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
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_DisFile(int WinID, int FileID);

/*
打开文本控件的文本文件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_OpenFile(int WinID, int FileID);

/*
关闭文本控件的文本文件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_CloseFile(int WinID, int FileID);

/*
删除文本控件的文本文件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_DelFile(int WinID, int FileID);

/*
	同步显示多个文本控件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SynDis(char * pList,int NumBytes);

/*
	多行显示并且播报语音
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SYN_DisEx(	int StartWinID,
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
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Create(int WinID,int x0, int y0, int xSize, int ySize);

/*
删除图片控件
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Del(int WinID);

/*
向图片控件追加图片
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Add(int WinID,int FID,uint8_t EnterMode,uint8_t EnterSpeed,
							uint8_t StopMode,uint8_t StopTime,uint8_t ExitMode,uint8_t ExitSpeed);

/*
删除所有图片
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Clr(int WinID);

#if defined(__cplusplus)
}
#endif

#endif



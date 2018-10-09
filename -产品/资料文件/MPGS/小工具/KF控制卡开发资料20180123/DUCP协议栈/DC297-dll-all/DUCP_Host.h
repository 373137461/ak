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
��¼������DUCP������
*/
DUCP_ERR_T	DUCP_HOST_SYS_Connet(const char * Password);

/*
ͬ��������
*/
DUCP_ERR_T	DUCP_HOST_SYS_SYNPN(int PN);

/*
���ĵ�¼����
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetPassword(const char * Password);

/*
��ȡ��¼����
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetPassword(char * Password);

/*
��ȡ�̼���Ϣ
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetFirmware(DEVICE_FRAMWARE_T * pFirmware);

/*
���±���ʱ��
*/
DUCP_ERR_T	DUCP_HOST_SYS_UpdateTime(uint16_t Year,
									uint8_t Month,
									uint8_t Day,
									uint8_t Week,
									uint8_t Hour,
									uint8_t Minute,
									uint8_t Second);

/*
���õ�ַ
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetAddr(uint8_t Addr);

/*
����IP��ַ
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetIP(const char * IP);
/*
���ö˿�
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetPort(uint32_t Port);

/*
���ò�����
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetBaud(uint32_t Baud);

/*
����ɨ��Ƶ��
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetScanFre(uint16_t Fre);

/*
��������
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetLight(uint8_t Light);

/*
��������
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetVol(uint8_t Vol);

/*
����ϵͳ
*/
DUCP_ERR_T	DUCP_HOST_SYS_Reset(void);

/*
	����IO�ڹ���
*/
DUCP_ERR_T	DUCP_HOST_SYS_CfgIO(IO_PIN_ID_E Pin,IO_PIN_FUN_E Fun);

/*
	����IO�����״̬
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetOutState(IO_PIN_ID_E Pin,int OnOff);

/*
	��ȡIO������״̬
*/
DUCP_ERR_T	DUCP_HOST_SYS_ReadInputState(IO_PIN_ID_E Pin,int * pRetState);

/*
	����LED��������
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDrv(int v);

/*
	����OE����
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetOEPolarity(int v);

/*
	�������ݼ���
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDataPolarity(int v);

/*
	����LE�ź���ʱ
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetLEDelay(int En);

/*
	�������غ�����
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetGWAndMask(const char * GW,const char * Mask);

/*
	���밲ȫģʽ
*/
DUCP_ERR_T	DUCP_HOST_SYS_EnterSafMode(const char * pswd);

/*
	������֤��
	
	Msg: ��Ϣ��ַ
	MsgLen: ��Ϣ���ȣ����255���ֽ�,�������255��ֻ�����ǰ255���ֽڡ�
	pOutResult:���ص�32λ���
*/
DUCP_ERR_T	DUCP_HOST_SYS_Clic(const char * Msg,int MsgLen,int * pOutResult);

/*
	������ʾ�ߴ�
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDisSize(int XSize,int YSize);

/*
	������ʾ����
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetXYMIR(int Flag);

/*
	����485����ģʽ
*/
DUCP_ERR_T	DUCP_HOST_SYS_Set485Mode(int ModeIndex);

/*
	��ȡ���в���
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetAll(SysSettings_t * pSet);

/*
	�������в���
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetAll(SysSettings_t * pSet);

/*
	�����ѻ�
*/
DUCP_ERR_T	DUCP_HOST_SYS_Offline(int Mode, int Place, int Line, int Color);

/*
	�ָ���������
*/
DUCP_ERR_T	DUCP_HOST_SYS_Factory(void);

/*
	ʹ��TTS������������(��Ҫ�����ⲿTTSӲ������ģ��)
*/
DUCP_ERR_T	DUCP_HOST_SYS_TTSEn(int Enable);

/*
	����Ŀ¼
*/
DUCP_ERR_T	DUCP_HOST_FM_Mount(const char * Path);

/*
	���ļ�
*/
DUCP_ERR_T	DUCP_HOST_FM_Open(const char * Path,int Opt);

/*
	�����ļ��Ķ�дλ��
*/
DUCP_ERR_T	DUCP_HOST_FM_Seek(int Offset);

/*
	д�ļ�
*/
DUCP_ERR_T	DUCP_HOST_FM_Write(const uint8_t * pData,uint32_t Size);

/*
	���ļ�
*/
DUCP_ERR_T	DUCP_HOST_FM_Read(uint8_t * pData,uint32_t Size,uint32_t * pRetSize);

/*
	ͬ���ļ���������
*/
DUCP_ERR_T	DUCP_HOST_FM_SynBuff(void);

/*
	�رյ�ǰ�ļ�
*/
DUCP_ERR_T	DUCP_HOST_FM_Close(void);

/*
	ɾ����ǰ�ļ�
*/
DUCP_ERR_T	DUCP_HOST_FM_Del(const char * Path);

/*
	�����ļ�
*/
DUCP_ERR_T	DUCP_HOST_FM_Copy(const char * DesPath,const char * SrcPath,int Opt);

/*
	��ʽ������
*/
DUCP_ERR_T	DUCP_HOST_FM_FDisk(void);

/*
��������
*/
DUCP_ERR_T	DUCP_HOST_TTS_Play(const char * pText, uint8_t Opt);

/*
ֹͣ��������
*/
DUCP_ERR_T	DUCP_HOST_TTS_Stop(void);

/*
���Ƶ�
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawPoint(int x0, int y0);

/*
������
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawLine(int x0, int y0, int x1, int y1);

/*
���ƾ���
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawRect(int x0, int y0, int x1, int y1);

/*
������
*/
DUCP_ERR_T	DUCP_HOST_2D_FillRect(int x0, int y0, int x1, int y1);

/*
����Բ
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawCircle(int x0, int y0, int r);

/*
���Բ
*/
DUCP_ERR_T	DUCP_HOST_2D_FillCircle(int x0, int y0, int r);

/*
����λͼ
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawBitmap(int x0, int y0, int xSize, int ySize,
									int BitsPerPixle, int BytesPerLine,
									int DataSize, int ColorTabelSize,
									const uint8_t * pData);

/*
��ʾ�ı�
*/
DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText);

/*
���û�ͼ��ɫ
*/
DUCP_ERR_T	DUCP_HOST_2D_SetColor(int Color);

/*
���ñ�����ɫ
*/
DUCP_ERR_T	DUCP_HOST_2D_SetBkColor(int Color);

/*
��������
*/
DUCP_ERR_T	DUCP_HOST_2D_SetFont(int FontIndex);

/*
����ϵͳ�Դ���λͼ
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawSysIcon(int x0, int y0, int Num,int Denom,int IconIndex);

/*
��ʾ���д���
*/
DUCP_ERR_T	DUCP_HOST_WM_ShowWindow(int WinID);

/*
�������д���
*/
DUCP_ERR_T	DUCP_HOST_WM_HideWindow(int WinID);

/*
ɾ�����д���
*/
DUCP_ERR_T	DUCP_HOST_WM_DelWindow(int WinID);

/*
	���ô����Զ�ͬ����ʾ
*/
DUCP_ERR_T	DUCP_HOST_WM_AutoSyn(int En);


/*
�����ı��ؼ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_Create(int WinID, int Stile, int x0, int y0, int xSize, int ySize);

/*
ɾ���ı��ؼ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_Del(int WinID);


/*
���ı��ؼ�����ʾ�ı�������ӿ����ص����ֵ�����ܱ��档�Ƽ�ʹ������ӿ���ʾ�������ĵ����ݡ�
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
�����ı��ؼ�������
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetFont(int WinID, int FontIndex);

/*
�����ı��ؼ����ı���ɫ
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetTextColor(int WinID, int Color);

/*
�����ı��ؼ��ı�����ɫ
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetBkColor(int WinID, int Color);

/*
ֹͣ��ʾ�ı��ؼ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_StopDis(int WinID);

/*
�����ı��ļ����ı��ؼ�����������ӿ����ص����ֻᱣ���ڴ����У�����ᱣ�档
������Ƶ��ʹ������ӿڣ�������Խ���FLASH��ʹ��������
����Բ��������ĵ��������ص������С����� �����ȡ�
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
��ʾ�ı��ؼ����ı��ļ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_DisFile(int WinID, int FileID);

/*
���ı��ؼ����ı��ļ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_OpenFile(int WinID, int FileID);

/*
�ر��ı��ؼ����ı��ļ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_CloseFile(int WinID, int FileID);

/*
ɾ���ı��ؼ����ı��ļ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_DelFile(int WinID, int FileID);

/*
	ͬ����ʾ����ı��ؼ�
*/
DUCP_ERR_T DUCP_HOST_TWIN_SynDis(char * pList,int NumBytes);

/*
	������ʾ���Ҳ�������
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
����ͼƬ�ؼ�
*/
DUCP_ERR_T DUCP_HOST_PIC_Create(int WinID,int x0, int y0, int xSize, int ySize);

/*
ɾ��ͼƬ�ؼ�
*/
DUCP_ERR_T DUCP_HOST_PIC_Del(int WinID);

/*
��ͼƬ�ؼ�׷��ͼƬ
*/
DUCP_ERR_T DUCP_HOST_PIC_Add(int WinID,int FID,uint8_t EnterMode,uint8_t EnterSpeed,
							uint8_t StopMode,uint8_t StopTime,uint8_t ExitMode,uint8_t ExitSpeed);

/*
ɾ������ͼƬ
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



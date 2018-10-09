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

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DUCP_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DUCP_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DUCP_EXPORTS
#define DUCP_API __declspec(dllexport)
#else
#define DUCP_API __declspec(dllimport)
#endif


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*
��¼������DUCP������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Connet(const char * Password);

/*
ͬ��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SYNPN(int PN);

/*
���ĵ�¼����
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetPassword(const char * Password);

/*
��ȡ��¼����
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_GetPassword(char * Password);

/*
��ȡ�̼���Ϣ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_GetFirmware(DEVICE_FRAMWARE_T * pFirmware);

/*
���±���ʱ��
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_UpdateTime(uint16_t Year,
									uint8_t Month,
									uint8_t Day,
									uint8_t Week,
									uint8_t Hour,
									uint8_t Minute,
									uint8_t Second);

/*
���õ�ַ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetAddr(uint8_t Addr);

/*
����IP��ַ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetIP(const char * IP);
/*
���ö˿�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetPort(uint32_t Port);

/*
���ò�����
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetBaud(uint32_t Baud);

/*
����ɨ��Ƶ��
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetScanFre(uint16_t Fre);

/*
��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetLight(uint8_t Light);

/*
��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetVol(uint8_t Vol);

/*
����ϵͳ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Reset(void);

/*
	����IO�ڹ���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_CfgIO(IO_PIN_ID_E Pin,IO_PIN_FUN_E Fun);

/*
	����IO�����״̬
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetOutState(IO_PIN_ID_E Pin,int OnOff);

/*
	��ȡIO������״̬
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_ReadInputState(IO_PIN_ID_E Pin,int * pRetState);

/*
	����LED��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetDrv(int v);

/*
	����OE����
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetOEPolarity(int v);

/*
	�������ݼ���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetDataPolarity(int v);

/*
	����LE�ź���ʱ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetLEDelay(int En);

/*
	�������غ�����
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetGWAndMask(const char * GW,const char * Mask);

/*
	���밲ȫģʽ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_EnterSafMode(const char * pswd);

/*
	������֤��
	
	Msg: ��Ϣ��ַ
	MsgLen: ��Ϣ���ȣ����255���ֽ�,�������255��ֻ�����ǰ255���ֽڡ�
	pOutResult:���ص�32λ���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Clic(const char * Msg,int MsgLen,int * pOutResult);

/*
	������ʾ�ߴ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetDisSize(int XSize,int YSize);

/*
	������ʾ����
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetXYMIR(int Flag);

/*
	����485����ģʽ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_Set485Mode(int ModeIndex);

/*
	��ȡ���в���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_GetAll(SysSettings_t * pSet);

/*
	�������в���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_SetAll(SysSettings_t * pSet);

/*
	ʹ��TTS������������(��Ҫ�����ⲿTTSӲ������ģ��)
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_SYS_TTSEn(int Enable);

/*
	����Ŀ¼
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Mount(const char * Path);

/*
	���ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Open(const char * Path,int Opt);

/*
	�����ļ��Ķ�дλ��
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Seek(int Offset);

/*
	д�ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Write(const uint8_t * pData,uint32_t Size);

/*
	���ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Read(uint8_t * pData,uint32_t Size,uint32_t * pRetSize);

/*
	ͬ���ļ���������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_SynBuff(void);

/*
	�رյ�ǰ�ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Close(void);

/*
	ɾ����ǰ�ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Del(const char * Path);

/*
	�����ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_Copy(const char * DesPath,const char * SrcPath,int Opt);

/*
	��ʽ������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_FM_FDisk(void);

/*
��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_TTS_Play(const char * pText, uint8_t Opt);

/*
ֹͣ��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_TTS_Stop(void);

/*
���Ƶ�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawPoint(int x0, int y0);

/*
������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawLine(int x0, int y0, int x1, int y1);

/*
���ƾ���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawRect(int x0, int y0, int x1, int y1);

/*
������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_FillRect(int x0, int y0, int x1, int y1);

/*
����Բ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawCircle(int x0, int y0, int r);

/*
���Բ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_FillCircle(int x0, int y0, int r);

/*
����λͼ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawBitmap(int x0, int y0, int xSize, int ySize,
									int BitsPerPixle, int BytesPerLine,
									int DataSize, int ColorTabelSize,
									const uint8_t * pData);

/*
��ʾ�ı�
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText);

/*
���û�ͼ��ɫ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_SetColor(int Color);

/*
���ñ�����ɫ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_SetBkColor(int Color);

/*
��������
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_SetFont(int FontIndex);

/*
����ϵͳ�Դ���λͼ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_2D_DrawSysIcon(int x0, int y0, int Num,int Denom,int IconIndex);

/*
��ʾ���д���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_ShowWindow(int WinID);

/*
�������д���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_HideWindow(int WinID);

/*
ɾ�����д���
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_DelWindow(int WinID);

/*
	���ô����Զ�ͬ����ʾ
*/
EXTERN_C DUCP_API DUCP_ERR_T	DUCP_HOST_WM_AutoSyn(int En);


/*
�����ı��ؼ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_Create(int WinID, int Stile, int x0, int y0, int xSize, int ySize);

/*
ɾ���ı��ؼ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_Del(int WinID);


/*
���ı��ؼ�����ʾ�ı�������ӿ����ص����ֵ�����ܱ��档�Ƽ�ʹ������ӿ���ʾ�������ĵ����ݡ�
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
�����ı��ؼ�������
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SetFont(int WinID, int FontIndex);

/*
�����ı��ؼ����ı���ɫ
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SetTextColor(int WinID, int Color);

/*
�����ı��ؼ��ı�����ɫ
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SetBkColor(int WinID, int Color);

/*
ֹͣ��ʾ�ı��ؼ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_StopDis(int WinID);

/*
�����ı��ļ����ı��ؼ�����������ӿ����ص����ֻᱣ���ڴ����У�����ᱣ�档
������Ƶ��ʹ������ӿڣ�������Խ���FLASH��ʹ��������
����Բ��������ĵ��������ص������С����� �����ȡ�
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
��ʾ�ı��ؼ����ı��ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_DisFile(int WinID, int FileID);

/*
���ı��ؼ����ı��ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_OpenFile(int WinID, int FileID);

/*
�ر��ı��ؼ����ı��ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_CloseFile(int WinID, int FileID);

/*
ɾ���ı��ؼ����ı��ļ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_DelFile(int WinID, int FileID);

/*
	ͬ����ʾ����ı��ؼ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_TWIN_SynDis(char * pList,int NumBytes);

/*
	������ʾ���Ҳ�������
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
����ͼƬ�ؼ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Create(int WinID,int x0, int y0, int xSize, int ySize);

/*
ɾ��ͼƬ�ؼ�
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Del(int WinID);

/*
��ͼƬ�ؼ�׷��ͼƬ
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Add(int WinID,int FID,uint8_t EnterMode,uint8_t EnterSpeed,
							uint8_t StopMode,uint8_t StopTime,uint8_t ExitMode,uint8_t ExitSpeed);

/*
ɾ������ͼƬ
*/
EXTERN_C DUCP_API DUCP_ERR_T DUCP_HOST_PIC_Clr(int WinID);

#if defined(__cplusplus)
}
#endif

#endif



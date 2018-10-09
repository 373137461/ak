/*
****************************************************************************************************
*                                             DUCP HOST
*                      			Displayer universal control protocal for host
*                                      	   Master Source File
*
*                          			(c) Copyright 2016-2017, KF 
*                                        All Rights Reserved
*
* File : DUCP_Host.c
* By   : Lyon 
* Date : 2016-1-1
* Email: yangzhonglai@163.com
****************************************************************************************************
*/
#include <stdint.h>
#include "DUCP_Host.H"




MB_MSG_T Msg;
MB_MSG_T * pMsg = &Msg;

static int _SendMsgOverTimeDef = SEND_MSG_OVERTIME_DEF;
static int _ReadMsgOverTimeDef = READ_MSG_OVERTIME_DEF;

static void * memcpy(void * pvDes, const void  *pvSrc, uint32_t Size)
{
	void * pvDesBk = pvDes;
	if (!pvDes || !pvSrc) {
		return pvDesBk;
	}
	while (Size--) {
		*((uint8_t *)pvDes)++ = *((uint8_t *)pvSrc)++;
	}

	return pvDesBk;
}

static uint32_t strlen(const char  *p)
{
	uint32_t Len = 0;
	if (!p) {
		return 0;
	}
	while (*p != 0) {
		Len ++;
		p ++;
	}
	return Len;
}

static char * strcpy(char  *pdes,const char *psrc)
{
	uint32_t Len = 0;
	char * pDesBk = pdes;
	if (!pdes || !psrc) {
		return pDesBk;
	}
	while (*psrc != 0) {
		Len ++;
		*pdes ++ = *psrc ++;
	}
	return pDesBk;
}

uint32_t ConvertStrToInt(const char ** ppStr, uint8_t Length)
{
	uint32_t Value;
	uint32_t Temp;
	uint8_t x;
	const char * pStr = *ppStr;

	int i;
	for (i = 0; i < Length; i++) {
		if ((pStr[i] > '9') || (pStr[i] < '0')) {
			break;
		}
	}
	Length = i;

	Value = 0;
	while (Length--) {
		Temp = 1;
		x = Length;
		while (x--)
			Temp *= 10;
		Temp *= (*pStr++ - '0');
		Value += Temp;
	}
	if (*pStr != 0) {
		pStr++;
	}
	*ppStr = pStr;
	return Value;
}


/*
	交互一次消息
*/
DUCP_ERR_T	_TsfMsg(MB_MSG_T * pMsg,int SendOvt,int ReadOvt)
{
	uint8_t MsgId;
	
	MsgId = pMsg->MsgId;
	if(MB_MSG_Send(pMsg,SendOvt)) {
		return ((MsgId)?MsgId:0xff);
	}
	if (MB_MSG_Read(pMsg, ReadOvt)) {
		return ((MsgId) ? MsgId : 0xff);
	}
	if(pMsg->MsgId != MsgId) {
		return ((MsgId)?MsgId:0xff);
	}
	return DUCP_ERR_NONE;
}

MB_MSG_T*	Return_TsfMsg(MB_MSG_T * pMsg, int SendOvt, int ReadOvt)
{
	uint8_t MsgId;

	//MsgId = pMsg->MsgId

	return Return_MB_MSG(pMsg, SendOvt);
}


/*
	登录和连接UDCP服务器
*/
DUCP_ERR_T	DUCP_HOST_SYS_Connet(const char * Password)
{
	DUCP_ERR_T Err;
	
	memcpy(pMsg->Data,Password,6);
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_CONNECT;
	pMsg->DLen = 6;
	Err = _TsfMsg(pMsg,_SendMsgOverTimeDef,_ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = pMsg->Data[0];
	return Err;
}
/*
同步包序列
*/
DUCP_ERR_T	DUCP_HOST_SYS_SYNPN(int PN)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SYN_PN;
	pMsg->DLen = 2;
	pMsg->Data[0] = PN & 0xff;
	pMsg->Data[1] = (PN >> 8) & 0xff;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = pMsg->Data[0];
	return Err;
}

/*
	更改登录密码
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetPassword(const char * Password)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_PASSWAORD;
	pMsg->DLen = 6;
	memcpy(pMsg->Data,Password,6);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = pMsg->Data[0];
	return Err;
}

/*
	获取登录密码
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetPassword(char * Password)
{
	DUCP_ERR_T Err;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_GET_PASSWAORD;
	pMsg->DLen = 0;

	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	if(pMsg->DLen != 6) {
		return DUCP_CMD_SYS_GET_PASSWAORD;
	}
	memcpy(Password,pMsg->Data,6);
	return DUCP_ERR_NONE;
}


/*
获取设备固件信息
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetFirmware(DEVICE_FRAMWARE_T * pFrimware)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_GET_FIRMWARE;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	if (pMsg->DLen != sizeof(DEVICE_FRAMWARE_T)) {
		return DUCP_CMD_SYS_GET_FIRMWARE;
	}
	memcpy(pFrimware, pMsg->Data, sizeof(DEVICE_FRAMWARE_T));
	return DUCP_ERR_NONE;
}

/*
更新本地时间
*/
DUCP_ERR_T	DUCP_HOST_SYS_UpdateTime(uint16_t Year,uint8_t Month,uint8_t Day,uint8_t Week,uint8_t Hour,uint8_t Minute,uint8_t Second)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_UPTIME;
	pMsg->DLen = 8;
	*(uint16_t *)&pMsg->Data[0] = Year;
	pMsg->Data[2] = Month;
	pMsg->Data[3] = Day;
	pMsg->Data[4] = Week;
	pMsg->Data[5] = Hour;
	pMsg->Data[6] = Minute;
	pMsg->Data[7] = Second;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = pMsg->Data[0];
	return Err;
}
//=========================================================================================================================================
rMB_MSG_T*	DUCP_HOST_SYS_UpdateTime0(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Week, uint8_t Hour, uint8_t Minute, uint8_t Second)
{
	rMB_MSG_T *ptr;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_UPTIME;
	pMsg->DLen = 8;
	*(uint16_t *)&pMsg->Data[0] = Year;
	pMsg->Data[2] = Month;
	pMsg->Data[3] = Day;
	pMsg->Data[4] = Week;
	pMsg->Data[5] = Hour;
	pMsg->Data[6] = Minute;
	pMsg->Data[7] = Second;
	ptr = Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct  MB_MSG_T *ptr;
	return ptr;
}
/*
重启系统
*/
DUCP_ERR_T	DUCP_HOST_SYS_Reset(void)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_RESET;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = pMsg->Data[0];
	return Err;
}

/*
	设置地址
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetAddr(uint8_t Addr)
{
	DUCP_ERR_T Err;

	pMsg->Data[0] = Addr;
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_ADDR;
	pMsg->DLen = 1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = pMsg->Data[0];
	return Err;
}


/*
	设置IP地址
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetIP(const char * IP)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_IP;
	pMsg->DLen = 4;
	pMsg->Data[0] = (uint8_t)ConvertStrToInt(&IP, 3);
	pMsg->Data[1] = (uint8_t)ConvertStrToInt(&IP, 3);
	pMsg->Data[2] = (uint8_t)ConvertStrToInt(&IP, 3);
	pMsg->Data[3] = (uint8_t)ConvertStrToInt(&IP, 3);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	设置端口
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetPort(uint32_t Port)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_PORT;
	pMsg->DLen = 4;
	*(uint32_t *)&pMsg->Data[0] = Port;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	设置波特率
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetBaud(uint32_t Baud)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_BAUD;
	pMsg->DLen = 4;
	*(uint32_t *)&pMsg->Data[0] = Baud;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	设置扫描频率
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetScanFre(uint16_t Fre)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_SCAN_FRE;
	pMsg->DLen = 2;
	*(uint16_t *)&pMsg->Data[0] = Fre;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
	设置亮度
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetLight(uint8_t Light)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_LIGHT;
	pMsg->DLen = 1;
	pMsg->Data[0] = Light;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
	设置音量
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetVol(uint8_t Vol)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_VOL;
	pMsg->DLen = 1;
	pMsg->Data[0] = Vol;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}
//====================================================================================================================
rMB_MSG_T*	DUCP_HOST_SYS_SetVol0(uint8_t Vol)
{
	DUCP_ERR_T Err;
	rMB_MSG_T *ptr;
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_VOL;
	pMsg->DLen = 1;
	pMsg->Data[0] = Vol;
	ptr = Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct  MB_MSG_T *ptr;
	return ptr;
}
/*
	配置IO口功能
*/
DUCP_ERR_T	DUCP_HOST_SYS_CfgIO(IO_PIN_ID_E Pin,IO_PIN_FUN_E Fun)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_CFG_IO;
	pMsg->DLen = 2;
	pMsg->Data[0] = Pin;
	pMsg->Data[1] = Fun;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	设置IO口输出状态
*/
//uint8_t  rebox[255];
///==================================================================================================================================
rMB_MSG_T*	DUCP_HOST_SYS_SetOutState0(IO_PIN_ID_E Pin, int OnOff)
{
	DUCP_ERR_T Err;
	rMB_MSG_T *ptr;
	//ptr = &rebox[0];
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_IO;
	pMsg->DLen = 5;
	pMsg->Data[0] = Pin;
	*(int *)&pMsg->Data[1] = OnOff;
	//Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);

	ptr=Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct  MB_MSG_T *ptr;
	/*if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;*/
	return ptr;

}
///==================================================================================================================================
DUCP_ERR_T	DUCP_HOST_SYS_SetOutState(IO_PIN_ID_E Pin, int OnOff)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_IO;
	pMsg->DLen = 5;
	pMsg->Data[0] = Pin;
	*(int *)&pMsg->Data[1] = OnOff;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	读取IO口输入状态
*/
DUCP_ERR_T	DUCP_HOST_SYS_ReadInputState(IO_PIN_ID_E Pin,int * pRetState)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_READ_IO;
	pMsg->DLen = 1;
	pMsg->Data[0] = Pin;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		*pRetState = 0;
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	*pRetState = *(uint32_t *)&pMsg->Data[1];
	return Err;
}

/*
	设置LED驱动程序
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDrv(int v)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_DRV;
	pMsg->DLen = 1;
	pMsg->Data[0] = v;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}


/*
	设置OE极性
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetOEPolarity(int v)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_OEP;
	pMsg->DLen = 1;
	pMsg->Data[0] = v;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	设置数据极性
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDataPolarity(int v)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_DP;
	pMsg->DLen = 1;
	pMsg->Data[0] = v;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	设置LE信号延时
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetLEDelay(int En)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_LE;
	pMsg->DLen = 1;
	pMsg->Data[0] = En;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	设置网关和掩码
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetGWAndMask(const char * GW,const char * Mask)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_GW_AND_MASK;
	pMsg->DLen = 8;
	pMsg->Data[0] = (uint8_t)ConvertStrToInt(&GW, 3);
	pMsg->Data[1] = (uint8_t)ConvertStrToInt(&GW, 3);
	pMsg->Data[2] = (uint8_t)ConvertStrToInt(&GW, 3);
	pMsg->Data[3] = (uint8_t)ConvertStrToInt(&GW, 3);
	pMsg->Data[4] = (uint8_t)ConvertStrToInt(&Mask, 3);
	pMsg->Data[5] = (uint8_t)ConvertStrToInt(&Mask, 3);
	pMsg->Data[6] = (uint8_t)ConvertStrToInt(&Mask, 3);
	pMsg->Data[7] = (uint8_t)ConvertStrToInt(&Mask, 3);

	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	进入安全模式
*/
DUCP_ERR_T	DUCP_HOST_SYS_EnterSafMode(const char * pswd)
{
	DUCP_ERR_T Err;
	int Len;
	
	if(!pswd) {
		return DUCP_CMD_SYS_SET_SAF_MODE;
	}
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_SAF_MODE;
	pMsg->DLen = 6;
	Len = strlen(pswd);

	if (Len > 6) {
		Len = 6;
	}

	memcpy(pMsg->Data,pswd,Len);
	for(;Len < 6;Len ++) {
		pMsg->Data[Len] = 0;
	}
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	计算验证码
	
	Msg: 消息地址
	MsgLen: 消息长度，最多255个字节,如果大于255，只会计算前255个字节。
	pOutResult:返回的32位结果
*/
DUCP_ERR_T	DUCP_HOST_SYS_Clic(const char * Msg,int MsgLen,int * pOutResult)
{
	DUCP_ERR_T Err;
	
	if(!Msg) {
		return DUCP_CMD_SYS_CLIC;
	}
	if(MsgLen > 255) {
		MsgLen = 255;
	}
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_CLIC;
	pMsg->DLen = MsgLen;
	memcpy(pMsg->Data,Msg,MsgLen);
	
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	设置显示尺寸
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetDisSize(int XSize,int YSize)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_DIS_SIZE;
	pMsg->DLen = 4;
	*(uint16_t *)&pMsg->Data[0] = XSize;
	*(uint16_t *)&pMsg->Data[2] = YSize;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}


/*
	设置显示镜像
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetXYMIR(int Flag)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_XYMIR;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)Flag;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	设置485工作模式
*/
DUCP_ERR_T	DUCP_HOST_SYS_Set485Mode(int ModeIndex)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_485MODE;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)ModeIndex;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	获取所有参数
*/
DUCP_ERR_T	DUCP_HOST_SYS_GetAll(SysSettings_t * pSet)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_GET_ALL;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if((Err == 0) && (pMsg->DLen == sizeof(SysSettings_t))) {
		memcpy(pSet,pMsg->Data,pMsg->DLen);
	}
	return Err;
}

/*
	设置所有参数
*/
DUCP_ERR_T	DUCP_HOST_SYS_SetAll(SysSettings_t * pSet)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_ALL;
	pMsg->DLen  = sizeof(SysSettings_t);
	memcpy(pMsg->Data,pSet,pMsg->DLen);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	使能TTS播放所有文字(需要配置外部TTS硬件解码模块)
*/
DUCP_ERR_T	DUCP_HOST_SYS_TTSEn(int Enable)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_TTSEN;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)Enable;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	设置脱机
*/
DUCP_ERR_T	DUCP_HOST_SYS_Offline(int Mode, int Place, int Line, int Color)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_SET_OFFLINE;
	pMsg->DLen = 4;
	pMsg->Data[0] = (uint8_t)Mode;
	pMsg->Data[1] = (uint8_t)Place;
	pMsg->Data[2] = (uint8_t)Line;
	pMsg->Data[3] = (uint8_t)Color;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	恢复出厂设置
*/
DUCP_ERR_T	DUCP_HOST_SYS_Factory(void)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SYS_FACTORY;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	return Err;
}

/*
	挂载目录
*/
DUCP_ERR_T	DUCP_HOST_FM_Mount(const char * Path)
{
	DUCP_ERR_T Err;
	int Len;

	Len = strlen(Path);
	if(Len > DUCP_PATH_LEN_MAX) {
		return DUCP_CMD_FM_MOUNT;
	}

	memcpy(pMsg->Data,Path,Len);
	pMsg->Data[Len] = 0;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_MOUNT;
	pMsg->DLen = Len + 1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		Err = DUCP_CMD_FM_MOUNT;
	}
	return Err;
}

/*
	打开文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Open(const char * Path,int Opt)
{
	DUCP_ERR_T Err;
	int Len;

	Len = strlen(Path);
	if(Len > DUCP_PATH_LEN_MAX) {
		return DUCP_CMD_FM_OPEN;
	}
	memcpy(&pMsg->Data[1],Path,Len);
	pMsg->Data[Len + 1] = 0;
	pMsg->Data[0] = (uint8_t)Opt;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_OPEN;
	pMsg->DLen = Len + 1 + 1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		Err = DUCP_CMD_FM_OPEN;
	}
	return Err;
}

/*
	设置文件的读写位置
*/
DUCP_ERR_T	DUCP_HOST_FM_Seek(int Offset)
{
	DUCP_ERR_T Err;

	*(uint32_t *)&pMsg->Data[0] = (uint32_t)Offset;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_SEEK;
	pMsg->DLen = 4;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		Err = DUCP_CMD_FM_SEEK;
	}
	return Err;
}

/*
	写文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Write(const uint8_t * pData,uint32_t Size)
{
	DUCP_ERR_T Err;
	uint32_t Off,wSize;
	
	for(Off = 0;Off < Size;) {
		wSize = (Size - Off);
		if(wSize > 255) {
			wSize = 255;
		}
		memcpy(&pMsg->Data[0],&pData[Off],wSize);
		pMsg->PN[0] = 0xff;
		pMsg->PN[1] = 0xff;
		pMsg->MsgId = DUCP_CMD_FM_WRITE;
		pMsg->DLen = wSize;
		Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
		if (pMsg->Data[0] != DUCP_ERR_NONE) {
			return DUCP_CMD_FM_WRITE;
		}
		Off += wSize;
	}
	return Err;
}

/*
	读文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Read(uint8_t * pData,uint32_t Size,uint32_t * pRetSize)
{
	DUCP_ERR_T Err;
	uint32_t Off = 0;
	
	do {
		pMsg->PN[0] = 0xff;
		pMsg->PN[1] = 0xff;
		pMsg->MsgId = DUCP_CMD_FM_READ;
		pMsg->DLen = 0;
		Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
		if (Err != DUCP_ERR_NONE) {
			return DUCP_CMD_FM_READ;
		}
		memcpy(&pData[Off],&pMsg->Data[0],pMsg->DLen);
		Off += pMsg->DLen;
		if(pMsg->DLen == 0) {
			break;
		}
	} while(Off < Size);

	*pRetSize = Off;
	
	return Err;
}

/*
	同步文件缓存数据
*/
DUCP_ERR_T	DUCP_HOST_FM_SynBuff(void)
{
	DUCP_ERR_T Err;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_SYNBUFF;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		return DUCP_CMD_FM_SYNBUFF;
	}
	return Err;
}

/*
	关闭当前文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Close(void)
{
	DUCP_ERR_T Err;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_COLOSE;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		return DUCP_CMD_FM_COLOSE;
	}
	return Err;
}



/*
	删除当前文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Del(const char * Path)
{
	DUCP_ERR_T Err;
	int Len;
	
	Len = strlen(Path);
	if(Len > DUCP_PATH_LEN_MAX) {
		return DUCP_CMD_FM_DEL;
	}
	memcpy(&pMsg->Data[0],Path,Len);	
	pMsg->Data[Len] = 0;
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_DEL;
	pMsg->DLen = Len + 1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		return DUCP_CMD_FM_DEL;
	}
	return Err;
}

/*
	复制文件
*/
DUCP_ERR_T	DUCP_HOST_FM_Copy(const char * DesPath,const char * SrcPath,int Opt)
{
	DUCP_ERR_T Err;
	int Len;
	int SrcOffset;
	
	Len = strlen(DesPath);
	if(Len > DUCP_PATH_LEN_MAX) {
		return DUCP_CMD_FM_COPY;
	}
	memcpy(&pMsg->Data[2],DesPath,Len);	
	SrcOffset = Len + 2 + 1;
	pMsg->Data[0] = SrcOffset;
	pMsg->Data[1] = Opt;
	pMsg->Data[Len + 2] = 0;
	
	Len = strlen(SrcPath);
	if(Len > DUCP_PATH_LEN_MAX) {
		return DUCP_CMD_FM_COPY;
	}
	memcpy(&pMsg->Data[SrcOffset],SrcPath,Len);	
	if((SrcOffset + Len + 1) > 255) {
		return DUCP_CMD_FM_COPY;
	}
	pMsg->Data[SrcOffset + Len] = 0;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_COPY;
	pMsg->DLen = SrcOffset + Len + 1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		return DUCP_CMD_FM_COPY;
	}
	return Err;
}


/*
	格式化磁盘
*/
DUCP_ERR_T	DUCP_HOST_FM_FDisk(void)
{
	DUCP_ERR_T Err;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_FM_FDISK;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (pMsg->Data[0] != DUCP_ERR_NONE) {
		return DUCP_CMD_FM_FDISK;
	}
	return Err;
}

/*
播放语音
*/
DUCP_ERR_T	DUCP_HOST_TTS_Play(const char * pText,uint8_t Opt)
{
	DUCP_ERR_T Err;
	int Len = 0;

	if (!pText) {
		return DUCP_CMD_TTS_PLAY;
	}
	Len = strlen(pText);
	if (Len > sizeof(pMsg->Data) - 1) {
		return DUCP_CMD_TTS_PLAY;
	}
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TTS_PLAY;
	pMsg->DLen = Len + 1;
	pMsg->Data[0] = Opt;
	memcpy(&pMsg->Data[1], pText, Len);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

//==========================================================================================================================
/*
返回声音播放协议包
*/
rMB_MSG_T*	DUCP_HOST_TTS_Play0(const char * pText, uint8_t Opt)
{
	DUCP_ERR_T Err;
	int Len = 0;
	rMB_MSG_T *ptr;

	Len = strlen(pText);

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TTS_PLAY;
	pMsg->DLen = Len + 1;
	pMsg->Data[0] = Opt;
	memcpy(&pMsg->Data[1], pText, Len);
	ptr = Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct  MB_MSG_T *ptr;
	return ptr;
}
/*
停止播放语音
*/
DUCP_ERR_T	DUCP_HOST_TTS_Stop(void)
{
	DUCP_ERR_T Err;
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TTS_STOP;
	pMsg->DLen = 0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
绘制点
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawPoint(int x0, int y0)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DRAW_POINT;
	pMsg->DLen = 4;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	绘制线
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawLine(int x0,int y0,int x1,int y1)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DRAW_LINE;
	pMsg->DLen = 8;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)x1;
	*(int16_t *)&pMsg->Data[6] = (int16_t)y1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
绘制矩形
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawRect(int x0, int y0, int x1, int y1)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DRAW_RECT;
	pMsg->DLen = 8;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)x1;
	*(int16_t *)&pMsg->Data[6] = (int16_t)y1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
填充矩形
*/
DUCP_ERR_T	DUCP_HOST_2D_FillRect(int x0, int y0, int x1, int y1)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_FILL_RECT;
	pMsg->DLen = 8;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)x1;
	*(int16_t *)&pMsg->Data[6] = (int16_t)y1;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
绘制圆
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawCircle(int x0, int y0, int r)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DRAW_CICLE;
	pMsg->DLen = 6;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)r;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
填充圆
*/
DUCP_ERR_T	DUCP_HOST_2D_FillCircle(int x0, int y0, int r)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_FILL_CICLE;
	pMsg->DLen = 6;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)r;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
绘制位图
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawBitmap(int x0, int y0, int xSize,int ySize,
									int BitsPerPixle,int BytesPerLine,
									int DataSize, int ColorTabelSize,
									const uint8_t * pData)
{
	DUCP_ERR_T Err;

	if (!pData || (DataSize >= 4096) ||
	   (DataSize != (ColorTabelSize + BytesPerLine * ySize))){
		return DUCP_CMD_2D_DRAW_BITMAP;
	}
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DRAW_BITMAP;  
	pMsg->DLen = 18;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)xSize;
	*(int16_t *)&pMsg->Data[6] = (int16_t)ySize;
	*(uint16_t *)&pMsg->Data[8] = (uint16_t)BitsPerPixle;
	*(uint16_t *)&pMsg->Data[10] = (uint16_t)BytesPerLine;
	*(uint16_t *)&pMsg->Data[12] = (uint16_t)ColorTabelSize;
	*(uint32_t *)&pMsg->Data[14] = (uint32_t)DataSize;

	int BuffLen = sizeof(pMsg->Data);
	int BuffPos = 18;
	int wLen = 0;
	int i;
	int PN = 0;

	/*下载数据*/
	while (DataSize) {
		wLen = DataSize;
		if (wLen > (BuffLen - BuffPos)) {
			wLen = BuffLen - BuffPos;
		}
		for (i = 0; i < wLen; i++) {
			pMsg->Data[BuffPos + i] = *pData++;
		}
		if ((DataSize - wLen) == 0) {
			PN = 0XFFFFFFFF;
		}
		pMsg->PN[0] = (uint8_t)(PN & 0XFF);
		pMsg->PN[1] = (uint8_t)((PN >> 8) & 0XFF);
		pMsg->MsgId = DUCP_CMD_2D_DRAW_BITMAP;
		pMsg->DLen = wLen + BuffPos;
		Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
		if (Err) {
			return Err;
		}
		Err = (DUCP_ERR_T)pMsg->Data[0];
		if (Err) {
			return Err;
		}
		BuffPos = 0;
		DataSize -= wLen;
		PN++;
	}
	return Err;
}


/*
显示文本
*/
DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText)
{
	DUCP_ERR_T Err;
	int Len;

	Len = strlen(pText);
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DIS_TEXT;
	pMsg->DLen = Len + 4;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	strcpy(&pMsg->Data[4], pText);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
设置绘图颜色
*/
DUCP_ERR_T	DUCP_HOST_2D_SetColor(int Color)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_SET_TCOLOR;
	pMsg->DLen = 4;
	*(int *)&pMsg->Data[0] = (int)Color;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
设置背景颜色
*/
DUCP_ERR_T	DUCP_HOST_2D_SetBkColor(int Color)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_SET_BCOLOR;
	pMsg->DLen = 4;
	*(int *)&pMsg->Data[0] = (int)Color;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
设置字体
*/
DUCP_ERR_T	DUCP_HOST_2D_SetFont(int FontIndex)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_SET_FONT;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)FontIndex;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
绘制系统自带的位图
*/
DUCP_ERR_T	DUCP_HOST_2D_DrawSysIcon(int x0, int y0,int Num,int Denom,int IconIndex)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_2D_DRAW_SYSICON;
	pMsg->DLen = 10;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)Num;
	*(int16_t *)&pMsg->Data[6] = (int16_t)Denom;
	*(int16_t *)&pMsg->Data[8] = (int16_t)IconIndex;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
显示窗口
*/
DUCP_ERR_T	DUCP_HOST_WM_ShowWindow(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_WIN_SHOW;
	pMsg->DLen = 2;
	pMsg->Data[0] = WinID & 0XFF;
	pMsg->Data[1] = (WinID >> 8) & 0XFF;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
隐藏窗口
*/
DUCP_ERR_T	DUCP_HOST_WM_HideWindow(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_WIN_HIDLE;
	pMsg->DLen = 2;
	pMsg->Data[0] = WinID & 0XFF;
	pMsg->Data[1] = (WinID >> 8) & 0XFF;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
删除窗口
*/
DUCP_ERR_T	DUCP_HOST_WM_DelWindow(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_WIN_DEL;
	pMsg->DLen = 2;
	pMsg->Data[0] = WinID & 0XFF;
	pMsg->Data[1] = (WinID >> 8) & 0XFF;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	设置窗口自动同步显示
*/
DUCP_ERR_T	DUCP_HOST_WM_AutoSyn(int En)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_WIN_AUTO_SYN;
	pMsg->DLen = 1;
	pMsg->Data[0] = En;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
创建文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_Create(int WinID, int Stile, int x0, int y0, int xSize, int ySize)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_CREATE;
	pMsg->DLen = 10;
	pMsg->Data[0] = (uint8_t)WinID;
	pMsg->Data[1] = (uint8_t)Stile;
	*(int16_t *)&pMsg->Data[2] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[4] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[6] = (int16_t)xSize;
	*(int16_t *)&pMsg->Data[8] = (int16_t)ySize;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (int)pMsg->Data[0];
	return Err;
}


/*
删除文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_Del(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_DEL;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)WinID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}
/*
显示文本
*/
DUCP_ERR_T DUCP_HOST_TWIN_DisText(int WinID,
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
	int DisTimes)
{
	DUCP_ERR_T Err = 0xff;
	int BuffPos;
	int BuffLen;
	int wLen;
	int Len;
	int i;
	int PN;

	BuffPos = 0;
	PN = 0;
	BuffLen = sizeof(pMsg->Data);
	Len = strlen(pText);
	if (Len > 4096) {/*限制4K文本*/
		return DUCP_CMD_TWIN_DIS_TEXT;
	}
	DUCP_HOST_SYS_SYNPN(0);

	pMsg->Data[BuffPos++] = (uint8_t)WinID;
	pMsg->Data[BuffPos++] = (uint8_t)EnterMode;
	pMsg->Data[BuffPos++] = (uint8_t)EnterSpeed;
	pMsg->Data[BuffPos++] = (uint8_t)DelayMode;
	pMsg->Data[BuffPos++] = (uint8_t)DelayTime;
	pMsg->Data[BuffPos++] = (uint8_t)EixtMode;
	pMsg->Data[BuffPos++] = (uint8_t)EixtSpeed;
	pMsg->Data[BuffPos++] = (uint8_t)FontIndex;
	pMsg->Data[BuffPos++] = (uint8_t)DisTimes;
	*(int *)&pMsg->Data[BuffPos] = (int)TextColor;
	BuffPos += 4;
	*(int *)&pMsg->Data[BuffPos] = (int)BkColor;
	BuffPos += 4;
	*(uint16_t *)&pMsg->Data[BuffPos] = (uint16_t)Len;
	BuffPos += 2;

	while (Len) {
		wLen = Len;
		if (wLen > (BuffLen - BuffPos)) {
			wLen = BuffLen - BuffPos;
		}
		for (i = 0; i < wLen; i++) {
			pMsg->Data[BuffPos + i] = *pText++;
		}
		if ((Len - wLen) == 0) {
			PN = 0XFFFFFFFF;
		}
		pMsg->PN[0] = (uint8_t)(PN & 0XFF);
		pMsg->PN[1] = (uint8_t)((PN >> 8) & 0XFF);
		pMsg->MsgId = DUCP_CMD_TWIN_DIS_TEXT;
		pMsg->DLen = wLen + BuffPos;
		Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
		if (Err) {
			return Err;
		}
		Err = (DUCP_ERR_T)pMsg->Data[0];
		if (Err) {
			return Err;
		}
		BuffPos = 0;
		Len -= wLen;
		PN++;
	}
	return Err;
}

///=====================================================================================================
/*
返回下载文本协议包
*/
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
	int BkColor)
{
	DUCP_ERR_T Err;
	int BuffPos;
	int BuffLen;
	int wLen;
	int Len;
	int i;
	int PN;
	rMB_MSG_T *ptr;
	BuffPos = 0;
	PN = 0;
	BuffLen = sizeof(pMsg->Data);
	Len = strlen(pText);
	//if (Len > (60 * 1024)) {/*限制60K文本*/
	//	return DUCP_CMD_TWIN_DOWN_TFILE;
	//}

	pMsg->Data[BuffPos++] = (uint8_t)WinID;
	pMsg->Data[BuffPos++] = (uint8_t)FileID;
	pMsg->Data[BuffPos++] = (uint8_t)0X0C;
	pMsg->Data[BuffPos++] = (uint8_t)EnterMode;
	pMsg->Data[BuffPos++] = (uint8_t)EnterSpeed;
	pMsg->Data[BuffPos++] = (uint8_t)DelayMode;
	pMsg->Data[BuffPos++] = (uint8_t)DelayTime;
	pMsg->Data[BuffPos++] = (uint8_t)EixtMode;
	pMsg->Data[BuffPos++] = (uint8_t)EixtSpeed;
	pMsg->Data[BuffPos++] = (uint8_t)FontIndex;
	*(int *)&pMsg->Data[BuffPos] = (int)TextColor;
	BuffPos += 4;
	*(int *)&pMsg->Data[BuffPos] = (int)BkColor;
	BuffPos += 4;
	*(uint16_t *)&pMsg->Data[BuffPos] = (uint16_t)Len;
	BuffPos += 2;

	
		wLen = Len;
		if (Len > (BuffLen - BuffPos)) {
			wLen = BuffLen - BuffPos;
		}
		for (i = 0; i < wLen; i++) {
			pMsg->Data[BuffPos + i] = *pText++;
		}
		if ((Len - wLen) == 0) {
			PN = 0XFFFF;
		}
		pMsg->PN[0] = (uint8_t)(PN & 0XFF);
		pMsg->PN[1] = (uint8_t)((PN >> 8) & 0XFF);
		pMsg->MsgId = DUCP_CMD_TWIN_DOWN_TFILE;
		pMsg->DLen = wLen + BuffPos;
		
		ptr = Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct
		return ptr;
}


//==================================================================================
/*
返回显示文本协议包
*/
rMB_MSG_T* DUCP_HOST_TWIN_DisText0(int WinID,
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
									int DisTimes)
{
	DUCP_ERR_T Err = 0xff;
	int BuffPos;
	int BuffLen;
	int wLen;
	int Len;
	int i;
	int PN;
	rMB_MSG_T *ptr;
	BuffPos = 0;
	PN = 0;
	BuffLen = sizeof(pMsg->Data);
	Len = strlen(pText);
	//if (Len > 4096) {/*限制4K文本*/
	//	return 0;
	//}
	//DUCP_HOST_SYS_SYNPN(0);

	pMsg->Data[BuffPos ++] = (uint8_t)WinID;
	pMsg->Data[BuffPos ++] = (uint8_t)EnterMode;
	pMsg->Data[BuffPos ++] = (uint8_t)EnterSpeed;
	pMsg->Data[BuffPos ++] = (uint8_t)DelayMode;
	pMsg->Data[BuffPos ++] = (uint8_t)DelayTime;
	pMsg->Data[BuffPos ++] = (uint8_t)EixtMode;
	pMsg->Data[BuffPos ++] = (uint8_t)EixtSpeed;
	pMsg->Data[BuffPos ++] = (uint8_t)FontIndex;
	pMsg->Data[BuffPos++] = (uint8_t)DisTimes;
	*(int *)&pMsg->Data[BuffPos] = (int)TextColor;
	BuffPos += 4;
	*(int *)&pMsg->Data[BuffPos] = (int)BkColor;
	BuffPos += 4;
	*(uint16_t *)&pMsg->Data[BuffPos] = (uint16_t)Len;
	BuffPos += 2;

	///while (Len) {
		wLen = Len;
		if (wLen > (BuffLen - BuffPos)) {
			wLen = BuffLen - BuffPos;
		}
		for (i = 0; i < wLen; i++) {
			pMsg->Data[BuffPos + i] = *pText++;
		}
		if ((Len - wLen) == 0) {
			PN = 0XFFFFFFFF;
		}
		pMsg->PN[0] = (uint8_t)(PN & 0XFF);
		pMsg->PN[1] = (uint8_t)((PN >> 8) & 0XFF);
		pMsg->MsgId = DUCP_CMD_TWIN_DIS_TEXT;
		pMsg->DLen = wLen + BuffPos;


		 ptr = Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct
		 return ptr;

		 
}

/*
设置文本控件的字体
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetFont(int WinID,int FontIndex)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_SET_FONT;
	pMsg->DLen = 2;
	pMsg->Data[0] = (uint8_t)WinID;
	pMsg->Data[1] = (uint8_t)FontIndex;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
设置文本控件的文本颜色
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetTextColor(int WinID,int Color)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_SET_TCOLOR;
	pMsg->DLen = 5;
	pMsg->Data[0] = (uint8_t)WinID;
	*(int *)&pMsg->Data[1] = (int)Color;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
设置文本控件的背景颜色
*/
DUCP_ERR_T DUCP_HOST_TWIN_SetBkColor(int WinID, int Color)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_SET_BCOLOR;
	pMsg->DLen = 5;
	pMsg->Data[0] = (uint8_t)WinID;
	*(int *)&pMsg->Data[1] = (int)Color;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
停止显示文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_StopDis(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_STOP_DIS;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)WinID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
下载文本文件与文本控件关联
*/
DUCP_ERR_T DUCP_HOST_TWIN_DownTextFile( int WinID,
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
										int BkColor)
{
	DUCP_ERR_T Err;
	int BuffPos;
	int BuffLen;
	int wLen;
	int Len;
	int i;
	int PN;

	BuffPos = 0;
	PN = 0;
	BuffLen = sizeof(pMsg->Data);
	Len = strlen(pText);
	if (Len > (60 * 1024)) {/*限制60K文本*/
		return DUCP_CMD_TWIN_DOWN_TFILE;
	}

	pMsg->Data[BuffPos++] = (uint8_t)WinID;
	pMsg->Data[BuffPos++] = (uint8_t)FileID;
	pMsg->Data[BuffPos++] = (uint8_t)0X0C;
	pMsg->Data[BuffPos++] = (uint8_t)EnterMode;
	pMsg->Data[BuffPos++] = (uint8_t)EnterSpeed;
	pMsg->Data[BuffPos++] = (uint8_t)DelayMode;
	pMsg->Data[BuffPos++] = (uint8_t)DelayTime;
	pMsg->Data[BuffPos++] = (uint8_t)EixtMode;
	pMsg->Data[BuffPos++] = (uint8_t)EixtSpeed;
	pMsg->Data[BuffPos++] = (uint8_t)FontIndex;
	*(int *)&pMsg->Data[BuffPos] = (int)TextColor;
	BuffPos += 4;
	*(int *)&pMsg->Data[BuffPos] = (int)BkColor;
	BuffPos += 4;
	*(uint16_t *)&pMsg->Data[BuffPos] = (uint16_t)Len;
	BuffPos += 2;

	while (Len) {
		wLen = Len;
		if (Len > (BuffLen - BuffPos)) {
			wLen = BuffLen - BuffPos;
		}
		for (i = 0; i < wLen; i++) {
			pMsg->Data[BuffPos + i] = *pText++;
		}
		if ((Len - wLen) == 0) {
			PN = 0XFFFF;
		}
		pMsg->PN[0] = (uint8_t)(PN & 0XFF);
		pMsg->PN[1] = (uint8_t)((PN >> 8) & 0XFF);
		pMsg->MsgId = DUCP_CMD_TWIN_DOWN_TFILE;
		pMsg->DLen = wLen + BuffPos;
		Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
		if (Err) {
			return Err;
		}
		Err = (DUCP_ERR_T)pMsg->Data[0];
		if (Err) {
			return Err;
		}
		BuffPos = 0;
		Len -= wLen;
		PN++;
	}
	return Err;
}

/*
显示文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_DisFile(int WinID,int FileID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_DIS_TFILE;
	pMsg->DLen = 2;
	pMsg->Data[0] = (uint8_t)WinID;
	pMsg->Data[1] = (uint8_t)FileID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
打开文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_OpenFile(int WinID, int FileID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_OPEN_TFILE;
	pMsg->DLen = 2;
	pMsg->Data[0] = (uint8_t)WinID;
	pMsg->Data[1] = (uint8_t)FileID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
关闭文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_CloseFile(int WinID, int FileID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_CLOSE_TFILE;
	pMsg->DLen = 2;
	pMsg->Data[0] = (uint8_t)WinID;
	pMsg->Data[1] = (uint8_t)FileID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
删除文本控件的文本文件
*/
DUCP_ERR_T DUCP_HOST_TWIN_DelFile(int WinID, int FileID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_DEL_TFILE;
	pMsg->DLen = 2;
	pMsg->Data[0] = (uint8_t)WinID;
	pMsg->Data[1] = (uint8_t)FileID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
	同步显示多个文本控件
*/
DUCP_ERR_T DUCP_HOST_TWIN_SynDis(char * pList,int NumBytes)
{
	DUCP_ERR_T Err;
	int i;
	
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_TWIN_SYN_DIS;


	if(NumBytes >= 255) {
		return DUCP_CMD_TWIN_SYN_DIS;
	}
	i = 0;
	while(NumBytes >= 2) {
		pMsg->Data[i ++] = (uint8_t)pList[i];/*TWID*/
		pMsg->Data[i ++] = (uint8_t)pList[i];/*FID*/
		NumBytes -= 2;
	}
	pMsg->DLen = i;

	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


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
													const char * pVoice)
{
	DUCP_ERR_T Err = 0xff;
	int BuffPos;
	int TextLen;
	int VoiceLen;
	
	BuffPos = 0;
	TextLen = strlen(pText);
	VoiceLen = strlen(pVoice);

	if(TextLen == 0) {
		return DUCP_CMD_TWIN_SYN_DISEX;
	}
	if ((TextLen + VoiceLen + 19 + 2) > sizeof(pMsg->Data)) {/*限制携带数据长度*/
		return DUCP_CMD_TWIN_SYN_DISEX;
	}

	/*文本头*/
	pMsg->Data[BuffPos ++] = (uint8_t)StartWinID;
	pMsg->Data[BuffPos ++] = (uint8_t)EnterMode;
	pMsg->Data[BuffPos ++] = (uint8_t)EnterSpeed;
	pMsg->Data[BuffPos ++] = (uint8_t)DelayMode;
	pMsg->Data[BuffPos ++] = (uint8_t)DelayTime;
	pMsg->Data[BuffPos ++] = (uint8_t)EixtMode;
	pMsg->Data[BuffPos ++] = (uint8_t)EixtSpeed;
	pMsg->Data[BuffPos ++] = (uint8_t)FontIndex;
	pMsg->Data[BuffPos++] = (uint8_t)DisTimes;
	*(int *)&pMsg->Data[BuffPos] = (int)TextColor;
	BuffPos += 4;
	*(int *)&pMsg->Data[BuffPos] = (int)BkColor;
	BuffPos += 4;
	*(uint16_t *)&pMsg->Data[BuffPos] = (uint16_t)TextLen;
	BuffPos += 2;

	/*文字*/
	memcpy(&pMsg->Data[BuffPos],pText,TextLen);
	BuffPos += TextLen;

	/*语音*/
	if(VoiceLen) {
		pMsg->Data[BuffPos ++] = 0x0a;
		memcpy(&pMsg->Data[BuffPos],pVoice,VoiceLen);
		BuffPos += VoiceLen;
	}
	pMsg->Data[BuffPos++] = 0x07;
	pMsg->Data[BuffPos] = 0;

	/*打包发送*/
	pMsg->PN[0] = 0XFF;
	pMsg->PN[1] = 0XFF;
	pMsg->MsgId = DUCP_CMD_TWIN_SYN_DISEX;
	pMsg->DLen = BuffPos +1;
	if ((BuffPos + 1) > sizeof(pMsg->Data)) {/*限制携带数据长度*/
		return DUCP_CMD_TWIN_SYN_DISEX;
	}
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	
	return Err;
}

/*
创建图片控件
*/
DUCP_ERR_T DUCP_HOST_PIC_Create(int WinID,int x0, int y0, int xSize, int ySize)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_PIC_CREATE;
	pMsg->DLen = 9;
	pMsg->Data[0] = (uint8_t)WinID;
	*(int16_t *)&pMsg->Data[1] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[3] = (int16_t)y0;
	*(int16_t *)&pMsg->Data[5] = (int16_t)xSize;
	*(int16_t *)&pMsg->Data[7] = (int16_t)ySize;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (int)pMsg->Data[0];
	return Err;
}

/*
删除图片控件
*/
DUCP_ERR_T DUCP_HOST_PIC_Del(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_PIC_DEL;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)WinID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

/*
向图片控件追加图片
*/
DUCP_ERR_T DUCP_HOST_PIC_Add(int WinID,int FID,uint8_t EnterMode,uint8_t EnterSpeed,
										uint8_t StopMode,uint8_t StopTime,uint8_t ExitMode,uint8_t ExitSpeed)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_PIC_ADD;
	pMsg->DLen = 9;
	pMsg->Data[0] = (uint8_t)WinID;
	*(uint16_t *)&pMsg->Data[1] = FID;
	pMsg->Data[3] = (uint8_t)EnterMode;
	pMsg->Data[4] = (uint8_t)EnterSpeed;
	pMsg->Data[5] = (uint8_t)StopMode;
	pMsg->Data[6] = (uint8_t)StopTime;
	pMsg->Data[7] = (uint8_t)ExitMode;
	pMsg->Data[8] = (uint8_t)ExitSpeed;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}


/*
删除所有图片
*/
DUCP_ERR_T DUCP_HOST_PIC_Clr(int WinID)
{
	DUCP_ERR_T Err;

	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_PIC_CLR;
	pMsg->DLen = 1;
	pMsg->Data[0] = (uint8_t)WinID;
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}
/*
绘制二维码
*/
DUCP_ERR_T	DUCP_HOST_PIC_DrawQR(int x0, int y0, uint8_t option, uint8_t time, const char * pText)
{
	//DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText)
	DUCP_ERR_T Err;
	int Len;

	Len = strlen(pText);
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_PIC_QR;
	pMsg->DLen = Len + 6;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	pMsg->Data[4] = option;
	pMsg->Data[5] = time;
	strcpy(&pMsg->Data[6], pText);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}

//=========================================================================================================================================

/*
返回二维码协议包
*/
rMB_MSG_T*	DUCP_HOST_PIC_DrawQR0(int x0, int y0, uint8_t option, uint8_t time, const char * pText)
{
	//DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText)
	DUCP_ERR_T Err;
	int Len;
	rMB_MSG_T *ptr;

	Len = strlen(pText);
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_PIC_QR;
	pMsg->DLen = Len + 6;
	*(int16_t *)&pMsg->Data[0] = (int16_t)x0;
	*(int16_t *)&pMsg->Data[2] = (int16_t)y0;
	pMsg->Data[4] = option;
	pMsg->Data[5] = time;
	strcpy(&pMsg->Data[6], pText);
	ptr = Return_TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef); // return MB_MSG_T struct  MB_MSG_T *ptr;

	return ptr;
}
/*
手动遥控闸计数
*/
DUCP_ERR_T	DUCP_HOST_SwtichCount_Controll(uint8_t option, SwitchControll_t *swcnr)
{
	
	DUCP_ERR_T Err;
	int Len;

	//Len = strlen(pText);
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_SwitchContoll;


	pMsg->DLen = sizeof(SwitchControll_t)+1;
	pMsg->Data[0] = option;
	memcpy(&pMsg->Data[1], swcnr, pMsg->DLen);



	//strcpy(&pMsg->Data[6], pText);
	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	memcpy(swcnr, &pMsg->Data[1], sizeof(SwitchControll_t));
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}
/*
控制卡加密及授权
*/
DUCP_ERR_T	DUCP_HOST_Secret_Key(uint8_t option, uint32_t * key)
{
	//DUCP_ERR_T	DUCP_HOST_2D_DisText(int x0, int y0, const char * pText)
	DUCP_ERR_T Err;
	int Len;

	//Len = strlen(pText);
	pMsg->PN[0] = 0xff;
	pMsg->PN[1] = 0xff;
	pMsg->MsgId = DUCP_CMD_Secret_Key,//171123;


		pMsg->DLen = 5;
	pMsg->Data[0] = option;
	memcpy(&pMsg->Data[1], key, pMsg->DLen);




	Err = _TsfMsg(pMsg, _SendMsgOverTimeDef, _ReadMsgOverTimeDef);
	if (Err) {
		return Err;
	}
	memcpy(key, &pMsg->Data[1], 5);
	Err = (DUCP_ERR_T)pMsg->Data[0];
	return Err;
}
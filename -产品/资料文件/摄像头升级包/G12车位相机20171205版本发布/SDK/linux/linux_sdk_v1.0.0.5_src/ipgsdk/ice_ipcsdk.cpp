#include "ice_ipcsdk.h"
#include "ice_com_type.h"
/*#include "ice_dtca_result.h"
#include "ice_vdc_result.h"*/

#ifdef _WIN32
#include <pcap.h>
#include "rtspc.h"
#include "ffmpeg.h"
#include "dec.h"
#include "..\draw\draw.h"
#include "CreateDump.h"
#include <IPTypes.h>
#include <IPHlpApi.h>
#else
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#endif

#include "socket.h"
#include "evtp.h"
//#include "HisiVoiceEngine\include\hi_voice_api.h"
#include "Log.h"
#include "sc.h"
#include "sm.h"

#include <time.h>
/*#include<mmsystem.h>
#pragma  comment(lib, "winmm.lib")

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")*/

//#ifdef USE_FFMPEG
#ifdef _WIN32
#ifdef _WIN64
#pragma comment(lib, "WpdPack\\Lib\\x64\\wpcap.lib")
#else
#pragma comment(lib, "WpdPack\\Lib\\wpcap.lib")
#endif
#endif
//#endif

/*#include <queue>
typedef std::queue<void*> stream_queue;*/

static int g_nEnableLog = 0;
static char g_logPath[256] = {0};

/*static const char* g_szAlarmType[] = 
{
"实时_硬触发+临时车辆",
"实时_视频触发+临时车辆",
"实时_软触发+临时车辆",
"实时_硬触发+白名单",
"实时_视频触发+白名单",
"实时_软触发+白名单",
"实时_硬触发+黑名单",
"实时_视频触发+黑名单",
"实时_软触发+黑名单",
"脱机_硬触发+临时车辆",
"脱机_视频触发+临时车辆",
"脱机_软触发+临时车辆",
"脱机_硬触发+白名单",
"脱机_视频触发+白名单",
"脱机_软触发+白名单",
"脱机_硬触发+黑名单",
"脱机_视频触发+黑名单",
"脱机_软触发+黑名单",
"实时_硬触发+过期白名单",
"实时_视频触发+过期白名单",
"实时_软触发+过期白名单",
"脱机_硬触发+过期白名单",
"脱机_视频触发+过期白名单",
"脱机_软触发+过期白名单"
};

typedef struct
{
char plate[16];
char date_begin[16];
char date_end[16];
char time_begin[16];
char time_end[16];
char type[16];

} whitelist_info_t;

#define MAX_WHITE_LIST 8192*/

#define BUF_SIZE (2 * 1024 * 1024)
//#define MAX_WAVE_HDR 32

typedef struct
{
	char ip[32];
	char buf[BUF_SIZE];
	ICE_U16 u16ICEPort;
	ICE_U16 u16OnvifPort;
	ICE_U16 u16RtspPort;
	ICE_U16 u16EvtpPort;
	ICE_U8 u8MainStream;

	ICE_U16 need_passwd;
	char passwd[4096];

#ifdef _WIN32
	rtspc_handle_t rtspc, rtsp_algo;
	dec_handle_t dec;

	/*ICE_IPCSDK_OnStream pfOnStream;
	void *pvStreamParam;
	ICE_IPCSDK_OnFrame pfOnFrame;
	void *pvFrameParam;

	ICE_IPCSDK_OnPlate pfOnPlate;
	ICE_IPCSDK_OnPlate_Cdecl pfOnPlate_Cdecl;
	void *pvPlateParam;*/
	HWND hWnd;
	/*ICE_IPCSDK_OnFrame_Planar pfOnFramePlanar;
	void *pvFramePlanarParam;

	ICE_IPCSDK_OnStream pfOnData;
	void *pvDataParam;*/

	draw_handle_t draw_handle;
	int width, height;
#endif

	//stream_queue *queue;
	//BOOL bPreview;

	/*BOOL m_bTalk;
	HWAVEIN m_hWaveIn;
	WAVEFORMATEX m_WaveFormatEx;
	WAVEHDR *m_WaveHdr[MAX_WAVE_HDR];
	hiVOICE_G711_STATE_S m_G711_STATE_ENC;
	HWAVEOUT m_hWaveOut;
	hiVOICE_G711_STATE_S m_G711_STATE_DEC;
	int wavein_loss_count;

	stream_queue *talk_queue_in, *talk_queue_out;
	HANDLE hTalkMutexIn, hTalkMutexOut;
	HANDLE hTalkThreadIn, hTalkThreadOut;

	BOOL bTrigger;
	ICE_VDC_PICTRUE_INFO_BUFFER_S info;*/

	ICE_IPCSDK_OnSerialPort pfOnSerialPort;
	//ICE_IPCSDK_OnSerialPort_Cdecl pfOnSerialPort_Cdecl;
	ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort_RS232;
	void *pvSerialPortParam;
	void *pvSerialPortParam_RS232;

	/*whitelist_info_t *whitelist;
	int whitelist_count, white_count, black_count;
	int white_index[MAX_WHITE_LIST], black_index[MAX_WHITE_LIST];

	ICE_IPCSDK_OnPastPlate pfOnPastPlate;
	ICE_IPCSDK_OnPastPlate_Cdecl pfOnPastPlate_Cdecl;
	void *pvPastPlateParam;*/

	evtp_handle_t evtp_handle;

	/*PAVIFILE pavfile;
	PAVISTREAM pavstream;
	int count, ts;
	int frame_width, frame_height;
	HANDLE hMutex;
	BYTE *rec_buf;
	int rec_len;*/
	CLog *clog;

	int enable_utf8;

	ICE_IPCSDK_OnParkingSpaceInfo pfOnParkingSpaceInfo;
	void *pvParkingSpaceInfo;
} sdk_handle_t;

ICE_IPCSDK_OnDeviceEvent g_pfOnDeviceEvent = NULL;
void *g_pvDeviceEventParam = NULL;

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK);
ICE_IPCSDK_API void ICE_IPCSDK_Close(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenDevice_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd);

/*void ConvertUtf8ToTChar(const char* src, TCHAR *dst, int size)
{
WCHAR tmp[128];
MultiByteToWideChar(CP_UTF8, 0, src, -1, tmp, 128);

WideCharToMultiByte(CP_ACP, 0, tmp, -1, dst, size, NULL, NULL);
}

void ConvertTCharToUtf8(const TCHAR* src, char *dst, int size)
{
WCHAR tmp[128];
MultiByteToWideChar(CP_ACP, 0, src, -1, tmp, 128);

WideCharToMultiByte(CP_UTF8, 0, tmp, -1, dst, size, NULL, NULL);
}*/

// 网络接收数据流后的回调函数,COM组件同步实现，区别是不采用队列方式，采用回调方式实现
void callback(void *param, uint8_t type, 
			  uint32_t timestamp, void *data, int len)
{
	sdk_handle_t *handle = (sdk_handle_t*)param;

	if (NULL == data)
	{
		if ((0 == type) && (1 == len))
		{
			/*SYSTEMTIME st;
			GetSystemTime(&st);

			ICE_IPCSDK_SyncTime(handle, st.wYear, (ICE_U8)st.wMonth, 
			(ICE_U8)st.wDay, (ICE_U8)st.wHour + 8, (ICE_U8)st.wMinute);

			ICE_IPCSDK_SetArm(handle, 1);*/
		}

		/*if (NULL != handle->pfOnStream)
		{
		(*handle->pfOnStream)(handle->pvStreamParam, 
		type, timestamp, NULL, len);
		}*/

		if (NULL != g_pfOnDeviceEvent)
		{
			(*g_pfOnDeviceEvent)(g_pvDeviceEventParam, 
				handle->ip, (ICE_U32)len, 0, 0, 0, 0);
			if (0 == len)
				handle->clog->Logf("%s %s",handle->ip, "相机连接状态: 离线");
			else
				handle->clog->Logf("%s %s", handle->ip, "相机连接状态: 在线");			
		}
		return;
	}

	/*if (97 == type)
	{
	if (!handle->m_bTalk)
	return;

	short buf[1024];
	short size;

	HI_VOICE_DecodeFrame(&handle->m_G711_STATE_DEC, (short*)data, buf, &size);

	size *= 2;
	WAVEHDR *pWaveHdr = (WAVEHDR*)malloc(sizeof(WAVEHDR) + size);
	if (NULL == pWaveHdr)
	return;

	memset(pWaveHdr, 0, sizeof(WAVEHDR));
	memcpy(pWaveHdr + 1, buf, size);

	pWaveHdr->lpData = (LPSTR)(pWaveHdr + 1);
	pWaveHdr->dwBufferLength = size;

	waveOutPrepareHeader(handle->m_hWaveOut, pWaveHdr, sizeof(WAVEHDR));
	waveOutWrite(handle->m_hWaveOut, pWaveHdr, sizeof(WAVEHDR));
	return;
	}
	else */if (99 == type || 95 == type)
	{
		if (99 == type)
		{
			if (NULL != handle->pfOnSerialPort)
			{
				(*handle->pfOnSerialPort)(handle->pvSerialPortParam, handle->ip, (char*)data, len);
				handle->clog->Logf("%s %s %d", handle->ip, "收到相机发送的rs485串口数据，长度为： ",len);
			}
			/*else if (NULL != handle->pfOnSerialPort_Cdecl)
			{
			(*handle->pfOnSerialPort_Cdecl)(handle->pvSerialPortParam, handle->ip, (char*)data, len);
			handle->clog->Logf("%s %s %d",handle->ip, "收到相机发送的rs485串口数据，长度为： ",len);
			}*/
		}
		else if (95 == type)
		{
			if (NULL != handle->pfOnSerialPort_RS232)
			{
				(*handle->pfOnSerialPort_RS232)(handle->pvSerialPortParam_RS232, handle->ip, (char*)data, len);
				handle->clog->Logf("%s %s %d", handle->ip, "收到相机发送的rs232串口数据，长度为： ",len);
			}
		}

		return;
	}
	else if (94 == type)
	{
		if (NULL != g_pfOnDeviceEvent)
		{
			(*g_pfOnDeviceEvent)(g_pvDeviceEventParam, handle->ip, ICE_DEVICE_IO_CHANGED, 
				*((char*)data), *((char*)data+1), *((char*)data+2), *((char*)data+3));
			handle->clog->Logf("%s %s %d%d%d%d","IO状态改变，值为： ",handle->ip, *((char*)data), *((char*)data+1), *((char*)data+2), *((char*)data+3));
		}
	}
	else if (106 == type)
	{
		ICE_PARKING_SPACE_RESULT_S *info = (ICE_PARKING_SPACE_RESULT_S*)data;
		if (info->u8ParkingPlaceNum > ICE_MAX_PLACE_NUM)
			info->u8ParkingPlaceNum = ICE_MAX_PLACE_NUM;

		int s32PicDataLen = len - sizeof(ICE_PARKING_SPACE_RESULT_S);
		char *ipg_buf = (char*)(info + 1);

		for (int i = 0; i < info->u8ParkingPlaceNum; i++)
		{
			if (((info->astOutput[i].enParkingPlaceStatus == ICE_IPG_EVENT_TYPE_HAVE_CAR) 
				|| (info->astOutput[i].enParkingPlaceStatus == ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE))
				&& (info->astOutput[i].stPlateInfo.flConfidence <= 0))
				strcpy(info->astOutput[i].stPlateInfo.as8PlateNum, "无牌车");
		}
		if (NULL != handle->pfOnParkingSpaceInfo)
			(*handle->pfOnParkingSpaceInfo)(handle->pvParkingSpaceInfo, handle->ip, info, ipg_buf, s32PicDataLen, NULL, 0, 0, 0, 0);
	}

#ifdef _WIN32
	char nalu_type = *((char*)data) & 0x1F;
	if (9 == nalu_type)
		nalu_type = *((char*)data + 6) & 0x1F;

	if (/*handle->bPreview && */(PAYLOAD_TYPE_H264 == type)  && 
		(nalu_type < 24) && (NULL != handle->dec))
	{
		dec_process(handle->dec, timestamp, data, len);
		//return;
	}
#endif

#if 0
	//if (NULL != handle->pfOnStream)
	{
		char *buf = (char*)data;
		int skip = 0;

		if ((PAYLOAD_TYPE_H264 == type) && (31 == nalu_type))
		{
			type = 100 + *(buf + 1);
			skip = 2;
		}

		if (PAYLOAD_TYPE_VLPR == type)
		{
			ICE_VDC_PICTRUE_INFO_BUFFER_S *info;
			int count = 1;//len / sizeof(ICE_VD_PICTRUE_INFO_BUFFER_S);
			ICE_VDC_PICTRUE_INFO_BUFFER_S *buffer = (ICE_VDC_PICTRUE_INFO_BUFFER_S*)(buf + skip);

			if (NULL != handle->pfOnStream)
			{
				(*handle->pfOnStream)(handle->pvStreamParam, 
					125, timestamp, buf + skip, len - skip);
			}

			for (int i = 0; i < count; i++)
			{
				info = &buffer[i];
				int parse_tlv = 1;

#ifdef _WIN64
				if (len < ((int)sizeof(ICE_VDC_PICTRUE_INFO_S) + info->s32PicDataLen)-4)
				{
					info->s32PicDataLen = 0;
					parse_tlv = 0;
				}
#else
				if (len < ((int)sizeof(ICE_VDC_PICTRUE_INFO_S) + info->s32PicDataLen))
				{
					info->s32PicDataLen = 0;
					parse_tlv = 0;
				}
#endif

				if (info->s32HavePlate)
				{
					/*ConvertUtf8ToTChar(info->stPlateInfo.as8PlateNum, 
					info->stPlateInfo.as8PlateNum, 16);*/

					memcpy(handle->buf, info->stPlateInfo.as8PlateNum, 16);
					memcpy(handle->buf + 16, info->cPlateColor, 32);
				}
				else
				{
					strcpy(handle->buf, "无牌车");
					memset(handle->buf + 16, 0, 32);
				}

				if (handle->enable_utf8)
				{
					ConvertTCharToUtf8(handle->buf, handle->buf, 16);
					ConvertTCharToUtf8(handle->buf + 16, handle->buf + 16, 32);
				}

				*(int*)(handle->buf + 48) = info->s32HavePlate;
				*(short*)(handle->buf + 52) = info->stPlateInfo.stPlateRect.s16Left;
				*(short*)(handle->buf + 54) = info->stPlateInfo.stPlateRect.s16Top;
				*(short*)(handle->buf + 56) = info->stPlateInfo.stPlateRect.s16Right;
				*(short*)(handle->buf + 58) = info->stPlateInfo.stPlateRect.s16Bottom;

				*(int*)(handle->buf + 60) = info->s32PicDataLen;
				if (info->s32PicDataLen > 0)
					memcpy(handle->buf + 64, info->as8PictureData, info->s32PicDataLen);

				static ICE_SYSTEMTIME_S zero_time = {0};
				BOOL bHistory = (0 != memcmp(&info->stCapTime, &zero_time, sizeof(ICE_SYSTEMTIME_S)));
				*(int*)(handle->buf + 64 + info->s32PicDataLen) = bHistory;

				if (!bHistory && handle->bTrigger)
				{
					memcpy(&handle->info, data, len);
					handle->bTrigger = FALSE;
				}

				if (/*!bHistory && */(NULL != handle->pfOnStream))
				{
					(*handle->pfOnStream)(handle->pvStreamParam, 
						type, timestamp, handle->buf, 68 + info->s32PicDataLen);
				}

				char *jpgdata = NULL;
				int jpglen = 0;

				info->pstVbrResult = NULL;
				if (parse_tlv)
				{
					char *tlv_data = info->as8PictureData + info->s32PicDataLen;

#ifdef _WIN64
					int tlv_total = len - ((int)sizeof(ICE_VDC_PICTRUE_INFO_S) - 4) - info->s32PicDataLen;
#else
					int tlv_total = len - (int)sizeof(ICE_VDC_PICTRUE_INFO_S) - info->s32PicDataLen;
#endif


					while (tlv_total > 0)
					{
						uint16_t tlv_len = *(uint16_t*)tlv_data;
						uint16_t tlv_type = *(uint16_t*)(tlv_data + 2);

						if (0 == tlv_type)
						{
							jpgdata = tlv_data + 4;
							jpglen = tlv_len;
						}
						else if (1 == tlv_type)
						{
							info->pstVbrResult = (ICE_VBR_RESULT_S*)(tlv_data + 4);
						}
						else if (2== tlv_type)
						{
							info->pPhoneMacList = (ICE_Phone_Mac_List*)(tlv_data + 4);
						}

						tlv_data += (4 + tlv_len);
						tlv_total -= (4 + tlv_len);
					}
				}

				int vehicle_color = info->stPlateInfo.eVehicleColor;
				if (NULL != info->pstVbrResult)
				{
					ConvertUtf8ToTChar(info->pstVbrResult->szLogName, 
						info->pstVbrResult->szLogName, 20);
					ConvertUtf8ToTChar(info->pstVbrResult->szSubLogName, 
						info->pstVbrResult->szSubLogName, 20);
					ConvertUtf8ToTChar(info->pstVbrResult->szProductYearName, 
						info->pstVbrResult->szProductYearName, 20);
					ConvertUtf8ToTChar(info->pstVbrResult->szLabelTotal, 
						info->pstVbrResult->szLabelTotal, 40);

					size_t slen = strlen(info->pstVbrResult->szProductYearName);
					if ('\r' == info->pstVbrResult->szProductYearName[slen - 1])
						info->pstVbrResult->szProductYearName[slen - 1] = '\0';

					slen = strlen(info->pstVbrResult->szLabelTotal);
					if ('\r' == info->pstVbrResult->szLabelTotal[slen - 1])
						info->pstVbrResult->szLabelTotal[slen - 1] = '\0';

					vehicle_color = info->enVehicleColor;
				}

				if (!bHistory)
				{
					struct tm tm;
					tm.tm_year = info->stLiveCapTime.u16Year - 1900;
					tm.tm_mon = info->stLiveCapTime.u16Month - 1;
					tm.tm_mday = info->stLiveCapTime.u16Day;
					tm.tm_hour = info->stLiveCapTime.u16Hour;
					tm.tm_min = info->stLiveCapTime.u16Minute;
					tm.tm_sec = info->stLiveCapTime.u16Second;
					tm.tm_isdst = -1;
					if (NULL != handle->pfOnPlate)
					{
						(*handle->pfOnPlate)(handle->pvPlateParam, handle->ip, handle->buf, handle->buf + 16, 
							info->as8PictureData, info->s32PicDataLen, jpgdata, jpglen, 
							(ICE_S16)(info->fSpeed+0.5), (ICE_S16)info->s32VehicleType, 0, 0, 
							info->stPlateInfo.flConfidence, vehicle_color, 
							info->stPlateInfo.ePlateType, info->enDirect, info->s32AlarmType, 
							info->u32SerialNum, (LONG)mktime(&tm), 
							((ICE_U32)((uint64_t)info >> 32)), 
							((ICE_U32)((uint64_t)info & 0xffffffff)));
						handle->clog->Logf("%s %s %s %s %s",handle->ip, "实时抓拍数据： ", handle->buf, handle->buf+16, g_szAlarmType[info->s32AlarmType]);
					}
					else if (NULL != handle->pfOnPlate_Cdecl)
					{
						(*handle->pfOnPlate_Cdecl)(handle->pvPlateParam, handle->ip, handle->buf, handle->buf + 16, 
							info->as8PictureData, info->s32PicDataLen, jpgdata, jpglen, 
							info->stPlateInfo.stPlateRect.s16Left, info->stPlateInfo.stPlateRect.s16Top, 
							info->stPlateInfo.stPlateRect.s16Right, info->stPlateInfo.stPlateRect.s16Bottom, 
							info->stPlateInfo.flConfidence, vehicle_color, 
							info->stPlateInfo.ePlateType, info->enDirect, info->s32AlarmType, 
							info->u32SerialNum, 0, ((ICE_U32)((uint64_t)info >> 32)), 
							((ICE_U32)((uint64_t)info & 0xffffffff)));
					}
				}
				else
				{
					struct tm tm;
					tm.tm_year = info->stCapTime.u16Year - 1900;
					tm.tm_mon = info->stCapTime.u16Month - 1;
					tm.tm_mday = info->stCapTime.u16Day;
					tm.tm_hour = info->stCapTime.u16Hour;
					tm.tm_min = info->stCapTime.u16Minute;
					tm.tm_sec = info->stCapTime.u16Second;
					tm.tm_isdst = -1;

					if (NULL != handle->pfOnPastPlate)
					{
						(*handle->pfOnPastPlate)(handle->pvPastPlateParam, handle->ip, 
							(LONG)mktime(&tm), handle->buf, handle->buf + 16, 
							info->as8PictureData, info->s32PicDataLen, jpgdata, jpglen, 
							info->stPlateInfo.stPlateRect.s16Left, info->stPlateInfo.stPlateRect.s16Top, 
							info->stPlateInfo.stPlateRect.s16Right, info->stPlateInfo.stPlateRect.s16Bottom, 
							info->stPlateInfo.flConfidence, vehicle_color, 
							info->stPlateInfo.ePlateType, info->enDirect, info->s32AlarmType, 0, 0, 0, 0);
						handle->clog->Logf("%s %s %s %s %s", handle->ip, "离线抓拍数据： ", handle->buf,handle->buf+16, g_szAlarmType[info->s32AlarmType]);
					}
					else if (NULL != handle->pfOnPastPlate_Cdecl)
					{
						(*handle->pfOnPastPlate_Cdecl)(handle->pvPastPlateParam, handle->ip, 
							(LONG)mktime(&tm), handle->buf, handle->buf + 16, 
							info->as8PictureData, info->s32PicDataLen, jpgdata, jpglen, 
							info->stPlateInfo.stPlateRect.s16Left, info->stPlateInfo.stPlateRect.s16Top, 
							info->stPlateInfo.stPlateRect.s16Right, info->stPlateInfo.stPlateRect.s16Bottom, 
							info->stPlateInfo.flConfidence, vehicle_color, 
							info->stPlateInfo.ePlateType, info->enDirect, info->s32AlarmType, 0, 0, 0, 0);
					}
				}
			}
		}
		else if (PAYLOAD_TYPE_VDM == type)
		{
			if (NULL != handle->pfOnStream)
			{
				(*handle->pfOnStream)(handle->pvStreamParam, 
					125, timestamp, buf + skip, len - skip);
			}
		}
		else
		{
			if (NULL != handle->pfOnStream)
			{
				(*handle->pfOnStream)(handle->pvStreamParam, 
					type, timestamp, buf + skip, len - skip);
			}
		}
	}
#endif
}
// 在ICE_IPCSDK_Open之前调用，调用一次即可
ICE_IPCSDK_API void ICE_IPCSDK_Init()
{
	CLog::Init();

#ifdef _WIN32
	CCreateDump::Instance()->DeclarDumpFile("dumpfile");
	WSADATA data;
	WSAStartup(MAKEWORD(2,2), &data);

	draw_init();
#endif

	//AVIFileInit();
	sc_init();
	sm_init();

	//SetPriorityClass(GetCurrentProcess(), /*HIGH_PRIORITY_CLASS*/REALTIME_PRIORITY_CLASS);
}

// 在ICE_IPCSDK_Close之后调用，调用一次即可
ICE_IPCSDK_API void ICE_IPCSDK_Fini()
{
	sm_fini();
	sc_fini();
	//AVIFileExit();

#ifdef _WIN32
	draw_fini();
	WSACleanup();
#endif

	CLog::Fini();
}

void evtp_callback(void *param, 
				   uint32_t type, void *data, int len)
{
	sdk_handle_t *handle = (sdk_handle_t*)param;
	if ((ICE_EVENT_TYPE_RS485_EVENT == type)/* && (NULL == handle->rtspc)*/)
	{
		callback(param, (uint8_t)99, 0, (char*)data, len);
		return;
	}

	if ((ICE_EVENT_TYPE_RS232_EVENT == type)/* && (NULL == handle->rtspc)*/)
	{
		callback(param, (uint8_t)95, 0, (char*)data, len);
		return;
	}

	if ((ICE_EVENT_TYPE_IO_EVENT == type)/* && (NULL == handle->rtspc)*/)
	{
		callback(param, (uint8_t)94, 0, (char*)data, len);
		return;
	}

	if ((ICE_EVENT_TYPE_VLPR_EVENT != type) && 
		(ICE_EVENT_TYPE_VLPREXT_EVENT != type) && 
		(ICE_EVENT_TYPE_IPG_EVENT != type))
	{
		if (NULL == data)
			callback(param, 0, 0, NULL, len);

		return;
	}

	/*if (ICE_EVENT_TYPE_VLPR_EVENT == type)
	type = 101;
	else if (0x2100 == type)
	type = 99;
	else
	return;*/

	if (ICE_EVENT_TYPE_VLPR_EVENT == type)
		callback(param, (uint8_t)101, 0, (char*)data, len);
	else if (ICE_EVENT_TYPE_VLPREXT_EVENT == type)
		callback(param, (uint8_t)105, 0, (char*)data, len);
	else if (ICE_EVENT_TYPE_IPG_EVENT == type)
		callback(param, (uint8_t)106, 0, (char*)data, len);
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenDevice(const ICE_CHAR *pcIP)
{
	return ICE_IPCSDK_OpenDevice_Passwd(pcIP, NULL);
}

ICE_HANDLE SDK_OpenDevice_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
								 ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort)
{
	if (NULL == pcIP)
		return NULL;

	ICE_U32 addr = inet_addr(pcIP);
	if ((0 == addr) || (INADDR_NONE == addr))
		return NULL;

	sdk_handle_t *handle = (sdk_handle_t*)malloc(sizeof(sdk_handle_t));
	if (NULL == handle)
		return NULL;

	memset(handle, 0, sizeof(sdk_handle_t));
	//handle->bPreview = TRUE;

	strcpy(handle->ip, pcIP);
	handle->u16ICEPort = u16ICEPort;
	handle->u16OnvifPort = u16OnvifPort;
	handle->u16RtspPort = u16RTSPPort;
	handle->u16EvtpPort = u16EvtpPort;
	handle->clog = CLog::GetInstance();//new CLog();
	handle->clog->setFilePath(g_logPath);
	handle->clog->setIp(pcIP);
	handle->clog->setEnableLog(g_nEnableLog);

	/*handle->rtsp_algo = rtspc_start(pcIP, 8554, u8OverTCP, callback, handle);
	if (NULL == handle->rtsp_algo)
	{
	rtspc_stop(handle->rtspc);
	free(handle);
	return NULL;
	}*/

	if (NULL != pcPasswd)
	{
		handle->need_passwd = 1;
		strcpy(handle->passwd, pcPasswd);
	}

	if (0 == g_nEnableLog)
		handle->evtp_handle = evtp_start_passwd(handle->ip, u16EvtpPort,  pcPasswd, evtp_callback, handle);
	else
		handle->evtp_handle = evtp_start_passwd_withLog(handle->ip, u16EvtpPort,  handle->clog, pcPasswd, evtp_callback, handle);
	if (NULL == handle->evtp_handle)
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	/*memset(&handle->m_WaveFormatEx, 0, sizeof(handle->m_WaveFormatEx));
	handle->m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	handle->m_WaveFormatEx.nChannels = 1;
	handle->m_WaveFormatEx.wBitsPerSample = 16;
	handle->m_WaveFormatEx.cbSize = 0;
	handle->m_WaveFormatEx.nSamplesPerSec = 8000;
	handle->m_WaveFormatEx.nAvgBytesPerSec = 16000;
	handle->m_WaveFormatEx.nBlockAlign = 2;

	memset(handle->m_WaveHdr, 0, sizeof(handle->m_WaveHdr));
	for (int i = 0; i < MAX_WAVE_HDR; i++)
	{
	handle->m_WaveHdr[i] = (WAVEHDR*)malloc(sizeof(WAVEHDR) + 960);
	if (NULL == handle->m_WaveHdr[i])
	continue;

	memset(handle->m_WaveHdr[i], 0, sizeof(WAVEHDR));

	handle->m_WaveHdr[i]->dwBufferLength = 960;
	handle->m_WaveHdr[i]->lpData = (LPSTR)(handle->m_WaveHdr[i] + 1);
	}

	handle->hMutex = CreateMutex(NULL, FALSE, NULL);
	if (NULL == handle->hMutex)
	{
	ICE_IPCSDK_Close(handle);
	return NULL;
	}

	handle->rec_buf = (BYTE*)malloc(2 * 1024 * 1024);
	if (NULL == handle->rec_buf)
	{
	ICE_IPCSDK_Close(handle);
	return NULL;
	}*/

	usleep(300000);
	if (!ICE_IPCSDK_GetStatus(handle))
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	if (NULL == pcPasswd)
		handle->clog->Logf("%s %s",handle->ip, "建立连接成功，连接方式：普通连接");
	else
		handle->clog->Logf("%s %s", handle->ip, "建立连接成功，连接方式：密码连接");

	return handle;
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenDevice_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd)
{
	if (NULL == pcIP)
		return NULL;

	return SDK_OpenDevice_Passwd(pcIP, pcPasswd, 554, 8117, 8080, 8200);
}

#if 0
// ICE_IPCSDK_Open自动分配一个端口,发改委项目使用本接口(嘉德恒安)
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_Open(const ICE_CHAR *pcIP, ICE_U8 u8OverTCP, 
										  ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
										  ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
										  ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam)
{
	return ICE_IPCSDK_Open_Passwd(pcIP, NULL, 
		u8OverTCP, u16RTSPPort, u16ICEPort, u16OnvifPort, u8MainStream, 
		pfOnStream, pvStreamParam, pfOnFrame, pvFrameParam);
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_Open_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
												 ICE_U8 u8OverTCP, ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
												 ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
												 ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
												 ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam)
{
	ICE_HANDLE _handle = ICE_IPCSDK_OpenDevice_Passwd(pcIP, pcPasswd);
	if (NULL == _handle)
		return NULL;

	sdk_handle_t *handle = (sdk_handle_t*)_handle;

	handle->pfOnStream = pfOnStream;
	handle->pvStreamParam = pvStreamParam;
	handle->u16ICEPort = u16ICEPort;
	handle->u16OnvifPort = u16OnvifPort;

	handle->pfOnFrame = pfOnFrame;
	handle->pvFrameParam = pvFrameParam;

	ICE_U32 ret = ICE_IPCSDK_StartStream(handle, u8MainStream, NULL);
	if (ICE_STATUS_ERROR == ret)
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	usleep(300000);
	if (!ICE_IPCSDK_GetStatus(handle))
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	if (NULL == pcPasswd)
		handle->clog->Logf("%s %s", handle->ip, "开启视频，调用接口：ICE_IPCSDK_Open");
	else
		handle->clog->Logf("%s %s", handle->ip, "开启视频，调用接口：ICE_IPCSDK_Open_Passwd");

	return handle;
}
#endif

#ifdef _WIN32
void SDK_OnFrame(void *pvParam, ICE_U32 u32Timestamp, 
				 ICE_U8 *pu8Data[], ICE_S32 s32Linesize[], 
				 ICE_S32 s32Width, ICE_S32 s32Height, 
				 ICE_U8 *rawdata, ICE_S32 rawlen)
{
	if (NULL == pvParam)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)pvParam;

	if (NULL != pu8Data)
	{
		if ((NULL != handle->hWnd) && IsWindow(handle->hWnd))
		{
			if ((s32Width != handle->width) || (s32Height != handle->height))
			{
				handle->width = s32Width;
				handle->height = s32Height;

				if (NULL != handle->draw_handle)
				{
					draw_destroy(handle->draw_handle);
					handle->draw_handle = NULL;
				}

				handle->draw_handle = draw_create(handle->hWnd, 
					s32Width, s32Height, NULL, NULL);
			}

			draw_display_yuv420(handle->draw_handle, pu8Data, s32Linesize);
		}

		/*if ((NULL != pu8Data) && (NULL != handle->pfOnFramePlanar))
		{
		(*handle->pfOnFramePlanar)(handle->pvFramePlanarParam, u32Timestamp, 
		pu8Data[0], pu8Data[1], pu8Data[2], 
		s32Linesize[0], s32Linesize[1], s32Linesize[2], 
		s32Width, s32Height);
		}*/
	}

	/*if (NULL != handle->pfOnData)
	{
	(*handle->pfOnData)(handle->pvDataParam, 
	96, u32Timestamp, rawdata, rawlen);
	}

	if (NULL != handle->pfOnFrame)
	{
	(*handle->pfOnFrame)(handle->pvFrameParam, u32Timestamp, 
	pu8Data, s32Linesize, s32Width, s32Height, rawdata, rawlen);
	}

	WaitForSingleObject(handle->hMutex, INFINITE);
	if (NULL != handle->pavstream)
	{
	if ((0 != handle->ts) && (u32Timestamp != handle->ts))
	{
	AVIStreamWrite(handle->pavstream, handle->count++, 1, 
	handle->rec_buf, handle->rec_len, AVIIF_LIST, NULL, NULL);
	handle->rec_len = 0;
	}

	memcpy(handle->rec_buf + handle->rec_len, rawdata, rawlen);
	handle->rec_len += rawlen;
	}
	ReleaseMutex(handle->hMutex);

	handle->ts = u32Timestamp;
	handle->frame_width = s32Width;
	handle->frame_height = s32Height;*/
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_StartStream(ICE_HANDLE hSDK, 
											  ICE_U8 u8MainStream, ICE_U32 hWnd)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	if (NULL != handle->rtspc)
		return ICE_STATUS_ERROR;

	handle->rtspc = rtspc_start(handle->ip, handle->u16RtspPort, 1, u8MainStream, callback, handle);
	if (NULL == handle->rtspc)
		return ICE_STATUS_ERROR;

	handle->hWnd = (HWND)hWnd;
	handle->u8MainStream = u8MainStream;

	handle->dec = dec_create(SDK_OnFrame, hSDK);
	if (NULL == handle->dec)
	{
		ICE_IPCSDK_StopStream(handle);
		return ICE_STATUS_ERROR;
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API void ICE_IPCSDK_StopStream(ICE_HANDLE hSDK)
{
	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (NULL != handle->rtspc)
	{
		rtspc_stop(handle->rtspc);
		handle->rtspc = NULL;
	}

	if (NULL != handle->dec)
	{
		dec_destroy(handle->dec);
		handle->dec = NULL;
	}

	if (NULL != handle->draw_handle)
	{
		draw_destroy(handle->draw_handle);
		handle->draw_handle = NULL;
	}

	handle->width = 0;
	handle->height = 0;
}
#endif

#if 0
ICE_IPCSDK_API void ICE_IPCSDK_SetDataCallback(ICE_HANDLE hSDK, 
											   ICE_IPCSDK_OnStream pfOnStream, void *pvParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnData = pfOnStream;
	handle->pvDataParam = pvParam;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TriggerExt(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 3000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "软触发扩展接口失败，原因：连接相机失败");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);
	header.u32Channel = 1;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM_RSP != header.u32Type))
	{
		handle->clog->Logf("%s %s", handle->ip, "软触发扩展接口失败，原因：相机无返回或者返回数据错误");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);

	handle->clog->Logf("%s %s", handle->ip, "软触发扩展接口成功");
	return header.u32Status;
}

ICE_IPCSDK_API void ICE_IPCSDK_SetFrameCallback(ICE_HANDLE hSDK, 
												ICE_IPCSDK_OnFrame_Planar pfOnFrame, void *pvParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnFramePlanar = pfOnFrame;
	handle->pvFramePlanarParam = pvParam;
}

ICE_IPCSDK_API void ICE_IPCSDK_SetPlateCallback(ICE_HANDLE hSDK, 
												ICE_IPCSDK_OnPlate pfOnPlate, void *pvParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnPlate = pfOnPlate;
	handle->pvPlateParam = pvParam;
}

ICE_IPCSDK_API void ICE_IPCSDK_SetPlateCallback_Cdecl(ICE_HANDLE hSDK, 
													  ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnPlate_Cdecl = pfOnPlate;
	handle->pvPlateParam = pvParam;
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenPreview(const ICE_CHAR *pcIP, 
												 ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
												 ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam)
{
	return ICE_IPCSDK_OpenPreview_Passwd(pcIP, NULL, 
		u8OverTCP, u8MainStream, hWnd, pfOnPlate, pvPlateParam);
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenPreview_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
														ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam)
{
	return ICE_IPCSDK_OpenPreviewExt_Passwd(pcIP, pcPasswd, u8OverTCP, u8MainStream, hWnd, 
		pfOnPlate, pvPlateParam, 554, 8117, 8080, 8200);
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenPreviewExt(const ICE_CHAR *pcIP, 
													ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
													ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
													ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
													ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort)
{
	return ICE_IPCSDK_OpenPreviewExt_Passwd(pcIP, NULL, 
		u8OverTCP, u8MainStream, hWnd, pfOnPlate, pvPlateParam, 
		u16RTSPPort, u16ICEPort, u16OnvifPort, u16EvtpPort);
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenPreviewExt_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
														   ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														   ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
														   ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
														   ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort)
{
	ICE_HANDLE hSDK = SDK_OpenDevice_Passwd(pcIP, pcPasswd, 
		u16RTSPPort, u16ICEPort, u16OnvifPort, u16EvtpPort);
	if (NULL == hSDK)
		return NULL;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	handle->pfOnPlate = pfOnPlate;
	handle->pvPlateParam = pvPlateParam;

	ICE_U32 ret = ICE_IPCSDK_StartStream(handle, u8MainStream, hWnd);
	if (ICE_STATUS_ERROR == ret)
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	usleep(300000);
	if (!ICE_IPCSDK_GetStatus(handle))
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	if (NULL == pcPasswd)
		handle->clog->Logf("%s %s", handle->ip, "开启视频成功，ICE_IPCSDK_Preview");
	else
		handle->clog->Logf("%s %s", handle->ip, "开启视频成功，ICE_IPCSDK_Preview_Passwd");

	return hSDK;
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenPreview_Cdecl(const ICE_CHAR *pcIP, 
													   ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
													   ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvPlateParam)
{
	return ICE_IPCSDK_OpenPreview_Cdecl_Passwd(pcIP, NULL, 
		u8OverTCP, u8MainStream, hWnd, pfOnPlate, pvPlateParam);
}

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_OpenPreview_Cdecl_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
															  ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
															  ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvPlateParam)
{
	ICE_HANDLE hSDK = ICE_IPCSDK_OpenDevice_Passwd(pcIP, pcPasswd);
	if (NULL == hSDK)
		return NULL;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	handle->pfOnPlate_Cdecl = pfOnPlate;
	handle->pvPlateParam = pvPlateParam;

	ICE_U32 ret = ICE_IPCSDK_StartStream(handle, u8MainStream, hWnd);
	if (ICE_STATUS_ERROR == ret)
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	usleep(300000);
	if (!ICE_IPCSDK_GetStatus(handle))
	{
		ICE_IPCSDK_Close(handle);
		return NULL;
	}

	return hSDK;
}

void StopTalk(ICE_HANDLE hSDK)
{
	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	handle->m_bTalk = FALSE;

	if (NULL != handle->m_hWaveIn)
	{
		usleep(600000);
		waveInStop(handle->m_hWaveIn);
		waveInReset(handle->m_hWaveIn);

		for (int i = 0; i < MAX_WAVE_HDR; i++)
		{
			if (NULL == handle->m_WaveHdr[i])
				continue;

			waveInUnprepareHeader(handle->m_hWaveIn, handle->m_WaveHdr[i], sizeof(WAVEHDR));
		}

		waveInClose(handle->m_hWaveIn);
		handle->m_hWaveIn = NULL;
	}

	if (NULL != handle->m_hWaveOut)
	{
		waveOutReset(handle->m_hWaveOut);
		waveOutClose(handle->m_hWaveOut);
		handle->m_hWaveOut = NULL;
	}
}
#endif

ICE_IPCSDK_API void ICE_IPCSDK_Close(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	/*if (NULL != handle->rec_buf)
	{
	free(handle->rec_buf);
	handle->rec_buf = NULL;
	}

	if (NULL != handle->hMutex)
	{
	CloseHandle(handle->hMutex);
	handle->hMutex = NULL;
	}

	StopTalk(hSDK);
	for (int i = 0; i < MAX_WAVE_HDR; i++)
	{
	if (NULL == handle->m_WaveHdr[i])
	continue;

	free(handle->m_WaveHdr[i]);
	handle->m_WaveHdr[i] = NULL;
	}*/

	if (NULL != handle->evtp_handle)
	{
		evtp_stop(handle->evtp_handle);
		handle->evtp_handle = NULL;
	}

#ifdef _WIN32
	if (NULL != handle->rtsp_algo)
	{
		rtspc_stop(handle->rtsp_algo);
		handle->rtsp_algo = NULL;
	}

	ICE_IPCSDK_StopStream(handle);
#endif

	free(handle);
}

#if 0
// 设置VD参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetVDParam(ICE_HANDLE hSDK, 
											 const ICE_VD_PARAM_S *pstParam)
{
	if ((NULL == hSDK) || (NULL == pstParam))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + sizeof(ICE_VD_PARAM_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, sizeof(ICE_VD_PARAM_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

// 获取VD参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetVDParam(ICE_HANDLE hSDK, 
											 ICE_VD_PARAM_S *pstParam)
{
	if ((NULL == hSDK) || (NULL == pstParam))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + sizeof(ICE_VD_PARAM_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, sizeof(ICE_VD_PARAM_S), 1000);

	close(sockfd);
	return header.u32Status;
}
// 设置VDC参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetVDCParam(ICE_HANDLE hSDK, 
											  const ICE_VDC_PARAM_S *pstParam)
{
	if ((NULL == hSDK) || (NULL == pstParam))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + sizeof(ICE_VDC_PARAM_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, sizeof(ICE_VDC_PARAM_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

// 获取VDC参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetVDCParam(ICE_HANDLE hSDK, 
											  ICE_VDC_PARAM_S *pstParam)
{
	if ((NULL == hSDK) || (NULL == pstParam))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + sizeof(ICE_VDC_PARAM_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, sizeof(ICE_VDC_PARAM_S), 1000);

	close(sockfd);
	return header.u32Status;
}

// 布防
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetArm(ICE_HANDLE hSDK, ICE_U8 u8Arm)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = u8Arm ? ICE_CONTROL_TYPE_VDR_ARM : ICE_CONTROL_TYPE_VDR_DISARM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	ICE_U32 u32RSP = u8Arm ? ICE_CONTROL_TYPE_VDR_ARM_RSP : ICE_CONTROL_TYPE_VDR_DISARM_RSP;

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (u32RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
// 获取布防状态
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetArm(ICE_HANDLE hSDK, ICE_U8 *pu8Arm)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + 1 != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pu8Arm, 1, 1000);

	close(sockfd);
	return header.u32Status;
}

//设置DTCA参数
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetDTCAParam(ICE_HANDLE hSDK, 
const ICE_CLBR_PARAM *pstCLBRParam, const ICE_DTCA_PARAM_ALGO *pstDTCAParam)
{
if ((NULL == hSDK) || (NULL == pstCLBRParam) || (NULL == pstDTCAParam))
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_ALGO_CONFIG_TYPE_SET_DTCA_RULE_PARAM;
header.u32Size = sizeof(ICE_OPER_DATA_S) + 
sizeof(ICE_CLBR_PARAM) + sizeof(ICE_DTCA_PARAM_ALGO);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
socket_send(sockfd, pstCLBRParam, sizeof(ICE_CLBR_PARAM), 1000);
socket_send(sockfd, pstDTCAParam, sizeof(ICE_DTCA_PARAM_ALGO), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_SET_DTCA_RULE_PARAM_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

close(sockfd);
return header.u32Status;
}

//获取DTCA参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDTCAParam(ICE_HANDLE hSDK, 
ICE_CLBR_PARAM *pstCLBRParam, ICE_DTCA_PARAM_ALGO *pstDTCAParam)
{
if ((NULL == hSDK) || (NULL == pstCLBRParam) || (NULL == pstDTCAParam))
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_ALGO_CONFIG_TYPE_GET_DTCA_RULE_PARAM;
header.u32Size = sizeof(ICE_OPER_DATA_S);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_GET_DTCA_RULE_PARAM_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) + sizeof(ICE_CLBR_PARAM) 
+ sizeof(ICE_DTCA_PARAM_ALGO) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

socket_recv(sockfd, pstCLBRParam, sizeof(ICE_CLBR_PARAM), 1000);
socket_recv(sockfd, pstDTCAParam, sizeof(ICE_DTCA_PARAM_ALGO), 1000);

close(sockfd);
return header.u32Status;
}

//设置TCNT参数（拌线版人数统计）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetTCNTParam(ICE_HANDLE hSDK, 
const ICE_TCNT_PARAM_ALGO *pstTCNTParam)
{
if ((NULL == hSDK) || (NULL == pstTCNTParam))
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO;
header.u32Size = sizeof(ICE_OPER_DATA_S) + sizeof(ICE_TCNT_PARAM_ALGO);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
socket_send(sockfd, pstTCNTParam, sizeof(ICE_TCNT_PARAM_ALGO), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

close(sockfd);
return header.u32Status;
}

//获取TCNT参数（拌线版人数统计）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetTCNTParam(ICE_HANDLE hSDK, 
ICE_TCNT_PARAM_ALGO *pstTCNTParam)
{
if ((NULL == hSDK) || (NULL == pstTCNTParam))
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO;
header.u32Size = sizeof(ICE_OPER_DATA_S);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) + sizeof(ICE_TCNT_PARAM_ALGO) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

socket_recv(sockfd, pstTCNTParam, sizeof(ICE_TCNT_PARAM_ALGO), 1000);

close(sockfd);
return header.u32Status;
}
//设置HCNT参数（基于人头的人数统计）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetHCNTParam(ICE_HANDLE hSDK, 
const ICE_CLBR_PARAM *pstCLBRParam, const ICE_HCNT_PARAM_ALGO *pstHCNTParam)
{
if ((NULL == hSDK) || (NULL == pstHCNTParam))
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO;
header.u32Size = sizeof(ICE_OPER_DATA_S) + sizeof(ICE_CLBR_PARAM) + sizeof(ICE_HCNT_PARAM_ALGO);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
socket_send(sockfd, pstCLBRParam, sizeof(ICE_CLBR_PARAM), 1000);
socket_send(sockfd, pstHCNTParam, sizeof(ICE_HCNT_PARAM_ALGO), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

close(sockfd);
return header.u32Status;
}
//获取HCNT参数（基于人头的人数统计）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetHCNTParam(ICE_HANDLE hSDK, 
ICE_CLBR_PARAM *pstCLBRParam, ICE_HCNT_PARAM_ALGO *pstHCNTParam)
{
if ((NULL == hSDK) || (NULL == pstHCNTParam))
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO;
header.u32Size = sizeof(ICE_OPER_DATA_S);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) + sizeof(ICE_CLBR_PARAM) + sizeof(ICE_HCNT_PARAM_ALGO) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

socket_recv(sockfd, pstCLBRParam, sizeof(ICE_CLBR_PARAM), 1000);
socket_recv(sockfd, pstHCNTParam, sizeof(ICE_HCNT_PARAM_ALGO), 1000);

close(sockfd);
return header.u32Status;
}*/

//设置相机曝光参数，包括定时、自动、手动模式，定时分三个时间段（白天、夜间、其它）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetExpAttr(ICE_HANDLE hSDK, const ICE_ExpAttr_S *pstExpAttr)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_ExpAttr_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_ISP_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstExpAttr, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_ISP_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
//获取相机曝光参数，包括定时、自动、手动模式，定时分三个时间段（白天、夜间、其它）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetExpAttr(ICE_HANDLE hSDK, ICE_ExpAttr_S *pstExpAttr)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_ExpAttr_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 3000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_ISP_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_ISP_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstExpAttr, size, 3000);
	close(sockfd);

	return header.u32Status;
}

// 获取相机当前IP地址，获取IP地址、掩码、网关
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetIPAddr(ICE_HANDLE hSDK, 
											ICE_U32 *pu32IP, ICE_U32 *pu32Mask, ICE_U32 *pu32Gateway)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 3 * sizeof(ICE_U32);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_BASE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_BASE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	ICE_U32 addr[3];
	socket_recv(sockfd, addr, size, 1000);
	close(sockfd);

	if (NULL != pu32IP)
		*pu32IP = addr[0];

	if (NULL != pu32Mask)
		*pu32Mask = addr[1];

	if (NULL != pu32Gateway)
		*pu32Gateway = addr[2];

	return header.u32Status;
}

// 设置相机当前IP地址，获取IP地址、掩码、网关
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetIPAddr(ICE_HANDLE hSDK, 
											ICE_U32 u32IP, ICE_U32 u32Mask, ICE_U32 u32Gateway)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 3 * sizeof(int);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_BASE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int addr[3] = {u32IP, u32Mask, u32Gateway};
	socket_send(sockfd, addr, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_BASE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
#endif

//设置IPG（车位）参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetIPGParam(ICE_HANDLE hSDK, const ICE_IPG_PARAM_S *pstParam)
{
	if ((NULL == hSDK) || (NULL == pstParam))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_ALGO_CONFIG_TYPE_SET_SFDV_RULE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + sizeof(ICE_IPG_PARAM_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, sizeof(ICE_IPG_PARAM_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_SET_SFDV_RULE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

//获取IPG（车位）参数
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetIPGParam(ICE_HANDLE hSDK, ICE_IPG_PARAM_S *pstParam)
{
	if ((NULL == hSDK) || (NULL == pstParam))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_ALGO_CONFIG_TYPE_GET_SFDV_RULE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_ALGO_CONFIG_TYPE_GET_SFDV_RULE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + sizeof(ICE_IPG_PARAM_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, sizeof(ICE_IPG_PARAM_S), 1000);

	close(sockfd);
	return header.u32Status;
}

#if 0
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetSnapCamera(ICE_HANDLE hSDK, 
												ICE_SNAP_CAMERA_S *pstSnapCamera)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_SNAP_CAMERA_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_SNAP_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_SNAP_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstSnapCamera, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetSnapCamera(ICE_HANDLE hSDK, 
												const ICE_SNAP_CAMERA_S *pstSnapCamera)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_SNAP_CAMERA_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_SNAP_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstSnapCamera, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_SNAP_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetFTP(ICE_HANDLE hSDK, ICE_U32 *pu32Enable, 
										 ICE_U32 *pu32IP, ICE_S8 *ps8Username, ICE_S8 *ps8Password, ICE_U32 *pu32Interval, 
										 ICE_S8 *ps8Path, ICE_U32 *pu32Plate, ICE_U32 *pu32XML)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 256;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_FTP_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_FTP_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	char buf[256] = {0};
	socket_recv(sockfd, buf, size, 1000);
	close(sockfd);

	if (NULL != pu32IP)
		*pu32IP = *(ICE_U32*)buf;

	if (NULL != ps8Username)
		strcpy(ps8Username, buf + 4);

	if (NULL != ps8Password)
		strcpy(ps8Password, buf + 68);

	if (NULL != pu32Interval)
		*pu32Interval = *(ICE_U32*)(buf + 132);

	if (NULL != pu32Enable)
		*pu32Enable = *(ICE_U32*)(buf + 136);

	if (NULL != pu32Plate)
		*pu32Plate = *(ICE_U32*)(buf + 140);

	if (NULL != pu32XML)
		*pu32XML = *(ICE_U32*)(buf + 144);

	if (NULL != ps8Path)
		strcpy(ps8Path, buf + 148);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetFTP(ICE_HANDLE hSDK, ICE_U32 u32Enable, 
										 ICE_U32 u32IP, const ICE_S8 *ps8Username, const ICE_S8 *ps8Password, ICE_U32 u32Interval, 
										 const ICE_S8 *ps8Path, ICE_U32 u32Plate, ICE_U32 u32XML)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 256;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_FTP_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	char buf[256] = {0};
	*(ICE_U32*)buf = u32IP;
	strcpy(buf + 4, ps8Username);
	strcpy(buf + 68, ps8Password);
	*(ICE_U32*)(buf + 132) = u32Interval;
	*(ICE_U32*)(buf + 136) = u32Enable;
	*(ICE_U32*)(buf + 140) = u32Plate;
	*(ICE_U32*)(buf + 144) = u32XML;
	strcpy(buf + 148, ps8Path);
	socket_send(sockfd, buf, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_FTP_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
#endif

//onvif接口实现
#define ONVIF_HDR \
	"POST / HTTP/1.1\r\n\
Content-Type: application/soap+xml;charset=utf-8;\r\n\
Host: %s:8080\r\n\
Content-Length: %d\r\n\r\n%s"

#define ONVIF_SEND(sockfd, buf, ip, req) \
{\
	sprintf((buf), ONVIF_HDR, ip, (int)strlen((req)), (req));\
	socket_send((sockfd), (buf), (int)strlen((buf)), 1000);\
	usleep(30000);\
}

#define ONVIF_XMLNS "\
xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\"\r\n\
xmlns:SOAP-ENC=\"http://www.w3.org/2003/05/soap-encoding\"\r\n\
xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\r\n\
xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\r\n\
xmlns:wsa5=\"http://www.w3.org/2005/08/addressing\"\r\n\
xmlns:tt=\"http://www.onvif.org/ver10/schema\"\r\n"

#define ONVIF_DEVICE_XMLNS \
	ONVIF_XMLNS\
	"xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\">\r\n"

#if 0
#define ONVIF_MEDIA_XMLNS \
	ONVIF_XMLNS\
	"xmlns:trt=\"http://www.onvif.org/ver10/media/wsdl\">\r\n"

#define ONVIF_GET_RELAY_OUTPUT \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_DEVICE_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<tds:GetRelayOutputs>\r\n\
</tds:GetRelayOutputs>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

#define ONVIF_SET_RELAY_OUTPUT \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_DEVICE_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<tds:SetRelayOutputSettings>\r\n\
<tds:RelayOutputToken>%s</tds:RelayOutputToken>\r\n\
<tds:Properties>\r\n\
<Mode>Monostable</Mode>\r\n\
<DelayTime>PT%dS</DelayTime>\r\n\
<IdleState>%s</IdleState>\r\n\
</tds:Properties>\r\n\
</tds:SetRelayOutputSettings>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

#define ONVIF_GET_PROFILE \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_MEDIA_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<GetProfile>\r\n\
<ProfileToken>%s</ProfileToken>\r\n\
</GetProfile>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

#define ONVIF_SET_VIDEO_ENC_CFG \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_MEDIA_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<SetVideoEncoderConfiguration>\r\n\
<Configuration token=\"%s\">\r\n\
<Resolution>\r\n\
<Width>%d</Width>\r\n\
<Height>%d</Height>\r\n\
</Resolution>\r\n\
<RateControl>\r\n\
<FrameRateLimit>%d</FrameRateLimit>\r\n\
<BitrateLimit>%d</BitrateLimit>\r\n\
</RateControl>\r\n\
</Configuration>\r\n\
</SetVideoEncoderConfiguration>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

#define ONVIF_SYSTEM_REBOOT \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_DEVICE_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<tds:SystemReboot>\r\n\
</tds:SystemReboot>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"
#endif

#define ONVIF_SET_SYSTEM_DATE_TIME \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_DEVICE_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<tds:SetSystemDateAndTime>\r\n\
<tds:DateTimeType>Manual</tds:DateTimeType>\r\n\
<tds:DaylightSavings>false</tds:DaylightSavings>\r\n\
<tds:UTCDateTime>\r\n\
<Time>\r\n\
<Hour>%d</Hour>\r\n\
<Minute>%d</Minute>\r\n\
<Second>%d</Second>\r\n\
</Time>\r\n\
<Date>\r\n\
<Year>%d</Year>\r\n\
<Month>%d</Month>\r\n\
<Day>%d</Day>\r\n\
</Date>\r\n\
</tds:UTCDateTime>\r\n\
</tds:SetSystemDateAndTime>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

#define ONVIF_GET_SYSTEM_DATE_TIME \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_DEVICE_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<tds:GetSystemDateAndTimeResponse>\r\n\
<tds:SystemDateAndTime>\r\n\
<tt:DateTimeType>Manual</tt:DateTimeType>\r\n\
<tt:DaylightSavings>false</tt:DaylightSavings>\r\n\
<tt:TimeZone>\r\n\
<tt:TZ>ChinaStandardTime-8</tt:TZ>\r\n\
</tt:TimeZone>\r\n\
<tt:LocalDateTime>\r\n\
<tt:Time>\r\n\
<tt:Hour>\r\n\
</tt:Hour>\r\n\
<tt:Minute>\r\n\
</tt:Minute>\r\n\
<tt:Second>\r\n\
</tt:Second>\r\n\
</tt:Time>\r\n\
<tt:Date>\r\n\
<tt:Year>\r\n\
</tt:Year>\r\n\
<tt:Month>\r\n\
</tt:Month>\r\n\
<tt:Day>\r\n\
</tt:Day>\r\n\
</tt:Date>\r\n\
</tt:LocalDateTime>\r\n\
</tds:SystemDateAndTime>\r\n\
</tds:GetSystemDateAndTimeResponse>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"
#if 0
#define ONVIF_IMAGING_XMLNS \
	ONVIF_XMLNS\
	"xmlns:timg=\"http://www.onvif.org/ver20/imaging/wsdl\">\r\n"

#define ONVIF_GET_IMAGING_SETTINGS \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_IMAGING_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<timg:GetImagingSettings>\r\n\
<timg:VideoSourceToken>MainVideoSrc</timg:VideoSourceToken>\r\n\
</timg:GetImagingSettings>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

#define ONVIF_SET_IMAGING_SETTINGS \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<SOAP-ENV:Envelope\r\n"\
	ONVIF_IMAGING_XMLNS\
	"<SOAP-ENV:Header>\r\n\
</SOAP-ENV:Header>\r\n\
<SOAP-ENV:Body>\r\n\
<timg:SetImagingSettings>\r\n\
<timg:VideoSourceToken>MainVideoSrc</timg:VideoSourceToken>\r\n\
<timg:ImagingSettings>\r\n\
<Brightness>%d</Brightness>\r\n\
<ColorSaturation>%d</ColorSaturation>\r\n\
<Contrast>%d</Contrast>\r\n\
<Sharpness>%d</Sharpness>\r\n\
</timg:ImagingSettings>\r\n\
</timg:SetImagingSettings>\r\n\
</SOAP-ENV:Body>\r\n\
</SOAP-ENV:Envelope>"

// 获取开关量设置（ONVIF实现）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetRelayOutput(
	ICE_HANDLE hSDK, ICE_U8 *pu8IdleState, ICE_U32 *pu32DelayTime)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[4096];
	ONVIF_SEND(sockfd, buf, handle->ip, ONVIF_GET_RELAY_OUTPUT);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	char *pos = strstr(buf, "<tt:IdleState>");
	if (NULL != pos)
	{
		pos += 14;
		*pu8IdleState = (0 == strncmp(pos, "closed", 6)) ? 1 : 0;
	}

	pos = strstr(buf, "<tt:DelayTime>PT");
	if (NULL != pos)
	{
		pos += 16;
		*pu32DelayTime = atoi(pos);
	}

	close(sockfd);
	return ICE_STATUS_OK;
}
// 设置开关量设置（ONVIF实现）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetRelayOutputSettings(
	ICE_HANDLE hSDK, ICE_U8 u8IdleState, ICE_U32 u32DelayTime)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[1024], req[1024];
	sprintf(req, ONVIF_SET_RELAY_OUTPUT, "RelayOutput", u32DelayTime, u8IdleState ? "closed" : "open");
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	if (NULL == strstr(buf, "200 OK"))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

// 获取开关量设置（ONVIF实现）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetRelayOutput2(
	ICE_HANDLE hSDK, ICE_U8 *pu8IdleState, ICE_U32 *pu32DelayTime)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[4096];
	ONVIF_SEND(sockfd, buf, handle->ip, ONVIF_GET_RELAY_OUTPUT);

	int len = socket_recv_unknown(sockfd, buf, 4096, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	char *output2 = strstr(buf, "RelayOutput2");
	if (NULL == output2)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	char *pos = strstr(output2, "<tt:IdleState>");
	if (NULL != pos)
	{
		pos += 14;
		*pu8IdleState = (0 == strncmp(pos, "closed", 6)) ? 1 : 0;
	}

	pos = strstr(output2, "<tt:DelayTime>PT");
	if (NULL != pos)
	{
		pos += 16;
		*pu32DelayTime = atoi(pos);
	}

	close(sockfd);
	return ICE_STATUS_OK;
}
// 设置开关量设置（ONVIF实现）
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetRelayOutput2Settings(
	ICE_HANDLE hSDK, ICE_U8 u8IdleState, ICE_U32 u32DelayTime)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[1024], req[1024];
	sprintf(req, ONVIF_SET_RELAY_OUTPUT, "RelayOutput2", u32DelayTime, u8IdleState ? "closed" : "open");
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	if (NULL == strstr(buf, "200 OK"))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IdleState, 
	ICE_U32 *pu32DelayTime, ICE_U32 *pu32Reserve)
{
	if ((NULL == hSDK) || (u32Index >= 2))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[4096];
	ONVIF_SEND(sockfd, buf, handle->ip, ONVIF_GET_RELAY_OUTPUT);

	int len = socket_recv_unknown(sockfd, buf, 4096, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	char token[128] = {0};
	if (0 == u32Index)
		strcpy(token, "RelayOutput");
	else if (1 == u32Index)
		sprintf(token, "RelayOutput%d", u32Index + 1);

	char *output = strstr(buf, token);
	if (NULL == output)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	char *pos = strstr(output, "<tt:IdleState>");
	if (NULL != pos)
	{
		pos += 14;
		*pu32IdleState = (0 == strncmp(pos, "closed", 6)) ? 1 : 0;
	}

	pos = strstr(output, "<tt:DelayTime>PT");
	if (NULL != pos)
	{
		pos += 16;
		*pu32DelayTime = atoi(pos);
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 u32IdleState, 
	ICE_U32 u32DelayTime, ICE_U32 u32Reserve)
{
	if ((NULL == hSDK) || (u32Index >= 2))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char token[128] = {0};
	if (0 == u32Index)
		strcpy(token, "RelayOutput");
	else if (1 == u32Index)
		sprintf(token, "RelayOutput%d", u32Index + 1);

	char buf[1024], req[1024];
	sprintf(req, ONVIF_SET_RELAY_OUTPUT, token, u32DelayTime, u32IdleState ? "closed" : "open");
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	if (NULL == strstr(buf, "200 OK"))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetEncoderSettings(
	ICE_HANDLE hSDK, ICE_U8 u8MainStream, 
	ICE_U32 *pu32Width, ICE_U32 *pu32Height, 
	ICE_U32 *pu32FrameRate, ICE_U32 *pu32BitRate)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[2048], req[1024];
	sprintf(req, ONVIF_GET_PROFILE, 
		u8MainStream ? "MainProfile" : "SubProfile");
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 2048, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	char *pos = strstr(buf, "<tt:Width>");
	if (NULL != pos)
		*pu32Width = atoi(pos + 10);

	pos = strstr(buf, "<tt:Height>");
	if (NULL != pos)
		*pu32Height = atoi(pos + 11);

	pos = strstr(buf, "<tt:FrameRateLimit>");
	if (NULL != pos)
		*pu32FrameRate = atoi(pos + 19);

	pos = strstr(buf, "<tt:BitrateLimit>");
	if (NULL != pos)
		*pu32BitRate = atoi(pos + 17);

	close(sockfd);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetEncoderSettings(
	ICE_HANDLE hSDK, ICE_U8 u8MainStream, 
	ICE_U32 u32Width, ICE_U32 u32Height, 
	ICE_U32 u32FrameRate, ICE_U32 u32BitRate)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[1024], req[1024];
	sprintf(req, ONVIF_SET_VIDEO_ENC_CFG, 
		u8MainStream ? "MainVideoEnc" : "SubVideoEnc", 
		u32Width, u32Height, u32FrameRate, u32BitRate);
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	if (NULL == strstr(buf, "200 OK"))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_Reboot(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int stream = (NULL != handle->rtspc);
	if (stream)
	{
		rtspc_stop(handle->rtspc);
		handle->rtspc = NULL;
	}

	if (NULL != handle->evtp_handle)
	{
		evtp_stop(handle->evtp_handle);
		handle->evtp_handle = NULL;
	}

	if (NULL != g_pfOnDeviceEvent)
	{
		(*g_pfOnDeviceEvent)(g_pvDeviceEventParam, 
			handle->ip, 0, 0, 0, 0, 0);
	}

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[2048];
	ONVIF_SEND(sockfd, buf, handle->ip, ONVIF_SYSTEM_REBOOT);

	int len = socket_recv_unknown(sockfd, buf, 2048, 1000);

	if (stream)
	{
		handle->rtspc = rtspc_start(handle->ip, handle->u16RtspPort, 
			1, handle->u8MainStream, callback, handle);
	}

	/*handle->evtp_handle = evtp_start_passwd(handle->ip, handle->u16EvtpPort, 
	(handle->need_passwd ? handle->passwd : NULL), evtp_callback, handle);*/
	if (0 == g_nEnableLog)
		handle->evtp_handle = evtp_start_passwd(handle->ip, handle->u16EvtpPort,  (handle->need_passwd ? handle->passwd : NULL), evtp_callback, handle);
	else
		handle->evtp_handle = evtp_start_passwd_withLog(handle->ip, handle->u16EvtpPort,  handle->clog, (handle->need_passwd ? handle->passwd : NULL), evtp_callback, handle);

	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	close(sockfd);
	return ICE_STATUS_OK;
}
#endif

// PC本机时间同步，当前建立连接后同步一次
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SyncTime(ICE_HANDLE hSDK, 
										   ICE_U16 u16Year, ICE_U8 u8Month, ICE_U8 u8Day, 
										   ICE_U8 u8Hour, ICE_U8 u8Min, ICE_U8 u8Sec)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	struct tm t;
	memset(&t, 0, sizeof(t));
	t.tm_year = u16Year-1900;
	t.tm_mon = u8Month-1;
	t.tm_mday = u8Day;
	t.tm_hour = u8Hour;
	t.tm_min = u8Min;
	t.tm_sec = u8Sec;

	time_t tt = mktime(&t);
	/*if (tt == -1)
	return ICE_STATUS_ERROR;*/

	struct tm *ptm = gmtime(&tt);

	int sockfd = socket_connect(handle->ip, handle->u16OnvifPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[4096], req[4096];
	sprintf(req, ONVIF_SET_SYSTEM_DATE_TIME, 
		ptm->tm_hour, ptm->tm_min, ptm->tm_sec, ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	if (NULL == strstr(buf, "200 OK"))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetHCNTCfg(ICE_HANDLE hSDK, 
ICE_S32 *ps32RS485Type, ICE_U32 *pu32DoorType, ICE_U32 *pu32Railway)
{
if (NULL == hSDK)
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;
static int size = 3 * sizeof(ICE_U32);

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_HCNT_PARAM;
header.u32Size = sizeof(ICE_OPER_DATA_S);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_HCNT_PARAM_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

char buf[64];
socket_recv(sockfd, buf, size, 1000);
close(sockfd);

if (NULL != ps32RS485Type)
*ps32RS485Type = *(ICE_S32*)buf;

if (NULL != pu32DoorType)
*pu32DoorType = *(ICE_U32*)(buf + 4);

if (NULL != pu32Railway)
*pu32Railway = *(ICE_U32*)(buf + 8);

return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetHCNTCfg(ICE_HANDLE hSDK, 
ICE_S32 s32RS485Type, ICE_U32 u32DoorType, ICE_U32 u32Railway)
{
if (NULL == hSDK)
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;
static int size = 3 * sizeof(ICE_U32);

int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_HCNT_PARAM;
header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

char buf[64];
*(ICE_S32*)buf = s32RS485Type;
*(ICE_U32*)(buf + 4) = u32DoorType;
*(ICE_U32*)(buf + 8) = u32Railway;
socket_send(sockfd, buf, size, 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_HCNT_PARAM_RSP != header.u32Type) || 
(sizeof(ICE_OPER_DATA_S) != header.u32Size))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

close(sockfd);
return header.u32Status;
}*/

#if 0
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAlarmInCfg(
	ICE_HANDLE hSDK, ICE_U32 *pu32IdleState)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_U32);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	char buf[64];
	socket_recv(sockfd, buf, size, 1000);
	close(sockfd);

	if (NULL != pu32IdleState)
		*pu32IdleState = *(ICE_U32*)buf;

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetAlarmInCfg(
	ICE_HANDLE hSDK, ICE_U32 u32IdleState)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_U32);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	char buf[64];
	*(ICE_U32*)buf = u32IdleState;
	socket_send(sockfd, buf, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetNTPCfg(
	ICE_HANDLE hSDK, ICE_U32 *pu32Mode, char *pcNTPServer, ICE_U32 *pu32TimeZone)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 32 * sizeof(ICE_U32) + 128;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_TMSYNC_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_TMSYNC_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	char buf[256];
	socket_recv(sockfd, buf, size, 1000);
	close(sockfd);

	if (NULL != pu32Mode)
		*pu32Mode = *(ICE_U32*)buf;

	if (NULL != pcNTPServer)
		strcpy(pcNTPServer, buf + 4);

	if (NULL != pu32TimeZone)
		*pu32TimeZone = *(ICE_U32*)(buf + 132);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetNTPCfg(
	ICE_HANDLE hSDK, ICE_U32 u32Mode, const char *pcNTPServer, ICE_U32 u32TimeZone)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 32 * sizeof(ICE_U32) + 128;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_TMSYNC_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	char buf[256];
	*(ICE_U32*)buf = u32Mode;
	strcpy(buf + 4, pcNTPServer);
	*(ICE_U32*)(buf + 132) = u32TimeZone;
	socket_send(sockfd, buf, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_TMSYNC_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetOSDCfg(ICE_HANDLE hSDK, ICE_OSDAttr_S *pstOSDAttr)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_OSDAttr_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_OSD_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_OSD_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstOSDAttr, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetOSDCfg(ICE_HANDLE hSDK, const ICE_OSDAttr_S *pstOSDAttr)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_OSDAttr_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_OSD_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstOSDAttr, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_OSD_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetSchedCfg(ICE_HANDLE hSDK, 
											  ICE_SCHED_TASK_S *pstTasks, ICE_U32 *pu32Count)
{
	*pu32Count = 0;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_SCHED_TASK_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_SCHED_TASK_CFG_RSP != header.u32Type))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstTasks, header.u32Size - sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	*pu32Count = (header.u32Size - sizeof(ICE_OPER_DATA_S)) / sizeof(ICE_SCHED_TASK_S);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetSchedCfg(ICE_HANDLE hSDK, 
											  const ICE_SCHED_TASK_S *pstTasks, const ICE_U32 u32Count)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_SCHED_TASK_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + u32Count * sizeof(ICE_SCHED_TASK_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstTasks, header.u32Size - sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_SCHED_TASK_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetImagingSettings(
	ICE_HANDLE hSDK, ICE_U32 *pu32Luma, ICE_U32 *pu32Contr, 
	ICE_U32 *pu32Hue, ICE_U32 *pu32Satu)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8080, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[2048];
	ONVIF_SEND(sockfd, buf, handle->ip, ONVIF_GET_IMAGING_SETTINGS);

	int len = socket_recv_unknown(sockfd, buf, 2048, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	char *pos = strstr(buf, "<tt:Brightness>");
	if (NULL != pos)
		*pu32Luma = atoi(pos + 15);

	pos = strstr(buf, "<tt:Contrast>");
	if (NULL != pos)
		*pu32Contr = atoi(pos + 13);

	pos = strstr(buf, "<tt:Sharpness>");
	if (NULL != pos)
		*pu32Hue = atoi(pos + 14);

	pos = strstr(buf, "<tt:ColorSaturation>");
	if (NULL != pos)
		*pu32Satu = atoi(pos + 20);

	close(sockfd);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetImagingSettings(
	ICE_HANDLE hSDK, ICE_U32 u32Luma, ICE_U32 u32Contr, 
	ICE_U32 u32Hue, ICE_U32 u32Satu)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8080, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	char buf[1024], req[1024];
	sprintf(req, ONVIF_SET_IMAGING_SETTINGS, 
		u32Luma, u32Satu, u32Contr, u32Hue);
	ONVIF_SEND(sockfd, buf, handle->ip, req);

	int len = socket_recv_unknown(sockfd, buf, 1024, 1000);
	if (len <= 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}
	buf[len] = '\0';

	if (NULL == strstr(buf, "200 OK"))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return ICE_STATUS_OK;
}

static int gettimeofday(struct timeval *tp, void *tz)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME stm;

	GetLocalTime(&stm);

	tm.tm_year = stm.wYear - 1900;
	tm.tm_mon = stm.wMonth - 1;
	tm.tm_mday = stm.wDay;
	tm.tm_hour = stm.wHour;
	tm.tm_min = stm.wMinute;
	tm.tm_sec = stm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);

	tp->tv_sec = (long)clock;
	tp->tv_usec = stm.wMilliseconds * 1000;
	return 0;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_OpenGate(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	struct timeval begin, end;
	gettimeofday(&begin, NULL);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 3000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "打开道闸失败，原因：连接相机失败");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		handle->clog->Logf("%s %s", handle->ip, "打开道闸失败，原因：相机无返回或返回信息错误");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	gettimeofday(&end, NULL);

	handle->clog->Logf("%s 打开道闸成功, 耗时 %d 毫秒", handle->ip, 
		(end.tv_sec - begin.tv_sec) * 1000 + (end.tv_usec - begin.tv_usec) / 1000);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_OpenGate2(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "打开道闸2失败，原因：连接相机失败");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		handle->clog->Logf("%s %s", handle->ip, "打开道闸2失败，原因：相机无返回或返回信息错误");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	handle->clog->Logf("%s %s", handle->ip, "打开道闸2成功");
	return header.u32Status;
}
#endif

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_ControlAlarmOut(ICE_HANDLE hSDK, ICE_U32 u32Index)
{
	if ((NULL == hSDK) || (u32Index >= 2))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	if (1 == u32Index)
		header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	ICE_U32 u32Type = ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT_RSP;
	if (1 == u32Index)
		u32Type = ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2_RSP;

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (u32Type != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

#if 0
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, 
						 DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	sdk_handle_t *handle = (sdk_handle_t*)dwInstance;

	if (WIM_DATA != uMsg)
		return;

	handle->wavein_loss_count = 0;
	LPWAVEHDR lpHdr = (LPWAVEHDR)dwParam1;

	if (NULL == handle->hTalkMutexIn)
		return;
	WaitForSingleObject(handle->hTalkMutexIn, INFINITE);
	handle->talk_queue_in->push(lpHdr);
	ReleaseMutex(handle->hTalkMutexIn);
}

void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, 
						  DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	sdk_handle_t *handle = (sdk_handle_t*)dwInstance;

	if (WOM_DONE != uMsg)
		return;

	LPWAVEHDR pWaveHdr = (LPWAVEHDR)dwParam1;

	WaitForSingleObject(handle->hTalkMutexOut, INFINITE);
	handle->talk_queue_out->push(pWaveHdr);
	ReleaseMutex(handle->hTalkMutexOut);
}

DWORD WINAPI talk_proc_in(void *param)
{
	sdk_handle_t *handle = (sdk_handle_t*)param;
	handle->wavein_loss_count = 0;

	while (handle->m_bTalk)
	{
		WaitForSingleObject(handle->hTalkMutexIn, INFINITE);
		if (handle->talk_queue_in->empty())
		{
			ReleaseMutex(handle->hTalkMutexIn);

			handle->wavein_loss_count++;
			if (handle->wavein_loss_count > 200)
			{
				CloseHandle(handle->hTalkThreadIn);
				handle->hTalkThreadIn = NULL;

				ICE_IPCSDK_EndTalk(handle);
				break;
			}

			usleep(10000);
			continue;
		}

		LPWAVEHDR lpHdr = (LPWAVEHDR)handle->talk_queue_in->front();
		handle->talk_queue_in->pop();
		ReleaseMutex(handle->hTalkMutexIn);

		waveInUnprepareHeader(handle->m_hWaveIn, lpHdr, sizeof(WAVEHDR));

		short buf[1024];
		HI_VOICE_EncodeFrame(&handle->m_G711_STATE_ENC, (short*)lpHdr->lpData, 
			buf, (short)(lpHdr->dwBytesRecorded/2));
		int len = sizeof(short) * (2 + buf[1]);

		int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
		if (-1 != sockfd)
		{
			static int size = sizeof(ICE_OPER_DATA_S);

			ICE_OPER_DATA_S header;
			memset(&header, 0, size);

			header.u32Type = ICE_CONTROL_TYPE_TALK_DATA;
			header.u32Size = size + len;

			socket_send(sockfd, &header, size, 1000);
			socket_send(sockfd, buf, len, 1000);
			close(sockfd);
		}

		waveInPrepareHeader(handle->m_hWaveIn, lpHdr, sizeof(WAVEHDR));
		waveInAddBuffer(handle->m_hWaveIn, lpHdr, sizeof(WAVEHDR));
	}

	return 0;
}

DWORD WINAPI talk_proc_out(void *param)
{
	sdk_handle_t *handle = (sdk_handle_t*)param;

	while (handle->m_bTalk)
	{
		WaitForSingleObject(handle->hTalkMutexOut, INFINITE);
		if (handle->talk_queue_out->empty())
		{
			ReleaseMutex(handle->hTalkMutexOut);
			usleep(10000);
			continue;
		}

		LPWAVEHDR pWaveHdr = (LPWAVEHDR)handle->talk_queue_out->front();
		handle->talk_queue_out->pop();
		ReleaseMutex(handle->hTalkMutexOut);

		waveOutUnprepareHeader(handle->m_hWaveOut, pWaveHdr, sizeof(WAVEHDR));
		free(pWaveHdr);
	}

	WaitForSingleObject(handle->hTalkMutexOut, INFINITE);
	while (!handle->talk_queue_out->empty())
	{
		LPWAVEHDR pWaveHdr = (LPWAVEHDR)handle->talk_queue_out->front();
		handle->talk_queue_out->pop();

		waveOutUnprepareHeader(handle->m_hWaveOut, pWaveHdr, sizeof(WAVEHDR));
		free(pWaveHdr);
	}
	ReleaseMutex(handle->hTalkMutexOut);

	return 0;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_BeginTalk(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	StopTalk(hSDK);
	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	waveInOpen(&handle->m_hWaveIn, WAVE_MAPPER, &handle->m_WaveFormatEx, 
		(DWORD_PTR)waveInProc, (DWORD_PTR)hSDK, CALLBACK_FUNCTION);
	if (NULL == handle->m_hWaveIn)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：无法打开语音设备。");
		return ICE_STATUS_ERROR;
	}

	for (int i = 0; i < MAX_WAVE_HDR; i++)
	{
		if (NULL == handle->m_WaveHdr[i])
			continue;

		waveInPrepareHeader(handle->m_hWaveIn, handle->m_WaveHdr[i], sizeof(WAVEHDR));
		waveInAddBuffer(handle->m_hWaveIn, handle->m_WaveHdr[i], sizeof(WAVEHDR));
	}

	HI_VOICE_EncReset(&handle->m_G711_STATE_ENC, G711_A);
	waveInStart(handle->m_hWaveIn);
	handle->m_bTalk = TRUE;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 != sockfd)
	{
		static int size = sizeof(ICE_OPER_DATA_S);

		ICE_OPER_DATA_S header;
		memset(&header, 0, size);

		header.u32Type = ICE_CONTROL_TYPE_TALK_BEGIN;
		header.u32Size = size;

		socket_send(sockfd, &header, size, 1000);
		close(sockfd);
	}
	else
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：连接相机失败。");
	waveOutOpen(&handle->m_hWaveOut, WAVE_MAPPER, &handle->m_WaveFormatEx, 
		(DWORD_PTR)waveOutProc, (DWORD_PTR)hSDK, CALLBACK_FUNCTION);
	HI_VOICE_DecReset(&handle->m_G711_STATE_DEC, G711_A);

	handle->talk_queue_in = new stream_queue;
	if (NULL == handle->talk_queue_in)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：talk_in队列初始化失败。");
		ICE_IPCSDK_EndTalk(hSDK);
		return ICE_STATUS_ERROR;
	}

	handle->talk_queue_out = new stream_queue;
	if (NULL == handle->talk_queue_out)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：talk_out队列初始化失败。");
		ICE_IPCSDK_EndTalk(hSDK);
		return ICE_STATUS_ERROR;
	}

	handle->hTalkMutexIn = CreateMutex(NULL, FALSE, NULL);
	if (NULL == handle->hTalkMutexIn)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：talk_in mutex初始化失败。");
		ICE_IPCSDK_EndTalk(hSDK);
		return ICE_STATUS_ERROR;
	}

	handle->hTalkMutexOut = CreateMutex(NULL, FALSE, NULL);
	if (NULL == handle->hTalkMutexOut)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：talk_out mutex初始化失败。");
		ICE_IPCSDK_EndTalk(hSDK);
		return ICE_STATUS_ERROR;
	}

	handle->hTalkThreadIn = CreateThread(NULL, 0, talk_proc_in, handle, 0, NULL);
	if (NULL == handle->hTalkThreadIn)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：talk_in 线程初始化失败。");
		ICE_IPCSDK_EndTalk(hSDK);
		return ICE_STATUS_ERROR;
	}

	handle->hTalkThreadOut = CreateThread(NULL, 0, talk_proc_out, handle, 0, NULL);
	if (NULL == handle->hTalkThreadOut)
	{
		handle->clog->Logf("%s %s", handle->ip, "对讲开启失败，原因：talk_out 线程初始化失败。");
		ICE_IPCSDK_EndTalk(hSDK);
		return ICE_STATUS_ERROR;
	}

	handle->clog->Logf("%s %s", handle->ip, "开始对讲");
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API void ICE_IPCSDK_EndTalk(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return;

	StopTalk(hSDK);
	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (NULL != handle->hTalkThreadIn)
	{
		WaitForSingleObject(handle->hTalkThreadIn, INFINITE);

		CloseHandle(handle->hTalkThreadIn);
		handle->hTalkThreadIn = NULL;
	}

	if (NULL != handle->hTalkThreadOut)
	{
		WaitForSingleObject(handle->hTalkThreadOut, INFINITE);

		CloseHandle(handle->hTalkThreadOut);
		handle->hTalkThreadOut = NULL;
	}

	if (NULL != handle->talk_queue_in)
	{
		delete handle->talk_queue_in;
		handle->talk_queue_in = NULL;
	}

	if (NULL != handle->talk_queue_out)
	{
		delete handle->talk_queue_out;
		handle->talk_queue_out = NULL;
	}

	if (NULL != handle->hTalkMutexIn)
	{
		CloseHandle(handle->hTalkMutexIn);
		handle->hTalkMutexIn = NULL;
	}

	if (NULL != handle->hTalkMutexOut)
	{
		CloseHandle(handle->hTalkMutexOut);
		handle->hTalkMutexOut = NULL;
	}

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 != sockfd)
	{
		static int size = sizeof(ICE_OPER_DATA_S);

		ICE_OPER_DATA_S header;
		memset(&header, 0, size);

		header.u32Type = ICE_CONTROL_TYPE_TALK_END;
		header.u32Size = size;

		socket_send(sockfd, &header, size, 1000);
		close(sockfd);
	}
	handle->clog->Logf("%s %s", handle->ip, "结束对讲");
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_IsTalking(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return 0;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	return handle->m_bTalk;
}

ICE_IPCSDK_API void ICE_IPCSDK_Preview(ICE_HANDLE hSDK, ICE_U32 u32Preview)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (u32Preview)
		ICE_IPCSDK_StartStream(handle, handle->u8MainStream, (ICE_U32)handle->hWnd);
	else
		ICE_IPCSDK_StopStream(handle);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetPhyChnCfg(ICE_HANDLE hSDK, ICE_PHYCHN_CFG_S *pstPhyChnCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_PHYCHN_CFG_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_PHYCHN_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_PHYCHN_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstPhyChnCfg, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetPhyChnCfg(ICE_HANDLE hSDK, const ICE_PHYCHN_CFG_S *pstPhyChnCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_PHYCHN_CFG_S);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_PHYCHN_CFG;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstPhyChnCfg, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_PHYCHN_CFG_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetARegCfg(ICE_HANDLE hSDK, ICE_EXP_AREGULATE_PARAM *pstARegCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_EXP_AREGULATE_PARAM);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_EXP_AREGULATE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_EXP_AREGULATE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstARegCfg, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetARegCfg(ICE_HANDLE hSDK, const ICE_EXP_AREGULATE_PARAM *pstARegCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_EXP_AREGULATE_PARAM);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_EXP_AREGULATE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstARegCfg, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_EXP_AREGULATE_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
#endif

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetUARTCfg(ICE_HANDLE hSDK, ICE_UART_PARAM *pstUARTCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_UART_PARAM);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_UART_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_UART_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstUARTCfg, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetUARTCfg(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_UART_PARAM);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_UART_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstUARTCfg, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_UART_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

#if 0
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetSDCfg(ICE_HANDLE hSDK, SD_card_param *pstSDCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(SD_card_param);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_SDCARD_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_SDCARD_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstSDCfg, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetSDCfg(ICE_HANDLE hSDK, const SD_card_param *pstSDCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(SD_card_param);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_SDCARD_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstSDCfg, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_SDCARD_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SDFormat(ICE_HANDLE hSDK, int timeout)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_SDCARD_FORMAT;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), timeout * 1000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_SDCARD_FORMAT_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SDUnload(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_SDCARD_UNLOAD;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_SDCARD_UNLOAD_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetHttpPostCfg(ICE_HANDLE hSDK, ICE_HTTP_POST_PARAM *pstHttpPostCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_HTTP_POST_PARAM);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstHttpPostCfg, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetHttpPostCfg(ICE_HANDLE hSDK, const ICE_HTTP_POST_PARAM *pstHttpPostCfg)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ICE_HTTP_POST_PARAM);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstHttpPostCfg, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetWhiteListParam(ICE_HANDLE hSDK, 
													int mode, int match, int bmode, int bmatch, int tmode)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(WhiteList_Param);

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_WHITELIST_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	WhiteList_Param param = {0};
	param.mode = mode;
	param.match = match;
	param.black_mode = bmode;
	param.black_match = bmatch;
	param.temp_mode = tmode;
	socket_send(sockfd, &param, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	return ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_WHITELIST_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size)) ? ICE_STATUS_ERROR : header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetWhiteListParam(ICE_HANDLE hSDK, 
													int* mode, int* match, int *bmode, int *bmatch, int *tmode)
{
	*mode = 0;
	*match = 0;
	*bmode = 0;
	*bmatch = 0;
	*tmode = 0;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(WhiteList_Param);

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_WHITELIST_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_WHITELIST_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	WhiteList_Param param = {0};
	socket_recv(sockfd, &param, size, 1000);
	close(sockfd);

	*mode = param.mode;
	*match = param.match;
	*bmode = param.black_mode;
	*bmatch = param.black_match;
	*tmode = param.temp_mode;
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_Trigger(ICE_HANDLE hSDK, ICE_CHAR *pcNumber, ICE_CHAR *pcColor, 
										  ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen)
{
	int max_try = 300;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 3000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "软触发失败，原因：连接相机失败");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM_RSP != header.u32Type))
	{
		handle->clog->Logf("%s %s", handle->ip, "软触发失败，原因：相机返回信息错误");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	/**nPicLen = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (*nPicLen > nPicSize)
	*nPicLen = nPicSize;

	SafeArrayAccessData(vPicData->parray, (void**)&buf);
	socket_recv(sockfd, buf, *nPicLen, 1000);
	SafeArrayUnaccessData(vPicData->parray);*/
	close(sockfd);
	handle->bTrigger = TRUE;

	while (max_try-- > 0)
	{
		if (!handle->bTrigger)
		{
			if (handle->info.s32HavePlate)
			{
				strcpy(pcNumber, handle->info.stPlateInfo.as8PlateNum);
				strcpy(pcColor, handle->info.cPlateColor);
			}
			else
			{
				strcpy(pcNumber, "无牌车");
				strcpy(pcColor, "");
			}

			*pu32PicLen = handle->info.s32PicDataLen;
			if (*pu32PicLen > u32PicSize)
				*pu32PicLen = u32PicSize;

			memcpy(pcPicData, handle->info.as8PictureData, *pu32PicLen);
			break;
		}

		/*LONG nLane, nLeft, nTop, nRight, nBottom, nTime, nSpeed, nLen;

		ICE_IPCSDK_GetPlate(hSDK, bstrNumber, bstrColor, 
		&nLane, &nLeft, &nTop, &nRight, &nBottom, &nTime, &nSpeed, 
		vPicData, 0, &nLen, bSuccess);
		if (*bSuccess)
		break;*/

		usleep(30000);
	}
	handle->clog->Logf("%s %s", handle->ip, "软触发成功");
	return ICE_STATUS_OK;
}
#endif

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	//if (!rtspc_get_status(handle->rtspc))
	return evtp_get_status(handle->evtp_handle);

	return ICE_STATUS_OK;
}

/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_Capture(ICE_HANDLE hSDK, 
ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen)
{
if (NULL == hSDK)
return ICE_STATUS_ERROR;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

int sockfd = socket_connect(handle->ip, 8117, 1000);
if (-1 == sockfd)
return ICE_STATUS_ERROR;

ICE_OPER_DATA_S header;
memset(&header, 0, sizeof(ICE_OPER_DATA_S));
header.u32Type = ICE_CONTROL_TYPE_CAPTURE;
header.u32Size = sizeof(ICE_OPER_DATA_S);

socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
if ((ret < 0) || (ICE_CONTROL_TYPE_CAPTURE_RSP != header.u32Type))
{
close(sockfd);
return ICE_STATUS_ERROR;
}

*pu32PicLen = header.u32Size - sizeof(ICE_OPER_DATA_S);
if (*pu32PicLen > u32PicSize)
*pu32PicLen = u32PicSize;

socket_recv(sockfd, pcPicData, *pu32PicLen, 1000);

close(sockfd);
return ICE_STATUS_OK;
}*/

ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack(ICE_HANDLE hSDK, 
													 ICE_IPCSDK_OnSerialPort pfOnSerialPort, void *pvSerialPortParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnSerialPort = pfOnSerialPort;
	handle->pvSerialPortParam = pvSerialPortParam;
}

/*ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack_Cdecl(ICE_HANDLE hSDK, 
ICE_IPCSDK_OnSerialPort_Cdecl pfOnSerialPort, void *pvSerialPortParam)
{
if (NULL == hSDK)
return;

sdk_handle_t *handle = (sdk_handle_t*)hSDK;

handle->pfOnSerialPort_Cdecl = pfOnSerialPort;
handle->pvSerialPortParam = pvSerialPortParam;
}*/

ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack_RS232(ICE_HANDLE hSDK, 
														   ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort, void *pvSerialPortParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnSerialPort_RS232 = pfOnSerialPort;
	handle->pvSerialPortParam_RS232 = pvSerialPortParam;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TransSerialPort(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "rs485透明串口发送失败，原因：连接相机失败。");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_TRANS_SERIAL_PORT;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + u32Len;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, (void*)pcData, u32Len, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RSP != header.u32Type))
	{
		handle->clog->Logf("%s %s", handle->ip, "rs485透明串口发送失败，原因：相机无返回或返回数据错误。");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	handle->clog->Logf("%s %s", handle->ip, "rs485透明串口发送成功");
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TransSerialPort_RS232(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "232透明串口发送失败，原因：连接相机失败。");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RS232;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + u32Len;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, (void*)pcData, u32Len, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RS232_RSP != header.u32Type))
	{
		handle->clog->Logf("%s %s", handle->ip, "232透明串口发送失败，原因：相机无返回或返回数据错误。");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	handle->clog->Logf("%s %s", handle->ip, "232透明串口发送成功");
	return ICE_STATUS_OK;
}

#if 0
#define MAX_RESND 30

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListGetCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count)
{
	*pu32Count = 0;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (NULL == handle->whitelist)
	{
		handle->whitelist = (whitelist_info_t*)malloc(
			MAX_WHITE_LIST * sizeof(whitelist_info_t));
		if (NULL == handle->whitelist)
		{
			handle->clog->Logf("%s %s", handle->ip, "获取黑白名单总数失败，原因：名单列表whitelist申请内存失败。");
			return ICE_STATUS_ERROR;
		}
	}

	/*int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	return ICE_STATUS_ERROR;

	int opt = 1000;
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt, sizeof(int));
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, sizeof(int));

	char buf[516], *cur;
	buf[0] = 0;
	buf[1] = 1;
	cur = buf + 2;

	strcpy(cur, "whitelist.txt");
	int len = strlen(cur);
	cur += len + 1;

	strcpy(cur, "octet");
	len = strlen(cur);
	cur += len + 1;

	strcpy(cur, "tsize");
	len = strlen(cur);
	cur += len + 1;
	strcpy(cur, "0");

	struct sockaddr_in addr;
	socklen_t size = sizeof(struct sockaddr_in);

	addr.sin_family = AF_INET;
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	addr.sin_addr.s_addr = inet_addr(handle->ip);
	addr.sin_port = htons(69);

	sendto(sockfd, buf, (cur - buf) + (strlen(cur) + 1), 0, (struct sockaddr*)&addr, size);

	int total = 0;
	char *list = (char*)malloc(1024 * 1024);
	if (NULL == list)
	{
	close(sockfd);
	return ICE_STATUS_ERROR;
	}

	short last = -1;
	do
	{
	int i = 0;
	for (; i < MAX_RESND; i++)
	{
	len = recvfrom(sockfd, buf, 516, 0, (struct sockaddr*)&addr, &size);
	if ((len > 0) && (0 == buf[0]) && (3 == buf[1]))
	break;
	}

	if (MAX_RESND == i)
	break;

	short current = ntohs(*(short*)(buf + 2));
	if (last != current)
	{
	memcpy(list + total, buf + 4, len - 4);
	total += len - 4;
	last = current;
	}

	buf[1] = 4;
	sendto(sockfd, buf, 4, 0, (struct sockaddr*)&addr, size);

	} while (516 == len);*/

	int sockfd = socket_connect(handle->ip, 8117, 10000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "获取黑白名单总数失败，原因：连接相机失败。");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_READ_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_READ_WHITE_LIST_RSP != header.u32Type))
	{
		handle->clog->Logf("%s %s", handle->ip, "获取黑白名单总数失败，原因：相机无返回或者返回数据错误。");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	char *list = (char*)malloc(1024 * 1024);
	if (NULL == list)
	{
		handle->clog->Logf("%s %s", handle->ip, "获取黑白名单总数失败，原因：名单列表list申请内存失败。");
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	int total = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (0 == total)
	{
		free(list);
		close(sockfd);
		handle->clog->Logf("%s %s", handle->ip, "获取黑白名单总数为0。");
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, list, total, 10000);
	close(sockfd);

	list[total++] = '\n';
	list[total] = '\0';
	char *cur = list;

	while (cur - list < total)
	{
		char *pos = strchr(cur, '\n');
		if (NULL == pos)
			break;

		if ('\r' == *(pos - 1))
			pos--;
		*pos = '\0';

		whitelist_info_t *info = handle->whitelist + *pu32Count;
		info->plate[0] = '\0';
		info->date_begin[0] = '\0';
		info->date_end[0] = '\0';
		info->time_begin[0] = '\0';
		info->time_end[0] = '\0';
		info->type[0] = '\0';

		char *pch = strtok(cur, ",\t ");
		int index = 0;

		while (pch != NULL)
		{
			switch (index)
			{
			case 0:
				strcpy(info->plate, pch);
				break;

			case 1:
				strcpy(info->date_begin, pch);
				break;

			case 2:
				strcpy(info->date_end, pch);
				break;

			case 3:
				strcpy(info->time_begin, pch);
				break;

			case 4:
				strcpy(info->time_end, pch);
				break;

			case 5:
				strcpy(info->type, pch);
				break;
			}

			index++;
			pch = strtok(NULL, ",\t ");
		}

		while (('\n' == *(pos + 1)) || ('\r' == *(pos + 1)))
			pos++;

		cur = pos + 1;
		(*pu32Count)++;

		if (*pu32Count >= MAX_WHITE_LIST)
			break;
	}

	free(list);
	//close(sockfd);

	handle->whitelist_count = *pu32Count;

	handle->clog->Logf("%s %d","获取黑白名单总数成功，总数为： ",*pu32Count);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListGetItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
												   ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
												   ICE_CHAR* pcRsrv1, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if ((NULL == handle->whitelist) || (s32Index < 0) || 
		(s32Index >= handle->whitelist_count))
	{
		handle->clog->Logf("%s %s", handle->ip, "获取黑白名单失败，原因：名单列表为空/序列号小于0或者大于名单总数。");
		return ICE_STATUS_ERROR;
	}

	strcpy(pcNumber, handle->whitelist[s32Index].plate);
	strcpy(pcDateBegin, handle->whitelist[s32Index].date_begin);
	strcpy(pcDateEnd, handle->whitelist[s32Index].date_end);
	strcpy(pcTimeBegin, handle->whitelist[s32Index].time_begin);
	strcpy(pcTimeEnd, handle->whitelist[s32Index].time_end);
	strcpy(pcRsrv1, handle->whitelist[s32Index].type);

	handle->clog->Logf("%s %s", handle->ip, "获取黑白名单成功。");
	return ICE_STATUS_OK;
}

#define MAX_TRY 1800
#define MAX_RESND 30

static BOOL upload_whitelist(const char* ip, const char* data, int len)
{
	/*int i, j, ret, sockfd = -1;
	BOOL bSuccess = FALSE;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	goto exit;

	int opt = 100;
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt, sizeof(int));
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, sizeof(int));

	char buf[516], *cur;
	buf[0] = 0;
	buf[1] = 2;
	cur = buf + 2;

	strcpy(cur, "whitelist.txt");
	int slen = strlen(cur);
	cur += slen + 1;

	strcpy(cur, "octet");
	slen = strlen(cur);
	cur += slen + 1;

	strcpy(cur, "tsize");
	slen = strlen(cur);
	cur += slen + 1;

	sprintf(cur, "%d", len);

	struct sockaddr_in addr;
	socklen_t size = sizeof(struct sockaddr_in);

	addr.sin_family = AF_INET;
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(69);

	for (i = 0; i < MAX_RESND; i++)
	{
	sendto(sockfd, buf, (cur - buf) + (strlen(cur) + 1), 0, (struct sockaddr*)&addr, size);

	char rsp[512];
	ret = recvfrom(sockfd, rsp, 512, 0, (struct sockaddr*)&addr, &size);
	if ((ret > 0) && (0 == rsp[0]) && (6 == rsp[1]))
	break;
	}

	if (MAX_RESND == i)
	goto exit;

	buf[1] = 3;
	int count = len / 512;
	int mod = len % 512;

	for (i = 0; i < count; i++)
	{
	*(short*)(buf + 2) = i;
	memcpy(buf + 4, data + i * 512, 512);

	for (j = 0; j < MAX_RESND; j++)
	{
	sendto(sockfd, buf, 516, 0, (struct sockaddr*)&addr, size);

	char rsp[512];
	ret = recvfrom(sockfd, rsp, 512, 0, (struct sockaddr*)&addr, &size);
	if ((ret > 0) && (0 == rsp[0]) && (4 == rsp[1]) && (i == *(short*)(rsp + 2)))
	break;
	}

	if (MAX_RESND == j)
	goto exit;
	}

	*(short*)(buf + 2) = count;

	if (NULL != data)
	memcpy(buf + 4, data + count * 512, mod);

	for (j = 0; j < 3; j++)
	{
	sendto(sockfd, buf, 4 + mod, 0, (struct sockaddr*)&addr, size);

	for (i = 0; i < MAX_TRY; i++)
	{
	ret = recvfrom(sockfd, buf + 4, 512, 0, (struct sockaddr*)&addr, &size);
	if (ret <= 0)
	continue;

	if (0 == buf[4])
	{
	if ((4 == buf[5]) && (count == *(short*)(buf + 6)))
	bSuccess = TRUE;
	}
	break;
	}

	if (i < MAX_TRY)
	break;
	}

	exit:

	if (-1 != sockfd)
	{
	close(sockfd);
	sockfd = -1;
	}*/

	int sockfd = socket_connect(ip, 8117, 10000);
	if (-1 == sockfd)
		return FALSE;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_WRITE_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + len;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	socket_send(sockfd, data, len, 10000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_WRITE_WHITE_LIST_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return FALSE;
	}

	close(sockfd);
	return TRUE;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListEditItem(ICE_HANDLE hSDK, ICE_S32 s32Index, const ICE_CHAR* pcNumber, 
													const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
													const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if ((NULL == handle->whitelist) || (s32Index < 0) || 
		(s32Index >= handle->whitelist_count))
		return ICE_STATUS_ERROR;

	whitelist_info_t info;
	memcpy(&info, &handle->whitelist[s32Index], sizeof(whitelist_info_t));

	strcpy(handle->whitelist[s32Index].plate, pcNumber);
	strcpy(handle->whitelist[s32Index].date_begin, pcDateBegin);
	strcpy(handle->whitelist[s32Index].date_end, pcDateEnd);
	strcpy(handle->whitelist[s32Index].time_begin, pcTimeBegin);
	strcpy(handle->whitelist[s32Index].time_end, pcTimeEnd);

	char *buf = (char*)malloc(1024 * 1024);
	if (NULL == buf)
		return ICE_STATUS_ERROR;

	char *cur = buf;
	for (int i = 0; i < handle->whitelist_count; i++)
	{
		int len = sprintf(cur, "%s\t%s\t%s\t%s\t%s\r\n", handle->whitelist[i].plate, 
			handle->whitelist[i].date_begin, handle->whitelist[i].date_end, 
			handle->whitelist[i].time_begin, handle->whitelist[i].time_end);
		cur += len;
	}

	BOOL bSuccess = upload_whitelist(handle->ip, buf, (int)strlen(buf));
	free(buf);

	if (!bSuccess)
	{
		memcpy(&handle->whitelist[s32Index], &info, sizeof(whitelist_info_t));
		return ICE_STATUS_ERROR;
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListInsertItem(ICE_HANDLE hSDK, ICE_S32 s32Index, const ICE_CHAR* pcNumber, 
													  const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
													  const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	ICE_S32 nFindIndex = -1;
	ICE_IPCSDK_WhiteListFindItem(hSDK, pcNumber, 0, &nFindIndex);
	if (-1 != nFindIndex)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if ((NULL == handle->whitelist) || (s32Index < 0) || 
		((handle->whitelist_count <= 0) && (0 != s32Index)) || 
		((handle->whitelist_count > 0) && (s32Index > handle->whitelist_count)) || 
		(handle->whitelist_count >= MAX_WHITE_LIST))
		return ICE_STATUS_ERROR;

	if (s32Index < handle->whitelist_count)
	{
		memmove(handle->whitelist + s32Index + 1, handle->whitelist + s32Index, 
			(handle->whitelist_count - s32Index) * sizeof(whitelist_info_t));
	}

	strcpy(handle->whitelist[s32Index].plate, pcNumber);
	strcpy(handle->whitelist[s32Index].date_begin, pcDateBegin);
	strcpy(handle->whitelist[s32Index].date_end, pcDateEnd);
	strcpy(handle->whitelist[s32Index].time_begin, pcTimeBegin);
	strcpy(handle->whitelist[s32Index].time_end, pcTimeEnd);

	char *buf = (char*)malloc(1024 * 1024);
	if (NULL == buf)
		return ICE_STATUS_ERROR;

	char *cur = buf;
	for (int i = 0; i < handle->whitelist_count + 1; i++)
	{
		int len = sprintf(cur, "%s\t%s\t%s\t%s\t%s\r\n", handle->whitelist[i].plate, 
			handle->whitelist[i].date_begin, handle->whitelist[i].date_end, 
			handle->whitelist[i].time_begin, handle->whitelist[i].time_end);
		cur += len;
	}

	BOOL bSuccess = upload_whitelist(handle->ip, buf, (int)strlen(buf));
	free(buf);

	if (!bSuccess)
	{
		if (s32Index < handle->whitelist_count)
		{
			memmove(handle->whitelist + s32Index, handle->whitelist + s32Index + 1, 
				(handle->whitelist_count - s32Index) * sizeof(whitelist_info_t));
		}
		return ICE_STATUS_ERROR;
	}

	handle->whitelist_count++;
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListDeleteItem(ICE_HANDLE hSDK, ICE_S32 s32Index)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if ((NULL == handle->whitelist) || (s32Index < 0) || 
		(s32Index >= handle->whitelist_count))
		return ICE_STATUS_ERROR;

	whitelist_info_t info;
	memcpy(&info, &handle->whitelist[s32Index], sizeof(whitelist_info_t));
	memmove(&handle->whitelist[s32Index], &handle->whitelist[s32Index + 1], 
		(handle->whitelist_count - s32Index - 1) * sizeof(whitelist_info_t));

	char *buf = (char*)malloc(1024 * 1024);
	if (NULL == buf)
		return ICE_STATUS_ERROR;

	char *cur = buf;
	for (int i = 0; i < handle->whitelist_count - 1; i++)
	{
		int len = sprintf(cur, "%s\t%s\t%s\t%s\t%s\r\n", handle->whitelist[i].plate, 
			handle->whitelist[i].date_begin, handle->whitelist[i].date_end, 
			handle->whitelist[i].time_begin, handle->whitelist[i].time_end);
		cur += len;
	}

	BOOL bSuccess = upload_whitelist(handle->ip, buf, (int)strlen(buf));
	free(buf);

	if (!bSuccess)
	{
		memmove(&handle->whitelist[s32Index + 1], &handle->whitelist[s32Index], 
			(handle->whitelist_count - s32Index - 1) * sizeof(whitelist_info_t));
		memcpy(&handle->whitelist[s32Index], &info, sizeof(whitelist_info_t));
		return ICE_STATUS_ERROR;
	}

	handle->whitelist_count--;
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListDelAllItems(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (NULL == handle->whitelist)
		return ICE_STATUS_ERROR;

	BOOL bSuccess = upload_whitelist(handle->ip, NULL, 0);

	if (!bSuccess)
		return ICE_STATUS_ERROR;

	handle->whitelist_count = 0;
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListFindItem(ICE_HANDLE hSDK, 
													const ICE_CHAR* pcNumber, ICE_S32 s32Start, ICE_S32 *s32Index)
{
	*s32Index = -1;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if ((NULL == handle->whitelist) || (0 == handle->whitelist_count) || 
		(s32Start < 0) || (s32Start >= handle->whitelist_count))
		return ICE_STATUS_ERROR;

	int i = s32Start;
	for (; i < handle->whitelist_count; i++)
	{
		if (0 == strcmp(handle->whitelist[i].plate, pcNumber))
			break;
	}

	if (handle->whitelist_count == i)
		return ICE_STATUS_ERROR;

	*s32Index = i;
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListEditItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
															 const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
															 const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(WHITELIST_ITEM);
	WHITELIST_ITEM item = {0};

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s","编辑黑白名单失败，原因：连接相机失败。 车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_EDIT_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	strcpy(item.plate_number, pcNumber);
	strcpy(item.valid_sdate, pcDateBegin);
	strcpy(item.valid_edate, pcDateEnd);
	strcpy(item.valid_stime, pcTimeBegin);
	strcpy(item.valid_etime, pcTimeEnd);
	strcpy(item.type, pcType);
	socket_send(sockfd, &item, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_EDIT_WHITE_LIST_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size) || (ICE_STATUS_OK != header.u32Status))
	{
		handle->clog->Logf("%s %s","编辑黑白名单失败，原因：相机无返回或者返回数据失败。车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	handle->clog->Logf("%s %s","编辑黑白名单成功。车牌号： ",pcNumber);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListInsertItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
															   const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
															   const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(WHITELIST_ITEM);
	WHITELIST_ITEM item = {0};

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s","增加黑白名单失败，原因：连接相机失败。 车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_ADD_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	strcpy(item.plate_number, pcNumber);
	strcpy(item.valid_sdate, pcDateBegin);
	strcpy(item.valid_edate, pcDateEnd);
	strcpy(item.valid_stime, pcTimeBegin);
	strcpy(item.valid_etime, pcTimeEnd);
	strcpy(item.type, pcType);
	socket_send(sockfd, &item, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_ADD_WHITE_LIST_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size) || (ICE_STATUS_OK != header.u32Status))
	{
		handle->clog->Logf("%s %s","增加黑白名单失败，原因：相机无返回或者返回数据失败。车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	handle->clog->Logf("%s %s","增加黑白名单成功。车牌号： ",pcNumber);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListDeleteItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(WHITELIST_ITEM);
	WHITELIST_ITEM item = {0};

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s","删除黑白名单失败，原因：连接相机失败。 车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_DEL_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	strcpy(item.plate_number, pcNumber);
	socket_send(sockfd, &item, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_DEL_WHITE_LIST_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size) || (ICE_STATUS_OK != header.u32Status))
	{
		handle->clog->Logf("%s %s","删除黑白名单失败，原因：相机无返回或者返回数据失败。车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	handle->clog->Logf("%s %s","删除黑白名单成功。 车牌号： ",pcNumber);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListDelAllItems_ByNumber(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "删除所有黑白名单失败，原因：连接相机失败。 byNumber ");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_DELALL_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S);
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_DELALL_WHITE_LIST_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size) || (ICE_STATUS_OK != header.u32Status))
	{
		handle->clog->Logf("%s %s", handle->ip, "删除所有黑白名单失败，原因：相机无返回或者返回数据失败。byNumber");
		return ICE_STATUS_ERROR;
	}

	handle->clog->Logf("%s %s", handle->ip, "删除所有黑白名单成功。 byNumber ");
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WhiteListFindItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
															 ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, ICE_CHAR* pcType, 
															 ICE_CHAR* pcRsrv1, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(WHITELIST_ITEM);
	WHITELIST_ITEM item = {0};

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s","查找黑白名单失败，原因：连接相机失败。 车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_FIND_WHITE_LIST;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	strcpy(item.plate_number, pcNumber);
	socket_send(sockfd, &item, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_FIND_WHITE_LIST_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size) || (ICE_STATUS_OK != header.u32Status))
	{
		close(sockfd);
		handle->clog->Logf("%s %s","查找黑白名单失败，原因：相机无返回或者返回数据失败。车牌号： ",pcNumber);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, &item, size, 1000);
	close(sockfd);

	strcpy(pcDateBegin, item.valid_sdate);
	strcpy(pcDateEnd, item.valid_edate);
	strcpy(pcTimeBegin, item.valid_stime);
	strcpy(pcTimeEnd, item.valid_etime);
	strcpy(pcType, item.type);

	handle->clog->Logf("%s %s","查找黑白名单成功。车牌号： ",pcNumber);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API void ICE_IPCSDK_SetPastPlateCallBack(ICE_HANDLE hSDK, 
													ICE_IPCSDK_OnPastPlate pfOnPastPlate, void *pvPastPlateParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnPastPlate = pfOnPastPlate;
	handle->pvPastPlateParam = pvPastPlateParam;
}

ICE_IPCSDK_API void ICE_IPCSDK_SetPastPlateCallBack_Cdecl(ICE_HANDLE hSDK, 
														  ICE_IPCSDK_OnPastPlate_Cdecl pfOnPastPlate, void *pvPastPlateParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnPastPlate_Cdecl = pfOnPastPlate;
	handle->pvPastPlateParam = pvPastPlateParam;
}

BOOL avi_create(const char *name, int width, int height, 
				PAVIFILE *file, PAVISTREAM *stream)
{
	AVIFileOpen(file, name, OF_WRITE | OF_CREATE, NULL);
	if (NULL == *file)
		return FALSE;

	AVISTREAMINFO strhdr;
	memset(&strhdr, 0, sizeof(strhdr));
	strhdr.fccType = streamtypeVIDEO;
	strhdr.fccHandler = mmioFOURCC('H', '2', '6', '4');
	strhdr.dwScale = 1;
	strhdr.dwRate = 25;

	AVIFileCreateStream(*file, stream, &strhdr);
	if (NULL == *stream)
	{
		AVIFileRelease(*file);
		return FALSE;
	}

	BITMAPINFOHEADER header;
	memset(&header, 0, sizeof(BITMAPINFOHEADER));
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biPlanes = 1;
	header.biBitCount = 24;
	header.biCompression = mmioFOURCC('H', '2', '6', '4');
	header.biWidth = width;
	header.biHeight = height;

	AVIStreamSetFormat(*stream, 0, &header, sizeof(header));
	return TRUE;
}

void avi_destroy(PAVIFILE file, PAVISTREAM stream)
{
	if (NULL != stream)
	{
		AVIStreamClose(stream);
		stream = NULL;
	}

	if (NULL != file)
	{
		AVIFileRelease(file);
		file = NULL;
	}
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_StartRecord(ICE_HANDLE hSDK, const ICE_CHAR *pcFileName)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (NULL != handle->pavstream)
	{
		handle->clog->Logf("%s %s", handle->ip, "打开录像失败，原因：无视频流。");
		return ICE_STATUS_ERROR;
	}

	WaitForSingleObject(handle->hMutex, INFINITE);
	handle->count = 0;
	handle->ts = 0;
	avi_create(pcFileName, handle->frame_width, handle->frame_height, 
		&handle->pavfile, &handle->pavstream);
	ReleaseMutex(handle->hMutex);
	handle->clog->Logf("%s %s", handle->ip, "打开录像");
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API void ICE_IPCSDK_StopRecord(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	if (NULL == handle->pavstream)
	{
		handle->clog->Logf("%s %s", handle->ip, "关闭录像失败，原因：无视频流。");
		return;
	}

	WaitForSingleObject(handle->hMutex, INFINITE);
	avi_destroy(handle->pavfile, handle->pavstream);
	handle->pavfile = NULL;
	handle->pavstream = NULL;
	ReleaseMutex(handle->hMutex);
	handle->clog->Logf("%s %s", handle->ip, "关闭录像");
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetHDTriggerParam(ICE_HANDLE hSDK, HDTrigger_Param *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(HDTrigger_Param);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_HDTRIGGER_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_HDTRIGGER_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetHDTriggerParam(ICE_HANDLE hSDK, const HDTrigger_Param *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(HDTrigger_Param);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_HDTRIGGER_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_HDTRIGGER_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WriteUserData(ICE_HANDLE hSDK, const char* pcData)
{
	if ((NULL == hSDK) || (NULL == pcData))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	int len = (int)strlen(pcData);

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + len;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pcData, len, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_WriteUserData_Binary(
	ICE_HANDLE hSDK, const char* pcData, ICE_U32 nOffset, ICE_U32 nLen)
{
	if ((NULL == hSDK) || (NULL == pcData))
		return ICE_STATUS_ERROR;

	ICE_U32 len = nOffset + nLen;
	if (len > 4096)
		return ICE_STATUS_ERROR;

	char szData[4096];
	ICE_U32 u32Size = ICE_IPCSDK_ReadUserData_Binary(hSDK, szData, 4096, 0, 4096);
	if (0 == u32Size)
		return ICE_STATUS_ERROR;

	memcpy(szData + nOffset, pcData, nLen);
	if (len < u32Size)
		len = u32Size;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + len;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, szData, len, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_ReadUserData(ICE_HANDLE hSDK, char* pcData, int nSize)
{
	if ((NULL == hSDK) || (NULL == pcData))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA_RSP != header.u32Type))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	int len = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (len > nSize - 1)
		len = nSize - 1;

	socket_recv(sockfd, pcData, len, 1000);
	pcData[len] = '\0';

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_ReadUserData_Binary(
	ICE_HANDLE hSDK, char* pcData, ICE_U32 nSize, ICE_U32 nOffset, ICE_U32 nLen)
{
	if ((NULL == hSDK) || (NULL == pcData))
		return ICE_STATUS_ERROR;

	ICE_U32 len = nOffset + nLen;
	if (len > 4096)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA_RSP != header.u32Type))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	len = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (len > 4096)
		len = 4096;

	char szData[4096];
	socket_recv(sockfd, szData, len, 1000);

	if (nLen > len - nOffset)
		nLen = len - nOffset;

	if (nLen > nSize)
		nLen = nSize;

	memcpy(pcData, szData + nOffset, nLen);
	close(sockfd);
	return nLen;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetWhiteCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count)
{
	*pu32Count = 0;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	ICE_U32 nTotal = 0;
	ICE_IPCSDK_WhiteListGetCount(hSDK, &nTotal);
	if (0 == nTotal)
		return ICE_STATUS_OK;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	handle->white_count = 0;

	for (int i = 0; i < (int)nTotal; i++)
	{
		if (('\0' == handle->whitelist[i].type[0]) || 
			(0 == _stricmp(handle->whitelist[i].type, "W")))
		{
			handle->white_index[handle->white_count] = i;
			handle->white_count++;
		}
	}

	*pu32Count = handle->white_count;
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetWhiteItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
											   ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
											   ICE_CHAR* pcRsrv1, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	if ((s32Index < 0) || (s32Index >= handle->white_count))
		return ICE_STATUS_ERROR;

	return ICE_IPCSDK_WhiteListGetItem(hSDK, handle->white_index[s32Index], pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_EditWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
												const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
												const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	return ICE_IPCSDK_WhiteListEditItem_ByNumber(hSDK, pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, "W", 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_InsertWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
												  const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
												  const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	return ICE_IPCSDK_WhiteListInsertItem_ByNumber(hSDK, pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, "W", 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetBlackCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count)
{
	*pu32Count = 0;

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	ICE_U32 nTotal = 0;
	ICE_IPCSDK_WhiteListGetCount(hSDK, &nTotal);
	if (0 == nTotal)
		return ICE_STATUS_OK;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	handle->black_count = 0;

	for (int i = 0; i < (int)nTotal; i++)
	{
		if (0 == _stricmp(handle->whitelist[i].type, "B"))
		{
			handle->black_index[handle->black_count] = i;
			handle->black_count++;
		}
	}

	*pu32Count = handle->black_count;
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetBlackItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
											   ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
											   ICE_CHAR* pcRsrv1, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	if ((s32Index < 0) || (s32Index >= handle->black_count))
		return ICE_STATUS_ERROR;

	return ICE_IPCSDK_WhiteListGetItem(hSDK, handle->black_index[s32Index], pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_EditBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
												const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
												const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	return ICE_IPCSDK_WhiteListEditItem_ByNumber(hSDK, pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, "B", 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_InsertBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
												  const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
												  const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4)
{
	return ICE_IPCSDK_WhiteListInsertItem_ByNumber(hSDK, pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, "B", 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_DelAllWhiteItems(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_U32 nCount = 0;
	ICE_IPCSDK_GetWhiteCount(hSDK, &nCount);
	if (0 == nCount)
		return ICE_STATUS_OK;

	for (int i = 0; i < (int)nCount; i++)
	{
		ICE_IPCSDK_WhiteListDeleteItem_ByNumber(hSDK, 
			handle->whitelist[handle->white_index[i]].plate);
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_DelAllBlackItems(ICE_HANDLE hSDK)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_U32 nCount = 0;
	ICE_IPCSDK_GetBlackCount(hSDK, &nCount);
	if (0 == nCount)
		return ICE_STATUS_OK;

	for (int i = 0; i < (int)nCount; i++)
	{
		ICE_IPCSDK_WhiteListDeleteItem_ByNumber(hSDK, 
			handle->whitelist[handle->black_index[i]].plate);
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_DeleteWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber)
{
	return ICE_IPCSDK_WhiteListDeleteItem_ByNumber(hSDK, pcNumber);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_FindWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
												ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
												ICE_CHAR* pcRsrv1, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4)
{
	char szType[16];

	return ICE_IPCSDK_WhiteListFindItem_ByNumber(hSDK, pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, szType, 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_DeleteBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber)
{
	return ICE_IPCSDK_WhiteListDeleteItem_ByNumber(hSDK, pcNumber);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_FindBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
												ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
												ICE_CHAR* pcRsrv1, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4)
{
	char szType[16];

	return ICE_IPCSDK_WhiteListFindItem_ByNumber(hSDK, pcNumber, 
		pcDateBegin, pcDateEnd, pcTimeBegin, pcTimeEnd, szType, 
		pcRsrv1, pcRsrv2, pcRsrv3, pcRsrv4);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAutoRebootParam(ICE_HANDLE hSDK, AutoRebootParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(AutoRebootParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_AUTO_REBOOT_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_AUTO_REBOOT_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetAutoRebootParam(ICE_HANDLE hSDK, const AutoRebootParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(AutoRebootParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_AUTO_REBOOT_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_AUTO_REBOOT_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_U32 SDK_Broadcast_ByName(ICE_HANDLE hSDK, const char* pcName, int index)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(Broadcast_Param);

	if (NULL == pcName)
		return ICE_STATUS_ERROR;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
	{
		handle->clog->Logf("%s %s", handle->ip, "语音播报失败，原因：连接相机失败");
		return ICE_STATUS_ERROR;
	}

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_BROADCSAT;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	Broadcast_Param param = {0};
	strcpy(param.filename, pcName);
	param.index = index;
	socket_send(sockfd, &param, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	close(sockfd);

	if ((ret < 0) || (ICE_CONTROL_TYPE_BROADCSAT_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		handle->clog->Logf("%s %s", handle->ip, "语音播报失败，原因：相机无返回或者返回信息错误");
		return ICE_STATUS_ERROR;
	}

	return ICE_STATUS_OK;
}

ICE_U32 SDK_Broadcast(ICE_HANDLE hSDK, ICE_U16 nIndex, int index)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	//sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(Broadcast_Param);

	static const char* filelist[] = {
		"0.g711a", 
		"1.g711a", 
		"2.g711a", 
		"3.g711a", 
		"4.g711a", 
		"5.g711a", 
		"6.g711a", 
		"7.g711a", 
		"8.g711a", 
		"9.g711a", 
		"10.g711a", 
		"100.g711a", 
		"1000.g711a", 
		"year.g711a", 
		"month.g711a", 
		"date.g711a", 
		"hour.g711a", 
		"minute.g711a", 
		"second.g711a", 
		"yuan.g711a", 
		"welcome.g711a", 
		"welinr.g711a", 
		"thsout.g711a", 
		"readcdf.g711a", 
		"cardbf.g711a", 
		"cardaf.g711a", 
		"cardend.g711a", 
		"cardear.g711a", 
		"readagain.g711a", 
		"cardnuse.g711a", 
		"cardloss.g711a", 
		"cardedat.g711a", 
		"entered.g711a", 
		"exited.g711a", 
		"park.g711a", 
		"consume.g711a", 
		"callin.g711a", 
		"callout.g711a", 
		"callbusy.g711a", 
		"noanswer.g711a", 
		"Errtime.g711a", 
		"exitsub.g711a", 
		"entersub.g711a", 
		"exitmain.g711a", 
		"netfail.g711a", 
		"thsin.g711a", 
		"thsouted.g711a", 
		"lessmey.g711a", 
		"nordcard.g711a", 
		"notwork.g711a", 
		"insertcard.g711a", 
		"chargeagain.g711a", 
		"takein.g711a", 
		"takeout.g711a", 
		"lestmey.g711a", 
		"charge.g711a", 
		"readOK.g711a", 
		"Motorcycle.g711a", 
		"SmallCar.g711a", 
		"MiddleCar.g711a", 
		"BigCar.g711a", 
		"SpuCar.g711a", 
		"PreDefCar.g711a", 
		"NoAuthEnter.g711a", 
		"WatchCard.g711a", 
		"OperateCard.g711a", 
		"ChsCarType.g711a", 
		"tian.g711a", 
		"takecard.g711a", 
		"69.g711a", 
		"70.g711a", 
		"71.g711a", 
		"72.g711a", 
		"73.g711a", 
		"74.g711a", 
		"75.g711a", 
		"A.g711a",
		"B.g711a",
		"C.g711a",
		"D.g711a",
		"E.g711a",
		"F.g711a",
		"G.g711a",
		"H.g711a",
		//"I.g711a", : Unexist plate letter
		"J.g711a",
		"K.g711a",
		"L.g711a",
		"M.g711a",
		"N.g711a",
		"O.g711a",
		"P.g711a",
		"Q.g711a",
		"R.g711a",
		"S.g711a",
		"T.g711a",
		"U.g711a",
		"V.g711a",
		"W.g711a",
		"X.g711a",
		"Y.g711a",
		"Z.g711a",
		//Area voice list
		"ao.g711a",
		"chuan.g711a",
		"e4.g711a",
		"gan1.g711a",
		"gan4.g711a",
		"gang.g711a",
		"gua.g711a",
		"gui.g711a",
		"hei.g711a",
		"hu.g711a",
		"ji2.g711a",
		"ji4.g711a",
		"jin1.g711a",
		"jin4.g711a",
		"jing1.g711a",
		"jing3.g711a",
		"liao.g711a",
		"ling.g711a",
		"lu.g711a",
		"meng.g711a",
		"min.g711a",
		"ning.g711a",
		"qing.g711a",
		"qiong.g711a",
		"shan.g711a",
		"shi.g711a",
		"su.g711a",
		"wan.g711a",
		"xiang.g711a",
		"xin.g711a",
		"xue.g711a",
		"yu2.g711a",
		"yu4.g711a",
		"yue.g711a",
		"yun.g711a",
		"zang.g711a",
		"zhe.g711a",
		/*zhong an new voice*/
		"MonthlyRentCar.g711a",
		"FreeCar.g711a",
		"TemporaryCar.g711a",
		"BankCar.g711a",
		"jiao.g711a",
		"payment.g711a",
		"QuicklyDefer.g711a",
		"AvailableTime.g711a"
	};
	static const char* filelistContent[] = {
		"0", 
		"1",
		"2",
		"3", 
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"十",
		"百",
		"千",
		"年",
		"月",
		"日",
		"小时",
		"分钟",
		"秒",
		"元",
		"有卡请刷卡, 无卡请取卡",
		"请刷卡",
		"请刷卡，临时卡请交卡",
		"有效期到",
		"您的卡快到期，请及时充值",
		"您的卡已过期，请充值",
		"您的卡被当作临时卡使用",
		"卡未开通",
		"重新读卡",
		"无效卡",
		"挂失卡",
		"此卡已过期",
		"已进场",
		"已出场",
		"停车",
		"消费",
		"call in",
		"call out",
		"对方忙",
		"对方无应答",
		"系统时间错误",
		"未出子区",
		"未进主区",
		"未出主区",
		"网络通讯失败",
		"欢迎光临",
		"一路顺风",
		"余额不足，卡上余额只有",
		"本机禁止读卡",
		"本机处于禁止状态",
		"请插卡",
		"补交收费",
		"带卡进场",
		"带卡出场",
		"卡上余额",
		"收费",
		"读卡成功",
		"摩托车",
		"小型车",
		"中型车",
		"大型车",
		"超大车",
		"预留车",
		"无授权",
		"值班员请确认放行",
		"操作卡",
		"值班员请选择车型",
		"天",
		"临时卡请交卡",	
		"请刷卡入场",
		"未注册用户卡",
		"当前时间段未授权",	
		"请取票入场",
		"车位已满",
		"非工作时间段",
		"小型车，请交费",	
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"澳",
		"川",
		"鄂",
		"甘",
		"赣",
		"港",
		"挂",
		"贵",
		"黑",
		"沪",
		"吉",
		"冀",
		"津",
		"晋",
		"京",
		"警",
		"辽",
		"领",
		"鲁",
		"蒙",
		"闽",
		"宁",
		"青",
		"琼",
		"陕",
		"使",
		"苏",
		"皖",
		"湘",
		"新",
		"学",
		"渝",
		"豫",
		"粤",
		"云",
		"藏",
		"浙",
		"月租车",
		"免费车",
		"临时车",
		"储值车",
		"角",
		"请缴费",
		"请尽快延期",
		"此卡可用日期"
	};

	int count = sizeof(filelist)/sizeof(char*);
	if ((nIndex < 0) || (nIndex >= count))
		return ICE_STATUS_ERROR;

	//handle->clog->Logf("%s %s","语音播报内容：", filelistContent[nIndex]);	return SDK_Broadcast_ByName(hSDK, filelist[nIndex], index);
	return SDK_Broadcast_ByName(hSDK, filelist[nIndex], index);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_Broadcast(ICE_HANDLE hSDK, ICE_U16 nIndex)
{
	return SDK_Broadcast(hSDK, nIndex, 1);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_BroadcastGroup(ICE_HANDLE hSDK, const ICE_CHAR* pcIndex)
{
	int index = 1;
	char szIndex[4096];

	if (NULL == pcIndex)
		return ICE_STATUS_ERROR;

	strcpy(szIndex, pcIndex);
	char *pch = strtok((char*)szIndex, ";\n,\t ");
	while (pch != NULL)
	{
		SDK_Broadcast(hSDK, atoi(pch), index++);
		pch = strtok(NULL, ";\n,\t ");
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_Broadcast_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName)
{
	return SDK_Broadcast_ByName(hSDK, pcName, 1);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_BroadcastGroup_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName)
{
	int index = 1;
	char *pszName = NULL;

	if (NULL == pcName)
		return ICE_STATUS_ERROR;

	pszName = (char*)malloc(strlen(pcName) + 1);
	if (NULL == pszName)
		return ICE_STATUS_ERROR;

	strcpy(pszName, pcName);
	char *pch = strtok(pszName, ";\n,\t ");
	while (pch != NULL)
	{
		SDK_Broadcast_ByName(hSDK, pch, index++);
		pch = strtok(NULL, ";\n,\t ");
	}

	free(pszName);
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetCity(ICE_HANDLE hSDK, ICE_U32 u32Index)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_VDC_PARAM_S param;
	memset(&param, 0, sizeof(ICE_VDC_PARAM_S));

	ICE_U32 ret = ICE_IPCSDK_GetVDCParam(handle->ip, &param);
	if (ICE_STATUS_OK != ret)
	{
		handle->clog->Logf("%s %s", handle->ip, "配置优先城市失败，原因：获取参数失败。");
		return ICE_STATUS_ERROR;
	}

	param.stPlateParam.s32PriorCityType = u32Index + 3;
	ret = ICE_IPCSDK_SetVDCParam(handle->ip, &param);
	if (ICE_STATUS_OK != ret)
	{
		handle->clog->Logf("%s %s", handle->ip, "配置优先城市失败");
		return ICE_STATUS_ERROR;
	}

	handle->clog->Logf("%s %s", handle->ip, "配置优先城市成功");
	return ICE_STATUS_OK;
}
#endif

ICE_IPCSDK_API void ICE_IPCSDK_SetDeviceEventCallBack(ICE_HANDLE hSDK, 
													  ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, void *pvDeviceEventParam)
{
	/*if (NULL == hSDK)
	return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;*/

	g_pfOnDeviceEvent = pfOnDeviceEvent;
	g_pvDeviceEventParam = pvDeviceEventParam;
}

//#ifdef USE_FFMPEG

void GetVersion(const char *version, bool bAlgo, char *subver)
{
	const char *str = strstr(version, ".SVR_");

	char info[512];
	if (NULL != str)
		strcpy(info, str + 5);
	else
		strcpy(info, version);

	if (!bAlgo)
	{
		char *str = strstr(info, ", algo : ");
		if (NULL != str)
		{
			char *chr = strstr(info, ", flash : ");
			if (NULL == chr)
				*str = '\0';
			else
				strcpy(str, chr);

			strcpy(subver, info);
		}
		else
		{
			str = strstr(info, "flash : ");
			if (NULL != str)
				strcpy(subver, str);
		}
	}
	else
		strcpy(subver, version);
}

#ifdef _WIN32
#define MAX_ADAPTER 16

ICE_IPCSDK_API void ICE_IPCSDK_SearchDev(char* szDevs)
{
	if (NULL == szDevs)
		return;

	IP_ADAPTER_INFO info[MAX_ADAPTER], *pinfo = info;
	ULONG lOutBufLen = MAX_ADAPTER * sizeof(IP_ADAPTER_INFO);

	if (ERROR_SUCCESS != GetAdaptersInfo(info, &lOutBufLen))
		return;

	szDevs[0] = '\0';

	while (NULL != pinfo)
	{
		char szName[128];
		char szMac[8];

		sprintf(szName, "\\Device\\NPF_%s", pinfo->AdapterName);
		memcpy(szMac, pinfo->Address, MAX_ADAPTER_ADDRESS_LENGTH);

		pcap_t *fp;
		char errbuf[PCAP_ERRBUF_SIZE];
		u_char packet[14];

		/* Open the adapter */
		fp = pcap_open_live(szName, 65536, 1, 30, errbuf);
		if (NULL == fp)
		{
			pinfo = pinfo->Next;
			continue;
		}

		memset(packet, 0xFF, 6);
		memcpy(packet + 6, szMac, 6);
		*(USHORT*)(packet + 12) = 0xF0FF;

		/* Send down the packet */
		if (0 != pcap_sendpacket(fp, packet, 14))
		{
			pcap_close(fp);
			pinfo = pinfo->Next;
			continue;
		}

		struct pcap_pkthdr *header;
		const u_char *pkt_data;
		struct in_addr addr;
		char buf[256];
		memset(buf, 0, sizeof(buf));

		time_t begin = time(NULL);

		while (TRUE)
		{
			time_t end = time(NULL);
			if ((end - begin >= 3) || (end < begin))
				break;

			if (pcap_next_ex(fp, &header, &pkt_data) <= 0)
				continue;

			if (memcmp(pkt_data, szMac, 6) || 
				(0xF1FF != *(USHORT*)(pkt_data + 12)))
				continue;

			addr.S_un.S_addr = *(ULONG*)(pkt_data + 14);
			sprintf(buf, "%02X-%02X-%02X-%02X-%02X-%02X\t%s\t", 
				pkt_data[6], pkt_data[7], pkt_data[8], 
				pkt_data[9], pkt_data[10], pkt_data[11], inet_ntoa(addr));

			strcat(szDevs, buf);

			if (header->len > 78)
			{
				memcpy(buf, pkt_data + 78, header->len - 78);
				buf[header->len - 78] = '\0';

				/*vlen = strlen(text) + 1;
				if (header->len > 78 + (unsigned)vlen)*/

				char text[512];
				memset(text, 0, sizeof(text));
				GetVersion(buf, 0, text);
				strcat(szDevs, text);
				strcat(szDevs, "\t");
			}

			if (header->len > 18)
			{
				if (header->len < 38)
				{
					memcpy(buf, pkt_data + 18, header->len - 18);
					buf[header->len - 18] = '\0';
				}
				else
				{
					memcpy(buf, pkt_data + 18, 20);
					buf[20] = '\0';
				}

				strcat(szDevs, buf);
				strcat(szDevs, "\r\n");
			}
		}

		pcap_close(fp);
		pinfo = pinfo->Next;
	}
}

void SendPacket(pcap_t *fp, const BYTE* dst, 
				const char* mac, const u_char* data, int len)
{
	u_char packet[256];

	sscanf(mac, "%x-%x-%x-%x-%x-%x", packet, packet + 1, 
		packet + 2, packet + 3, packet + 4, packet + 5);
	memcpy(packet + 6, dst, 6);
	memcpy(packet + 12, data, len);

	/* Send down the packet */
	pcap_sendpacket(fp, packet, 12 + len);
}

ICE_IPCSDK_API void ICE_IPCSDK_ModifyDevIP(const ICE_CHAR* szMac, const ICE_CHAR *szIP, const ICE_CHAR *szMask, const ICE_CHAR* szGateway)
{
	if(NULL == szMac)
		return;

	IP_ADAPTER_INFO info[MAX_ADAPTER], *pinfo = info;
	ULONG lOutBufLen = MAX_ADAPTER * sizeof(IP_ADAPTER_INFO);

	if (ERROR_SUCCESS != GetAdaptersInfo(info, &lOutBufLen))
		return;


	while (NULL != pinfo)
	{
		char szName[128];
		char szSrcMac[8];

		sprintf(szName, "\\Device\\NPF_%s", pinfo->AdapterName);
		memcpy(szSrcMac, pinfo->Address, MAX_ADAPTER_ADDRESS_LENGTH);

		pcap_t *fp;
		char errbuf[PCAP_ERRBUF_SIZE];
		u_char packet[14];

		/* Open the adapter */
		fp = pcap_open_live(szName, 65536, 1, 30, errbuf);
		if (NULL == fp)
		{
			pinfo = pinfo->Next;
			continue;
		}

		while (TRUE)
		{
			struct pcap_pkthdr *header;
			const u_char *pkt_data;

			if (pcap_next_ex(fp, &header, &pkt_data) <= 0)
				break;
		}

		BYTE data[512];
		*(USHORT*)data = 0xF2FF;

		ULONG *addr = (ULONG*)(data + 2);
		addr[0] = inet_addr(szIP);
		addr[1] = inet_addr(szMask);
		addr[2] = inet_addr(szGateway);

		SendPacket(fp, (BYTE*)szSrcMac, szMac, data, 14);

		pcap_close(fp);
		pinfo = pinfo->Next;
	}
}

#else

int get_addr(const char *szIfName, uint32_t *ip, char *mac)
{
	int sockfd;
	struct ifreq ir;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
		return -1;

	strcpy(ir.ifr_name, szIfName);
	ioctl(sockfd, SIOCGIFHWADDR, &ir);
	memcpy(mac, ir.ifr_hwaddr.sa_data, 6);

	ioctl(sockfd, SIOCGIFADDR, &ir);
	close(sockfd);

	*ip = ((struct sockaddr_in*)&ir.ifr_addr)->sin_addr.s_addr;
	return 0;
}

#define BUFEER_SIZE 2048

ICE_IPCSDK_API void ICE_IPCSDK_SearchDev(const char *szIfName, char *szDevs, int nSize, int nTimeoutMs)
{
	if ((NULL == szDevs) || (0 == nSize))
		return;

	szDevs[0] = '\0';

	int sockfd;
	uint32_t ip;
	uint16_t type = 0xF0FF;
	struct sockaddr_ll device;
	unsigned char buf[BUFEER_SIZE], mac[6];

	if (0 != get_addr(szIfName, &ip, (char*)mac))
		return;

	memset(&device, 0, sizeof(device));
	device.sll_ifindex = if_nametoindex(szIfName);
	device.sll_family = AF_PACKET;
	memcpy(device.sll_addr, mac, 6);
	device.sll_halen = htons(6);

	sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (-1 == sockfd)
		return;

	memset(buf, 0xFF, 6);
	memcpy(buf + 6, mac, 6);
	memcpy(buf + 12, &type, 2);

	sendto(sockfd, buf, 14, 0, (struct sockaddr*)&device, sizeof(device));

	int nTimeout = nTimeoutMs / 1000, vlen = 0, len;
	time_t begin = time(NULL);
	struct in_addr addr;
	char info[1024];

	while (1)
	{

		time_t end = time(NULL);
		if ((end - begin >= nTimeout) || (end < begin))
			break;

		len = recvfrom(sockfd, buf, BUFEER_SIZE, MSG_DONTWAIT, NULL, NULL);

		if (len <= 0)
		{
			usleep(1000);
			continue;
		}

		memcpy(&type, buf + 12, 2);

		if ((0 != memcmp(buf, mac, 6)) || (0xF1FF != type))
			continue;

		memcpy(&addr.s_addr, buf + 14, 4);

		sprintf(info, "%02X-%02X-%02X-%02X-%02X-%02X\t%s\t", 
			buf[6], buf[7], buf[8], buf[9], buf[10], buf[11], 
			inet_ntoa(addr));

		if (nSize - strlen(szDevs) <= strlen(info))
			break;

		strcat(szDevs, info);

		if (len > 78)
			{
				memcpy(info, buf + 78, len - 78);
				info[len - 78] = '\0';

				char text[512];
				memset(text, 0, sizeof(text));
				GetVersion(info, 0, text);
				strcat(szDevs, text);
				strcat(szDevs, "\t");
			}

			if (len > 18)
			{
				if (len < 38)
				{
					memcpy(info, buf + 18, len - 18);
					info[len - 18] = '\0';
				}
				else
				{
					memcpy(info, buf + 18, 20);
					info[20] = '\0';
				}

				strcat(szDevs, info);
				strcat(szDevs, "\r\n");
			}

	}

	close(sockfd);
}

ICE_IPCSDK_API void ICE_IPCSDK_ModifyDevIP(const char *szIfName, const ICE_CHAR* szMac, const ICE_CHAR *szIP, 
										   const ICE_CHAR *szMask, const ICE_CHAR* szGateway)
{
	int sockfd;
	uint32_t ip;
	struct sockaddr_ll device;
	unsigned char buf[256], mac[6];

	if (0 != get_addr(szIfName, &ip, (char*)mac))
		return;

	memset(&device, 0, sizeof(device));
	device.sll_ifindex = if_nametoindex(szIfName);
	device.sll_family = AF_PACKET;
	memcpy(device.sll_addr, mac, 6);
	device.sll_halen = htons(6);

	sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (-1 == sockfd)
		return;

	unsigned char data[32];
	*(unsigned short*)data = 0xF2FF;

	unsigned long *addr = (unsigned long *)(data + 2);
	addr[0] = inet_addr(szIP);
	addr[1] = inet_addr(szMask);
	addr[2] = inet_addr(szGateway);

	sscanf(szMac, "%x-%x-%x-%x-%x-%x", buf, buf+1, buf+2, buf+3, buf+4, buf+5);
	memcpy(buf + 6, mac, 6);
	memcpy(buf + 12, data, 14);

	sendto(sockfd, buf, 26, 0, (struct sockaddr*)&device, sizeof(device));
}

#endif

#if 0
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDNSAddr(ICE_HANDLE hSDK, ICE_U32 *pu32DNS, ICE_U32 *pu32DNS2)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 8 * sizeof(ICE_U32);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_DNS_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_DNS_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	ICE_U32 addr[8];
	socket_recv(sockfd, addr, size, 1000);
	close(sockfd);

	if (NULL != pu32DNS)
		*pu32DNS = addr[0];

	if (NULL != pu32DNS2)
		*pu32DNS2 = addr[1];

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetDNSAddr(ICE_HANDLE hSDK, ICE_U32 u32DNS, ICE_U32 u32DNS2)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = 8 * sizeof(int);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_DNS_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int addr[8] = {0};
	addr[0] = u32DNS;
	addr[1] = u32DNS2;
	socket_send(sockfd, addr, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_DNS_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
#endif

ICE_IPCSDK_API void ICE_IPCSDK_LogConfig(int openLog, const char *logPath)
{
	g_nEnableLog = openLog;

	if (NULL == logPath)
		strcpy(g_logPath, "d:\\");
	else
		strcpy(g_logPath, logPath);
}

#if 0
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLightParam(ICE_HANDLE hSDK, LightParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(LightParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_LIGHT_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_LIGHT_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLightParam(ICE_HANDLE hSDK, const LightParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(LightParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_LIGHT_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_LIGHT_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API void ICE_IPCSDK_EnableUTF8(ICE_HANDLE hSDK, int enable)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	handle->enable_utf8 = enable;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetReOpenParam(ICE_HANDLE hSDK, ReOpenParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ReOpenParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_REOPEN_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_REOPEN_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetReOpenParam(ICE_HANDLE hSDK, const ReOpenParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(ReOpenParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_REOPEN_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_REOPEN_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_FLOAT ICE_IPCSDK_VBR_CompareFeat(ICE_FLOAT *_pfResFeat1, ICE_U32 _iFeat1Len,
													ICE_FLOAT *_pfReaFeat2, ICE_U32 _iFeat2Len)
{
	ICE_FLOAT fRes = 0;
	if(_iFeat1Len!=_iFeat2Len || _iFeat2Len!=VBR_RES_TOPN*2)
		return fRes;
	for(int i=0; i<VBR_RES_TOPN; i++)
	{
		for(int j=0; j<VBR_RES_TOPN; j++)
		{
			if((ICE_U32)_pfResFeat1[i]==(ICE_U32)_pfReaFeat2[j])
			{
				fRes = (float)(0.5*(_pfResFeat1[VBR_RES_TOPN+i]+_pfReaFeat2[VBR_RES_TOPN+j]));
				j = VBR_RES_TOPN;
				i = VBR_RES_TOPN;
			}
		}
	}
	return fRes;		
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetOfflineAoParam(ICE_HANDLE hSDK, OfflineAoParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(OfflineAoParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_AO_PLAY_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_AO_PLAY_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) + size != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, pstParam, size, 1000);
	close(sockfd);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetOfflineAoParam(ICE_HANDLE hSDK, const OfflineAoParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	static int size = sizeof(OfflineAoParam);

	int sockfd = socket_connect(handle->ip, handle->u16ICEPort, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_AO_PLAY_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, pstParam, size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_AO_PLAY_PARAM_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	close(sockfd);
	return header.u32Status;
}
#endif

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetIOState(ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IOState, 
											 ICE_U32 *pu32Reserve1, ICE_U32 *pu32Reserve2)
{
	if ((NULL == hSDK) || (u32Index >= 4))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	char state[16];
	memset(state, 0, sizeof(state));

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_GET_IO_IN_STATE;
	header.u32Size = sizeof(ICE_OPER_DATA_S);

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);


	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_GET_IO_IN_STATE_RSP != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) >= header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	ret = socket_recv(sockfd, state, (header.u32Size - sizeof(ICE_OPER_DATA_S)), 1000);
	if (ret < 0)
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	*pu32IOState = state[u32Index];
	close(sockfd);
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_SDK_GetParam(ICE_HANDLE hSDK, const void* pstData, int len, 
										ICE_U32 u32Req, ICE_U32 u32Rsp, void *pstParam, ICE_U32 u32Size, int timeout_ms)
{
	if (NULL == hSDK)
		return 0;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return 0;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = u32Req;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + len;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if (len > 0)
		socket_send(sockfd, pstData, len, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), timeout_ms);
	if ((ret < 0) || (u32Rsp != header.u32Type))
	{
		close(sockfd);
		return 0;
	}

	ICE_U32 size = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (size > u32Size)
		size = u32Size;

	size = socket_recv(sockfd, pstParam, size, timeout_ms);
	close(sockfd);

	return size;
}

ICE_IPCSDK_API ICE_U32 ICE_SDK_SetParam(ICE_HANDLE hSDK, ICE_U32 u32Req, ICE_U32 u32Rsp, 
										const void *pstParam, ICE_U32 u32Size, int timeout_ms)
{
	if (NULL == hSDK)
		return 0;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return 0;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = u32Req;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + u32Size;

	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if (u32Size > 0)
		socket_send(sockfd, pstParam, u32Size, 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), timeout_ms);
	if ((ret < 0) || (u32Rsp != header.u32Type) || 
		(sizeof(ICE_OPER_DATA_S) != header.u32Size))
	{
		close(sockfd);
		return 0;
	}

	close(sockfd);
	return header.u32Status;
}

#if 0
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLEDParam(ICE_HANDLE hSDK, ICE_LED_PARAM *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, NULL, 0, ICE_CAMERA_CONFIG_TYPE_GET_LED_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_GET_LED_PARAM_RSP, pstParam, sizeof(ICE_LED_PARAM), 1000);

	if (sizeof(ICE_LED_PARAM) != u32Size)
		return ICE_STATUS_ERROR;

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLEDParam(ICE_HANDLE hSDK, const ICE_LED_PARAM *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_LED_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_SET_LED_PARAM_RSP, pstParam, sizeof(ICE_LED_PARAM), 1000);
}

//ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLEDPro1Param(ICE_HANDLE hSDK, Led_Display_Pro1_Param *pstParam)
//{
//	if (NULL == hSDK)
//		return ICE_STATUS_ERROR;
//
//	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
//
//	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, NULL, 0, ICE_CAMERA_CONFIG_TYPE_GET_LED_PROTOCOL1, 
//		ICE_CAMERA_CONFIG_TYPE_GET_LED_PROTOCOL1_RSP, pstParam, sizeof(Led_Display_Pro1_Param), 1000);
//
//	if (sizeof(Led_Display_Pro1_Param) != u32Size)
//		return ICE_STATUS_ERROR;
//
//	return ICE_STATUS_OK;
//}
//ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLEDPro1Param(ICE_HANDLE hSDK, const Led_Display_Pro1_Param *pstParam)
//{
//	if (NULL == hSDK)
//		return ICE_STATUS_ERROR;
//
//	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
//
//	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_LED_PROTOCOL1, 
//		ICE_CAMERA_CONFIG_TYPE_SET_LED_PROTOCOL1_RSP, pstParam, sizeof(Led_Display_Pro1_Param), 1000);
//}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLEDCard2Param(ICE_HANDLE hSDK, Led_Card_2_total_cfg_param *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, NULL, 0, ICE_CAMERA_CONFIG_TYPE_GET_LED_CARD_2_SERIAL_PROTOCOL, 
		ICE_CAMERA_CONFIG_TYPE_GET_LED_CARD_2_SERIAL_PROTOCOL_RSP, pstParam, sizeof(Led_Card_2_total_cfg_param), 1000);

	if (sizeof(Led_Card_2_total_cfg_param) != u32Size)
		return ICE_STATUS_ERROR;

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLEDCard2Param(ICE_HANDLE hSDK, const Led_Card_2_total_cfg_param *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_LED_CARD_2_SERIAL_PROTOCOL, 
		ICE_CAMERA_CONFIG_TYPE_SET_LED_CARD_2_SERIAL_PROTOCOL_RSP, pstParam, sizeof(Led_Card_2_total_cfg_param), 1000);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetForceCareraOfflineParam(ICE_HANDLE hSDK, Force_camera_offline_cfg_param *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, NULL, 0, ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_OFFLINE_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_OFFLINE_PARAM_RSP, pstParam, sizeof(Force_camera_offline_cfg_param), 1000);

	if (sizeof(Force_camera_offline_cfg_param) != u32Size)
		return ICE_STATUS_ERROR;

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetForceCareraOfflineParam(ICE_HANDLE hSDK, const Force_camera_offline_cfg_param *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_OFFLINE_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_OFFLINE_PARAM_RSP, pstParam, sizeof(Force_camera_offline_cfg_param), 1000);
}
#endif

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_Login(const ICE_CHAR *pcIP, ICE_CHAR *pcReserve1, ICE_CHAR *pcReserve2, 
										   ICE_U32 *nReserve1, ICE_U32 *nReserve2, ICE_U32 *nReserve3, ICE_U32 u32SyncTime)
{
	ICE_HANDLE hSDK = ICE_IPCSDK_OpenDevice(pcIP);
	if ((NULL != hSDK) && (1 == u32SyncTime))
	{
		time_t t = time(NULL);
		struct tm *ptm = localtime(&t);

		ICE_IPCSDK_SyncTime(hSDK, (short)ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, 
			ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	}
	return hSDK;
}

ICE_IPCSDK_API void ICE_IPCSDK_Logout(ICE_HANDLE hSDK)
{
	ICE_IPCSDK_Close(hSDK);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetSingleParkingSpaceStatus(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32SpaceNum,
															  ICE_PARKING_SPACE_OUTPUT_S *pstResult, ICE_CHAR *pcPicData, ICE_U32 u32Size, ICE_U32* pu32PicLen, 
															  ICE_CHAR *pcReserve, ICE_U32 u32Reserve, ICE_U32 *pu32Reserve)
{
	if ((u32SpaceCode >= ICE_MAX_PARKING_SPACE_NUM)|| (NULL == pstResult) || (NULL == pcPicData))
		return ICE_STATUS_ERROR;

	ICE_PARKING_SPACE_RESULT_S pstParkingResult;
	memset(&pstParkingResult, 0, sizeof(pstParkingResult));

	int ret = ICE_IPCSDK_GetAllParkingSpaceStatus(hSDK, &pstParkingResult, pcPicData, u32Size, pu32PicLen, NULL, NULL);
	if (1 == ret)
	{
		*u32SpaceNum = (ICE_U32)pstParkingResult.u8ParkingPlaceNum;
		memcpy(pstResult, &pstParkingResult.astOutput[u32SpaceCode], sizeof(ICE_PARKING_SPACE_OUTPUT_S));
	}

	return ret;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAllParkingSpaceStatus(ICE_HANDLE hSDK, ICE_PARKING_SPACE_RESULT_S *pstResult, 
														   ICE_CHAR *pcPicData,ICE_U32 u32Size, ICE_U32* pu32PicLen, void *pvReserve, ICE_U32* u32Reserve)
{
	if ((NULL == hSDK) || (NULL == pstResult) || (NULL == pcPicData))
		return ICE_STATUS_ERROR;

	memset(pstResult, 0, sizeof(ICE_PARKING_SPACE_RESULT_S));
	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CONTROL_TYPE_GET_ALL_PARKINGSPACE_STATUS;
	header.u32Size = sizeof(ICE_OPER_DATA_S);
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CONTROL_TYPE_GET_ALL_PARKINGSPACE_STATUS_RSP != header.u32Type))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	ICE_U32 size = socket_recv(sockfd, pstResult, sizeof(ICE_PARKING_SPACE_RESULT_S), 1000);
	if (size < sizeof(ICE_PARKING_SPACE_RESULT_S))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	size = header.u32Size - sizeof(ICE_OPER_DATA_S) - sizeof(ICE_PARKING_SPACE_RESULT_S);
	if (size > u32Size)
		size = u32Size;
	*pu32PicLen = socket_recv(sockfd, pcPicData, size, 1000);
	close(sockfd);

	for (int i = 0; i < pstResult->u8ParkingPlaceNum; i++)
	{
		if (((pstResult->astOutput[i].enParkingPlaceStatus == ICE_IPG_EVENT_TYPE_HAVE_CAR) 
			|| (pstResult->astOutput[i].enParkingPlaceStatus == ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE))
			&& (pstResult->astOutput[i].stPlateInfo.flConfidence <= 0))
			strcpy(pstResult->astOutput[i].stPlateInfo.as8PlateNum, "无牌车");
	}
	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetEnableParkingSpace(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 u32Enable)
{
	if ((NULL == hSDK) || (u32SpaceCode >= ICE_MAX_PLACE_NUM))
		return ICE_STATUS_ERROR;

	ICE_IPG_PARAM_S ipgParam;
	memset(&ipgParam, 0, sizeof(ICE_IPG_PARAM_S));

	int ret = ICE_IPCSDK_GetIPGParam(hSDK, &ipgParam);
	if (0 == ret)
		return ICE_STATUS_ERROR;
	ipgParam.stCameraPlace.stPlaceParam[u32SpaceCode].isAvalable = (ICE_BOOL)u32Enable;

	ret = ICE_IPCSDK_SetIPGParam(hSDK, &ipgParam);

	return ret;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetEnableParkingSpace(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32Enable)
{
	if ((NULL == hSDK) || (u32SpaceCode >= ICE_MAX_PLACE_NUM))
		return ICE_STATUS_ERROR;

	ICE_IPG_PARAM_S ipgParam;
	memset(&ipgParam, 0, sizeof(ICE_IPG_PARAM_S));

	int ret = ICE_IPCSDK_GetIPGParam(hSDK, &ipgParam);
	if (0 == ret)
		return ICE_STATUS_ERROR;

	*u32Enable = ipgParam.stCameraPlace.stPlaceParam[u32SpaceCode].isAvalable;

	return ret;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetParkingSpaceType(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 u32SpaceType)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_SET_PARKINGSPACE_TYPE;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + sizeof(ICE_U32);
	header.u32Id = u32SpaceCode;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, &u32SpaceType, sizeof(ICE_U32), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_SET_PARKINGSPACE_TYPE_RSP != header.u32Type))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetParkingSpaceType(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32SpaceType)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return ICE_STATUS_ERROR;

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_PARKINGSPACE_TYPE;
	header.u32Size = sizeof(ICE_OPER_DATA_S);
	header.u32Id = u32SpaceCode;
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_PARKINGSPACE_TYPE_RSP != header.u32Type)
		|| ((sizeof(ICE_OPER_DATA_S) + 4) != header.u32Size))
	{
		close(sockfd);
		return ICE_STATUS_ERROR;
	}

	socket_recv(sockfd, u32SpaceType, sizeof(ICE_U32), 1000);

	return header.u32Status;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetRemoteDevState(ICE_HANDLE hSDK, ICE_U32 *u32IsRemote, ICE_CHAR *pcRemoteIp, 
													ICE_U32 *u32Reserve1, ICE_U32 *u32Reserve2)
{
	if ((NULL == hSDK) || (NULL == pcRemoteIp))
		return ICE_STATUS_ERROR;

	char data[100];
	memset(data, 0 ,sizeof(data));

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return 0;

	char sendData[16];
	memset(sendData, 0, sizeof(sendData));
	strcpy(sendData, "key=remote");

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_REMOTE_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + strlen(sendData);
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, sendData, strlen(sendData), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_REMOTE_PARAM_RSP != header.u32Type))
	{
		close(sockfd);
		return 0;
	}

	ICE_U32 size = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (size > sizeof(data))
		size = sizeof(data);

	size = socket_recv(sockfd, data, size, 1000);
	close(sockfd);

	if (size <= 0)
		return ICE_STATUS_ERROR;

	char *subpch, *subchr;

	subpch = strtok(data, "&");
	while (subpch != NULL)
	{
		subchr = strchr(subpch, '=');
		if (NULL == subchr)
		{
			subpch = strtok(NULL, "&");
			continue;
		}

		*subchr++ = '\0';
		if (0 == strcmp(subpch, "enable_remote"))
			*u32IsRemote = (ICE_U32)atoi(subchr);
		else if (0 == strcmp(subpch, "remote_ip"))
			strcpy(pcRemoteIp, subchr);

		subpch = strtok(NULL, "&");
	}
	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetRemoteDevState(ICE_HANDLE hSDK, ICE_U32 u32IsRemote, const ICE_CHAR *pcRemoteIp,
													ICE_U32 u32Reserve1, ICE_U32 u32Reserve2)
{
	if ((NULL == hSDK) || (NULL == pcRemoteIp))
		return ICE_STATUS_ERROR;

	char data[100];
	memset(data, 0 ,sizeof(data));
	if (1 == u32IsRemote)
		sprintf(data, "enable_remote=on&remote_ip=%s", pcRemoteIp);
	else if (0 == u32IsRemote)
		sprintf(data, "remote_ip=%s", pcRemoteIp);

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_REMOTE_PARAM, ICE_CAMERA_CONFIG_TYPE_SET_REMOTE_PARAM_RSP,
		data, strlen(data), 2000);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetControlDevState(ICE_HANDLE hSDK, ICE_U32 *u32IsControlled, ICE_CHAR *pcControlIp,
													 ICE_U32 *u32Reserve1, ICE_U32 *u32Reserve2)
{
	if ((NULL == hSDK) || (NULL == pcControlIp))
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	int sockfd = socket_connect(handle->ip, 8117, 1000);
	if (-1 == sockfd)
		return 0;

	char data[100];
	memset(data, 0 ,sizeof(data));

	char sendData[16];
	memset(sendData, 0, sizeof(sendData));
	strcpy(sendData, "key=be_ctrl");

	ICE_OPER_DATA_S header;
	memset(&header, 0, sizeof(ICE_OPER_DATA_S));
	header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_CONTROL_PARAM;
	header.u32Size = sizeof(ICE_OPER_DATA_S) + strlen(sendData);
	socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	socket_send(sockfd, sendData, strlen(sendData), 1000);

	int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);
	if ((ret < 0) || (ICE_CAMERA_CONFIG_TYPE_GET_CONTROL_PARAM_RSP != header.u32Type))
	{
		close(sockfd);
		return 0;
	}

	ICE_U32 size = header.u32Size - sizeof(ICE_OPER_DATA_S);
	if (size > sizeof(data))
		size = sizeof(data);

	size = socket_recv(sockfd, data, size, 1000);
	close(sockfd);

	if (size <= 0)
		return ICE_STATUS_ERROR;

	char *subpch, *subchr;

	subpch = strtok(data, "&");
	while (subpch != NULL)
	{
		subchr = strchr(subpch, '=');
		if (NULL == subchr)
		{
			subpch = strtok(NULL, "&");
			continue;
		}

		*subchr++ = '\0';
		if (0 == strcmp(subpch, "enable_by_remote"))
			*u32IsControlled = (ICE_U32)atoi(subchr);
		else if (0 == strcmp(subpch, "by_remote_ip"))
			strcpy(pcControlIp, subchr);

		subpch = strtok(NULL, "&");
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetControlDevState(ICE_HANDLE hSDK, ICE_U32 u32IsControlled, const ICE_CHAR *pcControlIp,
													 ICE_U32 u32Reserve1, ICE_U32 u32Reserve2)
{
	if ((NULL == hSDK) || (NULL == pcControlIp))
		return ICE_STATUS_ERROR;

	char data[100];
	memset(data, 0 ,sizeof(data));
	if (1 == u32IsControlled)
		sprintf(data, "enable_by_remote=on&by_remote_ip=%s", pcControlIp);
	else if (0 == u32IsControlled)
		sprintf(data, "by_remote_ip=%s", pcControlIp);

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_CONTROL_PARAM, ICE_CAMERA_CONFIG_TYPE_SET_CONTROL_PARAM_RSP,
		data, strlen(data), 2000);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAllParkingSpaceLoops(ICE_HANDLE hSDK, ICE_IPG_PLACE_CONFIG_S *pstParam, ICE_U32 nWidth, ICE_U32 nHeight)
{
	if ((NULL == hSDK) || (NULL == pstParam) || (nWidth == 0) || (nHeight == 0))
		return ICE_STATUS_ERROR;

	ICE_IPG_PARAM_S ipgParam;
	memset(&ipgParam, 0, sizeof(ipgParam));

	int ret = ICE_IPCSDK_GetIPGParam(hSDK, &ipgParam);
	if (0 == ret)
		return ICE_STATUS_ERROR;

	float rx = (float)nWidth/ipgParam.s32ImgWidth;
	float ry = (float)nHeight/ipgParam.s32ImgHeight;

	for (int i=0; i<ipgParam.stCameraPlace.u8ParkingPlaceNum; i++)
	{
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Left *= rx;
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Bottom *= ry;
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Right *= rx;
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Top *= ry;
	}

	memcpy(pstParam, &ipgParam.stCameraPlace, sizeof(ICE_IPG_PLACE_CONFIG_S));

	return ret;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetAllParkingSpaceLoops(ICE_HANDLE hSDK, const ICE_IPG_PLACE_CONFIG_S *pstParam, ICE_U32 nWidth, ICE_U32 nHeight)
{
	if ((NULL == hSDK) || (NULL == pstParam) || (nWidth == 0) || (nHeight == 0))
		return ICE_STATUS_ERROR;

	ICE_IPG_PARAM_S ipgParam;
	memset(&ipgParam, 0, sizeof(ipgParam));

	int ret = ICE_IPCSDK_GetIPGParam(hSDK, &ipgParam);
	if (0 == ret)
		return ICE_STATUS_ERROR;
	memcpy(&ipgParam.stCameraPlace, pstParam, sizeof(ICE_IPG_PLACE_CONFIG_S));

	float rx = (float)ipgParam.s32ImgWidth/nWidth;
	float ry = (float)ipgParam.s32ImgHeight/nHeight;

	for (int i=0; i<ipgParam.stCameraPlace.u8ParkingPlaceNum; i++)
	{
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Left *= rx;
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Bottom *= ry;
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Right *= rx;
		ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Top *= ry;
		if(((ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Right - ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Left) < 20)
			|| ((ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Bottom - ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Top) < 20))
			return 0;

		if (ipgParam.stCameraPlace.u8ParkingPlaceNum == 3)
		{		
			if((ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Left <= 30)
				|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Top <= 30)
				|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Right >= (ipgParam.s32ImgWidth - 30))
				|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Bottom >= (ipgParam.s32ImgHeight - 30)))
				return 0;
		}
		else if((ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Left <= 0)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Left >= ipgParam.s32ImgWidth)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Top <= 0)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Top >= ipgParam.s32ImgHeight)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Right <= 0)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Right >= ipgParam.s32ImgWidth)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Bottom <= 0)
			|| (ipgParam.stCameraPlace.stPlaceParam[i].stRecRect.s16Bottom >= ipgParam.s32ImgHeight))
			return 0;
	}
	ret = ICE_IPCSDK_SetIPGParam(hSDK, &ipgParam);

	return ret;
}

ICE_IPCSDK_API void ICE_IPCSDK_SetParkingSpaceInfoCallBack(ICE_HANDLE hSDK, 
														   ICE_IPCSDK_OnParkingSpaceInfo pfParkingSpaceInfo, void *pvParam)
{
	if (NULL == hSDK)
		return;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	handle->pfOnParkingSpaceInfo = pfParkingSpaceInfo;
	handle->pvParkingSpaceInfo = pvParam;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetParkingSpaceNum(ICE_HANDLE hSDK, ICE_U32 *u32SpaceNum)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	ICE_IPG_PARAM_S ipgParam;
	memset(&ipgParam, 0, sizeof(ipgParam));

	int ret = ICE_IPCSDK_GetIPGParam(hSDK, &ipgParam);
	if (0 == ret)
		return ICE_STATUS_ERROR;
	*u32SpaceNum = ipgParam.stCameraPlace.u8ParkingPlaceNum;

	return ret;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLightCtlParam(ICE_HANDLE hSDK, const LightCtlParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_RGB_LIGHT_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_SET_RGB_LIGHT_PARAM_RSP, pstParam, sizeof(LightCtlParam), 1000);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLightCtlParam(ICE_HANDLE hSDK, LightCtlParam *pstParam)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;

	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, NULL, 0, ICE_CAMERA_CONFIG_TYPE_GET_RGB_LIGHT_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_GET_RGB_LIGHT_PARAM_RSP, pstParam, sizeof(LightCtlParam), 1000);

	if (sizeof(LightCtlParam) != u32Size)
		return ICE_STATUS_ERROR;

	return ICE_STATUS_OK;
}

//获取相机时间
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDevTime(ICE_HANDLE hSDK,
											 ICE_U16 *u16Year, ICE_U8 *u8Month, ICE_U8 *u8Day, 
											 ICE_U8 *u8Hour, ICE_U8 *u8Min, ICE_U8 *u8Sec)
{
	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	unsigned char data[16];
	memset(data, 0, sizeof(data));

	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, NULL, 0, ICE_CAMERA_CONFIG_TYPE_GET_SYSTEM_TIME, 
		ICE_CAMERA_CONFIG_TYPE_GET_SYSTEM_TIME_RSP, data, sizeof(data), 1000);

	*u8Month = (data[0] - '0') * 10 + data[1] - '0';
	*u8Day = (data[2] - '0') * 10 + data[3] - '0';
	*u8Hour = (data[4] - '0') * 10 + data[5] - '0';
	*u8Min = (data[6] - '0') * 10 + data[7] - '0';
	*u16Year = (data[8] - '0') * 1000 + (data[9] - '0') * 100 + (data[10] - '0') * 10 + (data[11] - '0');
	*u8Sec =  (data[13] - '0') * 10 + data[14] - '0';

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetCGIParam(ICE_HANDLE hSDK, http_conf_t *param)
{
	if (NULL == hSDK || NULL == param)
		return ICE_STATUS_ERROR;

	char data[1024];
	memset(data, 0, sizeof(data));

	char sendData[32] = {'\0'};
	sprintf(sendData, "key=http");
	ICE_U32 u32Size =  ICE_SDK_GetParam(hSDK, sendData, strlen(sendData), ICE_CAMERA_CONFIG_TYPE_GET_CGI_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_GET_CGI_PARAM_RSP, data, sizeof(data), 1000);

	if (u32Size <= 0)
		return ICE_STATUS_ERROR;

	char *subpch, *subchr;

	subpch = strtok(data, ",");
	while (subpch != NULL)
	{
		subchr = strchr(subpch, ':');
		if (NULL == subchr)
		{
			subpch = strtok(NULL, ",");
			continue;
		}

		*subchr++ = '\0';
		if (0 == strcmp(subpch, "\"http_enable\" "))
			param->http_enable = atoi(subchr);
		else if (0 == strcmp(subpch, " \"http_addr\" "))
		{
			strcpy(param->http_addr, subchr+2);
			param->http_addr[strlen(param->http_addr)- 1] = '\0';
		}
		else if (0 == strcmp(subpch, " \"small_pic\" "))
			param->small_pic = atoi(subchr);
		else if (0 == strcmp(subpch, " \"big_pic\" "))
			param->big_pic = atoi(subchr);
		else if (0 == strcmp(subpch, " \"upload_enable\" "))
			param->upload_enable = atoi(subchr);
		else if (0 == strcmp(subpch, " \"upload_interval\" "))
			param->upload_interval = atoi(subchr);
		else if (0 == strcmp(subpch, " \"heartbeat_enable\" "))
			param->heartbeat_enable = atoi(subchr);
		else if (0 == strcmp(subpch, " \"heartbeat_interval\" "))
			param->heartbeat_interval = atoi(subchr);

		subpch = strtok(NULL, ",");
	}

	return ICE_STATUS_OK;
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetCGIParam(ICE_HANDLE hSDK, const http_conf_t *param)
{
	if (NULL == hSDK || NULL == param)
		return ICE_STATUS_ERROR;

	char data[1024];
	memset(&data, 0, sizeof(data));

	sprintf(data, "key=http&http_enable=%s&http_addr=%s&small_pic=%s&big_pic=%s&upload_enable=%s&upload_interval=%d&heartbeat_enable=%s&heartbeat_interval=%d", 
		param->http_enable?"on":"", param->http_addr, param->small_pic?"on":"",
		param->big_pic?"on":"", param->upload_enable?"on":"", param->upload_interval, 
		param->heartbeat_enable?"on":"", param->heartbeat_interval);

	return ICE_SDK_SetParam(hSDK, ICE_CAMERA_CONFIG_TYPE_SET_CGI_PARAM, 
		ICE_CAMERA_CONFIG_TYPE_SET_CGI_PARAM_RSP, data, strlen(data), 2000);
}

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDevID(ICE_HANDLE hSDK, ICE_CHAR* szDevID)
{
	szDevID[0] = '\0';

	if (NULL == hSDK)
		return ICE_STATUS_ERROR;

	sdk_handle_t *handle = (sdk_handle_t*)hSDK;
	strcpy(szDevID, handle->ip);

	int sockfd = socket_connect(handle->ip, 8117, 3000);
	if (-1 != sockfd)
	{
		ICE_OPER_DATA_S header;
		memset(&header, 0, sizeof(ICE_OPER_DATA_S));
		header.u32Type = ICE_CAMERA_CONFIG_TYPE_GET_DEV_ID;
		header.u32Size = sizeof(ICE_OPER_DATA_S);

		socket_send(sockfd, &header, sizeof(ICE_OPER_DATA_S), 1000);

		int ret = socket_recv(sockfd, &header, sizeof(ICE_OPER_DATA_S), 3000);
		if ((ret > 0) && (ICE_CAMERA_CONFIG_TYPE_GET_DEV_ID_RSP == header.u32Type) && 
			(sizeof(ICE_OPER_DATA_S) + sizeof(Dev_ID) == header.u32Size))
		{
			Dev_ID id;
			socket_recv(sockfd, id.id, sizeof(Dev_ID), 3000);
			strcpy(szDevID, id.id);
		}

		close(sockfd);
	}

	return ICE_STATUS_OK;
}
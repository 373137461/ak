#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#ifdef COMPILEUTF8
#include <iconv.h>
#endif

#include "ice_ipcsdk.h"
#include "ice_ps_result.h"

#define OFFLINE 0
#define ONLINE  1

static int g_run = 1;
static ICE_HANDLE hSDK = NULL;

#ifdef COMPILEUTF8
//编码转换
int code_convert(const char *from_charset,const char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
  iconv_t cd;
  char **pin = &inbuf;
  char **pout = &outbuf;

  cd = iconv_open(to_charset,from_charset);
  if (cd==0)
       return -1;
  
  memset(outbuf,0,outlen);
  if (iconv(cd,pin,&inlen,pout,&outlen)==-1)
       return -1;
  
  iconv_close(cd);
  return 0;
}

//GB2312码转为UNICODE码

int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

#endif

//创建文件夹
int   CreatePath(const char *sPathName)  
{  
  char   DirName[256];  
  strcpy(DirName, sPathName);  
  int   i,len = strlen(DirName);  
  if(DirName[len-1]!='/')  
  strcat(DirName,   "/");  
   
  len = strlen(DirName);  
   
  for(i=1; i<len; i++)  
  {  
  	if(DirName[i]=='/')  
  	{  
  		DirName[i] = 0;  
  		if(access(DirName, R_OK)!=0)  
  		{  
    		if(mkdir(DirName, 0755)==-1)  
     		{   
        		perror("mkdir   error");   
            	return   -1;   
      		}  
  		}  
 	 DirName[i]   =   '/';  
	}  
}  
   
  return   0;  
}

//保存图片
static void savePic(const char* pcIp, void* pvPicData, long nPicLen)
{
	if (NULL == pcIp || NULL == pvPicData)
		return;
	
	char path[256];
	char name[512];
	char prefix[512];
	FILE *fp;

	memset(path, 0, sizeof(path));
	memset(name, 0, sizeof(name));
	memset(prefix, 0, sizeof(prefix));

	time_t now;	
	time(&now);
	struct tm *timenow = localtime(&now);

	sprintf(path,"./snap/%s/%4d%02d%02d", pcIp, timenow->tm_year+1900, timenow->tm_mon+1, timenow->tm_mday);
	//printf("SavePic:%s\r\n", path);
	if (CreatePath(path) != 0 )
		return;
	
	sprintf(prefix, "%s/%4d%02d%02d%02d%02d%02d", path, timenow->tm_year+1900, timenow->tm_mon+1, timenow->tm_mday, 
		timenow->tm_hour,timenow->tm_min,timenow->tm_sec);
	
	sprintf(name, "%s.jpg", prefix);
	if (-1 != (access(name, 0)))
	{
		int count = 1;
		while (count <= 10)
		{
			sprintf(name, "%s_%d.jpg", prefix, count++);
			if (-1 == (access(name, 0)))
				break;
		}
	}
	
	//存图
	fp = fopen(name, "wb");
	if (NULL != fp)
	{
		fwrite(pvPicData, 1, nPicLen, fp);
		fclose(fp);
	}
	else
	{
		printf("open file failed!\r\n");
	}	
}

#define __min(a,b) ( ((a)>(b)) ? (b):(a) )

//实时抓拍数据
void SDK_OnParkingSpaceInfo(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_PARKING_SPACE_RESULT_S *pstParkingResult, ICE_CHAR *pcPicData, ICE_U32 u32PicLen, 
	void *pvReserve, ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4)
{
	static int nPlateNum = 0;
	char now_str[64];
	memset(now_str, 0 ,sizeof(now_str));
	struct tm* tp;
	
	time_t nCapTime = time(NULL);
	tp = localtime(&nCapTime);
	strftime(now_str, sizeof(now_str), "%Y-%m-%d %H:%M:%S", tp);

	int count = __min(ICE_MAX_PARKING_SPACE_NUM, pstParkingResult->u8ParkingPlaceNum);
	for (int i = 0; i < count; i++)
	{
		const ICE_PARKING_SPACE_OUTPUT_S *output = pstParkingResult->astOutput + i;

		static const char *status[] = {"无", "车位有车", "空车位", "单车占多车位", "车位禁用"};
		int enParkingPlaceStatus = 0;

		switch (output->enParkingPlaceStatus)
		{
		case ICE_IPG_EVENT_TYPE_NOON:
		default:
			enParkingPlaceStatus = 0;
			break;

		case ICE_IPG_EVENT_TYPE_HAVE_CAR:
			enParkingPlaceStatus = 1;
			break;

		case ICE_IPG_EVENT_TYPE_EMPTY_PLACE:
			enParkingPlaceStatus = 2;
			break;

		case ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE:
			enParkingPlaceStatus = 3;
			break;

		case ICE_IPG_EVENT_TYPE_DISABLED:
			enParkingPlaceStatus = 4;
			break;
		}
		
		char as8PlateNum[32];
#ifdef COMPILEUTF8//编译宏，表示要做转码，车牌号和车牌颜色需要由gb2312转为utf8
		/*转换编码，gb2312 to unicode,若不需要，则不调用*/
		g2u((char*)output->stPlateInfo.as8PlateNum, 
			strlen(output->stPlateInfo.as8PlateNum), 
			as8PlateNum, sizeof(as8PlateNum));
#else
		strcpy(as8PlateNum, output->stPlateInfo.as8PlateNum);
#endif

		char color[32] = {0};
		static const char *colors[] = {"未知", "蓝色", "黄色", "白色", "黑色", "绿色", "绿色", "黄绿色"};
		if ((output->stPlateInfo.ePlateColor >= 0) && (output->stPlateInfo.ePlateColor <= 7))
			strcpy(color, colors[output->stPlateInfo.ePlateColor]);
		
		char cartype[32] = {0};
		static const char *cartypes[] = {"临时", "预定", "固定"};
		if ((output->s32CarType >= 0) && (output->s32CarType <= 2))
			strcpy(cartype, cartypes[output->s32CarType]);

		char eventtype[32] = {0};
		static const char *eventtypes[] = {"无变化", "入车", "出车"};
		if ((output->s32EventType >= 0) && (output->s32EventType <= 2))
		strcpy(eventtype, eventtypes[output->s32EventType]);

		//需要显示在界面的信息
		printf("%d: %s,%s,车位%d,%s,%s,%s,%s,%s\n", ++nPlateNum, pcIP, now_str, i + 1, 
			status[enParkingPlaceStatus], as8PlateNum, color, cartype, eventtype);
	}
	
	savePic(pcIP, pcPicData, u32PicLen);
}

//接收到的rs485串口数据
void OnSerialPort(void *pvParam, 
	const char *pcIP, char *pcData, ICE_U32 u32Len)
{
	static long nRecvPortData = 0;
	ICE_U32 i = 0;

	printf("%ld: %s: recv rs485 SerialPort data Number:%u\nrecv rs485 data: ", ++nRecvPortData, pcIP, u32Len);
	
	for (; i < u32Len; ++i)
		printf("%02hhx ", pcData[i]);//显示
	
	printf("\n");
}

//接收到的rs232数据
void OnSerialPort_rs232(void *pvParam, 
	const char *pcIP, char *pcData, ICE_U32 u32Len)
{
	static long nRecvPortData_rs232 = 0;
	ICE_U32 i = 0;

	printf("%ld: %s: recv rs232 SerialPort data Number:%u\nrecv rs232 data: ", ++nRecvPortData_rs232, pcIP, u32Len);

	for (; i < u32Len; ++i)
		printf("%02hhx ", pcData[i]);//显示
	
	printf("\n");
}

//相机事件处理，现在包括IO状态改变事件和相机连接状态事件
void OnDeviceEvent(void *pvParam, const char *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4)
{
	if (u32EventType == 2)
		printf("IO状态改变，值为：%u%u%u%u\n", u32EventData1,u32EventData2,u32EventData3,u32EventData4);
	else
	{
		if (1 == u32EventType)
			printf("%s当前状态:在线\n", pcIP);
		else if (0 == u32EventType)
			printf("%s当前状态:离线\n", pcIP);
	}
}

#ifdef _WIN32
BOOL WINAPI handle_sig(DWORD msgType)
{
	if ((CTRL_C_EVENT == msgType) || (CTRL_CLOSE_EVENT == msgType))
    {
        g_run = 0;
		Sleep(300);
        return TRUE;
    }

    return FALSE;
}
#else
void handle_sig(int signo)
{
    if (SIGINT == signo)
    	g_run = 0;
}
#endif

//判断相机ip是否不合理
int is_valid_ip(const char *ip, int index) 
{ 
    int section = 0; //每一节的十进制值 
    int dot = 0; //几个点分隔符 
    //int last = -1; //每一节中上一个字符 
    while(*ip)
    { 
        if(*ip == '.')
        { 
        	if (*(ip+1))
        	{
        		if (*(ip+1) == '.')
        			return 0;
        	}
        	else
        		return 0;
            dot++; 
            if(dot > 3)
            { 
                return 0; 
            } 
            if(section >= 0 && section <=255)
            { 
                section = 0; 
            }else{ 
                return 0; 
            } 
        }else if(*ip >= '0' && *ip <= '9')
        { 
            section = section * 10 + *ip - '0'; 
        }else{ 
            return 0; 
        } 
        //last = *ip; 
        ip++; 
    }

    if(section >= 0 && section <=255)
    { 
        if(3 == dot)
        {
        	if ((section == 0 || section == 255) && (0 == index))
        	{
        		return 0;
        	}
        return 1;
      }
    } 
    return 0; 
}

int main(int argc, char* argv[])
{
    static int nCamStatus = OFFLINE;
    int nCamCurrentStatus = OFFLINE;
  
	if (2 != argc)
		return 0;

	if (is_valid_ip(argv[1], 0) != 1)
	{
		printf("Ip is invalid!\n" );
		return 0;
	}
	
#ifdef _WIN32
	SetConsoleCtrlHandler(handle_sig, TRUE);
#else
	signal(SIGINT, handle_sig);
#endif	
	
	ICE_IPCSDK_Init();
	ICE_IPCSDK_LogConfig(1, "./log");

	ICE_IPCSDK_SetDeviceEventCallBack(NULL, OnDeviceEvent, NULL);//设置相机事件回调

	//连接相机
	hSDK = ICE_IPCSDK_Login(argv[1], NULL, NULL, NULL, NULL, NULL, 1);
	if (NULL == hSDK)
	{
		printf("connect failed!\n");
		goto exit;
	}

	ICE_IPCSDK_SetParkingSpaceInfoCallBack(hSDK, SDK_OnParkingSpaceInfo, NULL);
	ICE_IPCSDK_SetSerialPortCallBack(hSDK, OnSerialPort, NULL);//设置RS485串口数据回调
	ICE_IPCSDK_SetSerialPortCallBack_RS232(hSDK, OnSerialPort_rs232, NULL);//设置RS232串口数据回调
   
	while (g_run)
	{
		//调用ICE_IPCSDK_GetStatus获取相机状态
		nCamCurrentStatus = ICE_IPCSDK_GetStatus(hSDK);
		// printf("status:%d\n", nCamCurrentStatus);
		if (nCamCurrentStatus != nCamStatus)
		{
			nCamStatus = nCamCurrentStatus;
			if (OFFLINE == nCamStatus)
				printf("ICE_IPCSDK_GetStatus : offline\r\n");
			else
				printf("ICE_IPCSDK_GetStatus : online\r\n");
		}
		
		struct timeval delay;
		delay.tv_sec = 0;
		delay.tv_usec = 1000 * 1000; 
		select(0, NULL, NULL, NULL, &delay);
	}
	
exit:
	
	if (NULL != hSDK)
	{
		//断开相机
		ICE_IPCSDK_Logout(hSDK);
		hSDK = NULL;
	}
	ICE_IPCSDK_Fini();
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "ice_ipcsdk.h"

int main(int argc, char *argv[])
{
	if (2 != argc)
		return 0;
	
	ICE_IPCSDK_Init();
	ICE_IPCSDK_LogConfig(1, "./log");
	
	ICE_HANDLE hSDK = ICE_IPCSDK_Login(argv[1], NULL, NULL, NULL, NULL, 0);
	if (NULL == hSDK)
	{
		printf("连接相机失败\n");
		return 0;
	}
	
	struct tm *timenow;

	time_t now;	
	time(&now);
	timenow = localtime(&now);
	
	//时间同步
	ICE_U32 result = ICE_IPCSDK_SyncTime(hSDK, (short)timenow->tm_year+1900, timenow->tm_mon+1, timenow->tm_mday, 
		timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
	if(1 != result)
	{
		printf("时间同步失败");
	}
	else
	{
		unsigned short u16Year = 0;
		unsigned char u8Month = 0, u8Day = 0, u8Hour = 0, u8Min = 0, u8Sec = 0;
		
		//获取相机时间
		result = ICE_IPCSDK_GetDevTime(hSDK, &u16Year, &u8Month, &u8Day, &u8Hour, &u8Min, &u8Sec);
		if (1 != result)
		{
			printf("获取相机时间失败");
		}
		else
		{
			time_t tm_now;
			time(&tm_now);
			struct tm tmDev;
			memset(&tmDev, 0, sizeof(tmDev));
			tmDev.tm_year = u16Year-1900;
			tmDev.tm_mon = u8Month-1;
			tmDev.tm_mday = u8Day;
			tmDev.tm_hour = u8Hour;
			tmDev.tm_min = u8Min;
			tmDev.tm_sec = u8Sec; 
			
			time_t tt = mktime(&tmDev);
			
			//比较获取到的相机与本地时间是否一致
			if(tm_now != tt)
			{
				struct tm *tt_now;
				tt_now = localtime(&tm_now);
				printf("相机时间：%d-%d-%d %d:%d:%d\n", u16Year, u8Month, u8Day, u8Hour, u8Min, u8Sec);
				printf("本地时间：%d-%d-%d %d:%d:%d\n", tt_now->tm_year+1900, tt_now->tm_mon+1, tt_now->tm_mday,
					tt_now->tm_hour, tt_now->tm_min, tt_now->tm_sec);				
				result = 0;
			}
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}
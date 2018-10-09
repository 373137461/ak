#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
	
	ICE_U32 u32IsRemoteOld = 0, u32IsRemoteNew, u32IsRemote = 0;
	char ip_old[32], ip_new[32], ip[32];
	
	//备份旧参数
	ICE_U32 result = ICE_IPCSDK_GetRemoteDevState(hSDK, &u32IsRemoteOld, ip_old, NULL, NULL);
	if (1 != result)
	{
		printf("获取远程控灯参数失败\n");
	}
	else if (u32IsRemoteOld > 1)
	{
		printf("是否远程控灯参数无效\n");
		result = 0;
	}
	else
	{
		ICE_U32 addr = inet_addr(ip_old);
		if ((0 == addr) || (INADDR_NONE == addr))
		{
			printf("远程控灯IP参数无效\n");
			result = 0;
		}
	}
	
	if (1 == result)
	{
		srand(time(NULL));
		
		//随机生成新参数
		u32IsRemoteNew = rand() % 2;
		
		struct in_addr addr;
		addr.s_addr = rand();
		strcpy(ip_new, inet_ntoa(addr));
		
		//设置新参数
		result = ICE_IPCSDK_SetRemoteDevState(hSDK, u32IsRemoteNew, ip_new, 0, 0);
		if (1 != result)
		{
			printf("设置远程控灯参数失败\n");
		}
		else
		{
			//获取设置后的参数
			result = ICE_IPCSDK_GetRemoteDevState(hSDK, &u32IsRemote, ip, NULL, NULL);
			
			//恢复旧参数
			ICE_IPCSDK_SetRemoteDevState(hSDK, u32IsRemoteOld, ip_old, 0, 0);
			
			if (1 != result)
			{
				printf("获取远程控灯参数失败\n");
			}
			else if (u32IsRemote > 1)
			{
				printf("是否远程控灯参数无效\n");
				result = 0;
			}
			else
			{
				ICE_U32 addr = inet_addr(ip_old);
				if ((0 == addr) || (INADDR_NONE == addr))
				{
					printf("远程控灯IP参数无效\n");
					result = 0;
				}
				else if ((u32IsRemoteNew != u32IsRemote) || (0 != strcmp(ip_new, ip)))
				{
					printf("设置远程控灯参数未生效\n");
					result = 0;
				}
			}
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

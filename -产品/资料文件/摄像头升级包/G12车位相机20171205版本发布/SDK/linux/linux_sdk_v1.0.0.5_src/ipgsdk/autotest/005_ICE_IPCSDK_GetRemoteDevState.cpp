#include <stdio.h>
#include <stdlib.h>
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
	
	ICE_U32 u32IsRemote = 0;
	char ip[32];
	
	ICE_U32 result = ICE_IPCSDK_GetRemoteDevState(hSDK, &u32IsRemote, ip, NULL, NULL);
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
		ICE_U32 addr = inet_addr(ip);
		if ((0 == addr) || (INADDR_NONE == addr))
		{
			printf("远程控灯IP参数无效\n");
			result = 0;
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

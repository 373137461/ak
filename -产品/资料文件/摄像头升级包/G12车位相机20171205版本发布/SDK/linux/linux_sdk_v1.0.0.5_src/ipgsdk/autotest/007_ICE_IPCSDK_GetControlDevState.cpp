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
	
	ICE_U32 u32IsCtrl = 0;
	char ip[32];
	
	ICE_U32 result = ICE_IPCSDK_GetControlDevState(hSDK, &u32IsCtrl, ip, NULL, NULL);
	if (1 != result)
	{
		printf("获取受控灯参数失败\n");
	}
	else if (u32IsCtrl > 1)
	{
		printf("是否受控参数无效\n");
		result = 0;
	}
	else
	{
		ICE_U32 addr = inet_addr(ip);
		if ((0 == addr) || (INADDR_NONE == addr))
		{
			printf("受控灯IP参数无效\n");
			result = 0;
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

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
	
	ICE_U32 u32SpaceNum = 0;
	ICE_U32 result = ICE_IPCSDK_GetParkingSpaceNum(hSDK, &u32SpaceNum);
	if (1 != result)
	{
		printf("获取车位数失败\n");
	}
	else if ((u32SpaceNum < 1) || (u32SpaceNum > 3))
	{
		printf("车位数无效\n");
		result = 0;
	}
	
	if (1 == result)
	{
		ICE_U32 u32Index = 0;
		for (; u32Index < u32SpaceNum; u32Index++)
		{
			ICE_U32 u32SpaceType = 0;
			
			result = ICE_IPCSDK_GetParkingSpaceType(hSDK, u32Index, &u32SpaceType);
			if (1 != result)
			{
				printf("获取车位类型失败\n");
				break;
			}
			else if (u32SpaceType > 2)
			{
				printf("车位类型为非法值\n");
				result = 0;
				break;
			}
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

#include <stdio.h>
#include <stdlib.h>

#include "ice_ipcsdk.h"

int check_param(ICE_IPG_PLACE_CONFIG_S *param, int width, int height, float rx, float ry)
{
	if ((param->u8ParkingPlaceNum < 1) || (param->u8ParkingPlaceNum > 3))
	{
		printf("车位数无效\n");
		return 0;
	}
	else if ((param->bSpecialPlace < 0) || (param->bSpecialPlace > 1))
	{
		printf("是否特殊车位无效\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < param->u8ParkingPlaceNum; i++)
		{
			if ((param->stPlaceParam[i].isAvalable < 0) || (param->stPlaceParam[i].isAvalable > 1))
			{
				printf("车位是否使能为非法值\n");
				return 0;
			}
			else
			{
				int minx = (int)(20 * rx);
				int miny = (int)(20 * ry);
				
				int tolx = 0, toly = 0;
				if (3 == param->u8ParkingPlaceNum)
				{
					tolx = (int)(30 * rx);
					toly = (int)(30 * ry);
				}
				
				ICE_RECT_S *rect = &param->stPlaceParam[i].stRecRect;
				if ((abs(rect->s16Right - rect->s16Left) < minx) || 
					(abs(rect->s16Bottom - rect->s16Top) < miny) || 
					(rect->s16Left < tolx) || (rect->s16Left >= (width - tolx)) || 
					(rect->s16Top < toly) || (rect->s16Top >= (height - toly)) || 
					(rect->s16Right < tolx) || (rect->s16Right >= (width - tolx)) || 
					(rect->s16Bottom < toly) || (rect->s16Bottom >= (height - toly)))
				{
					printf("识别区域坐标为非法值\n");
					return 0;
				}
			}
		}
	}
	
	return 1;
}

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
	
	ICE_IPG_PARAM_S stParam = {0};
	ICE_U32 result = ICE_IPCSDK_GetIPGParam(hSDK, &stParam);
	if (1 != result)
	{
		printf("获取算法参数失败\n");
	}
	else if ((0 == stParam.s32ImgWidth) || (0 == stParam.s32ImgHeight))
	{
		printf("算法图像宽高无效\n");
		result = 0;
	}
	else
	{
		float rx = (float)1920/stParam.s32ImgWidth;
		float ry = (float)1080/stParam.s32ImgHeight;
		
		ICE_IPG_PLACE_CONFIG_S param = {0};
		ICE_U32 result = ICE_IPCSDK_GetAllParkingSpaceLoops(hSDK, &param, 1920, 1080);
		if (1 != result)
			printf("获取所有车位识别区域失败\n");
		else if (!check_param(&param, 1920, 1080, rx, ry))
			result = 0;
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ice_ipcsdk.h"

int check_param(LightCtlParam *param)
{
	if((param->u8LightEn < 0) || (param->u8LightEn > 3))
	{
		printf("是否亮灯参数无效\n");
		return 0;
	}
	
	if((param->u8Color < 1) || (param->u8Color > 4))
		{
		printf("灯光颜色参数无效\n");
		return 0;
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
	
	LightCtlParam param_old = {0}, param_new = {0}, param = {0};
	
	//get param，备份旧参数
	ICE_U32 result = ICE_IPCSDK_GetLightCtlParam(hSDK, &param_old);
	if (1 != result)
	{
		printf("获取强制控灯参数失败\n");
	}
	else 
		result = check_param(&param_old);
	
	//set param
	if (1 == result)
	{
		//随机生成新参数
		srand(time(NULL));
		param_new.u8LightEn = rand() % 4;
		param_new.u8Color = rand() % 4 + 1;
		
		//设置新参数
		result = ICE_IPCSDK_SetLightCtlParam(hSDK, &param_new);
		if (1 != result)
			printf("配置强制控灯参数失败\n");
		else
		{
			//获取设置的新参数
			result = ICE_IPCSDK_GetLightCtlParam(hSDK, &param);	
			//恢复旧参数
			ICE_IPCSDK_SetLightCtlParam(hSDK, &param_old);
			
			if (1 != result)
				printf("获取强制控灯参数失败\n");
			else
			{
				result = check_param(&param);
				if (1 == result)
				{
					if((param_new.u8LightEn != param.u8LightEn) ||
						(param_new.u8Color != param.u8Color))
						{
							printf("设置强制控灯参数未生效\n");
							result = 0;
						}
				}
			}
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}
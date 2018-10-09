#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ice_ipcsdk.h"

int check_param(http_conf_t *param)
{
	if ((param->http_enable < 0) || (param->http_enable > 1))
	{
		printf("启动http推送参数无效\n");
		return 0;
	}
	
	if ((param->small_pic < 0) || (param->small_pic > 1))
	{
		printf("小图片参数无效\n");
		return 0;
	}
	
	if ((param->big_pic < 0) || (param->big_pic > 1))
	{
		printf("大图片参数无效\n");
		return 0;
	}
	
	if ((param->upload_enable < 0) || (param->upload_enable > 1))
	{
		printf("启动定时上传参数无效\n");
		return 0;
	}
	
	if ((param->upload_interval < 1) || (param->upload_interval > 60))
	{
		printf("定时上传时间参数无效\n");
		return 0;
	}
	
	if ((param->heartbeat_enable < 0) || (param->heartbeat_enable > 1))
	{
		printf("启动心跳功能参数无效\n");
		return 0;
	}
	
	if ((param->heartbeat_interval < 1) || (param->heartbeat_interval > 60))
	{
		printf("心跳上传时间参数无效\n");
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
	
	http_conf_t param_old = {0}, param_new = {0}, param = {0};
	
	//get param,备份旧参数
	ICE_U32 result = ICE_IPCSDK_GetCGIParam(hSDK, &param_old);
	if (1 != result)
		printf("获取http推送参数失败\n");
	else
		result = check_param(&param_old);
	
	if (1 == result)
	{
		//随机生成新参数
		srand(time(NULL));
		param_new.http_enable = rand() % 2;
		param_new.small_pic = rand() % 2;
		param_new.big_pic = rand() % 2;
		param_new.upload_enable = rand() % 2;
		param_new.upload_interval = rand() % 60 + 1;
		param_new.heartbeat_enable = rand() % 2;
		param_new.heartbeat_interval = rand() % 60 + 1;
		sprintf(param_new.http_addr, "http://192.168.66.127");
		
		//设置新参数
		result = ICE_IPCSDK_SetCGIParam(hSDK, &param_new);
		if (1 != result)
			printf("设置http推送参数失败\n");
		else
		{
			//获取设置的新参数
			result = ICE_IPCSDK_GetCGIParam(hSDK, &param);
			//恢复旧参数
			ICE_IPCSDK_SetCGIParam(hSDK, &param_old);
			
			if (1 != result)
				printf("获取http推送参数失败\n");
			else
			{
				result = check_param(&param);
				if (1 == result)
				{
					if ((param_new.http_enable != param.http_enable) ||
						(param_new.small_pic != param.small_pic) ||
						(param_new.big_pic != param.big_pic) ||
						(param_new.upload_enable != param.upload_enable) ||
						(param_new.upload_interval != param.upload_interval) ||
						(param_new.heartbeat_enable != param.heartbeat_enable) ||
						(param_new.heartbeat_interval != param.heartbeat_interval) ||
						(0 != strcmp(param_new.http_addr, param.http_addr)))
					{
						printf("设置http推送参数未生效\n");
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

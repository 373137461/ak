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
	
	ICE_UART_PARAM param = {0};
	ICE_U32 result = ICE_IPCSDK_GetUARTCfg(hSDK, &param);
	if (1 != result)
	{
		printf("获取串口配置失败\n");
	}
	else
	{
		int i = 0;
		for (; i < 2; i++)
		{
			ice_uart *uart = &param.uart_param[i];
			
			if ((uart->uartEn < 0) || (uart->uartEn > 1))
			{
				printf("串口使能参数无效\n");
				break;
			}
			else if ((uart->uartWorkMode < 0) || (uart->uartWorkMode > 6))
			{
				printf("串口模式参数无效\n");
				break;
			}
			else if ((uart->baudRate < 0) || (uart->baudRate > 6))
			{
				printf("波特率参数无效\n");
				break;
			}
			else if ((uart->dataBits < 0) || (uart->dataBits > 3))
			{
				printf("数据位参数无效\n");
				break;
			}
			else if ((uart->parity < 0) || (uart->parity > 4))
			{
				printf("校验位参数无效\n");
				break;
			}
			else if ((uart->stopBits < 0) || (uart->stopBits > 1))
			{
				printf("停止位参数无效\n");
				break;
			}
			else if ((uart->flowControl < 0) || (uart->flowControl > 3))
			{
				printf("流控模式参数无效\n");
				break;
			}
		}
		
		if (i < 2)
			result = 0;
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

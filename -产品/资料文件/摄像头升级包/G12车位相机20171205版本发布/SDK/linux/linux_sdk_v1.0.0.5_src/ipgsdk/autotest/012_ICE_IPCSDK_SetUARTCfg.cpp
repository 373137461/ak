#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ice_ipcsdk.h"

int check_param(ICE_UART_PARAM *param)
{
	int i = 0;
	for (; i < 2; i++)
	{
		ice_uart *uart = &param->uart_param[i];
		
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
		return 0;
	
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
	
	ICE_UART_PARAM param_old = {0}, param_new, param = {0};
	
	//备份旧参数
	ICE_U32 result = ICE_IPCSDK_GetUARTCfg(hSDK, &param_old);
	if (1 != result)
		printf("获取串口配置失败\n");
	else
		result = check_param(&param_old);
	
	if (1 == result)
	{
		srand(time(NULL));
		
		//随机生成新参数
		for (int i = 0; i < 2; i++)
		{
			ice_uart *uart = &param_new.uart_param[i];
			
			uart->uartEn = rand() % 2;
			uart->uartWorkMode = rand() % 7;
			uart->baudRate = rand() % 7;
			//uart->dataBits = rand() % 4;
			uart->dataBits = 3;
			uart->parity = rand() % 5;
			uart->stopBits = rand() % 2;
			uart->flowControl = rand() % 4;
		}
		
		result = ICE_IPCSDK_SetUARTCfg(hSDK, &param_new);
		if (1 != result)
		{
			printf("设置串口配置失败\n");
		}
		else
		{
			//获取设置后的参数
			result = ICE_IPCSDK_GetUARTCfg(hSDK, &param);
			
			//恢复旧参数
			ICE_IPCSDK_SetUARTCfg(hSDK, &param_old);
			
			if (1 != result)
			{
				printf("获取串口配置失败\n");
			}
			else
			{
				result = check_param(&param);
				if (1 == result)
				{
					for (int i = 0; i < 2; i++)
					{
						ice_uart *uart_new = &param_new.uart_param[i];
						ice_uart *uart = &param.uart_param[i];
						
						if ((uart_new->uartEn != uart->uartEn) || 
							(uart_new->uartWorkMode != uart->uartWorkMode) || 
							(uart_new->baudRate != uart->baudRate) || 
							(uart_new->dataBits != uart->dataBits) || 
							(uart_new->parity != uart->parity) || 
							(uart_new->stopBits != uart->stopBits) || 
							(uart_new->flowControl != uart->flowControl))
						{
							printf("设置串口配置未生效\n");
							result = 0;
							break;
						}
					}
				}
			}
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

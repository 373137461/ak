#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

#include "ice_ipcsdk.h"

ICE_HANDLE hSDK = NULL;

void alarm_handler(int signo)
{
	printf("输入串口数据超时\n");
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	exit(0);
}

int parse_hex(const char *text, unsigned char *hex)
{
	int len = strlen(text), count = 0, total = 0;
	for (int i = 0; i < len; i++)
	{
		char data = text[i];
		if (isspace(data))
			continue;

		int value = 0;
		if (isdigit(data))
			value = data - '0';
		else if ((data >= 'a') && (data <= 'f'))
			value = 10 + data - 'a';
		else if ((data >= 'A') && (data <= 'F'))
			value = 10 + data - 'A';
		else
			continue;

		if ((len - 1 == i) && (0 != ((count + 1) % 2)))
		{
			hex[total] = value;
			total++;
		}
		else
		{
			if (0 == (count++ % 2))
			{
				hex[total] = value << 4;
			}
			else
			{
				hex[total] += value;
				total++;
			}
		}
	}
	
	return total;
}

#define TIMEOUT 30

int main(int argc, char *argv[])
{
	if (2 != argc)
		return 0;
	
	signal(SIGALRM, alarm_handler);
	
	ICE_IPCSDK_Init();
	ICE_IPCSDK_LogConfig(1, "./log");
	
	hSDK = ICE_IPCSDK_Login(argv[1], NULL, NULL, NULL, NULL, 0);
	if (NULL == hSDK)
	{
		printf("连接相机失败\n");
		return 0;
	}
	
	srand(time(NULL));
	
	unsigned char data[4];
	for (int i = 0; i < 4; i++)
		data[i] = rand() % 256;
	
	ICE_U32 result = ICE_IPCSDK_TransSerialPort(hSDK, (char*)data, 4);
	if (1 != result)
	{
		printf("485透传失败\n");
	}
	else
	{
		printf("请在%d秒内输入串口工具上收到的4个字节数据：\n", TIMEOUT);
		
		unsigned char hex[128];
		char text[1024];
		
		alarm(TIMEOUT);
		if ((NULL == fgets(text, 1024, stdin)) || (4 != parse_hex(text, hex)))
		{
			printf("输入格式错误\n");
			result = 0;
		}
		else
		{
			int i = 0;
			for (; i < 4; i++)
			{
				if (data[i] != hex[i])
					break;
			}
			
			if (i < 4)
			{
				printf("透传数据错误\n");
				result = 0;
			}
		}
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

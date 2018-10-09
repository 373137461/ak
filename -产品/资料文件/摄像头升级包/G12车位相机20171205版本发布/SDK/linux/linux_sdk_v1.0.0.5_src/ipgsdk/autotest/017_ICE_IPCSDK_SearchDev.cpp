#include <stdio.h>
#include <stdlib.h>

#include "ice_ipcsdk.h"

int main(int argc, char *argv[])
{
	if (2 != argc)
		return 0;
	
	char buf[1024] = {'\0'};
	ICE_IPCSDK_Init();
	ICE_IPCSDK_LogConfig(1, "./log");
	
	ICE_U32 result = 0;
	
	FILE *fp = fopen("./param", "r");
	if (NULL != fp)
	{
		fread(buf, sizeof(char), sizeof(buf), fp);
		char *subpch = strtok(buf, "\n");
		while(subpch != NULL)
		{
			if (strcmp(subpch, "[ethName]") != 0)
				subpch = strtok(NULL, "\n");
			else
			{
				subpch = strtok(NULL, "\n");
				if (subpch == NULL)
				{
					printf("接口名称未配置\n");
					result = 0;
				}
				else
				{
					char szDev[4096];
					memset(szDev, 0, sizeof(szDev));
	
					printf("—————————Begin search dev:\n");
					ICE_IPCSDK_SearchDev(subpch, szDev, 4096, 10000);
					printf("%s————————end search dev:\n",szDev);
					result = 1;
				}
			}
		}
	}
	else
		result = 0;
	
	ICE_IPCSDK_Fini();
	
	return result;
}

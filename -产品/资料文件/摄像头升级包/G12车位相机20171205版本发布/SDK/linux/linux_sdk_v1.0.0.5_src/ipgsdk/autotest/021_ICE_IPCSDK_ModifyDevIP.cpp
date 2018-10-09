#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <ctype.h>
#include <unistd.h>

#include "ice_ipcsdk.h"

int lastIndexOf(char *str1,char *str2)  
{  
    char *p=str1;  
    int i=0,len=strlen(str2);  
    p=strstr(str1,str2);  
    if(p==NULL)return -1;  
    while(p!=NULL)  
    {  
        for(;str1!=p;str1++)i++;  
        p=p+len;  
        p=strstr(p,str2);  
    }  
    return i;  
}  

/*截取src字符串中,从下标为start开始到end-1(end前面)的字符串保存在dest中(下标从0开始)*/  
void substring(char *dest,char *src,int start,int end)  
{  
    int i=start;  
    if(start>strlen(src))
		return;  
    if(end>strlen(src))  
        end=strlen(src);  
    while(i<end)  
    {     
        dest[i-start]=src[i];  
        i++;  
    }  
    dest[i-start]='\0';  
    return;  
}  

int main(int argc, char *argv[])
{
	if (2 != argc)
		return 0;
	
	char buf[1024] = {'\0'};
	ICE_IPCSDK_Init();
	ICE_IPCSDK_LogConfig(1, "./log");
	
	ICE_HANDLE hSDK = ICE_IPCSDK_Login(argv[1], NULL, NULL, NULL, NULL, 0);
	if (NULL == hSDK)
	{
		printf("连接相机失败\n");
		return 0;
	}
	
	ICE_U32 result = 0;
	char szDevIDSrc[16] = {'\0'};
	char szDevID[32] = {'\0'};
	
	result = ICE_IPCSDK_GetDevID(hSDK, szDevIDSrc);
	if (1 != result)
	{
		printf("获取相机mac失败\n");
		return 0;
	}
	
	sprintf(szDevID, "%c%c-%c%c-%c%c-%c%c-%c%c-%c%c", szDevIDSrc[0], szDevIDSrc[1], 
			szDevIDSrc[2], szDevIDSrc[3], szDevIDSrc[4], szDevIDSrc[5], szDevIDSrc[6], 
			szDevIDSrc[7], szDevIDSrc[8], szDevIDSrc[9], szDevIDSrc[10], szDevIDSrc[11]);
	
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
					//随机生成新ip
					srand(time(NULL));
					
					char ip_new[16] = {'\0'};
					int ip_1 = rand() % 255;
					int ip_2 = rand() %253 + 2;
					sprintf(ip_new, "192.168.%d.%d", ip_1, ip_2);
					char gateway[16] = {'\0'};
					sprintf(gateway, "192.168.%d.1", ip_1);
					
					//设置新ip
					char szDev[4096];
					memset(szDev, 0, sizeof(szDev));
					ICE_IPCSDK_ModifyDevIP(subpch, szDevID, ip_new, "255.255.255.0", gateway);
					
					sleep(2);
					//搜索设备
					ICE_IPCSDK_SearchDev(subpch, szDev, 4096, 10000);	
					
					//进行比较
					char *substr = strtok(szDev, "\t");
					while( NULL != substr)
					{
						if (strcasecmp(substr, szDevID) == 0)
						{
							substr = strtok(NULL, "\t");
							if (strcmp(substr, ip_new) != 0)
							{
								printf("修改IP未生效\n");
								result = 0;
							}
							else
							{
								int pos = lastIndexOf(argv[1], ".");
								char szGateway[16] = {'\0'};
								substring(szGateway, argv[1], 0, pos + 1);
								strcat(szGateway, "1");
								ICE_IPCSDK_ModifyDevIP(subpch, szDevID, argv[1], "255.255.255.0", gateway);
								result = 1;
								ICE_IPCSDK_Fini();
								return 1;
							}
							break;
						}
						
						substr = strtok(NULL, "\n");
						if (NULL == substr)
						{
							printf("未搜到到设备\n");
							result = 0;
							break;
						}
						substr = strtok(NULL, "\t");
					}	
					
					printf("未搜索到设备\n");
					result = 0;
				}
			}
		}
	}
	else
		result = 0;
	
	ICE_IPCSDK_Fini();
	
	return result;
}
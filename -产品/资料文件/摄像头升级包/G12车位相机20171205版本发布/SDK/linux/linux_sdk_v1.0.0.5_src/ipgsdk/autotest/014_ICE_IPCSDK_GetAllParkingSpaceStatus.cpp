#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ice_ipcsdk.h"

#define BUF_SIZE (1024 * 1024)

//汉字转数字
char code2index(short code)
{
	switch (code)
	{
	case -3395:
		return 40;

	case -22082:
		return 41;

	case -10805:
		return 42;

	case -14636:
		return 43;

	case -16964:
		return 44;

	case -1347:
		return 45;

	case -13885:
		return 46;

	case -13887:
		return 47;

	case -21828:
		return 48;

	case -9542:
		return 49;

	case -22853:
		return 50;

	case -7211:
		return 51;

	case -4403:
		return 52;

	case -2365:
		return 53;

	case -11336:
		return 54;

	case -19518:
		return 55;

	case -23084:
		return 56;

	case -2634:
		return 57;

	case -6449:
		return 58;

	case -15916:
		return 59;

	case -3911:
		return 60;

	case -4665:
		return 61;

	case -22348:
		return 62;

	case -3143:
		return 63;

	case -10062:
		return 64;

	case -15671:
		return 65;

	case -13640:
		return 66;

	case -7993:
		return 67;

	case -316:
		return 68;

	case -15664:
		return 69;

	case -6701:
		return 70;

	case -834:
		return 71;

	case -23622:
		return 72;

	case -10817:
		return 73;

	case -3383:
		return 74;

	case -20047:
		return 75;

	case -15428:
		return 76;

	case -12348:
		return 77;

	case -7239:
		return 78;

	case -13901:
		return 79;

	case -17216:
		return 80;

	case -20546:
		return 81;

	case -17974:
		return 82;

	case -4927:
		return 83;

	case -22575:
		return 84;

	case -11062:
		return 85;

	case -11591:
		return 86;

	case -9791:
		return 87;

	case -19522:
		return 88;

	case -9288:
		return 89;

	case -15184:
		return 90;

	case -1073:
		return 91;

	case -8271:
		return 92;

	case -20789:
		return 93;

	case -6219:
		return 94;

	case -10559:
		return 95;

	case -22323:
		return 96;

	case -3907:
		return 97;

	case -3645:
		return 98;

	default:
		return 0;
	}
}

//车牌号码转64位整数，返回0表示解析失败
uint64_t plate2int(const char *plate)
{
	int len, i = 0, count = 0;

	uint64_t value;
	char *pval = (char*)&value;

	//检查参数有效性
	if ((NULL == plate) || ('\0' == plate[0]))
		return 0;

	len = strlen(plate);

	//处理武警车牌
	if ('W' == plate[0])
	{
		if ((len > 1) && ('J' == plate[1]))
		{
			pval[count++] = 37;
			i = 2;
		}
	}

	for (; i < len; i++)
	{
		if (plate[i] < 0)
		{
			//汉字
			short code;
			char index;

			//汉字需要两个字节
			if ((i + 1) >= len)
				return 0;

			//汉字转换为数字
			memcpy(&code, plate + i, 2);
			index = code2index(code);
			pval[count++] = index;

			//处理民航车牌
			if (98 == index)
			{
				//民字后面没有足够字节，或者后面不是汉字
				if (((i + 3) >= len) || (plate[i + 2] >= 0))
					return 0;

				//民字后面不是航字
				memcpy(&code, plate + i + 2, 2);
				if (-16966 != code)
					return 0;

				//跳过民字后半部分与航字
				i += 3;
			}
			else
			{
				//跳过其它汉字后半部分
				i += 1;
			}
		}
		else
		{
			//数字0
			if (48 == plate[i])
			{
				pval[count++] = 10;
			}
			//数字1到9
			else if ((plate[i] >= 49) && (plate[i] <= 57))
			{
				pval[count++] = plate[i] - 48;
			}
			//大写字母
			else if ((plate[i] >= 65) && (plate[i] <= 90))
			{
				pval[count++] = plate[i] - 54;
			}
		}
	}

	//民航车牌最少的有6位，自定义车牌有8位，其它车牌一般为7位
	if ((count < 6) || (count > 8))
		return 0;
	
	//空位补0
	if (count < 8)
		memset(pval + count, 0, 8 - count);

	return value;
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

	ICE_U32 result = 1;
	ICE_CHAR *pcPicData = (ICE_CHAR*)malloc(BUF_SIZE);
	if (NULL == pcPicData)
	{
		printf("分配内存失败\n");
		result = 0;
	}
	else
	{
		unsigned char jpghdr[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46};
		ICE_U32 u32PicLen = 0;
		
		ICE_PARKING_SPACE_RESULT_S stResult = {0};
		result = ICE_IPCSDK_GetAllParkingSpaceStatus(hSDK, &stResult, 
			pcPicData, BUF_SIZE, &u32PicLen, NULL, NULL);
		
		if (1 != result)
		{
			printf("获取所有车位状态失败\n");
		}
		else if ((stResult.u8ParkingPlaceNum < 1) || (stResult.u8ParkingPlaceNum > 3))
		{
			printf("车位数无效\n");
			result = 0;
		}
		else if ((0 == u32PicLen) || (0 != memcmp(pcPicData, jpghdr, sizeof(jpghdr))))
		{
			printf("抓拍图无效\n");
			result = 0;
		}
		else
		{
			ICE_U32 u32Index = 0;
			for (; u32Index < stResult.u8ParkingPlaceNum; u32Index++)
			{
				ICE_PARKING_SPACE_OUTPUT_S *output = &stResult.astOutput[u32Index];
				
				if ((ICE_IPG_EVENT_TYPE_NOON != output->enParkingPlaceStatus) && 
					(ICE_IPG_EVENT_TYPE_HAVE_CAR != output->enParkingPlaceStatus) && 
					(ICE_IPG_EVENT_TYPE_EMPTY_PLACE != output->enParkingPlaceStatus) && 
					(ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE != output->enParkingPlaceStatus) && 
					(ICE_IPG_EVENT_TYPE_DISABLED != output->enParkingPlaceStatus))
				{
					printf("车位状态无效\n");
					result = 0;
					break;
				}
				else if ((output->stPlateInfo.flConfidence > 0) && (0 == plate2int(output->stPlateInfo.as8PlateNum)))
				{
					printf("车牌号码无效\n");
					result = 0;
					break;
				}
				else if ((output->stPlateInfo.ePlateColor < 0) || (output->stPlateInfo.ePlateColor > 7))
				{
					printf("车牌颜色无效\n");
					result = 0;
					break;
				}
				else if ((output->s32CarType < 0) || (output->s32CarType > 2))
				{
					printf("车位类型无效\n");
					result = 0;
					break;
				}
				else if ((output->s32EventType < 0) || (output->s32EventType > 2))
				{
					printf("事件类型无效\n");
					result = 0;
					break;
				}
			}
		}
		
		free(pcPicData);
	}
	
	ICE_IPCSDK_Logout(hSDK);
	ICE_IPCSDK_Fini();
	return result;
}

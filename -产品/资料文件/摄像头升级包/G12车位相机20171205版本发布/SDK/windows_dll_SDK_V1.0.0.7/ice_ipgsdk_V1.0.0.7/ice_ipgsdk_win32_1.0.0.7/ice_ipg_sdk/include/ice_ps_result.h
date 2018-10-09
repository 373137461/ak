#ifndef _ICE_PS_RESULT_H_
#define _ICE_PS_RESULT_H_
#include "ice_ipg_result.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct 
{
	ICE_S8				as8PlateNum[ICE_VLPR_PLATE_BUFLEN];			//!<  车牌号			size = 1*16
	ICE_RECT_S			stPlateRect;								//!<  车牌矩形框；		size = 2*4
	ICE_FLOAT			flConfidence;								//!<  车牌置信度		size = 4
	ICE_S32				s32PlateIntensity;							//!<  车牌亮度			size = 4
	ICE_PLATECOLOR_E	ePlateColor;								//!<  车牌颜色			size = 4
	ICE_PLATETYPE_E		ePlateType;									//!<  车牌类型			size = 4
	ICE_S8				astReserve[48];								//!<  预留参数		size = 48
}ICE_PARKING_SPACE_VLPR_OUTPUT_S;	//size = 88
typedef struct
{
	ICE_IPG_PARKING_SPACE_STATUS_E				enParkingPlaceStatus;			//!<  车位状态		size = 4
	ICE_PARKING_SPACE_VLPR_OUTPUT_S				stPlateInfo;					//!<  车牌信息		size = 88
	ICE_S32										s32CarType;						//!<  车位类型 0 临时 1 预定 2 固定 	size = 4
	ICE_S32										s32EventType;					//!<  事件类型 0 入车 1 出车			size = 4
	ICE_S32										s32Reserved[30];				//!<  保留 		size = 4*32
}ICE_PARKING_SPACE_OUTPUT_S;		//size = 100 + 128 = 228
#define ICE_MAX_PARKING_SPACE_NUM 6
typedef struct
{
	ICE_U8										u8ParkingPlaceNum;				//!< 相机检测车位数  	size = 1
	ICE_PARKING_SPACE_OUTPUT_S					astOutput[ICE_MAX_PARKING_SPACE_NUM];//!< 车位输出结果 		size = 6*228 = 1368
	ICE_S32										s32PicDataLen;					//!<图片长度			size = 4
	ICE_S32										s32Reserved[16];				//!< 保留				size = 4*16
}ICE_PARKING_SPACE_RESULT_S;		//size = 1368 + 69 = 1437

#ifdef __cplusplus
}
#endif


#endif // __ICE_PS_RESULT_H_

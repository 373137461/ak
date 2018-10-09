/*! \file ice_ipg_result.h
\brief ice_ipg_result.h document.
*/
#ifndef __ICE_IPG_RESULT_H__
#define __ICE_IPG_RESULT_H__

#include "ice_base_type.h"
#include "ice_ipg_config.h"
#include "ice_vlpr_result.h"

#ifdef __cplusplus
extern "C"
{
#endif

// typedef enum 
// {
// 	ICE_IPG_PICTURE_NOON 						= 0x0000,				//!<  无
// 	ICE_IPG_PICTURE_IGNORE						= 0x0001,				//!<  忽略图片
// 	ICE_IPG_PICTURE_CACHE						= 0x0002,				//!<  缓存图片
// 	ICE_IPG_PICTURE_SEND						= 0x0003,				//!<  发送图片
// }ICE_IPG_PICTURE_STATUS_E;

typedef enum 
{
	ICE_IPG_EVENT_TYPE_NOON 							= 0x0000,				//!<  无
	ICE_IPG_EVENT_TYPE_HAVE_CAR							= 0x0001,				//!<  车位有车
	ICE_IPG_EVENT_TYPE_EMPTY_PLACE						= 0x0002,				//!<  空车位
	ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE				= 0x0004,				//!<  单车占多车位
	ICE_IPG_EVENT_TYPE_DISABLED							= 0x0008,				//!<  车位禁用
}ICE_IPG_PARKING_SPACE_STATUS_E;

// typedef enum 
// {
// 	ICE_IPG_SPACE_LOCATION_NOON 							= 0x0000,				//!<  无
// 	ICE_IPG_SPACE_LOCATION_LEFTDOWN							= 0x0001,				//!<  左下车位
// 	ICE_IPG_SPACE_LOCATION_MIDDOWN							= 0x0002,				//!<  中下车位
// 	ICE_IPG_SPACE_LOCATION_RIGHTDOWN						= 0x0003,				//!<  右下车位
// 	ICE_IPG_SPACE_LOCATION_LEFTUP							= 0x0004,				//!<  左上车位
// 	ICE_IPG_SPACE_LOCATION_MIDUP							= 0x0005,				//!<  中上车位
// 	ICE_IPG_SPACE_LOCATION_RIGHTUP							= 0x0006,				//!<  右上车位
// }ICE_IPG_SPACE_LOCATION_E;

typedef struct
{
	ICE_IPG_PARKING_SPACE_STATUS_E				enParkingPlaceStatus;			//!<  车位状态
	ICE_VLPR_OUTPUT_S							stPlateInfo;					//!<  车牌信息
	//ICE_S8	 									s8VehicleType;					//!<  车辆类型
	ICE_S32										s32Reserved[16];				//!<  保留 
}ICE_IPG_OUTPUT_S;

typedef struct
{
	ICE_U8										u8ParkingPlaceNum;				//!< 相机检测车位数  
	ICE_IPG_OUTPUT_S							astOutput[ICE_MAX_PLACE_NUM];	//!< 车位输出结果 
	ICE_S8										*ps8DebugInfo;//debug				//!< 调试信息指针；
	ICE_S32										s32PicDataLen;				//!<图片长度
	ICE_S32										s32Reserved[15];				//!< 保留
}ICE_IPG_RESULT_S;

#ifdef __cplusplus
}
#endif

#endif  // __ICE_IPG_RESULT_H__

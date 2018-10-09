/*! \file ice_ipg_config.h
\brief ice_ipg_config.h document.
*/
#ifndef __ICE_IPG_CONFIG_H__
#define __ICE_IPG_CONFIG_H__

#include "ice_base_type.h"
#include "ice_vlpr_result.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define ICE_IPG_MAX_PARKING_PLACE_NUM	   8					//!< 最大车位数目
#define ICE_MAX_PLACE_NUM	ICE_IPG_MAX_PARKING_PLACE_NUM

// 
typedef struct
{
	ICE_RECT_S			stRecRect;								//!< 车位区域
	ICE_BOOL			isAvalable;								//!< 车位使能/禁用标志位
	ICE_S32				u32Reserved[8];							//!< 保留 
}ICE_IPG_PLACE_PARAM_S;


typedef struct
{
	ICE_U8					u8ParkingPlaceNum;					//!<  车位数目
	ICE_BOOL				bSpecialPlace;						//!<  是否是特殊车位，如开启，则需单位配置	
	ICE_IPG_PLACE_PARAM_S	stPlaceParam[ICE_MAX_PLACE_NUM];	//!<  车位参数
	ICE_S32 u32Reserved[64];									//!<  保留 
}ICE_IPG_PLACE_CONFIG_S;


typedef struct
//! 车牌参数定义
{
	ICE_S32					s32MinPlateWidth;						//!<  最小车牌宽度 									   
	ICE_S32					s32MaxPlateWidth;						//!<  最大车牌宽度 									 
	ICE_VLPR_CHARTYPE_E		ePriorCity;					 			//!<  优先城市 										 
	ICE_S32					s32PlateConfidThrld;					//!<  车牌可信度阈值（0-28），默认：10 

	//Jason: 新增下面三个配置参数
	ICE_S32					s32PlateTypeSp;							//!<  支持车牌类型     0默认全部开启；
	//ICE_S32					s32CarColorOn;							//!<  车身颜色启用； 0不启用
	//ICE_S32					s32PriorCityType;						//!<  优先城市类型
	ICE_S32					u32Reserved[13];                        //!<  保留     									
}ICE_IPG_PLATE_CONFIG_S;


typedef struct
{
	ICE_S32					s32ImgWidth;							 //!<  相机图像水平分辨率
	ICE_S32					s32ImgHeight;							 //!<  相机图像竖直分辨率
	ICE_S32					s32QcifWidth;							 //!<  相机图像水平分辨率
	ICE_S32					s32QcifHeight;							 //!<  相机图像竖直分辨率

	ICE_IPG_PLACE_CONFIG_S	stCameraPlace;							 //!<  车位配置参数
	ICE_IPG_PLATE_CONFIG_S  stPlateParam;							 //!<  车牌配置参数 
	ICE_S32					s32PlateProcessFrameNum;				 //!<  每个周期内车牌车牌识别的最大执行次数
	ICE_S32					s32CarDetFrameNum;						 //!<  每个周期内车辆检测次数
	ICE_S32					s32CarDetThrld;						 	 //!<  每个周期内检测到车辆次数的阈值
	ICE_S32					s32CarDetSense;						 	 //!<  车辆检测灵敏度（车检函数内部使用）
	ICE_S32					s32HaveCarAdd;						 	 //!<  有车累加值
	ICE_S32					s32NoCarReduce;						 	 //!<  无车减少值
	ICE_S32					s32WaitFrames;						 	 //!<  等待帧数;为等待过程帧数；
	ICE_S32					as32Reserved[32]; 						 //!<  保留
}ICE_IPG_PARAM_S;

typedef struct
{
	ICE_S32					as32Reserved[64]; 						 //!<  保留
}ICE_IPG_PROC_PARAM_S;

#ifdef __cplusplus
}
#endif


#endif // __ICE_IPG_CONFIG_H__


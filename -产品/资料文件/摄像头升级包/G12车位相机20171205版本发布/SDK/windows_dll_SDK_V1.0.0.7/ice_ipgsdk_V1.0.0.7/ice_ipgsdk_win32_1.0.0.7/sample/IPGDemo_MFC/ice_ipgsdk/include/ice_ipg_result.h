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
// 	ICE_IPG_PICTURE_NOON 						= 0x0000,				//!<  ��
// 	ICE_IPG_PICTURE_IGNORE						= 0x0001,				//!<  ����ͼƬ
// 	ICE_IPG_PICTURE_CACHE						= 0x0002,				//!<  ����ͼƬ
// 	ICE_IPG_PICTURE_SEND						= 0x0003,				//!<  ����ͼƬ
// }ICE_IPG_PICTURE_STATUS_E;

typedef enum 
{
	ICE_IPG_EVENT_TYPE_NOON 							= 0x0000,				//!<  ��
	ICE_IPG_EVENT_TYPE_HAVE_CAR							= 0x0001,				//!<  ��λ�г�
	ICE_IPG_EVENT_TYPE_EMPTY_PLACE						= 0x0002,				//!<  �ճ�λ
	ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE				= 0x0004,				//!<  ����ռ�೵λ
	ICE_IPG_EVENT_TYPE_DISABLED							= 0x0008,				//!<  ��λ����
}ICE_IPG_PARKING_SPACE_STATUS_E;

// typedef enum 
// {
// 	ICE_IPG_SPACE_LOCATION_NOON 							= 0x0000,				//!<  ��
// 	ICE_IPG_SPACE_LOCATION_LEFTDOWN							= 0x0001,				//!<  ���³�λ
// 	ICE_IPG_SPACE_LOCATION_MIDDOWN							= 0x0002,				//!<  ���³�λ
// 	ICE_IPG_SPACE_LOCATION_RIGHTDOWN						= 0x0003,				//!<  ���³�λ
// 	ICE_IPG_SPACE_LOCATION_LEFTUP							= 0x0004,				//!<  ���ϳ�λ
// 	ICE_IPG_SPACE_LOCATION_MIDUP							= 0x0005,				//!<  ���ϳ�λ
// 	ICE_IPG_SPACE_LOCATION_RIGHTUP							= 0x0006,				//!<  ���ϳ�λ
// }ICE_IPG_SPACE_LOCATION_E;

typedef struct
{
	ICE_IPG_PARKING_SPACE_STATUS_E				enParkingPlaceStatus;			//!<  ��λ״̬
	ICE_VLPR_OUTPUT_S							stPlateInfo;					//!<  ������Ϣ
	//ICE_S8	 									s8VehicleType;					//!<  ��������
	ICE_S32										s32Reserved[16];				//!<  ���� 
}ICE_IPG_OUTPUT_S;

typedef struct
{
	ICE_U8										u8ParkingPlaceNum;				//!< �����⳵λ��  
	ICE_IPG_OUTPUT_S							astOutput[ICE_MAX_PLACE_NUM];	//!< ��λ������ 
	ICE_S8										*ps8DebugInfo;//debug				//!< ������Ϣָ�룻
	ICE_S32										s32PicDataLen;				//!<ͼƬ����
	ICE_S32										s32Reserved[15];				//!< ����
}ICE_IPG_RESULT_S;

#ifdef __cplusplus
}
#endif

#endif  // __ICE_IPG_RESULT_H__

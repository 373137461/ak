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


#define ICE_IPG_MAX_PARKING_PLACE_NUM	   8					//!< ���λ��Ŀ
#define ICE_MAX_PLACE_NUM	ICE_IPG_MAX_PARKING_PLACE_NUM

// 
typedef struct
{
	ICE_RECT_S			stRecRect;								//!< ��λ����
	ICE_BOOL			isAvalable;								//!< ��λʹ��/���ñ�־λ
	ICE_S32				u32Reserved[8];							//!< ���� 
}ICE_IPG_PLACE_PARAM_S;


typedef struct
{
	ICE_U8					u8ParkingPlaceNum;					//!<  ��λ��Ŀ
	ICE_BOOL				bSpecialPlace;						//!<  �Ƿ������⳵λ���翪�������赥λ����	
	ICE_IPG_PLACE_PARAM_S	stPlaceParam[ICE_MAX_PLACE_NUM];	//!<  ��λ����
	ICE_S32 u32Reserved[64];									//!<  ���� 
}ICE_IPG_PLACE_CONFIG_S;


typedef struct
//! ���Ʋ�������
{
	ICE_S32					s32MinPlateWidth;						//!<  ��С���ƿ�� 									   
	ICE_S32					s32MaxPlateWidth;						//!<  ����ƿ�� 									 
	ICE_VLPR_CHARTYPE_E		ePriorCity;					 			//!<  ���ȳ��� 										 
	ICE_S32					s32PlateConfidThrld;					//!<  ���ƿ��Ŷ���ֵ��0-28����Ĭ�ϣ�10 

	//Jason: ���������������ò���
	ICE_S32					s32PlateTypeSp;							//!<  ֧�ֳ�������     0Ĭ��ȫ��������
	//ICE_S32					s32CarColorOn;							//!<  ������ɫ���ã� 0������
	//ICE_S32					s32PriorCityType;						//!<  ���ȳ�������
	ICE_S32					u32Reserved[13];                        //!<  ����     									
}ICE_IPG_PLATE_CONFIG_S;


typedef struct
{
	ICE_S32					s32ImgWidth;							 //!<  ���ͼ��ˮƽ�ֱ���
	ICE_S32					s32ImgHeight;							 //!<  ���ͼ����ֱ�ֱ���
	ICE_S32					s32QcifWidth;							 //!<  ���ͼ��ˮƽ�ֱ���
	ICE_S32					s32QcifHeight;							 //!<  ���ͼ����ֱ�ֱ���

	ICE_IPG_PLACE_CONFIG_S	stCameraPlace;							 //!<  ��λ���ò���
	ICE_IPG_PLATE_CONFIG_S  stPlateParam;							 //!<  �������ò��� 
	ICE_S32					s32PlateProcessFrameNum;				 //!<  ÿ�������ڳ��Ƴ���ʶ������ִ�д���
	ICE_S32					s32CarDetFrameNum;						 //!<  ÿ�������ڳ���������
	ICE_S32					s32CarDetThrld;						 	 //!<  ÿ�������ڼ�⵽������������ֵ
	ICE_S32					s32CarDetSense;						 	 //!<  ������������ȣ����캯���ڲ�ʹ�ã�
	ICE_S32					s32HaveCarAdd;						 	 //!<  �г��ۼ�ֵ
	ICE_S32					s32NoCarReduce;						 	 //!<  �޳�����ֵ
	ICE_S32					s32WaitFrames;						 	 //!<  �ȴ�֡��;Ϊ�ȴ�����֡����
	ICE_S32					as32Reserved[32]; 						 //!<  ����
}ICE_IPG_PARAM_S;

typedef struct
{
	ICE_S32					as32Reserved[64]; 						 //!<  ����
}ICE_IPG_PROC_PARAM_S;

#ifdef __cplusplus
}
#endif


#endif // __ICE_IPG_CONFIG_H__


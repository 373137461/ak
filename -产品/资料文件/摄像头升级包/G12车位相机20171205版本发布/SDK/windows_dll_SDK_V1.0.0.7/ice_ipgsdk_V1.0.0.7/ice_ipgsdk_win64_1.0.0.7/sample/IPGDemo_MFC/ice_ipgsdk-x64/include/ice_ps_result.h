#ifndef _ICE_PS_RESULT_H_
#define _ICE_PS_RESULT_H_
#include "ice_ipg_result.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct 
{
	ICE_S8				as8PlateNum[ICE_VLPR_PLATE_BUFLEN];			//!<  ���ƺ�			size = 1*16
	ICE_RECT_S			stPlateRect;								//!<  ���ƾ��ο�		size = 2*4
	ICE_FLOAT			flConfidence;								//!<  �������Ŷ�		size = 4
	ICE_S32				s32PlateIntensity;							//!<  ��������			size = 4
	ICE_PLATECOLOR_E	ePlateColor;								//!<  ������ɫ			size = 4
	ICE_PLATETYPE_E		ePlateType;									//!<  ��������			size = 4
	ICE_S8				astReserve[48];								//!<  Ԥ������		size = 48
}ICE_PARKING_SPACE_VLPR_OUTPUT_S;	//size = 88
typedef struct
{
	ICE_IPG_PARKING_SPACE_STATUS_E				enParkingPlaceStatus;			//!<  ��λ״̬		size = 4
	ICE_PARKING_SPACE_VLPR_OUTPUT_S				stPlateInfo;					//!<  ������Ϣ		size = 88
	ICE_S32										s32CarType;						//!<  ��λ���� 0 ��ʱ 1 Ԥ�� 2 �̶� 	size = 4
	ICE_S32										s32EventType;					//!<  �¼����� 0 �복 1 ����			size = 4
	ICE_S32										s32Reserved[30];				//!<  ���� 		size = 4*32
}ICE_PARKING_SPACE_OUTPUT_S;		//size = 100 + 128 = 228
#define ICE_MAX_PARKING_SPACE_NUM 6
typedef struct
{
	ICE_U8										u8ParkingPlaceNum;				//!< �����⳵λ��  	size = 1
	ICE_PARKING_SPACE_OUTPUT_S					astOutput[ICE_MAX_PARKING_SPACE_NUM];//!< ��λ������ 		size = 6*228 = 1368
	ICE_S32										s32PicDataLen;					//!<ͼƬ����			size = 4
	ICE_S32										s32Reserved[16];				//!< ����				size = 4*16
}ICE_PARKING_SPACE_RESULT_S;		//size = 1368 + 69 = 1437

#ifdef __cplusplus
}
#endif


#endif // __ICE_PS_RESULT_H_

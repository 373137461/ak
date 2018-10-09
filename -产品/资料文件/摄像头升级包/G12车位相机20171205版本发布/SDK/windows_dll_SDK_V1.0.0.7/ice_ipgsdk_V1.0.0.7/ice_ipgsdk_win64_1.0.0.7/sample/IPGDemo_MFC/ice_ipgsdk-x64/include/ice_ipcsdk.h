#ifndef _ICE_IPCSDK__H_
#define _ICE_IPCSDK__H_

#include "ice_com_type.h"
#include "ice_base_type.h"
//#include "ice_vd_config.h"
//#include "ice_vdc_config.h"
#include "ice_vlpr_result.h"
#include "ice_ps_result.h"
#include <time.h>

#ifdef _WIN32
#ifdef ICE_IPCSDK_EXPORTS
#define ICE_IPCSDK_API __declspec(dllexport)
#else
#define ICE_IPCSDK_API __declspec(dllimport)
#endif
#else
#define ICE_IPCSDK_API
#define __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PAYLOAD_TYPE_JPEG  26	//ץ��ͼƬ
#define PAYLOAD_TYPE_H264  96	//h264����
#define PAYLOAD_TYPE_DTCA  100	//�ܽ���
#define PAYLOAD_TYPE_VLPR  101	//���ƽ��
#define PAYLOAD_TYPE_TCNT  102	//�������
#define PAYLOAD_TYPE_HCNT  103	//�������
#define PAYLOAD_TYPE_IPG   104	//��λ���
#define PAYLOAD_TYPE_VDM   105	//�ƶ�����

/**
* @brief  ����¼�ö������
*/
typedef enum
{
	ICE_DEVICE_OFFLINE,		//����
	ICE_DEVICE_ONLINE,		//����
	ICE_DEVICE_IO_CHANGED			//IO״̬�ı�
} ICE_DEVICE_EVENT_TYPE;

/**
*  @brief  ȫ�ֳ�ʼ��
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_Init();
/**
*  @brief  ȫ���ͷ�
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_Fini();

#ifdef _WIN32
/**
*  @brief  ��ʼ��Ƶ
*  @param  [in] hSDK          �������ʱ���ص�sdk���
*  @param  [in] u8MainStream  �Ƿ�Ϊ��������1Ϊ��������0Ϊ������
*  @param  [in] hWnd          ��Ƶ���Ŵ��ھ��
*  @return 1 ������Ƶ���ɹ� 0 ������Ƶ��ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_StartStream(ICE_HANDLE hSDK, 
	ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  ������Ƶ
*  @param  [in] hSDK          �������ʱ���ص�sdk���
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_StopStream(ICE_HANDLE hSDK);
#endif

/**
*  @brief  ��ȡ���״̬
*  @param  [IN] hSDK      �������ʱ���ص�sdk���
*  @return 0 ���� 1 ���� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK);

/**
*  @brief  ͸�����ڻص�����
*  @param  [OUT] pvParam      ���ڻص��������������ֲ�ͬ���ڣ�ICE_IPCSDK_SetSerialPortCallBack��������һ��������
*  @param  [OUT] pcIP         ���ip
*  @param  [OUT] pcData       ��������
*  @param  [OUT] u32Len       ���ݳ���
*/
typedef void (__stdcall *ICE_IPCSDK_OnSerialPort)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ����͸������
*  @param  [IN] hSDK                   �������ʱ���ص�sdk���
*  @param  [IN] pfOnSerialPort         ICE_IPCSDK_OnSerialPort�ص�����
*  @param  [IN] pvSerialPortParam      ���ڻص��������������ֲ�ͬ����
*  @return void 
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  ����͸������(rs485)����
*  @param  [IN] hSDK      �������ʱ���ص�sdk���
*  @param  [IN] pcData    ��������
*  @param  [IN] u32Len    ���ݳ���
*  @return 0 ����ʧ�� 1 ���ͳɹ� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TransSerialPort(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ͸�����ڽ����¼��ص��ӿ�(rs232)
*  @param  [out] pvParam      ���ڻص��������������ֲ�ͬ���ڣ�ICE_IPCSDK_SetSerialPortCallBack_RS232��������һ��������
*  @param  [out] pcIP         ���ip
*  @param  [out] pcData       ��������
*  @param  [out] u32Len       ���ݳ���
*/
typedef void (__stdcall *ICE_IPCSDK_OnSerialPort_RS232)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ����͸�����ڽ����¼�(rs232)
*  @param  [in] hSDK                   �������ʱ���ص�sdk���
*  @param  [in] pfOnSerialPort         ICE_IPCSDK_OnSerialPort_RS232�ص�����
*  @param  [in] pvSerialPortParam      ���ڻص��������������ֲ�ͬ����
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack_RS232(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  ����͸������(rs232)����
*  @param  [in] hSDK      �������ʱ���ص�sdk���
*  @param  [in] pcData    ��������
*  @param  [in] u32Len    ���ݳ���
*  @return 0 ����ʧ�� 1 ���ͳɹ� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TransSerialPort_RS232(ICE_HANDLE hSDK, 
	ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ͨ���ûص�������ȡ���������״̬
*  @param  [OUT] pvParam             ������ӻص�����, �������ֲ�ͬ��������¼�(ICE_IPCSDK_SetDeviceEventCallBack��������һ������)
*  @param  [OUT] pcIP                ���ip
*  @param  [OUT] u32EventType        �¼����� 0������ 1������
*  @param  [OUT] u32EventData1       Ԥ������1 
*  @param  [OUT] u32EventData2       Ԥ������2
*  @param  [OUT] u32EventData3       Ԥ������3
*  @param  [OUT] u32EventData4       Ԥ������4
*/
typedef void (__stdcall *ICE_IPCSDK_OnDeviceEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4);

/**
*  @brief  �����������״̬�ص��¼�
*  @param  [IN] hSDK                         �������ʱ���ص�sdk���
*  @param  [IN] pfOnDeviceEvent              ������ӻص�
*  @param  [IN] pvDeviceEventParam           ������ӻص�����,�������ֲ�ͬ��������¼�
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetDeviceEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, void *pvDeviceEventParam);

/**
*  @brief  ��־����
*  @param  [IN] openLog     �Ƿ�����־
*  @param  [IN] logPath     ��־·����Ĭ��ΪD:\
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_LogConfig(int openLog, const char *logPath);

/**
*  @brief  �������
*  @param  [in]pcIP ���ip 
*  @param  [in]pcReserve1 Ԥ������1
*  @param  [in]pcReserve2 Ԥ������2
*  @param  [in]nReserve1  Ԥ������3
*  @param  [in]nReserve2  Ԥ������4
*  @param  [in]nReserve3  Ԥ������5
*  @param  [in]u32SyncTime  �Ƿ����ʱ��ͬ����Ĭ�Ͻ���ͬ��
*  @return sdk�����ʧ��ʱ����NULL
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_Login(const ICE_CHAR *pcIP, ICE_CHAR *pcReserve1, ICE_CHAR *pcReserve2, 
	ICE_U32 *nReserve1, ICE_U32 *nReserve2, ICE_U32 *nReserve3, ICE_U32 u32SyncTime = 1);

/**
*  @brief  �Ͽ�����
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_Logout(ICE_HANDLE hSDK);

/**
*  @brief  ��ȡ����µ�����λ�ĵ�ǰ״̬
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32SpaceCode ��λ���
*  @param  [out]u32SpaceNum ��λ����
*  @param  [out]pstResult ��λ�ĵ�ǰ״̬
*  @param  [out]pcPicData ��λͼƬ
*  @param  [in]u32Size ��������С
*  @param  [out]pu32PicLen ͼƬʵ�ʳ���
*  @param  [out]pcReserve Ԥ������1
*  @param  [in]u32Reserve Ԥ������2
*  @param  [out]pu32Reserve Ԥ������3
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetSingleParkingSpaceStatus(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32SpaceNum,
	ICE_PARKING_SPACE_OUTPUT_S *pstResult, ICE_CHAR *pcPicData, ICE_U32 u32Size, ICE_U32* pu32PicLen, 
	ICE_CHAR *pcReserve, ICE_U32 u32Reserve, ICE_U32 *pu32Reserve);

/**
*  @brief  ��ȡ��������г�λ�ĵ�ǰ״̬
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [out]pstResult ��λ�ĵ�ǰ״̬
*  @param  [out]pcPicData ��λͼƬ
*  @param  [in]u32Size ��������С
*  @param  [out]pu32PicLen ͼƬʵ�ʳ���
*  @param  [out]pvReserve Ԥ������1
*  @param  [in]u32PicSize Ԥ������2
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAllParkingSpaceStatus(ICE_HANDLE hSDK, ICE_PARKING_SPACE_RESULT_S *pstResult, 
	ICE_CHAR *pcPicData,ICE_U32 u32Size, ICE_U32* pu32PicLen, void *pvReserve, ICE_U32* u32Reserve);

/**
*  @brief  ���ó�λ����
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32SpaceCode ��λ���
*  @param  [in]u32SpaceType ��λ���ͣ�0����ʱ 1��Ԥ����2�̶���
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetParkingSpaceType(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 u32SpaceType);

/**
*  @brief  ��ȡ��λ����
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32SpaceCode ��λ���
*  @param  [out]u32SpaceType ��λ���ͣ�0����ʱ 1��Ԥ����2�̶���
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetParkingSpaceType(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32SpaceType);

/**
*  @brief  ���ý���/ʹ�ܳ�λ
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32SpaceCode ��λ���
*  @param  [in]u32Enable ��λʹ�ܣ�0������ 1��ʹ�ܣ�
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetEnableParkingSpace(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 u32Enable);

/**
*  @brief  ��ȡ����/ʹ�ܳ�λ
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32SpaceCode ��λ���
*  @param  [out]u32Enable ��λʹ�ܣ�0������ 1��ʹ�ܣ�
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetEnableParkingSpace(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32Enable);

/**
*  @brief  ��ȡԶ�̿صƲ���
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [out]u32IsRemote �Ƿ�Զ�̿���������� 0�����ƣ�1����
*  @param  [out]pcRemoteIp �Ƿ�Զ�̿����������
*  @param  [out]u32Reserve1 Ԥ������1
*  @param  [out]u32Reserve2 Ԥ������2
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetRemoteDevState(ICE_HANDLE hSDK, ICE_U32 *u32IsRemote, ICE_CHAR *pcRemoteIp, 
										ICE_U32 *u32Reserve1, ICE_U32 *u32Reserve2);

/**
*  @brief  ����Զ�̿صƲ���
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32IsRemote �Ƿ�Զ�̿���������� 0�����ƣ�1����
*  @param  [in]pcRemoteIp �Ƿ�Զ�̿����������
*  @param  [in]u32Reserve1 Ԥ������1
*  @param  [in]u32Reserve2 Ԥ������2
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetRemoteDevState(ICE_HANDLE hSDK, ICE_U32 u32IsRemote, const ICE_CHAR *pcRemoteIp,
										ICE_U32 u32Reserve1, ICE_U32 u32Reserve2);

/**
*  @brief  ��ȡ�ܿصƲ���
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [out]u32IsControlled �Ƿ�������������Զ�̿��� 0�����ܣ�1����
*  @param  [out]pcControlIp �Ƿ���Ʊ�������������ip
*  @param  [out]u32Reserve1 Ԥ������1
*  @param  [out]u32Reserve2 Ԥ������2
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetControlDevState(ICE_HANDLE hSDK, ICE_U32 *u32IsControlled, ICE_CHAR *pcControlIp,
										ICE_U32 *u32Reserve1, ICE_U32 *u32Reserve2);
/**
*  @brief  �����ܿصƲ���
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]u32IsControlled �Ƿ�������������Զ�̿��� 0�����ܣ�1����
*  @param  [in]pcControlIp �Ƿ���Ʊ�������������ip
*  @param  [in]u32Reserve1 Ԥ������1
*  @param  [in]u32Reserve2 Ԥ������2
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetControlDevState(ICE_HANDLE hSDK, ICE_U32 u32IsControlled, const ICE_CHAR *pcControlIp,
										ICE_U32 u32Reserve1, ICE_U32 u32Reserve2);

/**
*  @brief  ��ȡ���г�λʶ������
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [out]pstParam ��λʶ������ṹ��
*  @param  [in]nWidth    ��������ʲô�ֱ�����ȡ�õģ���ʾ������1280*720��ȡ�õģ���Ϊ1280��
*  @param  [in]nHeight    ��������ʲô�ֱ�����ȡ�õģ���ʾ�ߣ�����1280*720��ȡ�õģ���Ϊ720��
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAllParkingSpaceLoops(ICE_HANDLE hSDK, ICE_IPG_PLACE_CONFIG_S *pstParam, ICE_U32 nWidth, ICE_U32 nHeight);
/**
*  @brief  �������г�λʶ������
*  @param  [in]hSDK    �������ʱ���ص�sdk���
*  @param  [in]pstParam ��λʶ������ṹ��
*  @param  [in]nWidth    ��������ʲô�ֱ�����ȡ�õģ���ʾ������1280*720��ȡ�õģ���Ϊ1280��
*  @param  [in]nHeight    ��������ʲô�ֱ�����ȡ�õģ���ʾ�ߣ�����1280*720��ȡ�õģ���Ϊ720��
*  return	0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetAllParkingSpaceLoops(ICE_HANDLE hSDK, const ICE_IPG_PLACE_CONFIG_S *pstParam, ICE_U32 nWidth, ICE_U32 nHeight);
/**
*  @brief  ��λ״̬�л������ϴ����ݻص�
*  @param  [out]pvParam �ص�������
*  @param  [out]pcIP ���IP
*  @param  [out]pstParkingResult ���г�λ״̬
*  @param  [out]pcPicData ͼƬ����
*  @param  [out]u32PicLen ͼƬ����
*  @param  [out]pvReserve Ԥ������1
*  @param  [out]u32Reserve1 Ԥ������2
*  @param  [out]u32Reserve2 Ԥ������3
*  @param  [out]u32Reserve3 Ԥ������4
*  @param  [out]u32Reserve4 Ԥ������5
*  return	void
*/
typedef void(__stdcall *ICE_IPCSDK_OnParkingSpaceInfo)(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_PARKING_SPACE_RESULT_S *pstParkingResult, ICE_CHAR *pcPicData, ICE_U32 u32PicLen, 
	void *pvReserve, ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4);
/**
*  @brief  ���ó�λ״̬�л������ϴ����ݻص�
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [in]pfParkingSpaceInfo ��λ���ݻص�
*  @param  [in]pvParam �ص�������
*  return	void
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetParkingSpaceInfoCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnParkingSpaceInfo pfParkingSpaceInfo, void *pvParam);

/**
*  @brief  ��ȡ��λ����
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [out]u32SpaceNum ��λ��
*  return	0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetParkingSpaceNum(ICE_HANDLE hSDK, ICE_U32 *u32SpaceNum);

/**
*  @brief  ��ȡ��������
*  @param  [in]  hSDK             �������ʱ���ص�sdk���
*  @param  [out] pstUARTCfg       �������ò����ṹ��(ICE_UART_PARAM)
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetUARTCfg(ICE_HANDLE hSDK, ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  ���ô�������
*  @param  [in]  hSDK             �������ʱ���ص�sdk���
*  @param  [in] pstUARTCfg       �������ò���
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetUARTCfg(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  ��ȡIPG����λ������
*  @param  [in] hSDK    �������ʱ���ص�sdk���
*  @param  [out]pstParam ��λ����
*  return	0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetIPGParam(ICE_HANDLE hSDK, ICE_IPG_PARAM_S *pstParam);

/**
*  @brief  �����豸
*  @param  [IN] szDevs       �����豸��Ϣ���ַ���
*							   �����豸��Ϣ���ַ�������ʽΪ��mac��ַ\tip��ַ\t����汾��Ϣ\tӲ����Ϣ\r\n 
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_SearchDev(char* szDevs);

/**
*  @brief  �������޸�ip��ַ
*  @param  [IN] szMac          ���mac��ַ
*  @param  [IN] szIP           ���ip
*  @param  [IN] szMask         �������
*  @param  [IN] szGateway      �������
*  @return void
*/

ICE_IPCSDK_API void ICE_IPCSDK_ModifyDevIP(const ICE_CHAR* szMac, const ICE_CHAR *szIP, const ICE_CHAR *szMask, const ICE_CHAR* szGateway);

/**
*  @brief  ����ǿ�ƿصƲ���
*  @param  [IN] hSDK          sdk���
*  @param  [IN] pstParam      ǿ�ƿص����ýṹ��
*  @return void
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLightCtlParam(ICE_HANDLE hSDK, const LightCtlParam *pstParam); 

/**
*  @brief  ��ȡǿ�ƿصƲ���
*  @param  [IN]  hSDK          sdk���
*  @param  [OUT] pstParam      ǿ�ƿص����ýṹ��
*  @return void
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLightCtlParam(ICE_HANDLE hSDK, LightCtlParam *pstParam); 


/**
*  @brief  ʱ��ͬ��������ʱ�䣩
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] u16Year       ͬ��ʱ�����
*  @param  [IN] u8Month       ͬ��ʱ�����
*  @param  [IN] u8Day         ͬ��ʱ�����
*  @param  [IN] u8Hour        ͬ��ʱ���ʱ
*  @param  [IN] u8Min         ͬ��ʱ��ķ�
*  @param  [IN] u8Sec         ͬ��ʱ�����
*  @return 0 ʧ��, 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SyncTime(ICE_HANDLE hSDK, 
										   ICE_U16 u16Year, ICE_U8 u8Month, ICE_U8 u8Day, 
										   ICE_U8 u8Hour, ICE_U8 u8Min, ICE_U8 u8Sec);

/**
*  @brief  ��ȡ���ʱ��(����ʱ��)
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [OUT] u16Year       ���ʱ�����
*  @param  [OUT] u8Month       ���ʱ�����
*  @param  [OUT] u8Day         ���ʱ�����
*  @param  [OUT] u8Hour        ���ʱ���ʱ
*  @param  [OUT] u8Min         ���ʱ��ķ�
*  @param  [OUT] u8Sec         ���ʱ�����
*  @return 0 ʧ��, 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDevTime(ICE_HANDLE hSDK,
											 ICE_U16 *u16Year, ICE_U8 *u8Month, ICE_U8 *u8Day, 
											 ICE_U8 *u8Hour, ICE_U8 *u8Min, ICE_U8 *u8Sec);

/**
*  @brief  ��ȡhttp���Ͳ���
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [OUT] param		  http���Ͳ����ṹ��
*  @return 0 ʧ��, 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetCGIParam(ICE_HANDLE hSDK, http_conf_t *param);

/**
*  @brief  ����http���Ͳ���
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] param		  http���Ͳ����ṹ��
*  @return 0 ʧ��, 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetCGIParam(ICE_HANDLE hSDK, const http_conf_t *param);

#ifdef __cplusplus
}
#endif

#endif
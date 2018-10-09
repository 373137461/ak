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

#define PAYLOAD_TYPE_JPEG  26	//抓拍图片
#define PAYLOAD_TYPE_H264  96	//h264码流
#define PAYLOAD_TYPE_DTCA  100	//周界结果
#define PAYLOAD_TYPE_VLPR  101	//车牌结果
#define PAYLOAD_TYPE_TCNT  102	//计数结果
#define PAYLOAD_TYPE_HCNT  103	//计数结果
#define PAYLOAD_TYPE_IPG   104	//车位结果
#define PAYLOAD_TYPE_VDM   105	//移动卡口

/**
* @brief  相机事件枚举类型
*/
typedef enum
{
	ICE_DEVICE_OFFLINE,		//离线
	ICE_DEVICE_ONLINE,		//在线
	ICE_DEVICE_IO_CHANGED			//IO状态改变
} ICE_DEVICE_EVENT_TYPE;

/**
*  @brief  全局初始化
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_Init();
/**
*  @brief  全局释放
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_Fini();

#ifdef _WIN32
/**
*  @brief  开始视频
*  @param  [in] hSDK          连接相机时返回的sdk句柄
*  @param  [in] u8MainStream  是否为主码流，1为主码流，0为子码流
*  @param  [in] hWnd          视频播放窗口句柄
*  @return 1 连接视频流成功 0 连接视频流失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_StartStream(ICE_HANDLE hSDK, 
	ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  结束视频
*  @param  [in] hSDK          连接相机时返回的sdk句柄
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_StopStream(ICE_HANDLE hSDK);
#endif

/**
*  @brief  获取相机状态
*  @param  [IN] hSDK      连接相机时返回的sdk句柄
*  @return 0 离线 1 在线 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK);

/**
*  @brief  透明串口回调函数
*  @param  [OUT] pvParam      串口回调参数，用于区分不同串口（ICE_IPCSDK_SetSerialPortCallBack传入的最后一个参数）
*  @param  [OUT] pcIP         相机ip
*  @param  [OUT] pcData       串口数据
*  @param  [OUT] u32Len       数据长度
*/
typedef void (__stdcall *ICE_IPCSDK_OnSerialPort)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  设置透明串口
*  @param  [IN] hSDK                   连接相机时返回的sdk句柄
*  @param  [IN] pfOnSerialPort         ICE_IPCSDK_OnSerialPort回调函数
*  @param  [IN] pvSerialPortParam      串口回调参数，用于区分不同串口
*  @return void 
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  发送透明串口(rs485)数据
*  @param  [IN] hSDK      连接相机时返回的sdk句柄
*  @param  [IN] pcData    串口数据
*  @param  [IN] u32Len    数据长度
*  @return 0 发送失败 1 发送成功 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TransSerialPort(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  透明串口接收事件回调接口(rs232)
*  @param  [out] pvParam      串口回调参数，用于区分不同串口（ICE_IPCSDK_SetSerialPortCallBack_RS232传入的最后一个参数）
*  @param  [out] pcIP         相机ip
*  @param  [out] pcData       串口数据
*  @param  [out] u32Len       数据长度
*/
typedef void (__stdcall *ICE_IPCSDK_OnSerialPort_RS232)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  设置透明串口接收事件(rs232)
*  @param  [in] hSDK                   连接相机时返回的sdk句柄
*  @param  [in] pfOnSerialPort         ICE_IPCSDK_OnSerialPort_RS232回调函数
*  @param  [in] pvSerialPortParam      串口回调参数，用于区分不同串口
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetSerialPortCallBack_RS232(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  发送透明串口(rs232)数据
*  @param  [in] hSDK      连接相机时返回的sdk句柄
*  @param  [in] pcData    串口数据
*  @param  [in] u32Len    数据长度
*  @return 0 发送失败 1 发送成功 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TransSerialPort_RS232(ICE_HANDLE hSDK, 
	ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  通过该回调函数获取相机的连接状态
*  @param  [OUT] pvParam             相机连接回调参数, 用于区分不同相机连接事件(ICE_IPCSDK_SetDeviceEventCallBack传入的最后一个参数)
*  @param  [OUT] pcIP                相机ip
*  @param  [OUT] u32EventType        事件类型 0：离线 1：在线
*  @param  [OUT] u32EventData1       预留参数1 
*  @param  [OUT] u32EventData2       预留参数2
*  @param  [OUT] u32EventData3       预留参数3
*  @param  [OUT] u32EventData4       预留参数4
*/
typedef void (__stdcall *ICE_IPCSDK_OnDeviceEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4);

/**
*  @brief  设置相机连接状态回调事件
*  @param  [IN] hSDK                         连接相机时返回的sdk句柄
*  @param  [IN] pfOnDeviceEvent              相机连接回调
*  @param  [IN] pvDeviceEventParam           相机连接回调参数,用于区分不同相机连接事件
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetDeviceEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, void *pvDeviceEventParam);

/**
*  @brief  日志配置
*  @param  [IN] openLog     是否开启日志
*  @param  [IN] logPath     日志路径，默认为D:\
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_LogConfig(int openLog, const char *logPath);

/**
*  @brief  连接相机
*  @param  [in]pcIP 相机ip 
*  @param  [in]pcReserve1 预留参数1
*  @param  [in]pcReserve2 预留参数2
*  @param  [in]nReserve1  预留参数3
*  @param  [in]nReserve2  预留参数4
*  @param  [in]nReserve3  预留参数5
*  @param  [in]u32SyncTime  是否进行时间同步，默认进行同步
*  @return sdk句柄，失败时返回NULL
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_Login(const ICE_CHAR *pcIP, ICE_CHAR *pcReserve1, ICE_CHAR *pcReserve2, 
	ICE_U32 *nReserve1, ICE_U32 *nReserve2, ICE_U32 *nReserve3, ICE_U32 u32SyncTime = 1);

/**
*  @brief  断开连接
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_Logout(ICE_HANDLE hSDK);

/**
*  @brief  读取相机下单个车位的当前状态
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32SpaceCode 车位编号
*  @param  [out]u32SpaceNum 车位总数
*  @param  [out]pstResult 车位的当前状态
*  @param  [out]pcPicData 车位图片
*  @param  [in]u32Size 缓冲区大小
*  @param  [out]pu32PicLen 图片实际长度
*  @param  [out]pcReserve 预留参数1
*  @param  [in]u32Reserve 预留参数2
*  @param  [out]pu32Reserve 预留参数3
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetSingleParkingSpaceStatus(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32SpaceNum,
	ICE_PARKING_SPACE_OUTPUT_S *pstResult, ICE_CHAR *pcPicData, ICE_U32 u32Size, ICE_U32* pu32PicLen, 
	ICE_CHAR *pcReserve, ICE_U32 u32Reserve, ICE_U32 *pu32Reserve);

/**
*  @brief  读取相机下所有车位的当前状态
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [out]pstResult 车位的当前状态
*  @param  [out]pcPicData 车位图片
*  @param  [in]u32Size 缓冲区大小
*  @param  [out]pu32PicLen 图片实际长度
*  @param  [out]pvReserve 预留参数1
*  @param  [in]u32PicSize 预留参数2
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAllParkingSpaceStatus(ICE_HANDLE hSDK, ICE_PARKING_SPACE_RESULT_S *pstResult, 
	ICE_CHAR *pcPicData,ICE_U32 u32Size, ICE_U32* pu32PicLen, void *pvReserve, ICE_U32* u32Reserve);

/**
*  @brief  设置车位类型
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32SpaceCode 车位编号
*  @param  [in]u32SpaceType 车位类型（0：临时 1：预定；2固定）
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetParkingSpaceType(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 u32SpaceType);

/**
*  @brief  获取车位类型
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32SpaceCode 车位编号
*  @param  [out]u32SpaceType 车位类型（0：临时 1：预定；2固定）
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetParkingSpaceType(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32SpaceType);

/**
*  @brief  设置禁用/使能车位
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32SpaceCode 车位编号
*  @param  [in]u32Enable 车位使能（0：禁用 1：使能）
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetEnableParkingSpace(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 u32Enable);

/**
*  @brief  获取禁用/使能车位
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32SpaceCode 车位编号
*  @param  [out]u32Enable 车位使能（0：禁用 1：使能）
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetEnableParkingSpace(ICE_HANDLE hSDK, ICE_U32 u32SpaceCode, ICE_U32 *u32Enable);

/**
*  @brief  获取远程控灯参数
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [out]u32IsRemote 是否远程控制其他相机 0不控制，1控制
*  @param  [out]pcRemoteIp 是否远程控制其他相机
*  @param  [out]u32Reserve1 预留参数1
*  @param  [out]u32Reserve2 预留参数2
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetRemoteDevState(ICE_HANDLE hSDK, ICE_U32 *u32IsRemote, ICE_CHAR *pcRemoteIp, 
										ICE_U32 *u32Reserve1, ICE_U32 *u32Reserve2);

/**
*  @brief  设置远程控灯参数
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32IsRemote 是否远程控制其他相机 0不控制，1控制
*  @param  [in]pcRemoteIp 是否远程控制其他相机
*  @param  [in]u32Reserve1 预留参数1
*  @param  [in]u32Reserve2 预留参数2
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetRemoteDevState(ICE_HANDLE hSDK, ICE_U32 u32IsRemote, const ICE_CHAR *pcRemoteIp,
										ICE_U32 u32Reserve1, ICE_U32 u32Reserve2);

/**
*  @brief  获取受控灯参数
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [out]u32IsControlled 是否接受其他相机的远程控制 0不接受，1接受
*  @param  [out]pcControlIp 是否控制本相机的其他相机ip
*  @param  [out]u32Reserve1 预留参数1
*  @param  [out]u32Reserve2 预留参数2
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetControlDevState(ICE_HANDLE hSDK, ICE_U32 *u32IsControlled, ICE_CHAR *pcControlIp,
										ICE_U32 *u32Reserve1, ICE_U32 *u32Reserve2);
/**
*  @brief  设置受控灯参数
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]u32IsControlled 是否接受其他相机的远程控制 0不接受，1接受
*  @param  [in]pcControlIp 是否控制本相机的其他相机ip
*  @param  [in]u32Reserve1 预留参数1
*  @param  [in]u32Reserve2 预留参数2
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetControlDevState(ICE_HANDLE hSDK, ICE_U32 u32IsControlled, const ICE_CHAR *pcControlIp,
										ICE_U32 u32Reserve1, ICE_U32 u32Reserve2);

/**
*  @brief  获取所有车位识别区域
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [out]pstParam 车位识别区域结构体
*  @param  [in]nWidth    坐标是在什么分辨率下取得的，表示宽（如在1280*720下取得的，宽为1280）
*  @param  [in]nHeight    坐标是在什么分辨率下取得的，表示高（如在1280*720下取得的，高为720）
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetAllParkingSpaceLoops(ICE_HANDLE hSDK, ICE_IPG_PLACE_CONFIG_S *pstParam, ICE_U32 nWidth, ICE_U32 nHeight);
/**
*  @brief  设置所有车位识别区域
*  @param  [in]hSDK    连接相机时返回的sdk句柄
*  @param  [in]pstParam 车位识别区域结构体
*  @param  [in]nWidth    坐标是在什么分辨率下取得的，表示宽（如在1280*720下取得的，宽为1280）
*  @param  [in]nHeight    坐标是在什么分辨率下取得的，表示高（如在1280*720下取得的，高为720）
*  return	0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetAllParkingSpaceLoops(ICE_HANDLE hSDK, const ICE_IPG_PLACE_CONFIG_S *pstParam, ICE_U32 nWidth, ICE_U32 nHeight);
/**
*  @brief  车位状态切换主动上传数据回调
*  @param  [out]pvParam 回调上下文
*  @param  [out]pcIP 相机IP
*  @param  [out]pstParkingResult 所有车位状态
*  @param  [out]pcPicData 图片数据
*  @param  [out]u32PicLen 图片长度
*  @param  [out]pvReserve 预留参数1
*  @param  [out]u32Reserve1 预留参数2
*  @param  [out]u32Reserve2 预留参数3
*  @param  [out]u32Reserve3 预留参数4
*  @param  [out]u32Reserve4 预留参数5
*  return	void
*/
typedef void(__stdcall *ICE_IPCSDK_OnParkingSpaceInfo)(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_PARKING_SPACE_RESULT_S *pstParkingResult, ICE_CHAR *pcPicData, ICE_U32 u32PicLen, 
	void *pvReserve, ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4);
/**
*  @brief  设置车位状态切换主动上传数据回调
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [in]pfParkingSpaceInfo 车位数据回调
*  @param  [in]pvParam 回调上下文
*  return	void
*/
ICE_IPCSDK_API void ICE_IPCSDK_SetParkingSpaceInfoCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnParkingSpaceInfo pfParkingSpaceInfo, void *pvParam);

/**
*  @brief  获取车位个数
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [out]u32SpaceNum 车位数
*  return	0失败 1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetParkingSpaceNum(ICE_HANDLE hSDK, ICE_U32 *u32SpaceNum);

/**
*  @brief  获取串口配置
*  @param  [in]  hSDK             连接相机时返回的sdk句柄
*  @param  [out] pstUARTCfg       串口配置参数结构体(ICE_UART_PARAM)
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetUARTCfg(ICE_HANDLE hSDK, ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  设置串口配置
*  @param  [in]  hSDK             连接相机时返回的sdk句柄
*  @param  [in] pstUARTCfg       串口配置参数
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetUARTCfg(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  获取IPG（车位）参数
*  @param  [in] hSDK    连接相机时返回的sdk句柄
*  @param  [out]pstParam 车位参数
*  return	0失败 1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetIPGParam(ICE_HANDLE hSDK, ICE_IPG_PARAM_S *pstParam);

/**
*  @brief  搜索设备
*  @param  [IN] szDevs       包含设备信息的字符串
*							   包含设备信息的字符串，格式为：mac地址\tip地址\t相机版本信息\t硬件信息\r\n 
*  @return void
*/
#ifdef _WIN32
ICE_IPCSDK_API void ICE_IPCSDK_SearchDev(char* szDevs);
#else
void ICE_IPCSDK_SearchDev(const char *szIfName, char *szDevs, int nSize, int nTimeoutMs);
#endif

/**
*  @brief  跨网段修改ip地址
*  @param  [IN] szMac          相机mac地址
*  @param  [IN] szIP           相机ip
*  @param  [IN] szMask         相机掩码
*  @param  [IN] szGateway      相机网关
*  @return void
*/
#ifdef _WIN32
ICE_IPCSDK_API void ICE_IPCSDK_ModifyDevIP(const ICE_CHAR* szMac, const ICE_CHAR *szIP, const ICE_CHAR *szMask, const ICE_CHAR* szGateway);
#else
ICE_IPCSDK_API void ICE_IPCSDK_ModifyDevIP(const char *szIfName, const ICE_CHAR* szMac, const ICE_CHAR *szIP, 
										   const ICE_CHAR *szMask, const ICE_CHAR* szGateway);
#endif

/**
*  @brief  设置强制控灯参数
*  @param  [IN] hSDK          sdk句柄
*  @param  [IN] pstParam      强制控灯配置结构体
*  @return void
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetLightCtlParam(ICE_HANDLE hSDK, const LightCtlParam *pstParam); 

/**
*  @brief  获取强制控灯参数
*  @param  [IN]  hSDK          sdk句柄
*  @param  [OUT] pstParam      强制控灯配置结构体
*  @return void
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetLightCtlParam(ICE_HANDLE hSDK, LightCtlParam *pstParam); 


/**
*  @brief  时间同步（北京时间）
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] u16Year       同步时间的年
*  @param  [IN] u8Month       同步时间的月
*  @param  [IN] u8Day         同步时间的日
*  @param  [IN] u8Hour        同步时间的时
*  @param  [IN] u8Min         同步时间的分
*  @param  [IN] u8Sec         同步时间的秒
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SyncTime(ICE_HANDLE hSDK, 
										   ICE_U16 u16Year, ICE_U8 u8Month, ICE_U8 u8Day, 
										   ICE_U8 u8Hour, ICE_U8 u8Min, ICE_U8 u8Sec);

/**
*  @brief  获取相机时间(北京时间)
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [OUT] u16Year       相机时间的年
*  @param  [OUT] u8Month       相机时间的月
*  @param  [OUT] u8Day         相机时间的日
*  @param  [OUT] u8Hour        相机时间的时
*  @param  [OUT] u8Min         相机时间的分
*  @param  [OUT] u8Sec         相机时间的秒
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDevTime(ICE_HANDLE hSDK,
											 ICE_U16 *u16Year, ICE_U8 *u8Month, ICE_U8 *u8Day, 
											 ICE_U8 *u8Hour, ICE_U8 *u8Min, ICE_U8 *u8Sec);

/**
*  @brief  获取http推送参数
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [OUT] param		  http推送参数结构体
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetCGIParam(ICE_HANDLE hSDK, http_conf_t *param);

/**
*  @brief  设置http推送参数
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] param		  http推送参数结构体
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_SetCGIParam(ICE_HANDLE hSDK, const http_conf_t *param);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_GetDevID(ICE_HANDLE hSDK, ICE_CHAR* szDevID);

#ifdef __cplusplus
}
#endif

#endif
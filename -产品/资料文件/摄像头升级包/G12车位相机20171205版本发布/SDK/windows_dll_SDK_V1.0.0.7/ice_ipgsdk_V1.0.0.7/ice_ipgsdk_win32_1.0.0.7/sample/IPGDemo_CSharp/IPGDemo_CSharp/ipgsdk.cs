using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace IPGDemo_CSharp
{
    public partial class NativeConstants
    {

        /// ICE_MAX_PARKING_SPACE_NUM -> 6
        public const int ICE_MAX_PARKING_SPACE_NUM = 6;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ICE_RECT_S
    {
        public short s16Left;
        public short s16Top;
        public short s16Right;
        public short s16Bottom;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential, CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
    public struct ICE_PARKING_SPACE_VLPR_OUTPUT_S
    {
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 16)]
        public string as8PlateNum;
        public ICE_RECT_S stPlateRect;
        public float flConfidence;
        public int s32PlateIntensity;
        public int ePlateColor;
        public int ePlateType;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 48)]
        public string astReserve;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ICE_PARKING_SPACE_OUTPUT_S
    {
        public int enParkingPlaceStatus;
        public ICE_PARKING_SPACE_VLPR_OUTPUT_S stPlateInfo;
        public int s32CarType;
        public int s32EventType;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 30, ArraySubType = System.Runtime.InteropServices.UnmanagedType.I4)]
        public int[] s32Reserved;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ICE_PARKING_SPACE_RESULT_S
    {
        public byte u8ParkingPlaceNum;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 6, ArraySubType = System.Runtime.InteropServices.UnmanagedType.Struct)]
        public ICE_PARKING_SPACE_OUTPUT_S[] astOutput;
        public int s32PicDataLen;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 16, ArraySubType = System.Runtime.InteropServices.UnmanagedType.I4)]
        public int[] s32Reserved;
    }

    public enum ICE_BOOL
    {
        ICE_FALSE = 0,
        ICE_TRUE = 1,
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ICE_IPG_PLACE_PARAM_S
    {
        public ICE_RECT_S stRecRect;
        public ICE_BOOL isAvalable;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 8, ArraySubType = System.Runtime.InteropServices.UnmanagedType.I4)]
        public int[] u32Reserved;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ICE_IPG_PLACE_CONFIG_S
    {
        public byte u8ParkingPlaceNum;
        public int bSpecialPlace;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 8, ArraySubType = System.Runtime.InteropServices.UnmanagedType.Struct)]
        public ICE_IPG_PLACE_PARAM_S[] stPlaceParam;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 64, ArraySubType = System.Runtime.InteropServices.UnmanagedType.I4)]
        public int[] u32Reserved;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ice_uart
    {
        public int uartEn;
        public int uartWorkMode;
        public int baudRate;
        public int dataBits;
        public int parity;
        public int stopBits;
        public int flowControl;
        public int LEDControlCardType;
        public int LEDBusinessType;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 3, ArraySubType = System.Runtime.InteropServices.UnmanagedType.I4)]
        public int[] as32Reserved;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct ICE_UART_PARAM
    {
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = System.Runtime.InteropServices.UnmanagedType.Struct)]
        public ice_uart[] uart_param;
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 10, ArraySubType = System.Runtime.InteropServices.UnmanagedType.I4)]
        public int[] as32Reserved;
    }

    //强制控灯配置
    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential, CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
    public struct LightCtlParam
    {
        public byte u8LightEn; //是否亮灯  0关闭sdk控灯 1-灭  2-亮  3-闪烁
        public byte u8Color;   //灯光颜色  1-红色  2-绿色  3-黄色  4-蓝色

        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 8)]
        public string u32Reserved;
    }

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential, CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
    public struct http_conf_t
    {
        public int http_enable;//是否启动http推送(1:推送 0：不推送)
        [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 512)]
        public string http_addr;//http推送地址
        public int small_pic;//是否需要小图片(1:需要 0:不需要)
        public int big_pic;//是否需要大图片(1:需要 0:不需要)
        public int upload_enable;//是否启动定时上传（1:启动 0:不启动)
        public int upload_interval;//定时上传时间（分钟）
        public int heartbeat_enable;//是否启动心跳功能（1:启动 0:不启动)
        public int heartbeat_interval;//心跳上传时间（分钟）
    }

    class ipgsdk
    {
        public delegate void ICE_IPCSDK_OnDeviceEvent(System.IntPtr pvParam,
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
            uint u32EventType, uint u32EventData1, uint u32EventData2, uint u32EventData3, uint u32EventData4);

        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetDeviceEventCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_SetDeviceEventCallBack(System.IntPtr hSDK, ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, System.IntPtr pvDeviceEventParam);

        /**
        *  @brief  车位状态切换主动上传数据回调
        *  @param  【out】pvParam 回调上下文
        *  @param  【out】pcIP 相机IP
        *  @param  【out】hSDK 连接相机时返回的sdk句柄
        *  @param  【out】pstParkingResult 所有车位状态
        *  @param  【out】pcPicData 图片数据
        *  @param  【out】u32PicLen 图片长度
        *  @param  【out】pvReserve 预留给所有车牌数据
        *  @param  【out】u32Reserve1 预留参数1
        *  @param  【out】u32Reserve2 预留参数2
        *  @param  【out】u32Reserve3 预留参数3
        *  @param  【out】u32Reserve4 预留参数4
        *  return	void
        */
        [System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.StdCall)]
        public delegate void ICE_IPCSDK_OnParkingSpaceInfo(System.IntPtr pvParam,
        [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
        ref ICE_PARKING_SPACE_RESULT_S pstParkingResult, System.IntPtr pcPicData, uint u32PicLen,
        System.IntPtr pvReserve, uint u32Reserve1, uint u32Reserve2, uint u32Reserve3, uint u32Reserve4);

        /**
        *  @brief  设置车位状态切换主动上传数据回调
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】pfParkingSpaceInfo 车位数据回调
        *  @param  【in】pvParam 回调上下文
        *  return	void
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetParkingSpaceInfoCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_SetParkingSpaceInfoCallBack(System.IntPtr hSDK, ICE_IPCSDK_OnParkingSpaceInfo pfParkingSpaceInfo, System.IntPtr pvParam);
        /**
         *  @brief  全局初始化
         *  @return void
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_Init", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_Init();

        /**
         *  @brief  全局释放
         *  @return void
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_Fini", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_Fini();

        /**
        *  @brief  连接相机
        *  @param  【in】pcIP 相机ip 
        *  @param  【in】pcReserve1 预留参数1
        *  @param  【in】pcReserve2 预留参数2
        *  @param  【in】nReserve1  预留参数3
        *  @param  【in】nReserve2  预留参数4
        *  @param  【in】nReserve3  预留参数5
        *  @param  【in】u32SyncTime  是否进行时间同步，默认进行同步
        *  @return sdk句柄，失败时返回NULL
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_Login", CallingConvention = CallingConvention.Cdecl)]
        public static extern System.IntPtr ICE_IPCSDK_Login([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP, 
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcReserve1, 
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcReserve2,
            System.IntPtr nReserve1, System.IntPtr nReserve2, System.IntPtr nReserve3, uint u32SyncTim);

        /**
        *  @brief  断开连接
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  return void
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_Logout", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_Logout(System.IntPtr hSDK);

        /**
        *  @brief  连接视频
        *  @param  [IN] hSDK           连接相机时返回的句柄值
        *  @param  [IN] u8MainStream   是否请求主码流（1：主码流 0：子码流）
        *  @param  [IN] hWnd           预览视频的窗口句柄
        *  @return 1表示成功，0表示失败
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_StartStream", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_StartStream(System.IntPtr hSDK, byte u8MainStream, uint hWnd);

        /**
         *  @brief  断开视频
         *  @param  [IN] hSDK   连接相机时返回的句柄值
         *  @return void
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_StopStream", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_StopStream(System.IntPtr hSDK);

        /**
        *  @brief  读取相机下单个车位的当前状态
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】au8SpaceCode 车位编号
        *  @param  【out】u32SpaceNum 车位总数
        *  @param  【out】pstResult 车位的当前状态
        *  @param  【out】pcPicData 车位图片
        *  @param  【in】u32PicSize 缓冲区大小
        *  @param  【out】pu32PicLen 图片实际长度
        *  @param  【out】pcReserve 预留给车牌图的
        *  @param  【in】u32Reserve 预留给车牌图的缓冲区大小
        *  @param  【out】pu32Reserve 预留给车牌图的图片实际长度
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetSingleParkingSpaceStatus", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetSingleParkingSpaceStatus(System.IntPtr hSDK, uint u32SpaceCode, ref uint u32SpaceNum, ref ICE_PARKING_SPACE_OUTPUT_S pstResult,
            byte[] pcPicData, uint u32Size, ref uint pu32PicLen, System.IntPtr pcReserve, uint u32Reserve, ref uint pu32Reserve);
        /**
        *  @brief  读取相机下所有车位的当前状态
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【out】pstResult 车位的当前状态
        *  @param  【out】pcPicData 车位图片
        *  @param  【in】u32PicSize 缓冲区大小
        *  @param  【out】pu32PicLen 图片实际长度
        *  @param  【out】pvReserve 预留给所有车牌图
        *  @param  【in】u32PicSize 预留给所有车牌图的缓冲区大小
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetAllParkingSpaceStatus", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetAllParkingSpaceStatus(System.IntPtr hSDK, ref ICE_PARKING_SPACE_RESULT_S pstResult,
            byte[] pcPicData, uint u32Size, ref uint pu32PicLen, System.IntPtr pvReserve, ref uint u32Reserve);
        /**
        *  @brief  设置车位类型
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】u32SpaceCode 车位编号
        *  @param  【in】u32SpaceType 车位类型（0：临时 1：预定；2固定）
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetParkingSpaceType", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetParkingSpaceType(System.IntPtr hSDK, uint u32SpaceCode, uint u32SpaceType);

        /**
        *  @brief  获取车位类型
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】u32SpaceCode 车位编号
        *  @param  【out】u32SpaceType 车位类型（0：临时 1：预定；2固定）
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetParkingSpaceType", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetParkingSpaceType(System.IntPtr hSDK, uint u32SpaceCode, ref uint u32SpaceType);
        
        /**
        *  @brief  获取禁用/使能车位
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】u32SpaceCode 车位编号
        *  @param  【out】u32Enable 车位使能（0：禁用 1：使能）
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetEnableParkingSpace", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetEnableParkingSpace(System.IntPtr hSDK, uint u32SpaceCode, uint u32Enable);

        /**
        *  @brief  获取禁用/使能车位
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】u32SpaceCode 车位编号
        *  @param  【out】u32Enable 车位使能（0：禁用 1：使能）
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetEnableParkingSpace", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetEnableParkingSpace(System.IntPtr hSDK, uint u32SpaceCode, ref uint u32Enable);

        /**
        *  @brief  获取远程控制其他相机的状态
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【out】u32IsRemote 是否远程控制其他相机 0不控制，1控制
        *  @param  【out】pcRemoteIp 是否远程控制其他相机
        *  @param  【out】u32Reserve1 预留参数1
        *  @param  【out】u32Reserve2 预留参数2
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetRemoteDevState", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetRemoteDevState(System.IntPtr hSDK, ref uint u32IsRemote, StringBuilder pcRemoteIp, ref uint u32Reserve1, ref uint u32Reserve2);

        /**
        *  @brief  设置远程控制其他相机的状态
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】u32IsRemote 是否远程控制其他相机 0不控制，1控制
        *  @param  【in】pcRemoteIp 是否远程控制其他相机
        *  @param  【in】u32Reserve1 预留参数1
        *  @param  【in】u32Reserve2 预留参数2
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetRemoteDevState", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetRemoteDevState(System.IntPtr hSDK, uint u32IsRemote, string pcRemoteIp, uint u32Reserve1, uint u32Reserve2);
        /**
        *  @brief  获取被其他相机远程控制的状态
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【out】u32IsControlled 是否接受其他相机的远程控制 0不接受，1接受
        *  @param  【out】pcControlIp 是否控制本相机的其他相机ip
        *  @param  【out】u32Reserve1 预留参数1
        *  @param  【out】u32Reserve2 预留参数2
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetControlDevState", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetControlDevState(System.IntPtr hSDK, ref uint u32IsControlled, StringBuilder pcControlIp, ref uint u32Reserve1, ref uint u32Reserve2);

        /**
        *  @brief  设置被其他相机远程控制的状态
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】u32IsControlled 是否接受其他相机的远程控制 0不接受，1接受
        *  @param  【in】pcControlIp 是否控制本相机的其他相机ip
        *  @param  【in】u32Reserve1 预留参数1
        *  @param  【in】u32Reserve2 预留参数2
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetControlDevState", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetControlDevState(System.IntPtr hSDK, uint u32IsControlled, string pcControlIp, uint u32Reserve1, uint u32Reserve2);

        /**
        *  @brief  获取所有车位识别区域
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【out】pLoopParam 车位识别区域结构体
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetAllParkingSpaceLoops", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetAllParkingSpaceLoops(System.IntPtr hSDK, ref ICE_IPG_PLACE_CONFIG_S pstParam, uint nWidth, uint nHeight);
       
        /**
        *  @brief  设置所有车位识别区域
        *  @param  【in】 hSDK    连接相机时返回的sdk句柄
        *  @param  【in】pLoopParam 车位识别区域结构体
        *  return	0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetAllParkingSpaceLoops", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetAllParkingSpaceLoops(System.IntPtr hSDK, ref ICE_IPG_PLACE_CONFIG_S pstParam, uint nWidth, uint nHeight);

        /**
         *  @brief  发送RS485串口数据
         *  @param  [IN] hSDK      由连接相机接口获得的句柄
         *  @param  [IN] pcData    RS232串口数据
         *  @param  [IN] u32Len    串口数据长度
         *  @return 1表示成功，0表示失败
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_TransSerialPort", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_TransSerialPort(System.IntPtr hSDK, byte[] pcData, uint u32Len);

        /**
         *  @brief  发送RS232串口数据
         *  @param  [IN] hSDK      由连接相机接口获得的句柄
         *  @param  [IN] pcData    RS232串口数据
         *  @param  [IN] u32Len    串口数据长度
         *  @return 1表示成功，0表示失败
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_TransSerialPort_RS232", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_TransSerialPort_RS232(System.IntPtr hSDK, byte[] pcData, uint u32Len);

        /**
         *  @brief  通过该回调函数获得RS485数据
         *  @param  [OUT] pvParam   用户自定义参数，用来区分不同的sdk使用者，类似于线程入口函数的参数（即ICE_IPCSDK_SetSerialPortCallBack_RS232传入的最后一个参数）
         *  @param  [OUT] pcIP      相机ip
         *  @param  [OUT] pcData    串口数据首地址
         *  @param  [OUT] u32Len    串口数据长度
         *  @return void
         */
        public delegate void ICE_IPCSDK_OnSerialPort(System.IntPtr pvParam,
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
            System.IntPtr pcData, uint u32Len);

        /**
         *  @brief  设置获得RS485数据的相关回调函数
         *  @param  [IN] hSDK               连接相机时返回的sdk句柄
         *  @param  [IN] pfOnSerialPort     相机发送的RS232数据，通过该回调获得
         *  @param  [IN] pvSerialPortParam  回调函数中的参数，能区分开不同的使用者即可
         *  @return void
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetSerialPortCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_SetSerialPortCallBack(System.IntPtr hSDK, ICE_IPCSDK_OnSerialPort pfOnSerialPort,
                                                                         System.IntPtr pvSerialPortParam);

        /**
         *  @brief  通过该回调函数获得RS232数据
         *  @param  [OUT] pvParam   用户自定义参数，用来区分不同的sdk使用者，类似于线程入口函数的参数（即ICE_IPCSDK_SetSerialPortCallBack_RS232传入的最后一个参数）
         *  @param  [OUT] pcIP      相机ip
         *  @param  [OUT] pcData    串口数据首地址
         *  @param  [OUT] u32Len    串口数据长度
         *  @return void
         */
        public delegate void ICE_IPCSDK_OnSerialPort_RS232(System.IntPtr pvParam,
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
            System.IntPtr pcData, uint u32Len);

        /**
         *  @brief  设置获得RS232数据的相关回调函数
         *  @param  [IN] hSDK               连接相机时返回的sdk句柄
         *  @param  [IN] pfOnSerialPort     相机发送的RS232数据，通过该回调获得
         *  @param  [IN] pvSerialPortParam  回调函数中的参数，能区分开不同的使用者即可
         *  @return void
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetSerialPortCallBack_RS232", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_SetSerialPortCallBack_RS232(System.IntPtr hSDK, ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort,
                                                                         System.IntPtr pvSerialPortParam);
        /**
        *  @brief  获取串口配置
        *  @param  [IN]  hSDK             连接相机时返回的sdk句柄
        *  @param  [OUT] pstUARTCfg       串口配置参数结构体(ICE_UART_PARAM)
        *  @return 0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetUARTCfg", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetUARTCfg(System.IntPtr hSDK, ref ICE_UART_PARAM pstUARTCfg);

        /**
        *  @brief  设置串口配置
        *  @param  [IN]  hSDK             连接相机时返回的sdk句柄
        *  @param  [OUT] pstUARTCfg       串口配置参数
        *  @return 0 失败 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetUARTCfg", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetUARTCfg(System.IntPtr hSDK, ref ICE_UART_PARAM pstUARTCfg);

        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetParkingSpaceNum", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetParkingSpaceNum(System.IntPtr hSDK, ref uint u32SpaceNum);

        /**
         *  @brief  搜索区域网内相机
         *  @param  [OUT] szDevs   包含设备信息的字符串
         *                         包含设备信息的字符串，格式为：mac地址\tip地址\t相机版本信息\t硬件信息\r\n 
         *  @return void
         */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SearchDev", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_SearchDev(StringBuilder szDevs);

        /**
        *  @brief  跨网段修改ip地址
        *  @param  [IN] szMac          相机mac地址
        *  @param  [IN] szIP           相机ip
        *  @param  [IN] szMask         相机掩码
        *  @param  [IN] szGateway      相机网关
        *  @return void
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_ModifyDevIP", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ICE_IPCSDK_ModifyDevIP(
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string szMac, 
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string szIP, 
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string szMask, 
            [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string szGateway);

        /**
        *  @brief  设置强制控灯配置
        *  @param  [IN] hSDK          sdk句柄
        *  @param  [IN] pstParam      强制控灯配置结构体
        *  @return void
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetLightCtlParam", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetLightCtlParam(System.IntPtr hSDK, ref LightCtlParam pstParam);

        /**
        *  @brief  获取强制控灯配置
        *  @param  [IN]  hSDK          sdk句柄
        *  @param  [OUT] pstParam      强制控灯配置结构体
        *  @return void
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetLightCtlParam", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetLightCtlParam(System.IntPtr hSDK, ref LightCtlParam pstParam);

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
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SyncTime", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SyncTime(System.IntPtr hSDK, ushort u16Year, byte u8Month, byte u8Day, byte u8Hour, byte u8Min, byte u8Sec);

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
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetDevTime", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetDevTime(System.IntPtr hSDK, ref ushort u16Year, ref byte u8Month, ref byte u8Day, ref byte u8Hour, ref byte u8Min, ref byte u8Sec);

        /**
        *  @brief  获取http推送参数
        *  @param  [IN] hSDK          连接相机时返回的sdk句柄
        *  @param  [OUT] param		  http推送参数结构体
        *  @return 0 失败, 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_GetCGIParam", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_GetCGIParam(System.IntPtr hSDK, ref http_conf_t param);

        /**
        *  @brief  设置http推送参数
        *  @param  [IN] hSDK          连接相机时返回的sdk句柄
        *  @param  [IN] param		  http推送参数结构体
        *  @return 0 失败, 1 成功
        */
        [System.Runtime.InteropServices.DllImportAttribute("ice_ipgsdk.dll", EntryPoint = "ICE_IPCSDK_SetCGIParam", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint ICE_IPCSDK_SetCGIParam(System.IntPtr hSDK, ref http_conf_t param);
    }
}

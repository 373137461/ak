unit ipgsdk;

interface

uses
 Windows, Messages, WinSock;

const
  DLL_ICE       = 'ice_ipgsdk.dll';

  // ice_base_type.h
  ICE_NULL      = 0;
  ICE_SUCESS    = 0;

  ICE_MODULE_DATLEN       = 1024;
  ICE_MAX_POLYGON_NUM     = 32;
  ICE_MAX_TRAJECT_LEN     = 40;
  ICE_MAX_TGT_NUM         = 64;                                                 //!< 目标最大数目
  ICE_MAX_EVT_NUM         = 128;                                                //!< 事件最大数目

type                 
  // ice_base_type.h
  ICE_U8        = Byte;
  ICE_PU8       = PByte;
  ICE_U16       = Word;
  ICE_PU16      = PWORD;
  ICE_U32       = UINT;
  ICE_PU32      = PUINT;
  ICE_S8        = Shortint;
  ICE_S16       = Smallint;
  ICE_S32       = Integer;
  ICE_PS32      = PInteger;
  ICE_FLOAT     = Single;
  ICE_U64       = ULONG;
  ICE_S64       = Int64;
  ICE_CHAR      = Char;
  ICE_PCHAR     = PChar;
  ICE_HANDLE    = Pointer;

type
ICE_RECT_S = record
  s16Left: SmallInt;
  s16Top:  SmallInt;
  s16Right: SmallInt;
  s16Bottom: SmallInt;
end;

type
ICE_PARKING_SPACE_VLPR_OUTPUT_S = record
  as8PlateNum: array[0..15] of Char;
  stPlateRect: ICE_RECT_S;
  flConfidence: Single;
  s32PlateIntensity: Integer;
  ePlateColor: Integer;
  ePlateType: Integer;
  astReserve: array[0..47] of Char;
end;

type
PSpaceOutput = ^ICE_PARKING_SPACE_OUTPUT_S;
ICE_PARKING_SPACE_OUTPUT_S = record
  enParkingPlaceStatus: Integer;
  stPlateInfo: ICE_PARKING_SPACE_VLPR_OUTPUT_S;
  s32CarType: Integer;
  s32EventType: Integer;
  s32Reserved: array[0..29] of Integer;
end;

type
PSpaceResult = ^ICE_PARKING_SPACE_RESULT_S;
ICE_PARKING_SPACE_RESULT_S = record
  u8ParkingPlaceNum: Byte;
  astOutput: array[0..5] of ICE_PARKING_SPACE_OUTPUT_S;
  s32PicDataLen: Integer;
  s32Reserved: array[0..15] of Integer;
end;

type
ICE_IPG_PLACE_PARAM_S = record
  stRecRect: ICE_RECT_S;
  isAvalable: Integer;
  u32Reserved: array[0..7] of Integer;
end;

type
PIpgConfig = ^ICE_IPG_PLACE_CONFIG_S;
ICE_IPG_PLACE_CONFIG_S = record
  u8ParkingPlaceNum: Byte;
  bSpecialPlace: Integer;
  stPlaceParam: array[ 0..7] of ICE_IPG_PLACE_PARAM_S;
  u32Reserved: array[0..63] of Integer;
end;

type ICE_IPCSDK_OnDeviceEvent = procedure(pvParam: Pointer; pcIP: PChar;
  u32EventType: ICE_U32; u32EventData1: ICE_U32; u32EventData2: ICE_U32;
  u32EventData3: ICE_U32; u32EventData4: ICE_U32);stdcall;

procedure ICE_IPCSDK_SetDeviceEventCallBack(hSDK: ICE_HANDLE; pfOnDeviceEvent: ICE_IPCSDK_OnDeviceEvent;
                                            pvParam: Pointer); cdecl; external DLL_ICE

procedure ICE_IPCSDK_Init(); cdecl; external DLL_ICE

procedure ICE_IPCSDK_Fini(); cdecl; external DLL_ICE

function ICE_IPCSDK_Login(pcIP: ICE_PCHAR; pcReserve1: ICE_PCHAR; pcReserve2: ICE_PCHAR;
                          nReserve1: PUINT; nReserve2: PUINT; nReserve3: PUINT;
                          u32SyncTime: ICE_U32): ICE_HANDLE; cdecl; external DLL_ICE

procedure ICE_IPCSDK_Logout(hSDK: ICE_HANDLE); cdecl; external DLL_ICE

function ICE_IPCSDK_StartStream(hSDK: ICE_HANDLE; u8MainStream: ICE_U8; hWnd: ICE_U32): ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetSingleParkingSpaceStatus(hSDK: ICE_HANDLE; u32SpaceCode: ICE_U32; u32SpaceNum: PUINT;
            pstResult: PSpaceOutput; pcPicData: PChar; u32Sizez: ICE_U32; pu32PicLen: ICE_PU32;
            pcReserve: PChar; u32Reserve: ICE_U32; pu32Reserve: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetAllParkingSpaceStatus(hSDK: ICE_HANDLE; pstResult: PSpaceResult; pcPicData: PChar;
            u32Size: ICE_U32; pu32PicLen: ICE_PU32; pvReserve: Pointer; u32Reserve: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SetParkingSpaceType(hSDK: ICE_HANDLE; u32SpaceCode: ICE_U32; u32SpaceType: ICE_U32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetParkingSpaceType(hSDK: ICE_HANDLE; u32SpaceCode: ICE_U32; u32SpaceType: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SetEnableParkingSpace(hSDK: ICE_HANDLE; u32SpaceCode: ICE_U32; u32Enable: ICE_U32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetEnableParkingSpace(hSDK: ICE_HANDLE; u32SpaceCode: ICE_U32; u32Enable: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetRemoteDevState(hSDK: ICE_HANDLE; u32IsRemote: ICE_PU32; pcRemoteIp: PChar;
                                      u32Reserve1: ICE_PU32; u32Reserve2: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SetRemoteDevState(hSDK: ICE_HANDLE; u32IsRemote: ICE_U32; pcRemoteIp: PChar;
                                      u32Reserve1: ICE_U32; u32Reserve2: ICE_U32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetControlDevState(hSDK: ICE_HANDLE; u32IsControlled: ICE_PU32; pcControlIp: PChar;
                                        u32Reserve1: ICE_PU32; u32Reserve2: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SetControlDevState(hSDK: ICE_HANDLE; u32IsControlled: ICE_U32; pcControlIp: PChar;
                                        u32Reserve1: ICE_U32; u32Reserve2: ICE_U32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_GetAllParkingSpaceLoops(hSDK: ICE_HANDLE; pstParam: PIpgConfig; nWidth: ICE_U32; nHeight: ICE_U32):ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SetAllParkingSpaceLoops(hSDK: ICE_HANDLE; pstParam: PIpgConfig; nWidth: ICE_U32; nHeight: ICE_U32):ICE_U32; cdecl; external DLL_ICE

type ICE_IPCSDK_OnParkingSpaceInfo = procedure(pvParam: Pointer; pcIP: ICE_PCHAR; pstParkingResult: PSpaceResult; pcPicData: PChar;
                                          u32PicLen: ICE_U32; pvReserve: Pointer; u32Reserve1: ICE_U32; u32Reserve2: ICE_U32;
                                          u32Reserve3: ICE_U32; u32Reserve4: ICE_U32);stdcall;

procedure ICE_IPCSDK_SetParkingSpaceInfoCallBack(hSDK: ICE_HANDLE; pfParkingSpaceInfo: ICE_IPCSDK_OnParkingSpaceInfo;
                                                  pvParam: Pointer); cdecl; external DLL_ICE

function ICE_IPCSDK_GetParkingSpaceNum(hSDK: ICE_HANDLE; u32SpaceNum: ICE_PU32):ICE_U32; cdecl; external DLL_ICE

type ICE_IPCSDK_OnSerialPort = procedure(pvParam: Pointer; pcIP: PChar; pcData: PChar; u32Len: ICE_U32);stdcall;

procedure ICE_IPCSDK_SetSerialPortCallBack(hSDK: ICE_HANDLE; pfOnSerialPort: ICE_IPCSDK_OnSerialPort;
                                            pvSerialPortParam: Pointer); cdecl; external DLL_ICE

type ICE_IPCSDK_OnSerialPort_RS232 = procedure(pvParam: Pointer; pcIP: PChar; pcData: PChar; u32Len: ICE_U32);stdcall;

procedure ICE_IPCSDK_SetSerialPortCallBack_RS232(hSDK: ICE_HANDLE; pfOnSerialPort: ICE_IPCSDK_OnSerialPort_RS232;
                                            pvSerialPortParam: Pointer); cdecl; external DLL_ICE

 type
  ice_uart = record
    uartEn: Integer; //串口是否使能0 不适用，1使用，默认为1使用
    uartWorkMode: Integer; //串口工作模式，0:车牌协议，1:透明串口，默认为0 车牌协议
    baudRate: Integer;  //波特率，默认值为9600，常用波特率 1200、2400、4800、9600、19200、38400、115200
    dataBits: Integer;  //数据位，默认值为 8，可选值为： 5、6、7、8
    parity: Integer;    //校验位，默认值为 无，可选值为：无、奇校验、偶校验、标记、空格
    stopBits: Integer;  //停止位，默认值为 1，可选值为：1、2
    flowControl: Integer; //流控模式，默认值为 无，可选值为：  无、硬件，Xon/Xoff
    as32Reserved: array[0..4] of Integer; //预留参数
  end;

  type
  PUartParam = ^ICE_UART_PARAM;
  ICE_UART_PARAM = record
    uart_param: array[0..1] of ice_uart;//多个串口说明
    as32Reserved: array[0..9] of Integer;//预留参数
  end;
  
function ICE_IPCSDK_GetUARTCfg(hSDK: ICE_HANDLE; pstUARTCfg: PUartParam): ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SetUARTCfg(hSDK: ICE_HANDLE; pstUARTCfg: PUartParam): ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_TransSerialPort(hSDK: ICE_HANDLE; pcData: ICE_PCHAR; u32Len: ICE_U32): ICE_U32; cdecl; external DLL_ICE
function ICE_IPCSDK_TransSerialPort_RS232(hSDK: ICE_HANDLE; pcData: ICE_PCHAR; u32Len: ICE_U32): ICE_U32; cdecl; external DLL_ICE

procedure ICE_IPCSDK_SearchDev(szDevs: ICE_PCHAR);cdecl; external DLL_ICE
procedure ICE_IPCSDK_ModifyDevIP(szMac: ICE_PCHAR; szIP: ICE_PCHAR; szMask: ICE_PCHAR; szGateway: ICE_PCHAR);cdecl; external DLL_ICE

  type
  PLightCtrlParam = ^LightCtlParam;
  LightCtlParam = record
    u8LightEn: Byte;
    u8Color: Byte;
    u32Reserved: array[0..7] of Byte;
  end;

function ICE_IPCSDK_SetLightCtlParam(hSDK: ICE_HANDLE; pstParam: PLightCtrlParam): ICE_U32; cdecl; external DLL_ICE
function ICE_IPCSDK_GetLightCtlParam(hSDK: ICE_HANDLE; pstParam: PLightCtrlParam): ICE_U32; cdecl; external DLL_ICE

function ICE_IPCSDK_SyncTime(hSDK: ICE_HANDLE; u16Year: ICE_U16; u8Month: ICE_U8; u8Day: ICE_U8; u8Hour: ICE_U8;
                            u8Min: ICE_U8; u8Sec: ICE_U8): ICE_U32; cdecl; external DLL_ICE
function ICE_IPCSDK_GetDevTime(hSDK: ICE_HANDLE; u16Year: ICE_PU16; u8Month: ICE_PU8; u8Day: ICE_PU8; u8Hour: ICE_PU8;
                            u8Min: ICE_PU8; u8Sec: ICE_PU8): ICE_U32; cdecl; external DLL_ICE

  type
  PHttp_conf_t = ^http_conf_t;
  http_conf_t = record
    http_enable: Integer;
    http_addr: array[0..511] of Byte;
    small_pic: Integer;
    big_pic: Integer;
    upload_enable: Integer;
    upload_interval: Integer;
    heartbeat_enable: Integer;
    heartbeat_interval: Integer;
  end;

  function  ICE_IPCSDK_GetCGIParam(hSDK: ICE_HANDLE; param: PHttp_conf_t): ICE_U32; cdecl; external DLL_ICE
  function  ICE_IPCSDK_SetCGIParam(hSDK: ICE_HANDLE; param: PHttp_conf_t): ICE_U32; cdecl; external DLL_ICE
implementation
end.

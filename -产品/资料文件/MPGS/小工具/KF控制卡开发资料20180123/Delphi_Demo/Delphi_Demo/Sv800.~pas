unit Sv800;

interface
{ 使用方法：
  1、创建对象：Init_Comm(COM1);
  2、调用 GetIoInfo(Sy_id,SameCT:string) 获取IO记录， sy-id:，SameCT: 同一张卡刷卡的间隔时间  ;
  3、调用 nsv800.Run(max,min,); 方法，起动主板扫描;
          nsv800.SendType:=True; 设置SendType:标志;
  4、调用 nsv800.GetIoInfo; 获取采集的出入记录。
}

uses
  SysUtils, Windows, Messages, Classes, Graphics, Controls,  HR_KFLED,
  Forms, Dialogs,  Extctrls,MMSystem, WinInet;

const
  
    VIHICAL_NO_LEN = 8;  ///车牌号码长度；;

  type

   VOICE_ID_E = (E_VOICE_0,  ///0-10
                 E_VOICE_1,E_VOICE_2, E_VOICE_3,E_VOICE_4,E_VOICE_5,E_VOICE_6,E_VOICE_7,E_VOICE_8,E_VOICE_9,E_VOICE_10,
                 E_VOICE_100, ///11
                 E_VOICE_1K,  ///12,千；
                 E_VOICE_1M,  ///13,万；
                 E_VOICE_POINT, ///14,点；
                 E_VOICE_YUAN,  ///15,元；
                 E_VOICE_YEAR,  ///16,年；
                 E_VOICE_DAY,  ///17 日；
                 E_VOICE_DATE, ///18, 天；
                 E_VOICE_JAN,   ///19, 1月
                 E_VOICE_FEB,E_VOICE_MARCH,E_VOICE_APRIL,E_VOICE_MAY,E_VOICE_JUN,E_VOICE_JULY,E_VOICE_AUG,
                 E_VOICE_SEPT,E_VOICE_OCT,E_VOICE_NOV,E_VOICE_DEC, //30 ; 12月；
                 E_VOICE_BAD_CARD,  //31 此卡无效；
                 E_VOICE_LOSS_CARD, //32 挂失卡，
                 E_VOICE_NOAUTHOR,    //33 无授权卡
                 E_VOICE_OUTTIME,     //34 你的卡过期 XX 天，
                 E_VOICE_OUT_TODAY,    //35 你的卡今天到期；
                 E_VOICE_CARD_INFO,    //36: 你的卡有效期到：xx年xx月xx日  ;
                 E_VOICE_RE_ENTER,  //37重复进场；
                 E_VOICE_RE_EXIT,    ///38 重复出场；
                 E_VOICE_IN,      ///39 欢迎光临
                 E_VOICE_OUT,  ///40 一路顺风
                 E_VOICE_VEHICAL_TYPE,  ///41车型
                 E_VOICE_CHARGE, ///42: 收费
                 E_VOICE_WAIT, ///43 请稍后；
                 E_VOICE_PORT_ENTER,  //44; 入口xx,
                 E_VOICE_PORT_EXIT,  ///45: 出口xx,
                 E_VOICE_PORT_ENTER_EXIT, ///46：出入口ｘｘ；　
                 E_VOICE_FORBIT_INOUT, ////47: 禁止时出 ；
                 E_VOICE_STAY_TIME,  // 48停留时间 ;
                 E_VOICE_STAY_HOUR,  //小时，
                 E_VOICE_STAY_MINI,  //分钟；
                 E_VOICE_GET_CARD,
                 E_VOICE_READ_CARD,
                 E_VOICE_FORBIT_READ,
                 E_VOICE_RES2,
                 E_VOICE_RES3,
                 E_VOICE_RES4,
                 E_VOICE_RES5,
                 E_VOICE_MAX
                 );


  pCTRL_CONFIG_T = ^CTRL_CONFIG_T;
  CTRL_CONFIG_T = record
    timeout_delay: char;
    voice_volume: char;
    res:array[0..4] of Char;
    led_len:Char;
    led_txt:array[0..63] of char;
  end;


  pRS485_VOICE_DATA_HEAD = ^RS485_VOICE_DATA_HEAD;
  RS485_VOICE_DATA_HEAD = record
    port_type: char;   ////0：入口， 1：出口；
    voice_len: char;   ////语音长度;
    is_clean_prev:Char; ////1：清除之前的语音；
    res:Char;
  end;

  pRS485_LED_DATA_HEAD = ^RS485_LED_DATA_HEAD;
  RS485_LED_DATA_HEAD = record
    port_type: char;   ////0：入口， 1：出口；
    text_len: char;   ////Led长度;
    res:array[0..1] of char;
  end;

  pRS485_CARD_DATA_BANK_HEAD = ^RS485_CARD_DATA_BANK_HEAD;
  RS485_CARD_DATA_BANK_HEAD = record
    min_card_no: Integer;   ////最大的卡号；
    max_card_no: Integer;   ////最小的卡号；
    index:Integer; ///序号
  end;

  pRS485_DATE_T = ^RS485_DATE_T;
  RS485_DATE_T = record
    year: Char;   ////卡号；
    month:Char ;   ////有效期
    Date: char; ///序号
    wdate:char; // 0-6 星期天 - 六；
  end;

  pRS485_TIME_T = ^RS485_TIME_T;
  RS485_TIME_T = record
    year: Char;   ////卡号；
    month:Char ;   ////有效期
    Date: char; ///序号
    wdate:char; // 0-6 星期天 - 六；
    hour:char;
    sencond:Char;
    res:Char;
  end;

  pRS485_CARD_INFO_T = ^RS485_CARD_INFO_T;
  RS485_CARD_INFO_T = record
    card_no: Integer;   ////卡号；
    effect_date: RS485_DATE_T ;   ////有效期
    vihical_no:array[0..VIHICAL_NO_LEN] of char; ///序号
    flag:char;     ///bit:0,持失， bit：1 ：黑名单；
    res:array[0..2] of Char;
  end;

  pRS485_LOG = ^RS485_LOG;
  RS485_LOG = record
    card_no:Integer;   ////卡号；
    curr_time:RS485_TIME_T ;   ////有效期
    log_event: char; ///序号
    log_flag:char; // 0-6 星期天 - 六；
    res:array[0..1] of char;
  end;

  pLOCAL_INFO = ^LOCAL_INFO;
  LOCAL_INFO = record
    switch_Set:char;   ////拨码开关；；
    loop:RS485_TIME_T ;   ////有效期
    res:array[0..2] of char; ///序号
    time:RS485_TIME_T; // 0-6 星期天 - 六；
    reader1_card_no:Integer;
    reader2_card_no:Integer;
  end;

  pREADER_CARD_T = ^READER_CARD_T;
  READER_CARD_T = record
    read_id:char;   ////拨码开关；；
    res:array[0..2]of Char;    ////有效期
    card_no:integer; ///序号
  end;


    Function Init_Comm(Port:String):integer; stdcall;
    procedure Close_Comm(Port:String); stdcall;
    function HaveSigned(MaxWaitTime: Cardinal): Boolean; stdcall;
    function HaveSignedA(MaxWaitTime: Cardinal): Boolean; stdcall;

//    Function ShowLed(LedStr,LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;

  //  Function Ledspack(LedStr, LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;
    Function setVLNum(LedNum, LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;


    Function ShowLedSycw(LedStr,LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;

    Function ShowLedljxs(LedStr,LedAddr:PChar; Time:Byte; aobj:Pointer= nil):integer;  Stdcall;
    Function ShowLedGG(LedStr:PChar; LedAddr, Section,Move,Stay,Time:Byte; aobj:Pointer= nil):integer;  Stdcall;  /// 广告
 //   Function ShowLeddebug(LedStr:PChar; LedAddr, Section,Move,Stay,Time:Byte; aobj:Pointer= nil):integer;  Stdcall;  /// 广告
    function SetLpTime(LedAddr:PChar; aobj:Pointer = nil):integer; Stdcall;

    function ChangeLPAdd(Address,NewAddress,Section:Byte;aobj:Pointer= nil):Byte; StdCall;
    Function ClearDP(Address,Section:Byte;aobj:Pointer= nil):Byte; StdCall;


    function WritePort(Time: Integer; s: string; aobj:Pointer= nil;  LedType:Integer = 1): string;
    function SendCommand(Address, Command, Sect: Byte; str: PChar; aobj:Pointer= nil): Byte; stdcall;
    function ResultHandle(s: string): Byte;

    function DisplayTextold(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
    function DisplayTextspackandshow(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

    function DisplayText(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

    function DisplayTextSpack(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;


 //   function HR_KFDisplayText(DA, , TWID,ETM,ETS,DM,DT,EXM,EXS,FINDEX,DRS,TC,BC,TL,TEXT,
  //  Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFDisplayText(DA, TWID,ETM,ETS,DM,DT,EXM,EXS,FINDEX,DRS,TC,BC,TL:string; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

    

    function HR_KFDisplayTextYW(DA, TWID,ETM,ETS,DM,DT,EXM,EXS,FINDEX,DRS,TC,BC,TL:string; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFGGDisplayText(DA, TWID,FID,AF,ETM,ETS,DM,DT,EXM,EXS,FINDEX,TC,BC,TL:string; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFShowTimes(DA: string ; TWID: string;  FIDs: String; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFClearDisplayText(DA, TWID,FID:string; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFStopDsplayText(DA, TWID:string; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFSetTime(DA:string; Timestr:string; aobj:Pointer= nil): Byte; stdcall;

    function HR_KFNewAdd(DA:string; NewAdd:string; aobj:Pointer= nil): Byte; stdcall;


    function HR_KFSpack(DA: string ; SpType: string;  LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
    function HR_KFSetDatatype(DA: string ; SpType: string;   aobj:Pointer= nil): Byte; stdcall;
    function HR_KFSetOEtype(DA: string ; SpType: string;   aobj:Pointer= nil): Byte; stdcall;

    Function HR_KFShowLedSycw(LedStr:PChar; DA:string; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;



    function DisplaySetSpackVoc(Address, Section, vl:Byte; aobj:Pointer= nil): Byte; stdcall;



    function DisplayTime(Address, Section:Byte; aobj:Pointer= nil): Byte; stdcall;
    function OpenMain( Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
    function CloseMain(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
    function OpenSection(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;

    function  CloseSection(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
    function  DisplaySection(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
    function  SetupTime(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
    function  ChangeAddress(Address, LastAddress: Byte; aobj:Pointer= nil): Byte; stdcall;
    function  ClearMem( Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
    function  ChangeLength(Address, Length: Byte; aobj:Pointer= nil): Byte; stdcall;
    function  ChangeRows( Address, Rows: Byte; aobj:Pointer= nil): Byte; stdcall;
    function   DownloadSection(Address, Sect: Byte; LpStr: PChar; aobj:Pointer= nil): Byte; stdcall;
    procedure  SendLedMessage(LedStr:String; aObj:Pointer = nil); stdcall;

    function  setCardLen(CardNo:Integer):string;  stdcall;
    function  setSyidLen(Syid:Integer):string;  stdcall ;
    procedure  Debug(msg:string); stdcall
    function  bakText(str:string):integer; stdcall ;
    function  AsciiToHex(str: string): string;

    function SpackvocTest(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;



  var

    hComPort:Cardinal;
    CanRead:Boolean;
    OldCard:string;
    OldCardNum:Integer;
    OpenDoorNum:integer;
    OpenDoorNumError:integer;
    aBuff:PChar;
    cmd,sy_id,IoDataNo,CardNo,CardID,IOdateTime,Status,ModuleNo,OrdCardID:string;

  const
    STX = $02;   //命令开始.
    ETX = $03;   //命令结束
    ACK = $06;   //确认
    NACK = $07;  //非确认
    SERR = $08;  //扇区没有内容
    CLF = $0c;   //行起始字符,扇区打开.
    CLS = $0d;   //扇区关闭字符

    OPMAIN = $20;  //主策略显示*,带*号的命令其无数据字符或数据字符无意义
    CLMAIN = $21;  //主策略关闭*
    OPSECT = $22;  //打开扇区*
    CLSECT = $23;  //关闭扇区*
    DPSECT = $24;  //显示扇区*  常用命令!
    DLSECT = $25;  //下载扇区   常用命令!
    DLsect9A = $9A;  //控制显示屏
    STTIME = $26;  //设置时间
    CHADDR = $27;  //更换地址*
    CLRMEM = $28;  //清除内存*
    DLFONT = $29;  //下载点阵
    CHLENG = $2a;  //更改长度*
    CHROWS = $2b;  //更改行数*
    DP_TTS = $2c;  //文本发音.

    function PARKCOM_OpenGate_Buff(Ctrlid:Byte; gatetype:Byte; retbuff:PChar; retlen:PInteger):Integer; cdecl; external 'ParkCom.dll';

    function PARKCOM_PACK_RESOLVE(packbuff:PChar; packlen:Integer; retbuff:PChar; retlen:pInteger; ctrlid:PInteger; rettype:PInteger):Integer; cdecl; external 'ParkCom.dll';

    function PARKCOM_HeartBeat_Buff(ctrlid:Byte; retbuff:PChar; retlen:PInteger):Integer; cdecl; external 'ParkCom.dll';

    function PARKCOM_DisplayVoice_Buff(ctrlid:Byte; voicehead:RS485_VOICE_DATA_HEAD; pvoicedata:PChar; retbuff:PChar; retlen:PInteger):Integer; cdecl; external 'ParkCom.dll';


    function StrToHexStr2(const S:string):string; stdcall ;
    function StrToHexStrHK(const S:string; SendChar:PChar ):string; stdcall ;
    function StrToHexStr3(const S:string;  b:PByteArray):PByteArray; stdcall ;
    function HexToInt (str:string) : word; stdcall;
    function StrToHexStr1(const S:string):string;  stdcall ;
    function StrToHexStr(const S:string):string; stdcall ;

//    ///--Arm 控制板协议--------------------------------------------------------------------------
//    function ArmGetLedCode(LedStr:string):String; stdcall;
//    function ArmGetLedCode2(LedStr:string):String; stdcall;
//    Function ArmInitSystem(Sy_id:string):integer; stdcall;
//    Function ArmSetModel(Sy_id:string; aType:integer):integer; stdcall;
//    Function ArmScanInfo(Sy_id:string):integer; stdcall;
//    Function ArmGetFee(Sy_id:string):integer; stdcall;
//    Function ArmSetFee(Sy_id:string):integer; stdcall;

    function DecToHexStr(Buff:PChar; num:Integer):string; stdcall;
//    Function ArmGetIDCardID(Sy_id:string):String; stdcall;

//
//    Function ArmCRC(CardID:string):string; stdcall;
//    Function ArmOpenDoor(Sy_id:string; Time:string):integer; stdcall;
//    Function ArmCloseDoor(Sy_id:string; Time:string):integer; stdcall;
//    Function ArmSetDateTime(Sy_id:string; Time:string):integer; stdcall;
//    Function ArmGetDateTime(Sy_id:string):String; stdcall;
//    Function ArmShowLed(Sy_id:string; LedStr:string):integer; stdcall;
//    Function ArmAddCard(Sy_id:string; CardID:string):integer; stdcall;
//    Function ArmDelCard(Sy_id:string; CardID:string):integer; stdcall;
//    Function ArmGetCard(Sy_id:string; CardID:string):String; stdcall;
//
//    Function ArmShowLedTest(Sy_id:string; LedStr:string):integer; stdcall;

//
//    Function GetYsCRC(Str:string):string;
//    procedure  YsOpenLed();
//    procedure  YsCloseLed();
//    Procedure  YsSendStr(Str:string);
//    Procedure  YsSendGG(Str:string; LedAdd:Integer=1; LedNo:Integer=1; StrNo:Integer=1; activ:string='01'; speed:string='0A'; stop:string='00');
//    Procedure  YsSendDT(Str:string; LedAdd:Integer=1; LedNo:Integer=1; StrNo:Integer=1; activ:string='01'; speed:string='0A'; stop:string='00');
//    Procedure  YsSend(Str:string; LedAdd:Integer=1; LedNo:Integer=1; StrNo:Integer=1; activ:string='01'; speed:string='0A'; stop:string='00'; aobj:Pointer= nil);
//
//    Function  YsSetTime(Str:string; LedAdd:Integer=1;aobj:Pointer= nil):Integer; stdcall;
//
//    Function  YsSetDateCS(width,Heigh,color,Date,OE:Integer; LedAdd:Integer=1;aobj:Pointer= nil):Integer; stdcall;

//    字节0：显示屏宽度（单位：像素）/8
//字节1：屏高（单位：像素）/8
//字节2：颜色类型，1=普通；2=增强双色；3=彩色；（目前不支持彩色）
//字节3：数据极性，0=负极性；1=正极性
//字节4：OE极性，0=负极性；1=正极性
//



implementation




Function Init_Comm(Port:String):Integer;
var
   cc:TCommConfig;
begin
   if hcomPort = 0 then
   begin
       hComPort:=CreateFile(PChar(Port),GENERIC_READ or GENERIC_WRITE,0,nil,OPEN_EXISTING,0,0);
       if (hComPort=invalid_handle_value) then
       begin
         Result:=1;
         Exit;
       end;
       GetCommState(hComPort,cc.dcb);
       cc.dcb.BaudRate:=CBR_19200;
       cc.dcb.Parity:=EVENPARITY;
       cc.dcb.ByteSize:=8;
       cc.dcb.StopBits:=ONESTOPBIT;
       if not SetCommState(hComPort,cc.dcb) then
          begin
            if not  BuildCommDCB('19200,e,8,1',cc.dcb) then
              begin
                Result:=1;
                CloseHandle(hComPort);
                hComPort:=0;
                Exit;
              end
            else  Result:=0;
          end
       else   Result:=0;
       CanRead:= True;
   end;
end;

procedure Close_Comm(Port:String);
begin
  CanRead:= False;
   if  hComPort = 0 then
       Exit;
       CloseHandle(hComPort);
       hComPort:=0;
end;


Procedure SameCardTime();
begin
   OrdCardID:='';
end;





function DecToHexStr(Buff:PChar; num:Integer):string; stdcall
//字符串转换成16进制字符串
var
  I:Integer;
begin
  for I:=0 to num -1 do
  begin
    if I=0 then
      Result:=IntToHex(Ord(Buff[0]),2)
    else Result:=Result+IntToHex(Ord(Buff[I]),2);
  end;
end;


{ THnComm }
                             


function StrToHexStr(const S:string):string;
//字符串转换成16进制字符串
var
  I:Integer;
begin
  for I:=1 to Length(S) do
  begin
    if I=1 then
      Result:=IntToHex(Ord(S[1]),2)
    else Result:=Result+' '+IntToHex(Ord(S[I]),2);
  end;
end;

function StrToHexStr1(const S:string):string;
//字符串转换成16进制字符串
var
  I:Integer;
begin
  for I:=1 to Length(S) do
  begin
    if I=1 then
      Result:=IntToHex(Ord(S[1]),2)
    else Result:=Result+IntToHex(Ord(S[I]),2);
  end;
end;

function HexToInt (str:string) : word;
var
   i , value : word;
   pos : word;
begin
   value:=0;
   pos:=length(str);
  for i:=1 to pos  do
  begin
      case str[i] of
      'f','F':
              value := value*16+15;
      'e','E':
              value := value*16+14;
      'd','D':
              value := value*16+13;
      'c','C':
              value := value*16+12;
      'b','B':
              value := value*16+11;
      'a','A':
              value := value*16+10;
      '0'..'9':
              value := value*16+ord(str[i])-ord('0');
      else
         result:=value;
         exit;
      end;
   result:=value;
  end;

end;

function StrToHexStr3(const S:string;  b:PByteArray):PByteArray;
//字符串转换成16进制字符串
var
  I:Integer;
  Len:Integer;
begin
  Len:= Length(S) ;
  Len:= Len div 2;
  for i:= 0 to Len do
    begin
       b[i]:= HexToInt(Copy(S,i * 2+1,2));
    end;
  Result:= b;
end;

function StrToHexStr2(const S:string):string;
//字符串转换成16进制字符串
var
  I:Integer;
begin
  for I:=1 to Length(S) do
  begin
    if I=1 then
      begin
      Result:=PChar(IntToHex(Ord(S[1]),2))
      end
    else
      begin
        Result:=PChar(Result+IntToHex(Ord(S[I]),2));
      end;
  end;
end;


function StrToHexStrHK(const S:string; SendChar:PChar):string; stdcall ;
//字符串转换成16进制字符串
var
  I:Integer;
begin
  for I:=1 to Length(S) do
  begin
    if I=1 then
      begin
      Result:=PChar(IntToHex(Ord(S[1]),2))
      end
    else
      begin

        Result:=PChar(Result+IntToHex(Ord(S[I]),2));
      end;
  end;
end;



function HaveSigned(MaxWaitTime: Cardinal): Boolean;
var
  WaitedTime: Cardinal;
begin
  WaitedTime:=0;
     while  (WaitedTime<MaxWaitTime)   do
        begin
           SleepEx(50,False);
           Inc(WaitedTime,50);
        end;
end;


function HaveSignedA(MaxWaitTime: Cardinal): Boolean; stdcall;
var
  WaitedTime: Cardinal;
begin
  WaitedTime:=0;
     while  (WaitedTime<MaxWaitTime)   do
        begin
           SleepEx(50,False);
           Inc(WaitedTime,50);
           Application.ProcessMessages;
        end;
end;

              
                      
function setCardLen(CardNo:Integer):string;
begin
  if CardNo > 0 then
  case  Length(IntToStr(CardNo)) of
    1:  Result:= '000000000000000'+ IntToStr(CardNo);
    2:  Result:= '00000000000000'+ IntToStr(CardNo);
    3:  Result:= '0000000000000'+ IntToStr(CardNo);
    4:  Result:= '000000000000'+ IntToStr(CardNo);
    5:  Result:= '00000000000'+ IntToStr(CardNo);
    6:  Result:= '0000000000'+ IntToStr(CardNo);
    7:  Result:= '000000000'+ IntToStr(CardNo);
    8:  Result:= '00000000'+ IntToStr(CardNo);
    9:  Result:= '0000000'+ IntToStr(CardNo);
    10: Result:= '000000'+ IntToStr(CardNo);
    11: Result:= '00000'+ IntToStr(CardNo);
    12: Result:= '0000'+ IntToStr(CardNo);
    13: Result:= '000'+ IntToStr(CardNo);
    14: Result:= '00'+ IntToStr(CardNo);
    15: Result:= '0'+ IntToStr(CardNo);
    16: Result:=  IntToStr(CardNo);
  end;
end;
              
function AsciiToHex(str: string): string;
var  i:integer;
     changestr:string;
begin
    changestr:='';
    for i:=1 to length(str) do
    changestr:=changestr+inttohex(ord(str[i]),2);
    AsciiToHex:=changestr;
end;


procedure  Debug(msg:string);
begin
   OutputDebugString(pchar(FormatDateTime('yyyy-mm-dd hh:mm:ss - zzz',Now)+' :' +Msg));
end;

function setSyidLen(Syid:Integer):string;
begin
  if Syid > 0 then
  case  Length(IntToStr(Syid)) of
    1:  Result:= '0'+ IntToStr(Syid);
    2:  Result:= IntToStr(Syid);
  end;
end;


Function ShowLedSycw(LedStr,LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;
begin
   CanRead:= False;
   Try
   HaveSigned(5);
    Try
      if Ledaddr <> ''  then
         begin
           if Length(LedStr) > 8 then
              begin
                 if GateNo <> '' then
                   begin
                       if aobj <> Nil then    DisplayTextold(StrtoInt(LedAddr), 220, 21, 0, 3, 21, LedStr,aobj);
//                     if GateNo = VideoIn.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 21, 0, 3, 21, LedStr,VideoIn);
//                     if GateNo = VideoOut.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 21, 0, 3, 21, LedStr,VideoOut);
//                     if GateNo = Video3.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 21, 0, 3, 21, LedStr,Video3);
//                     if GateNo = Video4.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 21, 0, 3, 21, LedStr,Video4);
                   end
                 else
                   DisplayTextold(StrtoInt(LedAddr), 220, 21, 0, 3, 21, LedStr,aobj);
             end
           else
             begin
                 if GateNo <> '' then
                   begin   
                       if aobj <> Nil then    DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 255, 0, LedStr,aobj);
                  //  if GateNo = VideoIn.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 0, 0, 255, 0, LedStr,VideoIn);
                  //   if GateNo = VideoOut.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 0, 0, 255, 0, LedStr,VideoOut);
                  //   if GateNo = Video3.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 0, 0, 255, 0, LedStr,Video3);
                  //   if GateNo = Video4.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 100, 0, 0, 255, 0, LedStr,Video4);
                   end
                 else
                   DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 255, 0, LedStr,aobj);
             end;
         end;
    Except
      Result:=1;
    end;
    finally
   CanRead:= True;
   end;
end;

Function setVLNum(LedNum, LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;
begin
   CanRead:= False;
   Try
   HaveSigned(5);
    Try
//      if Ledaddr <> ''  then
//         begin
//             if GateNo <> '' then
//               begin
//                 if aobj <> Nil then   DisplaySetSpackVoc(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,aobj);
////                 if GateNo = VideoIn.OpenGate then   DisplaySetSpackVoc(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,VideoIn);
////                 if GateNo = VideoOut.OpenGate then   DisplaySetSpackVoc(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,VideoOut);
////                 if GateNo = Video3.OpenGate then   DisplaySetSpackVoc(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,Video3);
////                 if GateNo = Video4.OpenGate then   DisplaySetSpackVoc(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,Video4);
//               end
//             else
//               DisplaySetSpackVoc(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,aobj);
//         end;
    Except
      Result:=1;
    end;
    finally
   CanRead:= True;
   end;
end;

//
//
//Function Ledspack(LedStr,LedAddr:PChar; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;
//var
//   i:integer;
//begin
//   CanRead:= False;
//   Try
//   HaveSigned(5);
//    Try
//      if Ledaddr <> ''  then
//         begin
//           if Length(LedStr) > 8 then
//              begin
//                 if GateNo <> '' then
//                   begin
//                     if aobj <> Nil then   DisplayTextspack(StrtoInt(LedAddr), 220, 21, 0, 5, 21, LedStr,aobj)
//                     else
//                       begin
//                          for i:= 0 to Park_SysVar.FVideoList.Count -1 do
//                            begin
//                                if GateNo = TVideo(Park_SysVar.FVideoList[i]).OpenGate then
//                                DisplayTextspack(StrtoInt(LedAddr), 220, 21, 0, 5, 21, LedStr,TVideo(Park_SysVar.FVideoList[i]));
//                            end;
//                       end;
//                   end
//                 else
//                   DisplayTextspack(StrtoInt(LedAddr), 220, 21, 0, 5, 21, LedStr,aobj);
//             end
//           else
//             begin
//                  if GateNo <> '' then
//                   begin
//                     if aobj <> Nil then   DisplayTextspack(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,aobj)
//                     else
//                       begin
//                          for i:= 0 to Park_SysVar.FVideoList.Count -1 do
//                            begin
//                                if GateNo = TVideo(Park_SysVar.FVideoList[i]).OpenGate then
//                                DisplayTextspack(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,TVideo(Park_SysVar.FVideoList[i]));
//                            end;
//                       end;
//                   end
//                 else
//                   DisplayTextspack(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,aobj);
//             end;
//         end;
//    Except
//      Result:=1;
//    end;
//    finally
//   CanRead:= True;
//   end;
//end;

//
//Function ShowLed(LedStr,LedAddr:PChar; GateNo:string= ''; aobj:Pointer= Nil ):integer;  Stdcall;
//var i:integer;
//begin
//   CanRead:= False;
//   Try
//   HaveSigned(60);
//    Try
//      if Ledaddr <> ''  then
//         begin
//           if  Park_SysVar.LedLeve = 1 then
//             begin
//                 if Length(LedStr) > 8 then
//                   begin
//                         if GateNo <> '' then
//                           begin
//                             if aobj <> Nil then   DisplayTextold(StrtoInt(LedAddr), 220,21, 0, 5,21, LedStr,aobj)
//                             else
//                               begin
//                                  for i:= 0 to Park_SysVar.FVideoList.Count -1 do
//                                    begin
//                                        if GateNo = TVideo(Park_SysVar.FVideoList[i]).OpenGate then
//                                        DisplayTextold(StrtoInt(LedAddr), 220, 21, 0, 5, 21, LedStr,TVideo(Park_SysVar.FVideoList[i]));
//                                    end;
//                               end;
//                           end
//                         else
//                           DisplayTextold(StrtoInt(LedAddr), 220, 21, 0, 5, 21, LedStr,aobj);
//                   end
//                 else
//                   begin
////                       if GateNo <> '' then
////                         begin
////                           if GateNo = VideoIn.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,VideoIn);
////                           if GateNo = VideoOut.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,VideoOut);
////                           if GateNo = Video3.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,Video3);
////                           if GateNo = Video4.OpenGate then   DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,Video4);
////                         end
////                       else
////                         DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,aobj);
//
//
//                         if GateNo <> '' then
//                           begin
//                             if aobj <> Nil then   DisplayTextold(StrtoInt(LedAddr), 220,0, 0, 5,0, LedStr,aobj)
//                             else
//                               begin
//                                  for i:= 0 to Park_SysVar.FVideoList.Count -1 do
//                                    begin
//                                        if GateNo = TVideo(Park_SysVar.FVideoList[i]).OpenGate then
//                                        DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,TVideo(Park_SysVar.FVideoList[i]));
//                                    end;
//                               end;
//                           end
//                         else
//                           DisplayTextold(StrtoInt(LedAddr), 220, 0, 0, 5, 0, LedStr,aobj);
//                   end;
//             end
//           else
//               begin
//                 if Length(LedStr) > 8 then
//                    begin
////                       if GateNo <> '' then
////                         begin
////                           if GateNo = VideoIn.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,VideoIn);
////                           if GateNo = VideoOut.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,VideoOut);
////                           if GateNo = Video3.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,Video3);
////                           if GateNo = Video4.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,Video4);
////                         end
////                       else
////                         DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,aobj);
//
//                        if GateNo <> '' then
//                           begin
//                             if aobj <> Nil then   DisplayText(StrtoInt(LedAddr), 220,21, 0, 8,21, LedStr,aobj)
//                             else
//                               begin
//                                  for i:= 0 to Park_SysVar.FVideoList.Count -1 do
//                                    begin
//                                        if GateNo = TVideo(Park_SysVar.FVideoList[i]).OpenGate then
//                                        DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,TVideo(Park_SysVar.FVideoList[i]));
//                                    end;
//                               end;
//                           end
//                         else
//                           DisplayText(StrtoInt(LedAddr), 220, 21, 0, 8, 21, LedStr,aobj);
//
//                   end
//                 else
//                   begin
////                       if GateNo <> '' then
////                         begin
////                           if GateNo = VideoIn.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,VideoIn);
////                           if GateNo = VideoOut.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,VideoOut);
////                           if GateNo = Video3.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,Video3);
////                           if GateNo = Video4.OpenGate then   DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,Video4);
////                         end
////                       else
////                         DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,aobj);
//
//                          if GateNo <> '' then
//                           begin
//                             if aobj <> Nil then   DisplayText(StrtoInt(LedAddr), 220,0, 0, 8,0, LedStr,aobj)
//                             else
//                               begin
//                                  for i:= 0 to Park_SysVar.FVideoList.Count -1 do
//                                    begin
//                                        if GateNo = TVideo(Park_SysVar.FVideoList[i]).OpenGate then
//                                        DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,TVideo(Park_SysVar.FVideoList[i]));
//                                    end;
//                               end;
//                           end
//                         else
//                           DisplayText(StrtoInt(LedAddr), 220, 0, 0, 8, 0, LedStr,aobj);
//                   end;
//               end;
//         end;
//    Except
//      Result:=1;
//    end;
//   finally
//   CanRead:= True;
//   end;
//end;

Function ShowLedljxs(LedStr,LedAddr:PChar; Time:Byte; aobj:Pointer= Nil ):integer;  Stdcall;
begin    ////立即显示
   CanRead:= False;
   Try
   HaveSigned(5);
   Try
      DisplayText(StrtoInt(LedAddr), 220, 1, 0, 3, 1, LedStr,aobj);
    Except
      Result:=1;
    end;
    finally
   CanRead:= True;
   end;
end;


//
//Function ShowLeddebug(LedStr:PChar; LedAddr, Section,Move,Stay,Time:Byte; aobj:Pointer= nil):integer;  Stdcall;  /// 广告
//begin
//   CanRead:= False;
//  Try
//   HaveSigned(5);
//    Try
//     // DisplayTextSpack(LedAddr, Section, Move, Stay, Time, Move, LedStr,aobj);
//      if Park_SysVar.LedType = '语音一体屏' then
//         DisplayTextold(LedAddr, Section, Move, Stay, Time, Move, LedStr,aobj);
//
//      if Park_SysVar.LedType = 'HR控制卡' then
//         begin
//           DisplayText(LedAddr, Section, Move, Stay, Time, Move, LedStr,aobj);
//           DisplayTextSpack(LedAddr, Section, Move, Stay, Time, Move, LedStr,aobj);
//         end;
//
//      if Park_SysVar.LedType = '一体控制卡' then
//         begin
//            // HR_KFSpack(DA: Byte SpType;PChar;  LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
//            // DA : 控制卡地址：
//            // SpType: 语音播报方式：
//            //         01:添加到语音队列，但是不开始播放；
//            //         02:添加到语音队列，并且开始播放；
//            //         03:先汪队列，在添加到语音队列，然后开始播放；
//
//           HR_KFSpack(IntToStr(LedAddr), '03', LedStr, aobj);
//         end;
//    Except
//      Result:=1;
//    end;
//    finally
//   CanRead:= True;
//   end;
//end;

Function ShowLedGG(LedStr:PChar; LedAddr, Section,Move,Stay,Time:Byte; aobj:Pointer= Nil ):integer;  Stdcall;  /// 广告
begin
   CanRead:= False;
  Try
   HaveSigned(5);
    Try
      DisplayTextOld(LedAddr, Section, Move, Stay, Time, Move, LedStr,aobj);
    Except
      Result:=1;
    end;
    finally
   CanRead:= True;
   end;
end;

Function ShowDateTime(LedStr,LedAddr:PChar; Section:Byte; aobj:Pointer= Nil):integer;  Stdcall;  /// 广告
begin
   CanRead:= False;
   Try
   HaveSigned(5);
    Try
      DisplayText(StrtoInt(LedAddr), Section, 21, 0, 0, 21, LedStr,aobj);
    Except
      Result:=1;
    end;
    finally
   CanRead:= True;
   end;
end;



function WritePort(Time: Integer; s: string; aobj:Pointer= nil;  LedType:Integer = 1): string;
var    //写入字符串和读取字符串(最长为缓冲区大小),
    i: DWord;  //Timeout读取等待时间.为0则无读动作, s为空则不写入.
    Tm: TCommTimeouts;
    cmdStr:string;
    str:string;
    strarr:pByteArray;
    Len:integer;
    yyStr:string;
    RecvLen:integer;
    errcode:integer;       
    hkstr:string;
    hkPChar:PChar;
    const  MAXBUF = 10000;  //最大一次读取字节数.
begin

  if aobj <> Nil then
    begin
        if s <> '' then  //写入字符串.
        begin
          hkstr:= s;
          case LedType of
            1:
              begin
                 WriteFile(hComPort, s[1], Length(s), i, nil);
              end;

            2: begin
                 Len:= Length(s) Div 2;
                 strarr:= AllocMem(Len * 4);
                 Try
                  WriteFile(hcomPort,StrToHexStr3(s,strarr)^,Len,i,nil);
                  finally
                     FreeMem(strarr);
                  end;
               end;

            3: begin
                   Len:= Length(s) Div 2;
                   strarr:= AllocMem(Len * 4);
                   Try
                    WriteFile(hcomPort,StrToHexStr3(s,strarr)^,Len,i,nil);
                    finally
                       FreeMem(strarr);
                    end;
               end;
          end;
        end;
        if Time > 0 then
        begin
          Tm.WriteTotalTimeoutMultiplier := 1;
          Tm.WriteTotalTimeoutConstant := 500;
          Tm.ReadIntervalTimeout := 10;
          Tm.ReadTotalTimeoutMultiplier := 0;
          Tm.ReadTotalTimeoutConstant := Time;  //延时读取时间.
          SetCommTimeouts(hComPort, Tm);
          SetLength(Result, MAXBUF);
          ReadFile(hComPort, Result[1], MAXBUF, i, nil);
          SetLength(Result, i);
        end  else Result := '';
    end
  else
    begin
       if s <> '' then  //写入字符串.
        begin
          case LedType of
            1:
              begin
                // WriteFile(hComPort, s[1], Length(s), i, nil);
                   Len:= Length(s) Div 2;
                 strarr:= AllocMem(Len * 4);
                 Try
                  WriteFile(hcomPort,StrToHexStr3(s,strarr)^,Len,i,nil);
                  finally
                     FreeMem(strarr);
                  end;
              end;
            2: begin
                 Len:= Length(s) Div 2;
                 strarr:= AllocMem(Len * 4);
                 Try
                  WriteFile(hcomPort,StrToHexStr3(s,strarr)^,Len,i,nil);
                  finally
                     FreeMem(strarr);
                  end;
               end;
            3: begin
                 Len:= Length(s) Div 2;
                 strarr:= AllocMem(Len * 4);
                 Try
                  WriteFile(hcomPort,StrToHexStr3(s,strarr)^,Len,i,nil);
                  finally
                     FreeMem(strarr);
                  end;
               end;
          end;
        end;
        if Time > 0 then
        begin
          Tm.WriteTotalTimeoutMultiplier := 1;
          Tm.WriteTotalTimeoutConstant := 500;
          Tm.ReadIntervalTimeout := 10;
          Tm.ReadTotalTimeoutMultiplier := 0;
          Tm.ReadTotalTimeoutConstant := Time;  //延时读取时间.
          SetCommTimeouts(hComPort, Tm);
          SetLength(Result, MAXBUF);
          ReadFile(hComPort, Result[1], MAXBUF, i, nil);
          SetLength(Result, i);
        end  else Result := '';
    end;
end;

function ResultHandle(s: string): Byte;
begin
  CanRead:= False;
  Try
  HaveSigned(5);
//处理返回结果.
  if s = Chr(ACK)  then Result := 0 else  //0=成功ok
  if s = Chr(NACK) then Result := 1 else  //1=出错error
  if s = ''        then Result := 2 else  //2=没有接收到数据no recieve data
  if s = Chr(SERR) then Result := 3 else Result := 1;  //3=扇区没内容no content
   finally
   CanRead:= True;
   end;
end;




function SendCommand(Address, Command, Sect: Byte; str: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;    //发送单个命令函数.建议使用.
begin
  if (Address > 220) or (Sect > 220) then Result := 6  //6=参数错误parameter error
  else
  begin
    s := Chr(STX) + Chr($20 + Address) + Chr(Command) +
                    Chr($20 + Sect) + string(str) + Chr(ETX);  //组合成一个命令字符串.
    s := WritePort(100, s,aobj);    //发送命令数据,等待返回值.
    Result := ResultHandle(s);  //处理接收数据.
  end;
end;



function  bakText(str:string):integer;
var
   Src :Byte ;
   temp : Byte;
   i:integer;
   ret:integer;
   strleng:Integer;
begin
  ret:=0;
  strleng:= Length(str);
  for i:=0 to strleng do
    begin
       temp := Byte(str[i]);
       ret := ret + temp;
    end;
  Result:= ret;
end;


 function DisplayTextold(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    sy_id:string;
    Ret:integer;
    i:integer;
begin
    s := string(LpText);

      if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
      begin
        s := Chr(CLF) +                 //行起始字符.
             Chr($20 + Entry) +         //进入模式
             Chr($20 + Stay) +          //停留模式.
             Chr($20 + StayTime) +      //停留时间.
             Chr($20 + Quit) +          //退出模式.
             Chr($20 + Length(s)) + s;  //字符长度和字符.
        s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                            Chr(DLSECT) + Chr($20 + Section) + s + Chr(ETX),aobj); //下载扇区.
        HaveSigned(50);
        s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                            Chr(DPSECT) + Chr($20 + Section) + Chr(ETX),aobj);  //显示扇区.
        Result := ResultHandle(s);      //处理结果.
        HaveSigned(50);
      end;
end;

          
function DisplayText(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    cc:Byte;
    CS:array[0..1] of Byte ;
    csInt:Byte;
    csTemp:Byte;
begin
  s := string(LpText);
  cc:= $85;
  //if lpText = '车位已满' then Section:=100;

  if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
  begin
    s := Chr($20 + Entry) +         //进入模式
         Chr($20 + Stay) +          //停留模式.
         Chr($20 + StayTime) +      //停留时间.
         Chr($20 + Quit) +          //退出模式.
         s;  //字符长度和字符.

       csInt:= STX + Address + $20 + DLSECT9A + Section + $20 + cc ;
       csTemp:= bakText(s);
       csInt:= csInt + csTemp;

       CS[0]  :=   ( csInt  shr  4)  +   32 ;
       CS[1]  :=   ( csInt and $0f)  +   32;   

    s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                        Chr(DLSECT9A) + Chr($20 + Section)+ Chr(cc) + s + Chr(CS[0]) + Chr(CS[1]) + Chr(ETX), aobj); //下载扇区.

    Result := ResultHandle(s);      //处理结果.
    HaveSigned(50);
  end;
end;


function DisplayTextspackandshow(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    cc:Byte;
    CS:array[0..1] of Byte ;
    csInt:Byte;
    csTemp:Byte;
begin
     s := string(LpText);
     cc:= $87;
     if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
      begin
         s := Chr($20 + Entry) +         //进入模式
              Chr($20 + Stay) +          //停留模式.
              Chr($20 + StayTime) +      //停留时间.
              Chr($20 + Quit) +          //退出模式.
              s;  //字符长度和字符.

         csInt:= STX + Address + $20 + DLSECT9A + Section + $20 + cc ;
         csTemp:= bakText(s);
         csInt:= csInt + csTemp;

         CS[0]  :=   ( csInt  shr  4)  +   32 ;
         CS[1]  :=   ( csInt and $0f)  +   32;

         s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                            Chr(DLSECT9A) + Chr($20 + Section)+ Chr(cc) + s + Chr(CS[0]) + Chr(CS[1]) + Chr(ETX), aobj); //下载扇区.

         Result := ResultHandle(s);      //处理结果.
         HaveSigned(50);
      end;
end;


function DisplayTextSpack(Address, Section,
            Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    cc:Byte;
    CS:array[0..1] of Byte ;
    csInt:Byte;
    csTemp:Byte;
begin
  Section:= 219;
  s := string(LpText);
  cc:=$83;
  sv800.HR_KFSpack(IntToHex(Address,2),'01',PChar(LpText),aobj); ///'欢迎光临'
end;

                     


function HR_KFDisplayText(DA,TWID,ETM,ETS,DM,DT,EXM,EXS,FINDEX,DRS,TC,BC,TL:string; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
begin
  {  DA: 控制卡地址：
     TWID：文本控件ＩＤ： 显示屏行数：
     ETM： 文本进入窗口的方式。 ETM：值含义： 00：立即显示；
                                              01：从右向左移动，
                                              02：从左向右移动，
                                              03：从下向上移动，
                                              04：从上向下移动，
                                              05：向下拉窗，
                                              06：向上拉窗，
                                              07：向左拉窗，
                                              08：向右拉窗，
                                              09：反亮显示，
                                              0A：无操作
                                              0B：中速左移动
                                              0C：中速右移动，
                                              0D：逐字显示，
                                              0E：向左开栅，
                                              0F：向右开栅，
                                              10：雪花显示
                                              11：隔行出现
                                              12：隔列出现
                                              13：慢速左移
                                              14：慢速右移
                                              15：连续移动
                                              16：慢速连续左移
                                              17：慢还连续右移
     ETS：   为文字进入的速度：取值范围：1-32 ，时基取决于当前的扫描周期；
     DM：    文字的停留方式，    DM取值含义： 00：停留 秒单位；
                                              01：停留1/10秒单位，
                                              02：停留 100 * 秒单位，
                                              03：快速 闪铄
                                              04：中速 闪铄
                                              05：慢速 闪铄
                                              06：单次 闪铄
                                              07：英文日期
                                              08：英文时间，
                                              09：中文日期，
                                              0A：中文时间
                                              0B：控制
                                              0C：循环，
                                              0D：温度，
                                              0E：声音，

     DT：  文字停留的时间。 取值范围：0-255.
     EXM： 文字退出的方式；    EXM：值含义：  00：立即退出；
                                              01：从右向左移动，
                                              02：从左向右移动，
                                              03：从下向上移动，
                                              04：从上向下移动，
                                              05：向下拉窗，
                                              06：向上拉窗，
                                              07：向左拉窗，
                                              08：向右拉窗，
                                              09：反亮显示，
                                              0A：无操作
                                              0B：中速左移动
                                              0C：中速右移动，
                                              0D：逐字显示，
                                              0E：向左开栅，
                                              0F：向右开栅，
                                              10：雪花显示
                                              11：隔行出现
                                              12：隔列出现
                                              13：慢速左移
                                              14：慢速右移
                                              15：连续移动
                                              16：慢速连续左移
                                              17：慢速连续右移
     EXS： 文字退出的速度。 取值范围：1-32；
     FINDEX,：文安的字体索引。  FINDEX：值含义：  00：ASCII8；
                                                  01：ASCII10，
                                                  02：ASCII13
                                                  03：宋体16，
                                                  04：宋体24，
                                                  05：宋体32，

     DRS：  为显示的次数：取值范围：0-255， 当为0时，表示无限循环显示！
     TC：   为文字的颜色值。存储结构为：RGB 三基色，各点8位，R表示红色分量，
            G表示绿色分量， B 表示蓝色分量，A  目前没有使用，保留字，各取值范围：0-255.
     BC：   为背景的颜色值。存储结构为：RGB 三基色，各点8位，R表示红色分量，
            G表示绿色分量， B 表示蓝色分量，A  目前没有使用，保留字，各取值范围：0-255.
     TL：   文安的长度：16位数据类型。 小端模式。 目前最大长度为：2K 字节。可以存储：1000个汉字信息；
     TEXT： 文字内容。 支持ASCII GBD2312 编码；单包最大长度为：255，超出单包最大长度时，需要分包传输！
  }

 //LpText:='';
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);

   if Length(string(TWID)) < 2 then TWID:='0'+ string(TWID)
   else TWID:= string(TWID);

   SP:='64';   PN1:='FF';   PN2:='FF';
   CMD:='62';

   cmd:=DAStr + SP + PN1 + PN2 + CMD ;

   if LpText <> '' then
      DL:= IntToHex(Length(LpText) + 19,2)
   else DL:='00';

   if DL = '00' then cmdstr:=cmd + DL
   else  cmdstr:= cmd + DL ;
   gbkstr:= URLEncode_gbk(LpText);
   cmdstr:= cmdstr + TWID + ETM + ETS + DM + DT + EXM + EXS + FINDEX + DRS + TC + BC + TL + gbkstr;

   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;


function HR_KFDisplayTextYW(DA, TWID,ETM,ETS,DM,DT,EXM,EXS,FINDEX,DRS,TC,BC,TL:string; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
begin
  {  DA: 控制卡地址：
     TWID：文本控件ＩＤ： 显示屏行数：
     ETM： 文本进入窗口的方式。 ETM：值含义： 00：立即显示；
                                              01：从右向左移动，
                                              02：从左向右移动，
                                              03：从下向上移动，
                                              04：从上向下移动，
                                              05：向下拉窗，
                                              06：向上拉窗，
                                              07：向左拉窗，
                                              08：向右拉窗，
                                              09：反亮显示，
                                              0A：无操作
                                              0B：中速左移动
                                              0C：中速右移动，
                                              0D：逐字显示，
                                              0E：向左开栅，
                                              0F：向右开栅，
                                              10：雪花显示
                                              11：隔行出现
                                              12：隔列出现
                                              13：慢速左移
                                              14：慢速右移
                                              15：连续移动
                                              16：慢速连续左移
                                              17：慢还连续右移
     ETS：   为文字进入的速度：取值范围：1-32 ，时基取决于当前的扫描周期；
     DM：    文字的停留方式，    DM取值含义： 00：停留 秒单位；
                                              01：停留1/10秒单位，
                                              02：停留 100 * 秒单位，
                                              03：快速 闪铄
                                              04：中速 闪铄
                                              05：慢速 闪铄
                                              06：单次 闪铄
                                              07：英文日期
                                              08：英文时间，
                                              09：中文日期，
                                              0A：中文时间
                                              0B：控制
                                              0C：循环，
                                              0D：温度，
                                              0E：声音，

     DT：  文字停留的时间。 取值范围：0-255.
     EXM： 文字退出的方式；    EXM：值含义：  00：立即退出；
                                              01：从右向左移动，
                                              02：从左向右移动，
                                              03：从下向上移动，
                                              04：从上向下移动，
                                              05：向下拉窗，
                                              06：向上拉窗，
                                              07：向左拉窗，
                                              08：向右拉窗，
                                              09：反亮显示，
                                              0A：无操作
                                              0B：中速左移动
                                              0C：中速右移动，
                                              0D：逐字显示，
                                              0E：向左开栅，
                                              0F：向右开栅，
                                              10：雪花显示
                                              11：隔行出现
                                              12：隔列出现
                                              13：慢速左移
                                              14：慢速右移
                                              15：连续移动
                                              16：慢速连续左移
                                              17：慢速连续右移
     EXS： 文字退出的速度。 取值范围：1-32；
     FINDEX,：文安的字体索引。  FINDEX：值含义：  00：ASCII8；
                                                  01：ASCII10，
                                                  02：ASCII13
                                                  03：宋体16，
                                                  04：宋体24，
                                                  05：宋体32，

     DRS：  为显示的次数：取值范围：0-255， 当为0时，表示无限循环显示！
     TC：   为文字的颜色值。存储结构为：RGB 三基色，各点8位，R表示红色分量，
            G表示绿色分量， B 表示蓝色分量，A  目前没有使用，保留字，各取值范围：0-255.
     BC：   为背景的颜色值。存储结构为：RGB 三基色，各点8位，R表示红色分量，
            G表示绿色分量， B 表示蓝色分量，A  目前没有使用，保留字，各取值范围：0-255.
     TL：   文安的长度：16位数据类型。 小端模式。 目前最大长度为：2K 字节。可以存储：1000个汉字信息；
     TEXT： 文字内容。 支持ASCII GBD2312 编码；单包最大长度为：255，超出单包最大长度时，需要分包传输！
  }

 //LpText:='';
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);

   if Length(string(TWID)) < 2 then TWID:='0'+ string(TWID)
   else TWID:= string(TWID);

   SP:='64';   PN1:='FF';   PN2:='FF';
   CMD:='62';

   cmd:=DAStr + SP + PN1 + PN2 + CMD ;

   if LpText <> '' then
      DL:= IntToHex(Length(LpText) + 19,2)
   else DL:='00';

   if DL = '00' then cmdstr:=cmd + DL
   else  cmdstr:= cmd + DL ;
   gbkstr:= URLEncode_gbk(LpText);
   cmdstr:= cmdstr + TWID + ETM + ETS + DM + DT + EXM + EXS + FINDEX + DRS + TC + BC + TL + gbkstr;

   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;



Function HR_KFShowLedSycw(LedStr:PChar; DA:string; GateNo:string =''; aobj:Pointer= nil):integer;  Stdcall;
var
  i:integer;
  Len1,Len2:string;
  len:integer;
  le:string;
  str:string;
  LedDa:String;
begin
    LedDa:= '1';
    str:= LedStr;
    len:= Length(Trim(str));
    le:= IntToHex(len,4);
    Len1:= Copy(le,1,2);
    Len2:= Copy(le,3,2);
    HR_KFDisplayTextYW(LedDa,DA,'15','01','00','05','15','01','03','01','FFFFFFFF','00000000', len2+Len1,LedStr, aobj);
end;



Function HR_KFGGDisplayText(DA, TWID,FID,AF,ETM,ETS,DM,DT,EXM,EXS,FINDEX,TC,BC,TL:string; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
begin
  {  DA: 控制卡地址：
     TWID：文本控件ＩＤ： 显示屏行数：
     ETM： 文本进入窗口的方式。 ETM：值含义： 00：立即显示；
                                              01：从右向左移动，
                                              02：从左向右移动，
                                              03：从下向上移动，
                                              04：从上向下移动，
                                              05：向下拉窗，
                                              06：向上拉窗，
                                              07：向左拉窗，
                                              08：向右拉窗，
                                              09：反亮显示，
                                              0A：无操作
                                              0B：中速左移动
                                              0C：中速右移动，
                                              0D：逐字显示，
                                              0E：向左开栅，
                                              0F：向右开栅，
                                              10：雪花显示
                                              11：隔行出现
                                              12：隔列出现
                                              13：慢速左移
                                              14：慢速右移
                                              15：连续移动
                                              16：慢速连续左移
                                              17：慢还连续右移
     ETS：   为文字进入的速度：取值范围：1-32 ，时基取决于当前的扫描周期；
     DM：    文字的停留方式，    DM取值含义： 00：停留 秒单位；
                                              01：停留1/10秒单位，
                                              02：停留 100 * 秒单位，
                                              03：快速 闪铄
                                              04：中速 闪铄
                                              05：慢速 闪铄
                                              06：单次 闪铄
                                              07：英文日期
                                              08：英文时间，
                                              09：中文日期，
                                              0A：中文时间
                                              0B：控制
                                              0C：循环，
                                              0D：温度，
                                              0E：声音，

     DT：  文字停留的时间。 取值范围：0-255.
     EXM： 文字退出的方式；    EXM：值含义：  00：立即退出；
                                              01：从右向左移动，
                                              02：从左向右移动，
                                              03：从下向上移动，
                                              04：从上向下移动，
                                              05：向下拉窗，
                                              06：向上拉窗，
                                              07：向左拉窗，
                                              08：向右拉窗，
                                              09：反亮显示，
                                              0A：无操作
                                              0B：中速左移动
                                              0C：中速右移动，
                                              0D：逐字显示，
                                              0E：向左开栅，
                                              0F：向右开栅，
                                              10：雪花显示
                                              11：隔行出现
                                              12：隔列出现
                                              13：慢速左移
                                              14：慢速右移
                                              15：连续移动
                                              16：慢速连续左移
                                              17：慢速连续右移
     EXS： 文字退出的速度。 取值范围：1-32；
     FINDEX,：文安的字体索引。  FINDEX：值含义：  00：ASCII8；
                                                  01：ASCII10，
                                                  02：ASCII13
                                                  03：宋体16，
                                                  04：宋体24，
                                                  05：宋体32，

     DRS：  为显示的次数：取值范围：0-255， 当为0时，表示无限循环显示！
     TC：   为文字的颜色值。存储结构为：RGB 三基色，各点8位，R表示红色分量，
            G表示绿色分量， B 表示蓝色分量，A  目前没有使用，保留字，各取值范围：0-255.
     BC：   为背景的颜色值。存储结构为：RGB 三基色，各点8位，R表示红色分量，
            G表示绿色分量， B 表示蓝色分量，A  目前没有使用，保留字，各取值范围：0-255.
     TL：   文安的长度：16位数据类型。 小端模式。 目前最大长度为：2K 字节。可以存储：1000个汉字信息；
     TEXT： 文字内容。 支持ASCII GBD2312 编码；单包最大长度为：255，超出单包最大长度时，需要分包传输！
  }

 //LpText:='';
 // if aobj <> Nil then  TVideo(aobj).YYStr :=  string(LpText);

//   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
//   else DAStr:= string(DA);
//
//   if Length(string(TWID)) < 2 then TWID:='0'+ string(TWID)
//   else TWID:= string(TWID);
//
//
// //  if Length(string(FID)) < 2 then FID:='0'+ string(FID)
// //  else FID:= string(FID);

   ///下载文本！
   DAStr:=DA;
   SP:='64';   PN1:='FF';   PN2:='FF';
   CMD:='67';  AF:='0C';
   cmd:= DAStr + SP + PN1 + PN2 + CMD ;
   if LpText <> '' then
      DL:= IntToHex(Length(LpText) + 20,2)
   else DL:='00';
   if DL = '00' then cmdstr:=cmd + DL
   else  cmdstr:= cmd + DL ;
   gbkstr:= URLEncode_gbk(LpText);

  // if Park_SysVar.LedColor = '单色' then
   TC :='FFFF0000';
   cmdstr:= cmdstr + TWID + FID + AF + ETM + ETS + DM + DT + EXM + EXS + FINDEX + TC + BC + TL + gbkstr;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.

   ///显示文本！
   CMD:='68';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;
   DL:='02';
   cmdstr:= cmd + DL ;
   cmdstr:= cmdstr + TWID + FID;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.


  //	00 64 FF FF 67 1C 00 00 0C 15 01 00 02 15 01 03 00 FF 00 00 00 00 00 00 08 00 BB B6 D3 AD B9 E2 C1 D9 00 B0
  //'00 64 FF FF 67 1C 00 00 0C 15 01 00 02 15 01 03 00 FF 00 00 00 00 00 00 00 00 BB B6 D3 AD B9 E2 C1 D9 81 5A'
  // '00 64 FF FF 67 1C 00 00 0C 15 01 00 05 15 01 03 00 FF 00 00 00 00 00 00 00 00 BB B6 D3 AD B9 E2 C1 D9 B7 BC'
  //'00 64 FF FF 62 1C 00 00 0C 15 01 00 05 15 01 03 00 FF 00 00 00 00 00 00 00 00 BB B6 D3 AD B9 E2 C1 D9 B1 EC'
  //	00 64 FF FF 68 02 00 00 D8 76

end;



function HR_KFShowTimes(DA: string ; TWID: string;  FIDs: String; aobj:Pointer= nil): Byte; stdcall;

var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
    i,j:Integer;
begin
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);
   for i:= 0 to 7 do
     begin
        TWID:='0'+ IntToStr(i);
        for j:= 0 to 3 do
          begin
             FIDs:='0'+ IntToStr(j);
             ///删除文本！
             SP:='64';   PN1:='FF';   PN2:='FF';
             CMD:='6C';
             cmd:=DAStr + SP + PN1 + PN2 + CMD ;
             DL:='02';

//             if FIDs <> '' then
//                DL:= IntToHex(Length(FIDs),2)
//             else DL:='00';
//
//             if DL = '00' then cmdstr:=cmd + DL
//             else  cmdstr:= cmd + DL ;

             cmdstr:= cmd + DL ;
             cmdstr:= cmdstr + TWID + FIDs;
             CRC1:= MB_CRC16(cmdstr);
             cmdstr:= cmdstr + CRC1;
             s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
          end;
     end;
   Result := ResultHandle(s);      //处理结果.
end;



function HR_KFStopDsplayText(DA, TWID:string; aobj:Pointer= nil): Byte; stdcall;

var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
    i,j:Integer;
    wd,fd:String;
begin
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);

   SP:='64';   PN1:='FF';   PN2:='FF';
   CMD:='66';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;
   DL:='01';
   cmdstr:= cmd + DL ;
   cmdstr:= cmdstr + TWID;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
             application.ProcessMessages;
   Result := ResultHandle(s);      //处理结果.
end;

function HR_KFClearDisplayText(DA, TWID,FID:string; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
    i,j:Integer;
    wd,fd:String;
begin
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);
      for j:= 0 to 3 do
        begin
            for i:= 0 to 15 do
            begin
               wd:='0'+ IntToStr(J);
               fd:= IntToHex(I,2);
               ///删除文本！
               SP:='64';   PN1:='FF';   PN2:='FF';
               CMD:='6B';
               cmd:=DAStr + SP + PN1 + PN2 + CMD ;
               DL:='02';
               cmdstr:= cmd + DL ;
               cmdstr:= cmdstr + wd + fd;
               CRC1:= MB_CRC16(cmdstr);
               cmdstr:= cmdstr + CRC1;
               s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
               HR_KFStopDsplayText(DAStr, wd, aobj);
               application.ProcessMessages;
            end;
          application.ProcessMessages;
        end;
   Result := ResultHandle(s);      //处理结果.
end;


function HR_KFNewAdd(DA:string; NewAdd:string; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
    NewAddStr:string;
begin
   if Length(string(NewAdd)) < 2 then NewAddStr:='0'+ string(NewAdd)
   else NewAddStr:= string(NewAdd);

   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);

   SP:='64';   PN1:='FF';   PN2:='FF';
   CMD:='07';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;
   DL:='01';
   cmdstr:= cmd + DL ;
   cmdstr:= cmdstr + NewAddStr;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;



function HR_KFSetTime(DA:string; Timestr:string; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
    i,j:Integer;
    Y1,Y2,MM,DD,HH,Mn,SS,WW:string;
    WWStr:string;
begin
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);
   SP:='64';   PN1:='FF';   PN2:='FF';
   CMD:='05';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;
   DL:='08';
   cmdstr:= cmd + DL ;
   Y1:= Copy(Timestr,1,4);
   //Y2:= Copy(Timestr,3,2);
   MM:= Copy(Timestr,5,2);
   DD:= Copy(Timestr,7,2);
   HH:= Copy(Timestr,9,2);
   Mn:= Copy(Timestr,11,2);
   SS:= Copy(Timestr,13,2);
   WWStr:=Copy(Timestr,15,4);

   Y1:= IntToHex(Strtoint(Y1),4);
   MM:= IntToHex(Strtoint(MM),2);
   DD:= IntToHex(Strtoint(DD),2);
   HH:= IntToHex(Strtoint(HH),2);
   Mn:= IntToHex(Strtoint(Mn),2);
   SS:= IntToHex(Strtoint(SS),2);
   Y2:= Copy(Y1,1,2);
   Y1:= Copy(Y1,3,2);

   if WWStr = '周日' then   WW:='01';
   if WWStr = '周一' then   WW:='02';
   if WWStr = '周二' then   WW:='03';
   if WWStr = '周三' then   WW:='04';
   if WWStr = '周四' then   WW:='05';
   if WWStr = '周五' then   WW:='06';
   if WWStr = '周六' then   WW:='07';

   cmdstr:= cmdstr + Y1 + Y2 + MM + DD + WW + HH + Mn + SS;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;



function HR_KFSpack(DA: string;  SpType:string;  LpText: PChar; aobj:Pointer= nil): Byte; stdcall;

var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
begin
  //s := string(LpText);
  //if aobj <> Nil then  TVideo(aobj).YYStr :=  string(LpText);
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);
   SP:='64';        PN1:='FF';         PN2:='FF';
   CMD:='30';     //  DL:='09';      //    YYType:='01';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;
   if LpText <> '' then
      DL:= IntToHex(Length(LpText) + 1,2)
   else DL:='00';

   if DL = '00' then cmdstr:=cmd + DL
   else  cmdstr:= cmd + DL + SpType;
   gbkstr:= URLEncode_gbk(LpText);
   cmdstr:= cmdstr + gbkstr;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;


function HR_KFSetDatatype(DA: string ; SpType: string;   aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
begin
  //s := string(LpText);
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);
   SP:='64';        PN1:='FF';         PN2:='FF';
   CMD:='13';       DL:='01';      //    YYType:='01';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;

   if DL = '00' then cmdstr:=cmd + DL
   else  cmdstr:= cmd + DL + SpType;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;


function HR_KFSetOEtype(DA: string ; SpType: string;   aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
   // YYType:string;
    cmd:string;
    cmdstr:string;
    gbkstr:string;
    CRC1:string;
    DAStr:string;
begin
  //s := string(LpText);
   if Length(string(DA)) < 2 then DAStr:='0'+ string(DA)
   else DAStr:= string(DA);
   SP:='64';        PN1:='FF';         PN2:='FF';
   CMD:='12';     //  DL:='09';      //    YYType:='01';
   cmd:=DAStr + SP + PN1 + PN2 + CMD ;    
   DL:='01';

   if DL = '00' then cmdstr:=cmd + DL
   else  cmdstr:= cmd + DL + SpType;
   CRC1:= MB_CRC16(cmdstr);
   cmdstr:= cmdstr + CRC1;
   s := WritePort(100, PAnsiChar(cmdstr), aobj, 3); //下载扇区.
   Result := ResultHandle(s);      //处理结果.
end;


function SpackvocTest(Address, Section,
         Entry, Stay, StayTime, Quit: Byte; LpText: PChar; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    cc:Byte;
    CS:array[0..1] of Byte ;
    csInt:Byte;
    csTemp:Byte;
    DA:String;
    SP:String;
    PN1:String;
    PN2:String;
    DL:String;
    Data:pByte;
    len:integer;
    YYType:string; 
      C1,C2:Byte;
      temp:Word;  
      i:integer;
  str:string;
  cmd:string;
  cmdstr:string;
  spkcmd:string;
  gbkstr:string;
  CRC1:string;
begin
  s := string(LpText);
 // if aobj <> Nil then  TVideo(aobj).YYStr :=  string(LpText);
 // if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
//  begin
      DA:='00';
      SP:='64';
      PN1:='FF';
      PN2:='FF';
      CMD:='30';
      DL:='09';
      YYType:='01';
  //    str:= SP + PN1 + PN2 + CMD + DL + YYType + '01D2BBC2B7CBB3B7E7';

    cmd:=DA + SP + PN1 + PN2 + CMD ;//+ DL + YYType

    if LpText <> '' then
       DL:= IntToHex(Length(LpText) + 1,2)
    else DL:='00';

    if DL = '00' then cmdstr:=cmd + DL
    else  cmdstr:= cmd + DL + YYType;

    gbkstr:= URLEncode_gbk(LpText);
    cmdstr:= cmdstr + gbkstr;
    CRC1:= MB_CRC16(cmdstr);
  //  Self.Memo1.Lines.Add(CRC1);
    cmdstr:= cmdstr + CRC1;

       s := WritePort(100, PAnsiChar(cmdstr), aobj); //下载扇区.
       Result := ResultHandle(s);      //处理结果.
       HaveSigned(50);
 // end;
end;



function DisplaySetSpackVoc(Address, Section, vl:Byte; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
    CS:array[0..1] of Byte ;
    csInt:Byte;
    csTemp:Byte;
begin
  if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
  begin
      //0x02 + DevAddr + 0x9C + SecAddr + VL + CS + 0x03
      Address:= 200;
      Address:= Address + $20;
      Section:=0;
      Section:= Section + $20;
      csInt:= STX + Address + $9C +  Section  + vl ;
      csInt:= csInt;
      CS[0]  :=   ( csInt  shr  4)  +   $20 ;
      CS[1]  :=   ( csInt and $0f)  +   $20;
      s := WritePort(100, Chr(STX) + Chr(Address) +
                     Chr($9C) + Chr(Section)+ Chr(vl) +  Chr(CS[0]) + Chr(CS[1]) + Chr(ETX), aobj); //下载扇区.
      Result := ResultHandle(s);      //处理结果.
      HaveSigned(50);
      s := WritePort(100, Chr(STX) + Chr(Address) +
                     Chr($2B) + Chr(vl) +  Chr(ETX), aobj); //下载扇区.
      Result := ResultHandle(s);      //处理结果.
      DisplayTextspack(220, 220, 21, 0, 5, 21, '欢迎光临',aobj);   
      HaveSigned(50);
      DisplayTextold(220, 220, 21, 0, 5, 21, '欢迎光临',aobj);

  end;

//  if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
//  begin
//      //0x02 + DevAddr + 0x9C + SecAddr + VL + CS + 0x03
//      Address:= 200;
//      Address:= Address + $20;
//      Section:=0;
//      Section:= Section + $20;
//     // csInt:= STX + Address + $2B +  vl ;
//    //  csInt:= csInt;
//    //  CS[0]  :=   ( csInt  shr  4)  +   $20 ;
//    //  CS[1]  :=   ( csInt and $0f)  +   $20;
//      s := WritePort(100, Chr(STX) + Chr(Address) +
//                     Chr($2B) + Chr(vl) +  Chr(ETX), aobj); //下载扇区.
//      Result := ResultHandle(s);      //处理结果.
//      HaveSigned(50);
//      DisplayTextspack(220, 220, 21, 0, 5, 21, '欢迎光临',aobj);
 // end;

end;





function DisplayTime(Address, Section:Byte; aobj:Pointer= nil): Byte; stdcall;
var s: string;   //下载到一个扇区并立即显示出来,建议直接调用SendCommand
begin
   s := FormatDateTime('yymmdd', Now) + IntToHex(DayOfWeek(Now), 2) +
        FormatDateTime('hhnnss', Now) + Copy(FormatDateTime('yyyy', Now), 1, 2)
       + '02-: ';
  if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
  begin
    s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                   Chr(STTIME) + Chr($20 + Section) + s + Chr(ETX),aobj); //下载扇区.
    HaveSigned(50);
    Result := ResultHandle(s);      //处理结果.
  end;
end;


Function ChangeLPAdd(Address,NewAddress,Section:Byte;aobj:Pointer= nil):Byte; StdCall;
var s:string;
begin
  if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
  begin
    s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                        Chr(CHADDR) + Chr($20 + NewAddress) + s + Chr(ETX),aobj); //下载扇区.
    HaveSigned(50);
    Result := ResultHandle(s);      //处理结果.
  end;
end;


Function ClearDP(Address,Section:Byte;aobj:Pointer= nil):Byte; StdCall;
var s:string;
begin
  if (Address > 220) or (Section > 220) then Result := 6 else //参数错误.
  begin
    s := WritePort(100, Chr(STX) + Chr($20 + Address) +
                        Chr(CLRMEM) + Chr($20 + Section) + s + Chr(ETX),aobj); //下载扇区.
    HaveSigned(50);
    Result := ResultHandle(s);      //处理结果.
  end;
end;



function SetLpTime(LedAddr:PChar; aobj:Pointer= nil):integer; Stdcall;
begin
   CanRead:= False;
   Try
   HaveSigned(5);
    Try
      DisplayTime(StrtoInt(LedAddr), 220,aobj);
    Except
      Result:=1;
    end;
   finally
   CanRead:= True;
   end;
end;


function OpenMain( Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
begin            //打开策略,相当于开机,建议直接调用SendCommand
  Result := SendCommand(Address, OPMAIN, Sect, '',aobj);
end;

function CloseMain(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
begin           //关闭策略 相当于关机,建议直接调用SendCommand
  Result := SendCommand(Address, CLMAIN, Sect, '',aobj);
end;

function OpenSection(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
begin          //打开扇区,建议直接调用SendCommand
  Result := SendCommand(Address, OPSECT, Sect, '',aobj);
end;

function CloseSection(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
begin          //关闭扇区,建议直接调用SendCommand
  Result := SendCommand(Address, CLSECT, Sect, '',aobj);
end;

function DisplaySection(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
begin         //显示扇区,建议直接调用SendCommand
  Result := SendCommand(Address, DPSECT, Sect, '',aobj);
end;

function SetupTime(Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
var        //设置时间,sect最好为220以免改变其他扇区内容.建议直接调用SendCommand
  s, Para: string;  //如要设置参数,把Para当参数.
begin               //时间字符格式 YYMMDDWWHHmmssCC02-:
  s := FormatDateTime('yymmdd', Now) + IntToHex(DayOfWeek(Now), 2) +
       FormatDateTime('hhnnss', Now) + Copy(FormatDateTime('yyyy', Now), 1, 2)
       + '02-: ' + Para+ Chr(ETX);
  Result := SendCommand( Address, STTIME, 220, PChar(s),aobj);
end;

function ChangeAddress(Address, LastAddress: Byte; aobj:Pointer= nil): Byte; stdcall;
begin             //更改地址,建议直接调用SendCommand
  Result := SendCommand(Address, CHADDR, LastAddress, '',aobj);
end;

function ClearMem( Address, Sect: Byte; aobj:Pointer= nil): Byte; stdcall;
begin             //清除内存,建议直接调用SendCommand
  Result := SendCommand( Address, CLRMEM, Sect, '',aobj);
end;

function ChangeLength(Address, Length: Byte; aobj:Pointer= nil): Byte; stdcall;
begin             //更改长度(8点),建议直接调用SendCommand
  Result := SendCommand( Address, CHLENG, Length, '',aobj);
end;

function ChangeRows( Address, Rows: Byte; aobj:Pointer= nil): Byte; stdcall;
begin             //更改行数(16点),建议直接调用SendCommand
  Result := SendCommand(Address, CHROWS, Rows, '',aobj);
end;

function DownloadSection(Address, Sect: Byte; LpStr: PChar; aobj:Pointer = nil): Byte; stdcall;
var s:string;     //下载扇区,建议直接调用SendCommand
begin
  s := string(LpStr);
  //if (Port and $80) <> 0 then  //地址高位为1自动转GB码.
  //   s := string(Big5ToGb(PChar(s)));
  Result := SendCommand(Address, DLSECT, Sect, PChar(s),aobj);
end;

    
procedure  SendLedMessage(LedStr:String; aObj:Pointer = nil);
var
  _SerialData  : String;
  _data         : array of Byte;
  _temp         : String;
  _cHead       : array[0..44 -1] of Byte;
  _trigger_display : array[0..5 -1] of Byte;
  sIp          : array[0..20 -1] of PAnsiChar;
  Ip           : String;
  p            : PByte;
  p1           : PByte;
  errCode      : LongWord;
begin
////发送串口数据
//  if aObj <> Nil then
//  begin
//    _cHead[0] := $02;
//    _cHead[1] := $21;
//    _cHead[2] := $25;
//    _cHead[3] := $fc;
//    _cHead[4] := $0c;
//    _cHead[5] := $36;
//    _cHead[6] := $20;
//    _cHead[7] := $26;
//    _cHead[8] := $20;
//    _cHead[9] := $20;
//    _SerialData := LedStr;
//
//    SetLength(_data,length(_SerialData));
//
//    _cHead[10] := $cd;
//    _cHead[11] := $e2;
//    _cHead[12] := $b2;
//    _cHead[13] := $bf;
//    _cHead[14] := $b3;
//    _cHead[15] := $b5;
//    _cHead[16] := $c1;
//    _cHead[17] := $be;
//    _cHead[18] := $bd;
//    _cHead[19] := $fb;
//    _cHead[20] := $d6;
//    _cHead[21] := $b9;
//    _cHead[22] := $c8;
//    _cHead[23] := $eb;
//    _cHead[24] := $c4;
//    _cHead[25] := $da;
//    _cHead[26] := $03;
//    _trigger_display[0] := $02;
//    _trigger_display[1] := $21;
//    _trigger_display[2] := $24;
//    _trigger_display[3] := $fc;
//    _trigger_display[4] := $03;
//
//    p := PByte(@_cHead[0]);
//    p1:= PByte(@_trigger_display[0]);
//    Ip := TVideo(aObj).VideoIP;
//    StrPCopy(@sIp,Ip);
//    errCode := CTV_TransferSerialPortMsg(PAnsiChar(Ip), 40000, p ,27,nil);
//  if(errCode = CTV_OK) Then
//  begin
//    Sleep(20);
//    CTV_TransferSerialPortMsg(PAnsiChar(Ip), 40000,p1 ,5,nil);
//  end;
//  end;
end;


Function GetYsCRC(Str:string):string;
var
  i:integer;
  HStr,Dstr:string;
  DecNum:Integer;
  DecTemp:Integer;
begin
  DecTemp:=0;
  for i:= 1 to Length(Str)  do
    begin
       if i <> 1 then
          HStr:= Copy(Str,i*2 - 1,2)
       else
          HStr:= Copy(Str,i,2);

       if HStr <> '' then
       DecTemp:= DecTemp + HextoInt(HStr);
    end;
 Result:= IntToHex(DecTemp,4);
end;




initialization
begin
  hcomPort:=0;
  if not Assigned(aBuff)  then
      aBuff:= AllocMem(255);   ///输入零时缓存
  OpenDoorNum:=0;
  OpenDoorNumError:=0;
end;

finalization
   Freemem(aBuff);

end.

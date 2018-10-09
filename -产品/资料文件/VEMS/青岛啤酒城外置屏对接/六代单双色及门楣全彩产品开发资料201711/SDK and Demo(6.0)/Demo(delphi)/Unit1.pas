unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,LedDll;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Memo1: TMemo;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var
    logf:TLOGFONT;
begin

end;

procedure TForm1.Button2Click(Sender: TObject);
var
    nResult:Integer;
    LedCommunicationInfo:COMMUNICATIONINFO;
    ErrStr:Array [0..255] of Char;
    hProgram:Integer;
    ARect:AREARECT;
    FProp:FONTPROP;
begin
//tcp通讯********************************************
    LedCommunicationInfo.SendType:=0;
    strpcopy(LedCommunicationInfo.IpStr,'192.168.1.245');
    LedCommunicationInfo.LedNumber:=1;
 //广播发送*********************************************
    //LedCommunicationInfo.SendType:=1;
 //串口通讯*********************************************
    //LedCommunicationInfo.SendType:=2;
    //LedCommunicationInfo.Commport:=1;
    //LedCommunicationInfo.Baud:=9600;
    //LedCommunicationInfo.LedNumber:=1;
    hProgram:=LV_CreateProgram(64,32,2);
    LV_AddProgram(hProgram,1,0,1);
    ARect.left:=0;
    ARect.top:=0;
    ARect.width:=64;
    ARect.height:=32;

    FillChar(FProp,sizeof(FProp),0);
    strpcopy(FProp.FontName,'宋体');
    FProp.FontSize:=12;
    FProp.FontColor:=COLOR_RED;

    LV_QuickAddSingleLineTextArea(hProgram,1,1,@ARect,ADDTYPE_STRING,PChar('胡半仙到此一游~'),@FProp,4);


    nResult:=LV_Send(@LedCommunicationInfo,hProgram);
    LV_DeleteProgram(hProgram);
    if nResult<>OK then
        begin
            LV_GetError(nResult,256,ErrStr);
            ShowMessage(ErrStr);
        end
    else
        begin
            ShowMessage('发送成功');
        end;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
    nResult:Integer;
    LedCommunicationInfo:COMMUNICATIONINFO;
    ErrStr:Array [0..255] of Char;
begin
//tcp通讯********************************************
    LedCommunicationInfo.SendType:=0;
    strpcopy(LedCommunicationInfo.IpStr,'192.168.1.245');
    LedCommunicationInfo.LedNumber:=1;
 //广播发送*********************************************
    //LedCommunicationInfo.SendType:=1;
 //串口通讯*********************************************
    //LedCommunicationInfo.SendType:=2;
    //LedCommunicationInfo.Commport:=1;
    //LedCommunicationInfo.Baud:=9600;
    //LedCommunicationInfo.LedNumber:=1;


    nResult:=LV_SetBasicInfo(@LedCommunicationInfo,2,64,32);
    if nResult<>OK then
        begin
            LV_GetError(nResult,256,ErrStr);
            ShowMessage(ErrStr);
        end
    else
        begin
            ShowMessage('设置屏参成功');
        end;
end;

procedure TForm1.Button4Click(Sender: TObject);
var
    nResult:Integer;
    LedCommunicationInfo:COMMUNICATIONINFO;
    ErrStr:Array [0..255] of Char;
    hProgram:Integer;
    ARect:AREARECT;
    PProp:PLAYPROP;
begin
//tcp通讯********************************************
    LedCommunicationInfo.SendType:=0;
    strpcopy(LedCommunicationInfo.IpStr,'192.168.1.245');
    LedCommunicationInfo.LedNumber:=1;
 //广播发送*********************************************
    //LedCommunicationInfo.SendType:=1;
 //串口通讯*********************************************
    //LedCommunicationInfo.SendType:=2;
    //LedCommunicationInfo.Commport:=1;
    //LedCommunicationInfo.Baud:=9600;
    //LedCommunicationInfo.LedNumber:=1;
    hProgram:=LV_CreateProgram(64,32,2);
    LV_AddProgram(hProgram,1,0,1);
    ARect.left:=0;
    ARect.top:=0;
    ARect.width:=64;
    ARect.height:=32;

    LV_AddImageTextArea(hProgram, 1, 1, @ARect, 0);


    FillChar(PProp,sizeof(PProp),0);
    PProp.InStyle:=0;
    PProp.DelayTime:=3;
    PProp.Speed:=4;

    //可以添加多个子项到图文区，如下添加可以选一个或多个添加
    nResult:=LV_AddFileToImageTextArea(hProgram,1,1,PChar('test.bmp'),@PProp);
    nResult:=LV_AddFileToImageTextArea(hProgram,1,1,PChar('test.jpg'),@PProp);
    nResult:=LV_AddFileToImageTextArea(hProgram,1,1,PChar('test.png'),@PProp);
    nResult:=LV_AddFileToImageTextArea(hProgram,1,1,PChar('test.gif'),@PProp);

    nResult:=LV_Send(@LedCommunicationInfo,hProgram);
    LV_DeleteProgram(hProgram);
    if nResult<>OK then
        begin
            LV_GetError(nResult,256,ErrStr);
            ShowMessage(ErrStr);
        end
    else
        begin
            ShowMessage('发送成功');
        end;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
    nResult:Integer;
    LedCommunicationInfo:COMMUNICATIONINFO;
    ErrStr:Array [0..255] of Char;
    hProgram:Integer;
    ARect:AREARECT;
    FProp:FONTPROP;
    PProp:PLAYPROP;
begin
//tcp通讯********************************************
    LedCommunicationInfo.SendType:=0;
    strpcopy(LedCommunicationInfo.IpStr,'192.168.1.245');
    LedCommunicationInfo.LedNumber:=1;
 //广播发送*********************************************
    //LedCommunicationInfo.SendType:=1;
 //串口通讯*********************************************
    //LedCommunicationInfo.SendType:=2;
    //LedCommunicationInfo.Commport:=1;
    //LedCommunicationInfo.Baud:=9600;
    //LedCommunicationInfo.LedNumber:=1;
    hProgram:=LV_CreateProgram(64,32,2);
    LV_AddProgram(hProgram,1,0,1);
    ARect.left:=0;
    ARect.top:=0;
    ARect.width:=64;
    ARect.height:=32;

    LV_AddImageTextArea(hProgram, 1, 1, @ARect, 0);

    FillChar(FProp,sizeof(FProp),0);
    strpcopy(FProp.FontName,'宋体');
    FProp.FontSize:=12;
    FProp.FontColor:=COLOR_RED;

    FillChar(PProp,sizeof(PProp),0);
    PProp.InStyle:=0;
    PProp.DelayTime:=3;
    PProp.Speed:=4;

    //可以添加多个子项到图文区，如下添加可以选一个或多个添加
 	nResult:=LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_STRING,PChar('上海灵信视觉技术股份有限公司'),@FProp,@PProp,0,0);//通过字符串添加一个多行文本到图文区，参数说明见声明注示
	nResult:=LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_FILE,PChar('test.rtf'),@FProp,@PProp,0,0);//通过rtf文件添加一个多行文本到图文区，参数说明见声明注示
	nResult:=LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_FILE,PChar('test.txt'),@FProp,@PProp,0,0);//通过txt文件添加一个多行文本到图文区，参数说明见声明注示


    nResult:=LV_Send(@LedCommunicationInfo,hProgram);
    LV_DeleteProgram(hProgram);
    if nResult<>OK then
        begin
            LV_GetError(nResult,256,ErrStr);
            ShowMessage(ErrStr);
        end
    else
        begin
            ShowMessage('发送成功');
        end;
end;

procedure TForm1.Button5Click(Sender: TObject);
var
    nResult:Integer;
    LedCommunicationInfo:COMMUNICATIONINFO;
    ErrStr:Array [0..255] of Char;
    hProgram:Integer;
    ARect:AREARECT;
    FProp:FONTPROP;
    DigitalClockInfo:DIGITALCLOCKAREAINFO;
begin
//tcp通讯********************************************
    LedCommunicationInfo.SendType:=0;
    strpcopy(LedCommunicationInfo.IpStr,'192.168.1.245');
    LedCommunicationInfo.LedNumber:=1;
 //广播发送*********************************************
    //LedCommunicationInfo.SendType:=1;
 //串口通讯*********************************************
    //LedCommunicationInfo.SendType:=2;
    //LedCommunicationInfo.Commport:=1;
    //LedCommunicationInfo.Baud:=9600;
    //LedCommunicationInfo.LedNumber:=1;
    hProgram:=LV_CreateProgram(64,32,2);
    LV_AddProgram(hProgram,1,0,1);


    FillChar(FProp,sizeof(FProp),0);
    strpcopy(FProp.FontName,'宋体');
    FProp.FontSize:=12;
    FProp.FontColor:=COLOR_RED;

    ARect.left:=0;
    ARect.top:=0;
    ARect.width:=64;
    ARect.height:=16;

    LV_QuickAddSingleLineTextArea(hProgram,1,1,@ARect,ADDTYPE_STRING,PChar('上海灵信视觉技术股份有限公司'),@FProp,4);

    ARect.left:=0;
    ARect.top:=16;
    ARect.width:=64;
    ARect.height:=16;
    FillChar(DigitalClockInfo,sizeof(DigitalClockInfo),0);
    DigitalClockInfo.TimeColor:=COLOR_RED;
    strpcopy(DigitalClockInfo.ShowStrFont.FontName,'宋体');
    DigitalClockInfo.ShowStrFont.FontSize:=12;
    DigitalClockInfo.IsShowHour:=1;
    DigitalClockInfo.IsShowMinute:=1;

    LV_AddDigitalClockArea(hProgram,1,2,@ARect,@DigitalClockInfo);

    nResult:=LV_Send(@LedCommunicationInfo,hProgram);
    LV_DeleteProgram(hProgram);
    if nResult<>OK then
        begin
            LV_GetError(nResult,256,ErrStr);
            ShowMessage(ErrStr);
        end
    else
        begin
            ShowMessage('发送成功');
        end;
end;

procedure TForm1.Button6Click(Sender: TObject);
var
    nResult:Integer;
    LedCommunicationInfo:COMMUNICATIONINFO;
    ErrStr:Array [0..255] of Char;
    hProgram:Integer;
    ARect:AREARECT;
    FProp:FONTPROP;
    DigitalClockInfo:DIGITALCLOCKAREAINFO;
begin
//tcp通讯********************************************
    LedCommunicationInfo.SendType:=0;
    strpcopy(LedCommunicationInfo.IpStr,'192.168.1.245');
    LedCommunicationInfo.LedNumber:=1;
 //广播发送*********************************************
    //LedCommunicationInfo.SendType:=1;
 //串口通讯*********************************************
    //LedCommunicationInfo.SendType:=2;
    //LedCommunicationInfo.Commport:=1;
    //LedCommunicationInfo.Baud:=9600;
    //LedCommunicationInfo.LedNumber:=1;
    hProgram:=LV_CreateProgram(64,32,2);
    LV_AddProgram(hProgram,1,0,1);


    FillChar(FProp,sizeof(FProp),0);
    strpcopy(FProp.FontName,'宋体');
    FProp.FontSize:=12;
    FProp.FontColor:=COLOR_RED;

    ARect.left:=0;
    ARect.top:=0;
    ARect.width:=64;
    ARect.height:=16;

    LV_QuickAddSingleLineTextArea(hProgram,1,1,@ARect,ADDTYPE_STRING,PChar('上海灵信视觉技术股份有限公司'),@FProp,4);

    ARect.left:=0;
    ARect.top:=16;
    ARect.width:=64;
    ARect.height:=16;
    FillChar(DigitalClockInfo,sizeof(DigitalClockInfo),0);
    DigitalClockInfo.TimeColor:=COLOR_RED;
    strpcopy(DigitalClockInfo.ShowStrFont.FontName,'宋体');
    DigitalClockInfo.ShowStrFont.FontSize:=12;
    DigitalClockInfo.IsShowHour:=1;
    DigitalClockInfo.IsShowMinute:=1;

    LV_AddDigitalClockArea(hProgram,1,2,@ARect,@DigitalClockInfo);
 //**************************************************************************

    LV_AddProgram(hProgram,2,0,1);
    ARect.left:=0;
    ARect.top:=0;
    ARect.width:=64;
    ARect.height:=16;
    strpcopy(FProp.FontName,'黑体');
    FProp.FontSize:=12;
    FProp.FontColor:=COLOR_GREEN;

    LV_QuickAddSingleLineTextArea(hProgram,2,1,@ARect,ADDTYPE_STRING,PChar('胡半仙到此一游~'),@FProp,4);

    ARect.left:=0;
    ARect.top:=16;
    ARect.width:=64;
    ARect.height:=16;
    FillChar(DigitalClockInfo,sizeof(DigitalClockInfo),0);
    DigitalClockInfo.TimeColor:=COLOR_RED;
    strpcopy(DigitalClockInfo.ShowStrFont.FontName,'黑体');
    DigitalClockInfo.ShowStrFont.FontSize:=12;
    DigitalClockInfo.IsShowHour:=1;
    DigitalClockInfo.IsShowMinute:=1;
    DigitalClockInfo.TimeFormat:=2;
    LV_AddDigitalClockArea(hProgram,2,2,@ARect,@DigitalClockInfo);

    nResult:=LV_Send(@LedCommunicationInfo,hProgram);
    LV_DeleteProgram(hProgram);
    if nResult<>OK then
        begin
            LV_GetError(nResult,256,ErrStr);
            ShowMessage(ErrStr);
        end
    else
        begin
            ShowMessage('发送成功');
        end;
end;

end.

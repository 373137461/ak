VERSION 5.00
Begin VB.Form MainForm 
   Caption         =   "demo"
   ClientHeight    =   5925
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8685
   LinkTopic       =   "Form1"
   ScaleHeight     =   5925
   ScaleWidth      =   8685
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command7 
      Caption         =   "Command7"
      Height          =   315
      Left            =   7800
      TabIndex        =   7
      Top             =   3420
      Width           =   855
   End
   Begin VB.CommandButton Command6 
      Caption         =   "两个节目下各有一个单行文本区和一个数字时钟区(多节目通过此方法添加)"
      Height          =   495
      Left            =   60
      TabIndex        =   5
      Top             =   2820
      Width           =   8535
   End
   Begin VB.CommandButton Command5 
      Caption         =   "一个节目下有一个连续左移的单行文本区和一个数字时钟区(多个区域都通过此方法添加)"
      Height          =   495
      Left            =   60
      TabIndex        =   4
      Top             =   2220
      Width           =   8535
   End
   Begin VB.CommandButton Command4 
      Caption         =   "一个节目下只有一个图片区(表格的显示通过自绘图片并通过此方式添加发送)"
      Height          =   495
      Left            =   60
      TabIndex        =   3
      Top             =   1680
      Width           =   8535
   End
   Begin VB.CommandButton Command3 
      Caption         =   "一个节目下只有一个多行文本区"
      Height          =   495
      Left            =   60
      TabIndex        =   2
      Top             =   1140
      Width           =   8535
   End
   Begin VB.CommandButton Command2 
      Caption         =   "一个节目下只有一个连接左移的单行文本区域"
      Height          =   495
      Left            =   60
      TabIndex        =   1
      Top             =   600
      Width           =   8535
   End
   Begin VB.CommandButton Command1 
      Caption         =   "设置屏参（注意：只需根据屏的宽高点数的颜色设置一次，发送节目时无需设置）"
      Height          =   495
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   8535
   End
   Begin VB.Label Label1 
      Caption         =   $"MainForm.frx":0000
      Height          =   1875
      Left            =   180
      TabIndex        =   6
      Top             =   3900
      Width           =   8295
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
Dim ErrStr As String
Dim nResult As Long
Dim LedCommunicationInfo As COMMUNICATIONINFO
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0) '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1
'//广播通讯********************************************************************************
    'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
'//串口通讯********************************************************************************
    'CommunicationInfo.SendType=2;//串口通讯
    'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
    'CommunicationInfo.Baud=9600;//波特率
    'CommunicationInfo.LedNumber=1;

nResult = LV_SetBasicInfo(LedCommunicationInfo, 1, 64, 32)
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "设置屏参成功"
End If


End Sub

Private Sub Command2_Click()
Dim ErrStr As String
Dim nResult As Long
Dim hProgram As Long
Dim ARect As AREARECT
Dim FProp As FONTPROP


Dim LedCommunicationInfo As COMMUNICATIONINFO
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.188" + Chr$(0)  '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//广播通讯********************************************************************************
    'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
'//串口通讯********************************************************************************
    'CommunicationInfo.SendType=2;//串口通讯
    'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
    'CommunicationInfo.Baud=9600;//波特率
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 1)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 32
FProp.FontName = "黑体" + Chr$(0) '后面必要加 Chr$(0)
FProp.FontSize = 14
FProp.FontColor = vbRed

Call LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "胡半仙到此一游~", FProp, 4)

nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "发送成功"
End If

End Sub

Private Sub Command3_Click()
Dim ErrStr As String
Dim nResult As Long
Dim hProgram As Long
Dim ARect As AREARECT
Dim FProp As FONTPROP
Dim PProp As PLAYPROP


Dim LedCommunicationInfo As COMMUNICATIONINFO
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//广播通讯********************************************************************************
    'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
'//串口通讯********************************************************************************
    'CommunicationInfo.SendType=2;//串口通讯
    'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
    'CommunicationInfo.Baud=9600;//波特率
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 32

Call LV_AddImageTextArea(hProgram, 1, 1, ARect, 0)



FProp.FontName = "黑体" + Chr$(0) '后面必要加 Chr$(0)
FProp.FontSize = 14
FProp.FontColor = vbRed

PProp.InStyle = 0
PProp.DelayTime = 3
PProp.Speed = 4

'可以添加多个子项到图文区，如下添加可以选一个或多个添加
Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_STRING, "上海灵信视觉技术股份有限公司", FProp, PProp, 0, 0) '通过字符串添加一个多行文本到图文区，参数说明见声明注示
'Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_FILE, "test.rtf", FProp, PProp, 0, 0) '通过rtf文件添加一个多行文本到图文区，参数说明见声明注示
'Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_FILE, "test.txt", FProp, PProp, 0, 0) '通过txt文件添加一个多行文本到图文区，参数说明见声明注示


nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "发送成功"
End If


End Sub

Private Sub Command4_Click()
Dim ErrStr As String
Dim nResult As Long
Dim hProgram As Long
Dim ARect As AREARECT
Dim PProp As PLAYPROP


Dim LedCommunicationInfo As COMMUNICATIONINFO
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//广播通讯********************************************************************************
    'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
'//串口通讯********************************************************************************
    'CommunicationInfo.SendType=2;//串口通讯
    'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
    'CommunicationInfo.Baud=9600;//波特率
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 32

Call LV_AddImageTextArea(hProgram, 1, 1, ARect, 0)



PProp.InStyle = 0
PProp.DelayTime = 3
PProp.Speed = 4

'可以添加多个子项到图文区，如下添加可以选一个或多个添加
nResult = LV_AddFileToImageTextArea(hProgram, 1, 1, "test.bmp", PProp)
nResult = LV_AddFileToImageTextArea(hProgram, 1, 1, "test.jpg", PProp)
nResult = LV_AddFileToImageTextArea(hProgram, 1, 1, "test.png", PProp)
PProp.Speed = 3
nResult = LV_AddFileToImageTextArea(hProgram, 1, 1, "test.gif", PProp)



nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "发送成功"
End If
End Sub

Private Sub Command5_Click()
Dim ErrStr As String
Dim nResult As Long
Dim hProgram As Long
Dim ARect As AREARECT
Dim FProp As FONTPROP


Dim LedCommunicationInfo As COMMUNICATIONINFO
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//广播通讯********************************************************************************
    'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
'//串口通讯********************************************************************************
    'CommunicationInfo.SendType=2;//串口通讯
    'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
    'CommunicationInfo.Baud=9600;//波特率
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 16
FProp.FontName = "宋体" + Chr$(0) '后面必要加 Chr$(0)
FProp.FontSize = 12
FProp.FontColor = vbRed

nResult = LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "上海灵信视觉技术股份有限公司~", FProp, 4)

ARect.left = 0
ARect.top = 16
ARect.width = 64
ARect.height = 16


Dim DigitalClockInfo As DIGITALCLOCKAREAINFO

DigitalClockInfo.TimeColor = vbGreen
DigitalClockInfo.ShowStrFont.FontName = "宋体" + Chr$(0)
DigitalClockInfo.ShowStrFont.FontSize = 11
DigitalClockInfo.IsShowHour = 1
DigitalClockInfo.IsShowMinute = 1

nResult = LV_AddDigitalClockArea(hProgram, 1, 2, ARect, DigitalClockInfo) '//注意区域号不能一样，详见函数声明注示


nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "发送成功"
End If
End Sub

Private Sub Command6_Click()
Dim ErrStr As String
Dim nResult As Long
Dim hProgram As Long
Dim ARect As AREARECT
Dim FProp As FONTPROP
Dim DigitalClockInfo As DIGITALCLOCKAREAINFO

Dim LedCommunicationInfo As COMMUNICATIONINFO
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//广播通讯********************************************************************************
    'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
'//串口通讯********************************************************************************
    'CommunicationInfo.SendType=2;//串口通讯
    'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
    'CommunicationInfo.Baud=9600;//波特率
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 16
FProp.FontName = "宋体" + Chr$(0) '后面必要加 Chr$(0)
FProp.FontSize = 12
FProp.FontColor = vbRed

nResult = LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "上海灵信视觉技术股份有限公司~", FProp, 4)

ARect.left = 0
ARect.top = 16
ARect.width = 64
ARect.height = 16

DigitalClockInfo.TimeColor = vbRed
DigitalClockInfo.ShowStrFont.FontName = "宋体" + Chr$(0)
DigitalClockInfo.ShowStrFont.FontSize = 12
DigitalClockInfo.IsShowHour = 1
DigitalClockInfo.IsShowMinute = 1

nResult = LV_AddDigitalClockArea(hProgram, 1, 2, ARect, DigitalClockInfo) '//注意区域号不能一样，详见函数声明注示

''''''''''''''''''''''''''''''''''''''''''''''''
LV_AddProgram hProgram, 2, 0, 1


ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 16
FProp.FontName = "宋体" + Chr$(0) '后面必要加 Chr$(0)
FProp.FontSize = 12
FProp.FontColor = vbRed

nResult = LV_QuickAddSingleLineTextArea(hProgram, 2, 1, ARect, ADDTYPE_STRING, "胡半仙到此一游~", FProp, 4)

ARect.left = 0
ARect.top = 16
ARect.width = 64
ARect.height = 16

DigitalClockInfo.TimeColor = vbRed
DigitalClockInfo.ShowStrFont.FontName = "黑体" + Chr$(0)
DigitalClockInfo.ShowStrFont.FontSize = 12
DigitalClockInfo.IsShowHour = 1
DigitalClockInfo.IsShowMinute = 1
DigitalClockInfo.TimeFormat = 2

nResult = LV_AddDigitalClockArea(hProgram, 2, 2, ARect, DigitalClockInfo) '//注意区域号不能一样，详见函数声明注示


nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "发送成功"
End If
End Sub











Private Sub Command7_Click()
Dim param As LEDCOMMUNICATIONPARAMETER
Dim LedCommunicationInfo As COMMUNICATIONINFO
Dim nRet As Long
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.187" + Chr$(0)  '后面必要加 Chr$(0)
LedCommunicationInfo.LedNumber = 1

param.dwMask = 0
param.IpStr = "192.168.1.250" + Chr$(0)
param.NetMaskStr = "255.255.255.0" + Chr$(0)
param.GatewayStr = "192.168.1.1" + Chr$(0)
param.MacStr = "ee-ee-ee-ee-ee-ee" + Chr$(0)

nRet = LV_SetLedCommunicationParameter(LedCommunicationInfo, param)
End Sub
















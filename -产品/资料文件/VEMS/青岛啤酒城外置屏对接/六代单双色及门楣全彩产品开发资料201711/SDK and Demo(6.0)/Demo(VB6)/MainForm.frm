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
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CommandButton Command7 
      Caption         =   "Command7"
      Height          =   315
      Left            =   7800
      TabIndex        =   7
      Top             =   3420
      Width           =   855
   End
   Begin VB.CommandButton Command6 
      Caption         =   "������Ŀ�¸���һ�������ı�����һ������ʱ����(���Ŀͨ���˷������)"
      Height          =   495
      Left            =   60
      TabIndex        =   5
      Top             =   2820
      Width           =   8535
   End
   Begin VB.CommandButton Command5 
      Caption         =   "һ����Ŀ����һ���������Ƶĵ����ı�����һ������ʱ����(�������ͨ���˷������)"
      Height          =   495
      Left            =   60
      TabIndex        =   4
      Top             =   2220
      Width           =   8535
   End
   Begin VB.CommandButton Command4 
      Caption         =   "һ����Ŀ��ֻ��һ��ͼƬ��(������ʾͨ���Ի�ͼƬ��ͨ���˷�ʽ��ӷ���)"
      Height          =   495
      Left            =   60
      TabIndex        =   3
      Top             =   1680
      Width           =   8535
   End
   Begin VB.CommandButton Command3 
      Caption         =   "һ����Ŀ��ֻ��һ�������ı���"
      Height          =   495
      Left            =   60
      TabIndex        =   2
      Top             =   1140
      Width           =   8535
   End
   Begin VB.CommandButton Command2 
      Caption         =   "һ����Ŀ��ֻ��һ���������Ƶĵ����ı�����"
      Height          =   495
      Left            =   60
      TabIndex        =   1
      Top             =   600
      Width           =   8535
   End
   Begin VB.CommandButton Command1 
      Caption         =   "�������Σ�ע�⣺ֻ��������Ŀ�ߵ�������ɫ����һ�Σ����ͽ�Ŀʱ�������ã�"
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
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0) '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1
'//�㲥ͨѶ********************************************************************************
    'CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
'//����ͨѶ********************************************************************************
    'CommunicationInfo.SendType=2;//����ͨѶ
    'CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
    'CommunicationInfo.Baud=9600;//������
    'CommunicationInfo.LedNumber=1;

nResult = LV_SetBasicInfo(LedCommunicationInfo, 1, 64, 32)
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "�������γɹ�"
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
LedCommunicationInfo.IpStr = "192.168.1.188" + Chr$(0)  '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//�㲥ͨѶ********************************************************************************
    'CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
'//����ͨѶ********************************************************************************
    'CommunicationInfo.SendType=2;//����ͨѶ
    'CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
    'CommunicationInfo.Baud=9600;//������
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 1)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 32
FProp.FontName = "����" + Chr$(0) '�����Ҫ�� Chr$(0)
FProp.FontSize = 14
FProp.FontColor = vbRed

Call LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "�����ɵ���һ��~", FProp, 4)

nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "���ͳɹ�"
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
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//�㲥ͨѶ********************************************************************************
    'CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
'//����ͨѶ********************************************************************************
    'CommunicationInfo.SendType=2;//����ͨѶ
    'CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
    'CommunicationInfo.Baud=9600;//������
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 32

Call LV_AddImageTextArea(hProgram, 1, 1, ARect, 0)



FProp.FontName = "����" + Chr$(0) '�����Ҫ�� Chr$(0)
FProp.FontSize = 14
FProp.FontColor = vbRed

PProp.InStyle = 0
PProp.DelayTime = 3
PProp.Speed = 4

'������Ӷ�����ͼ������������ӿ���ѡһ���������
Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_STRING, "�Ϻ������Ӿ������ɷ����޹�˾", FProp, PProp, 0, 0) 'ͨ���ַ������һ�������ı���ͼ����������˵��������עʾ
'Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_FILE, "test.rtf", FProp, PProp, 0, 0) 'ͨ��rtf�ļ����һ�������ı���ͼ����������˵��������עʾ
'Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_FILE, "test.txt", FProp, PProp, 0, 0) 'ͨ��txt�ļ����һ�������ı���ͼ����������˵��������עʾ


nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "���ͳɹ�"
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
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//�㲥ͨѶ********************************************************************************
    'CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
'//����ͨѶ********************************************************************************
    'CommunicationInfo.SendType=2;//����ͨѶ
    'CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
    'CommunicationInfo.Baud=9600;//������
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

'������Ӷ�����ͼ������������ӿ���ѡһ���������
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
    MsgBox "���ͳɹ�"
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
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//�㲥ͨѶ********************************************************************************
    'CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
'//����ͨѶ********************************************************************************
    'CommunicationInfo.SendType=2;//����ͨѶ
    'CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
    'CommunicationInfo.Baud=9600;//������
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 16
FProp.FontName = "����" + Chr$(0) '�����Ҫ�� Chr$(0)
FProp.FontSize = 12
FProp.FontColor = vbRed

nResult = LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "�Ϻ������Ӿ������ɷ����޹�˾~", FProp, 4)

ARect.left = 0
ARect.top = 16
ARect.width = 64
ARect.height = 16


Dim DigitalClockInfo As DIGITALCLOCKAREAINFO

DigitalClockInfo.TimeColor = vbGreen
DigitalClockInfo.ShowStrFont.FontName = "����" + Chr$(0)
DigitalClockInfo.ShowStrFont.FontSize = 11
DigitalClockInfo.IsShowHour = 1
DigitalClockInfo.IsShowMinute = 1

nResult = LV_AddDigitalClockArea(hProgram, 1, 2, ARect, DigitalClockInfo) '//ע������Ų���һ���������������עʾ


nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "���ͳɹ�"
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
LedCommunicationInfo.IpStr = "192.168.1.245" + Chr$(0)  '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1

'//�㲥ͨѶ********************************************************************************
    'CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
'//����ͨѶ********************************************************************************
    'CommunicationInfo.SendType=2;//����ͨѶ
    'CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
    'CommunicationInfo.Baud=9600;//������
    'CommunicationInfo.LedNumber=1;



hProgram = LV_CreateProgram(64, 32, 2)

Call LV_AddProgram(hProgram, 1, 0, 1)

ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 16
FProp.FontName = "����" + Chr$(0) '�����Ҫ�� Chr$(0)
FProp.FontSize = 12
FProp.FontColor = vbRed

nResult = LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "�Ϻ������Ӿ������ɷ����޹�˾~", FProp, 4)

ARect.left = 0
ARect.top = 16
ARect.width = 64
ARect.height = 16

DigitalClockInfo.TimeColor = vbRed
DigitalClockInfo.ShowStrFont.FontName = "����" + Chr$(0)
DigitalClockInfo.ShowStrFont.FontSize = 12
DigitalClockInfo.IsShowHour = 1
DigitalClockInfo.IsShowMinute = 1

nResult = LV_AddDigitalClockArea(hProgram, 1, 2, ARect, DigitalClockInfo) '//ע������Ų���һ���������������עʾ

''''''''''''''''''''''''''''''''''''''''''''''''
LV_AddProgram hProgram, 2, 0, 1


ARect.left = 0
ARect.top = 0
ARect.width = 64
ARect.height = 16
FProp.FontName = "����" + Chr$(0) '�����Ҫ�� Chr$(0)
FProp.FontSize = 12
FProp.FontColor = vbRed

nResult = LV_QuickAddSingleLineTextArea(hProgram, 2, 1, ARect, ADDTYPE_STRING, "�����ɵ���һ��~", FProp, 4)

ARect.left = 0
ARect.top = 16
ARect.width = 64
ARect.height = 16

DigitalClockInfo.TimeColor = vbRed
DigitalClockInfo.ShowStrFont.FontName = "����" + Chr$(0)
DigitalClockInfo.ShowStrFont.FontSize = 12
DigitalClockInfo.IsShowHour = 1
DigitalClockInfo.IsShowMinute = 1
DigitalClockInfo.TimeFormat = 2

nResult = LV_AddDigitalClockArea(hProgram, 2, 2, ARect, DigitalClockInfo) '//ע������Ų���һ���������������עʾ


nResult = LV_Send(LedCommunicationInfo, hProgram)
LV_DeleteProgram hProgram
If nResult Then
    ErrStr = String$(256, Chr(0))
    LV_GetError nResult, 256, ErrStr
    MsgBox ErrStr
Else
    MsgBox "���ͳɹ�"
End If
End Sub











Private Sub Command7_Click()
Dim param As LEDCOMMUNICATIONPARAMETER
Dim LedCommunicationInfo As COMMUNICATIONINFO
Dim nRet As Long
LedCommunicationInfo.SendType = 0
LedCommunicationInfo.IpStr = "192.168.1.187" + Chr$(0)  '�����Ҫ�� Chr$(0)
LedCommunicationInfo.LedNumber = 1

param.dwMask = 0
param.IpStr = "192.168.1.250" + Chr$(0)
param.NetMaskStr = "255.255.255.0" + Chr$(0)
param.GatewayStr = "192.168.1.1" + Chr$(0)
param.MacStr = "ee-ee-ee-ee-ee-ee" + Chr$(0)

nRet = LV_SetLedCommunicationParameter(LedCommunicationInfo, param)
End Sub
















Attribute VB_Name = "LedDll"
Option Explicit

'/*
' *****************************************************************************************************************
' *                                                    LED SDK 6.0
' *
' *                                                       ��ΰ
' *
' *
' *                                      (C) Copyright 2010 - 2015, LISTEN VISION
' *                                                 All Rights Reserved
' *
' *****************************************************************************************************************
' */


Public Const OK As Long = 0                     '�������سɹ�

Public Const ADDTYPE_STRING As Long = 0         '�������Ϊ�ִ�
Public Const ADDTYPE_FILE As Long = 1           '��ӵ�����Ϊ�ļ�



'******��Ŀ��ʱ��������ʱ�����ڵı�־��*****************************************
Public Const ENABLE_DATE As Long = &H1
Public Const ENABLE_TIME As Long = &H2
Public Const ENABLE_WEEK As Long = &H4
'*****************************************************************************

'******��Ŀ��ʱ������ĳ�����ú�*************************************************

Public Const WEEK_MON As Long = &H1
Public Const WEEK_TUES As Long = &H2
Public Const WEEK_WEN As Long = &H4
Public Const WEEK_THUR As Long = &H8
Public Const WEEK_FRI As Long = &H10
Public Const WEEK_SAT As Long = &H20
Public Const WEEK_SUN As Long = &H40

'*****************************************************************************

'**ͨѶ���ýṹ��*********************************************************
Type COMMUNICATIONINFO
    LEDType As Long             'LED����   0.Ϊ����6����ɫ��˫ɫ���߲ʿ�,      1.Ϊ����6��ȫ�ʿ�
    SendType As Long            'ͨѶ��ʽ  0.ΪTcp���ͣ��ֳƹ̶�IPͨѶ��,      1.�㲥���ͣ��ֳƵ���ֱ����      2.����ͨѶ      3.���̱���
    IpStr As String * 16        'LED����IP��ַ��ֻ��ͨѶ��ʽΪ0ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
    Commport As Long            '���ںţ�ֻ��ͨѶ��ʽΪ2ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
    Baud As Long                '�����ʣ�ֻ��ͨѶ��ʽΪ2ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ,   0.9600   1.57600   2.115200  ֱ�Ӹ�ֵ 9600��19200��38400��57600��115200���
    LedNumber As Long           'LED�����ţ�ֻ��ͨѶ��ʽΪ2ʱ������485ͨѶʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
    OutputDir As String * 260   '���̱����Ŀ¼��ֻ��ͨѶ��ʽΪ3ʱ���踳ֵ������ͨѶ��ʽ���踳ֵ
End Type
'***********************************************************************


'**��������ṹ��*********************************************************
Type AREARECT
    left As Long    '�������ϽǺ�����
    top As Long     '�������Ͻ�������
    width As Long   '����Ŀ��
    height As Long  '����ĸ߶�
End Type
'****************************************************************************


'***�������Խṹ��**********************************************************
Type FONTPROP
    FontName As String * 32     '������
    FontSize  As Long           '�ֺ�(��λ��)
    FontColor  As Long          '������ɫ
    FontBold   As Long          '�Ƿ�Ӵ�
    FontItalic  As Long         '�Ƿ�б��
    FontUnderline  As Long      'ʱ���»���
End Type
'****************************************************************************


'**ҳ����ʾ�����Խṹ��****************************************************
Type PLAYPROP
    InStyle As Long     '�볡�ؼ�ֵ��ȡֵ��Χ 0-39��
    OutStyle As Long    '�˳��ؼ�ֵ������Ч��Ԥ������0��
    Speed As Long       '�ؼ���ʾ�ٶ�(ȡֵ��Χ1-255)
    DelayTime As Long   'ҳ����ͣʱ��(1-65535)
End Type
'      /*  �ؼ�ֵ��Ӧ
'            0=������ʾ
'            1=���
'            2=����
'            3=����
'            4=����
'            5=����
'            6=��������
'            7=��������
'            8=��������
'            9=��������
'            10=��˸
'            11=������(����)
'            12=������(����)
'            13=������(����)
'            14=������(����)
'            15=ˮƽ������Ļ
'            16=���½�����Ļ
'            17=��������
'            18=��������
'            19=�󸲸�
'            20=�Ҹ���
'            21=�ϸ���
'            22=�¸���
'            23=ˮƽ��Ҷ(����)
'            24=ˮƽ��Ҷ(����)
'            25=��ֱ��Ҷ(����)
'            26=��ֱ��Ҷ(����)
'            27=���ҶԿ�
'            28=���¶Կ�
'            29=���ұպ�
'            30=���±պ�
'            31=��������
'            32=��������
'            33=��������
'            34=��������
'            35=��ɢ��������
'            36=��ɢ��������
'            37=ð��
'            38=��ѩ
'         */
'*******************************************************************************


'**���ý�Ŀ��ʱ���Խṹ��****************************************************
Type PROGRAMTIME
    EnableFlag As Long      '���ö�ʱ�ı�ǣ�ENABLE_DATEΪ��������,ENABLE_TIMEΪ����ʱ��,ENABLE_WEEKΪ��������,���û����������ϣ��� ENABLE_DATE | ENABLE_TIME | ENABLE_WEEK
    WeekValue As Long       '�������ں�ѡ��Ҫ��ʱ���������ĳЩ�죬�ú� WEEK_MON,WEEK_TUES,WEEK_WEN,WEEK_THUR,WEEK_FRI,WEEK_SAT,WEEK_SUN ͨ��������������
    StartYear As Long       '��ʼ��
    StartMonth As Long      '��ʼ��
    StartDay As Long        '��ʼ��
    StartHour As Long       '���ʱ
    StartMinute As Long     '��ʼ��
    StartSecond As Long     '��ʼ��
    EndYear As Long         '������
    EndMonth As Long        '������
    EndDay As Long         '������
    EndHour As Long         '����ʱ
    EndMinute As Long       '������
    EndSecond As Long       '������
End Type
'**********************************************************************************


'����ʱ�����Խṹ��*********************************************************************************
Type DIGITALCLOCKAREAINFO
    ShowStr As String * 128          '�Զ�����ʾ�ַ���
    ShowStrFont As FONTPROP          '�Զ�����ʾ�ַ����Լ���������ʱ����������ԣ�ע��������������FontColorֻ���Զ�����ʾ������Ч�����������ɫ�е�������ɫ���ԣ����Եĸ�ֵ��FONTPROP�ṹ��˵��
    TimeLagType As Long              'ʱ������ 0Ϊ��ǰ��1Ϊ�ͺ�
    HourNum As Long                  'ʱ��Сʱ��
    MiniteNum As Long               'ʱ�������
    DateFormat As Long              '���ڸ�ʽ 0.YYYY��MM��DD��  1.YY��MM��DD��  2.MM/DD/YYYY  3.YYYY/MM/DD  4.YYYY-MM-DD  5.YYYY.MM.DD  6.MM.DD.YYYY  7.DD.MM.YYYY
    DateColor As Long                  '����������ɫ
    WeekFormat As Long             '���ڸ�ʽ 0.����X  1.Monday  2.Mon.
    WeekColor As Long                  '����������ɫ
    TimeFormat As Long              'ʱ���ʽ 0.HHʱmm��ss��  1.HH�rmm��ss��  2.HH:mm:ss  3.���� HH:mm:ss  4.AM HH:mm:ss  5.HH:mm:ss ����  6.HH:mm:ss AM
    TimeColor As Long                 'ʱ��������ɫ
    IsShowYear As Long                     '�Ƿ���ʾ�� TRUEΪ��ʾ FALSE����ʾ ��ͬ
    IsShowWeek As Long                     '�Ƿ���ʾ����
    IsShowMonth As Long                    '�Ƿ���ʾ��
    IsShowDay As Long                    '�Ƿ���ʾ��
    IsShowHour As Long                     '�Ƿ���ʾʱ
    IsShowMinute As Long                  '�Ƿ���ʾ��
    IsShowSecond  As Long                  '�Ƿ���ʾ��
    IsMutleLineShow  As Long              '�Ƿ������ʾ
End Type
'******************************************************************************


'**ģ��ʱ�����Խṹ��*********************************************************
Type CLOCKAREAINFO
    ShowStr As String * 64           '�Զ�����ʾ�ַ���
    ShowStrFont As FONTPROP               '�Զ�����ʾ�ַ�����������
    TimeLagType As Long             'ʱ������ 0Ϊ��ǰ��1Ϊ�ͺ�
    HourNum As Long                 'ʱ��Сʱ��
    MiniteNum  As Long             'ʱ�������
    
    ClockType As Long             '��������  0.Բ��  1.������
    HourMarkColor As Long              'ʱ����ɫ
    HourMarkType  As Long           'ʱ������  0.Բ��  1.������
    HourMarkWidth  As Long          'ʱ����  1~16
    MiniteMarkColor  As Long            '�ֱ���ɫ
    MiniteMarkType  As Long          '�ֱ�����  0.Բ��  1.������
    MiniteMarkWidth  As Long         '�ֱ���  1~16
    
    HourPointerColor  As Long           'ʱ����ɫ
    MinutePointerColor  As Long         '������ɫ
    SecondPointerColor  As Long         '������ɫ
    
    HourPointerWidth  As Long        'ʱ��Ŀ��  1~5
    MinutePointerWidth  As Long      '����Ŀ��  1~5
    SecondPointerWidth  As Long      '����Ŀ��  1~5
    IsShowDate  As Long                     '�Ƿ���ʾ����
    DateFormat  As Long              '���ڸ�ʽ 0.YYYY��MM��DD��  1.YY��MM��DD��  2.MM/DD/YYYY  3.YYYY/MM/DD  4.YYYY-MM-DD  5.YYYY.MM.DD  6.MM.DD.YYYY  7.DD.MM.YYYY
    DateFont As FONTPROP                 '������������
    
    IsShowWeek As Long                    '�Ƿ���ʾ����
    WeekFormat  As Long              '���ڸ�ʽ 0.����X  1.Monday  2.Mon.
    WeekFont As FONTPROP                  '������������
End Type
'**************************************************************************************


'**��ʱ���Խṹ��**********************************************************************
Type TIMEAREAINFO
    ShowFormat As Long              '��ʾ��ʽ  0.xx��xxʱxx��xx��  1.xx��xx�rxx��xx��  2.xxDayxxHourxxMinxxSec  3.XXdXXhXXmXXs  4.xx:xx:xx:xx
    nYear As Long                  '������
    nMonth As Long                 '������
    nDay As Long                   '������
    nHour As Long                  '����ʱ
    nMinute As Long                '������
    nSecond As Long                '������
    
    IsShowDay As Long                     '�Ƿ���ʾ��
    IsShowHour As Long                    '�Ƿ���ʾʱ
    IsShowMinute As Long                  '�Ƿ���ʾ��
    IsShowSecond As Long                  '�Ƿ���ʾ��
    IsMutleLineShow As Long               '�Ƿ������ʾ��ָ�����Զ����������ʱ�����Ƿ������ʾ
    
    ShowStr As String * 128          '�Զ��������ַ���
    TimeStrColor As Long              '��ʱ���ֵ���ɫ
    ShowFont As FONTPROP                  '�Զ������ּ���ʱ������ɫ������FontColorֻ���Ķ���������Ч����ʱ������ɫΪTimeStrColor
End Type
'****************************************************************************************



'**LEDͨѶ�����޸Ľṹ��*****************************************************************
Type LEDCOMMUNICATIONPARAMETER
    dwMask As Long               'Ҫ�޸���ı��  0.�޸�����ͨѶ����  1.�޸Ĵ���ͨѶ����  2.�޸����ںʹ���ͨѶ����
    IpStr As String * 16         '�µ�IP��ַ��ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ����ʽ���� 192.168.1.100
    NetMaskStr As String * 16    '�µ��������룬ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ����ʽ���� 255.255.255.0
    GatewayStr As String * 16    '�µ����أ�ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ,��ʽ���� 192.168.1.1
    MacStr As String * 18       '�µ�MAC��ַ��ֻ��dwMaskΪ0��2ʱ���踳ֵ������ֵ���踳ֵ����ʽ���� 12-34-56-78-9a-bc,�������޸�����Ϊ ff-ff-ff-ff-ff-ff
    Baud As Long               '�����ʣ�ֻ��dwMaskΪ1��2ʱ���踳ֵ������ֵ���踳ֵ��0.9600  1.57600  2.115200
    LedNumber As Long          'LED���� 1~255,����ͨѶ��232ͨѶ��ֵ 1 ���ɣ�485����Ϳ��ƿ���ʾ��������ͬ�ſ�ͨѶ
End Type
'*****************************************************************************************


'**��ˮ�߿����Խṹ��************************************************************************
Type WATERBORDERINFO
    Flag As Long                           '��ˮ�߿�������ͱ�־��0.Ϊ��̬��Ԥ�õı߿�  1.Ϊ���ļ����صı߿�
    BorderType As Long                     '�߿�����ͣ�FlagΪ0����Ч��0.��ɫ�߿�  1.˫��ɫ�߿�  2.ȫ�ʱ߿�
    BorderValue As Long                    '�߿��ֵ��FlagΪ0����Ч����ɫ�߿�ȡֵ��Χ��0~39,˫��ɫ�߿�ȡֵ��Χ��0~34,ȫ�ʱ߿�ȡֵ��Χ��0~21
    BorderColor As Long                       '�߿�����ɫ,FlagΪ0����BorderTypeΪ0�ǲ���Ч
    BorderStyle As Long                    '�߿���ʾ����ʽ  0.�̶�  1.˳ʱ��  2.��ʱ��  3.��˸
    BorderSpeed As Long                    '�߿��������ٶ�
    WaterBorderBmpPath As String * 260  '�߿�ͼƬ�ļ���·����ע��ֻ����bmpͼƬ��ͼƬ��С�����ǿ��Ϊ32�㣬ȡ�߶�С�ڵ���8
End Type
'*********************************************************************************************


'**��ʱ��������������************************************************************************
Type ONOFFTIMEINFO
    TimeFlag(2) As Long
    StartHour(2) As Long
    StartMinute(2) As Long
    EndHour(2) As Long
    EndMinute(2) As Long
End Type
'********************************************************************************************


'**��ʱ������������**************************************************************************
Type BRIGHTNESSTIMEINFO
    TimeFlag(2) As Long
    StartHour(2) As Long
    StartMinute(2) As Long
    EndHour(2) As Long
    EndMinute(2) As Long
    BrightnessValue(2) As Long
End Type
'*******************************************************************************************






' *******************************************************************************************
' *  LV_CreateProgram            ������Ŀ���󣬷�������Ϊ HPROGRAM
' *
' *  ����˵��
' *              LedWidth        ���Ŀ��
' *              LedHeight       ���ĸ߶�
' *              ColorType       ������ɫ 1.��ɫ  2.˫��ɫ  3.�߲�  4.ȫ��
' *  ����ֵ
' *              0               ������Ŀ����ʧ��
' *              ��0             ������Ŀ����ɹ�
' ********************************************************************************************
Public Declare Function LV_CreateProgram Lib "LV_LED.DLL" (ByVal LedWidth As Long, ByVal LedHeight As Long, ByVal ColorType As Long) As Long

'/*********************************************************************************************
' *  LV_AddProgram               ���һ����Ŀ
' *
' *  ����˵��
' *              hProgram        ��Ŀ������
' *              ProgramNo       ��Ŀ��
' *              PlayTime        ��Ŀ����ʱ�� 0.��Ŀ����ʱ��  ��0.ָ������ʱ��
' *              LoopCount       ѭ�����Ŵ���
' *  ����ֵ
' *              0               �ɹ�
' *              ��0             ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddProgram Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal PlayTime As Long, ByVal LoopCount As Long) As Long

'/*********************************************************************************************
' *  LV_SetProgramTime           ���ý�Ŀ��ʱ
' *
' *  ����˵��
' *              hProgram        ��Ŀ������
' *              ProgramNo       ��Ŀ��
' *              pProgramTime    ��Ŀ��ʱ���ԣ����÷�ʽ��PROGRAMTIME�ṹ��עʾ
' *  ����ֵ
' *              0               �ɹ�
' *              ��0             ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_SetProgramTime Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, pProgramTime As PROGRAMTIME) As Long

'/*********************************************************************************************
' *  LV_AddImageTextArea             ���һ��ͼ������
' *
' *  ����˵��
' *              hProgram            ��Ŀ������
' *              ProgramNo           ��Ŀ��
' *              AreaNo              �����
' *              pAreaRect           �����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
' *              IsBackgroundArea    �Ƿ�Ϊ��������0.ǰ������Ĭ�ϣ� 1.������
' *  ����ֵ
' *              0                   �ɹ�
' *              ��0                 ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddImageTextArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, pAreaRect As AREARECT, ByVal IsBackgroundArea As Long) As Long


'/*********************************************************************************************
' *  LV_AddDataToImageTextAreaFromFile   ���һ���ļ���ͼ����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              FilePath                �ļ�·����֧�ֵ��ļ������� txt  rtf  bmp  gif  png  jpg jpeg tiff
' *              pPlayProp               ��ʾ�����ԣ����÷�ʽ��PLAYPROP�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddFileToImageTextArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, ByVal FilePath As String, pPlayProp As PLAYPROP) As Long

'/*********************************************************************************************
' *  LV_AddSingleLineTextToImageTextArea ���һ�������ı���ͼ����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              AddType                 ��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
' *              AddStr                  AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
' *              pFontProp               ���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
' *              pPlayProp               ��ʾ�����ԣ����÷�ʽ��PLAYPROP�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddSingleLineTextToImageTextArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, ByVal AddType As Long, ByVal AddStr As String, pFontProp As FONTPROP, pPlayProp As PLAYPROP) As Long

'/*********************************************************************************************
' *  LV_AddMultiLineTextToImageTextArea  ���һ�������ı���ͼ����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              AddType                 ��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
' *              AddStr                  AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
' *              pFontProp               ���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
' *              pPlayProp               ��ʾ�����ԣ����÷�ʽ��PLAYPROP�ṹ��עʾ
' *              nAlignment              ˮƽ������ʽ��0.�����  1.�Ҷ���  2.ˮƽ����  ��ע�⣺ֻ���ַ�����txt�ļ���Ч��
' *              IsVCenter               �Ƿ�ֱ����  0.�ö���Ĭ�ϣ� 1.��ֱ����
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddMultiLineTextToImageTextArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, ByVal AddType As Long, ByVal AddStr As String, pFontProp As FONTPROP, pPlayProp As PLAYPROP, ByVal nAlignment As Long, ByVal IsVCenter As Long) As Long



'/*********************************************************************************************
' *  LV_AddStaticTextToImageTextArea     ���һ����ֹ�ı���ͼ����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              AddType                 ��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
' *              AddStr                  AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
' *              pFontProp               ���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
' *              DelayTime               ��ʾ��ʱ�� 1~65535
' *              nAlignment              ˮƽ������ʽ��0.�����  1.�Ҷ���  2.ˮƽ����  ��ע�⣺ֻ���ַ�����txt�ļ���Ч��
' *              IsVCenter               �Ƿ�ֱ����  0.�ö���Ĭ�ϣ� 1.��ֱ����
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddStaticTextToImageTextArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, ByVal AddType As Long, ByVal AddStr As String, pFontProp As FONTPROP, ByVal DelayTime As Long, ByVal nAlignment As Long, ByVal IsVCenter As Long) As Long

'/*********************************************************************************************
' *  LV_QuickAddSingleLineTextArea       �������һ�������ı�����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              pAreaRect               �����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
' *              AddType                 ��ӵ�����  0.Ϊ�ַ���  1.�ļ���ֻ֧��txt��rtf�ļ���
' *              AddStr                  AddTypeΪ0��Ϊ�ַ�������,AddTypeΪ1��Ϊ�ļ�·��
' *              pFontProp               ���AddTypeΪ�ַ������ͻ�AddTypeΪ�ļ��������ļ�Ϊtxt��ɴ����Ը�ֵ�ĸýṹ�壬�����ɸ�NULL
' *              nSpeed                  �����ٶ� 1~255
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_QuickAddSingleLineTextArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, pAreaRect As AREARECT, ByVal AddType As Long, ByVal AddStr As String, pFontProp As FONTPROP, ByVal nSpeed As Long) As Long

'/*********************************************************************************************
' *  LV_AddDigitalClockArea              ���һ������ʱ������
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              pAreaRect               �����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
' *              pDigitalClockAreaInfo   ����ʱ�����ԣ���DIGITALCLOCKAREAINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddDigitalClockArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, pAreaRect As AREARECT, pDigitalClockAreaInfo As DIGITALCLOCKAREAINFO) As Long


'/*********************************************************************************************
' *  LV_AddTimeArea                      ���һ����ʱ����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              pAreaRect               �����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
' *              pTimeAreaInfo           ��ʱ���ԣ���TIMEAREAINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddTimeArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, pAreaRect As AREARECT, pTimeAreaInfo As TIMEAREAINFO) As Long

'/*********************************************************************************************
' *  LV_AddClockArea                     ���һ��ģ��ʱ������
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              pAreaRect               �����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
' *              pClockAreaInfo          ģ��ʱ�����ԣ���CLOCKAREAINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddClockArea Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, pAreaRect As AREARECT, pClockAreaInfo As CLOCKAREAINFO) As Long
'
'/*********************************************************************************************
' *  LV_AddWaterBorder                   ���һ����ˮ�߿�����
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' *              ProgramNo               ��Ŀ��
' *              AreaNo                  �����
' *              pAreaRect               �����������ԣ����÷�ʽ��AREARECT�ṹ��עʾ
' *              pWaterBorderInfo        ��ˮ�߿����ԣ���WATERBORDERINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AddWaterBorder Lib "LV_LED.DLL" (ByVal hProgram As Long, ByVal ProgramNo As Long, ByVal AreaNo As Long, pAreaRect As AREARECT, pWaterBorderInfo As WATERBORDERINFO) As Long

'/*********************************************************************************************
' *  LV_DeleteProgram                    ���ٽ�Ŀ����(ע�⣺����˽�Ŀ������ʹ�ã�����ô˺������٣����������ڴ�й¶)
' *
' *  ����˵��
' *              hProgram                ��Ŀ������
' ********************************************************************************************/

Public Declare Sub LV_DeleteProgram Lib "LV_LED.DLL" (ByVal hProgram As Long)


'/*********************************************************************************************
' *  LV_Send                             ���ͽ�Ŀ���˷���Ϊһ��һ����
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              hProgram                ��Ŀ������
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_Send Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal hProgram As Long) As Long

'/*********************************************************************************************
' *  LV_MultiSendOne                     ���ͽ�Ŀ���˷���Ϊ���������һ����Ŀ�����з���
' *
' *  ����˵��
' *              pCommunicationInfoArray ͨѶ������Ϊһ���飬��ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              hProgram                ��Ŀ������
' *              pResultArray            ���ͷ��صĽ������,�������غ�ͨ����ֵ�жϷ����Ƿ�ɹ���0Ϊ�ɹ�����0ʧ�ܣ�����LV_GetError����ȡ������Ϣ��
' *              LedCount                Ҫ���͵����ĸ�������ΪpCommunicationInfoArray��pResultArray������ϱ���
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_MultiSendOne Lib "LV_LED.DLL" (pCommunicationInfoArray() As COMMUNICATIONINFO, ByVal hProgram As Long, pResultArray() As Long, ByVal LedCount As Long) As Long

'/*********************************************************************************************
' *  LV_MultiSend                        ���ͽ�Ŀ���˷���Ϊ��������Ͳ�ͬ�Ľ�Ŀ�����з���
' *
' *  ����˵��
' *              pCommunicationInfoArray ͨѶ������Ϊһ���飬��ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              phProgramArray          ��Ŀ����������
' *              pResultArray            ���ͷ��صĽ������,�������غ�ͨ����ֵ�жϷ����Ƿ�ɹ���0Ϊ�ɹ�����0ʧ�ܣ�����LV_GetError����ȡ������Ϣ��
' *              LedCount                Ҫ���͵����ĸ�������ΪpCommunicationInfoArray��phProgramArray��pResultArray������ϱ���
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_MultiSend Lib "LV_LED.DLL" (pCommunicationInfoArray() As COMMUNICATIONINFO, phProgramArray() As Long, pResultArray() As Long, ByVal LedCount As Long) As Long


'/*********************************************************************************************
' *  LV_TestOnline                       ����LED���Ƿ��������
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_TestOnline Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO) As Long


'/*********************************************************************************************
' *  LV_SetBasicInfo                     ���û�������
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              ColorType               ������ɫ 1.��ɫ  2.˫��ɫ  3.�߲�  4.ȫ��
' *              LedWidth                ���Ŀ�ȵ���
' *              LedHeight               ���ĸ߶ȵ���
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_SetBasicInfo Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal ColorType As Long, ByVal LedWidth As Long, ByVal LedHeight As Long) As Long
'
'
'/*********************************************************************************************
' *  LV_SetOEDA                          ����OE DA
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              Oe                      OE  0.����Ч  1.����Ч
' *              Da                      DA  0.������  1.������
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_SetOEDA Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal Oe As Long, ByVal Da As Long) As Long
'
'
'/*********************************************************************************************
' *  LV_AdjustTime                       Уʱ
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_AdjustTime Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO) As Long



'/*********************************************************************************************
' *  LV_PowerOnOff                       ������
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              OnOff                   ����ֵ  0.����  1.����
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_PowerOnOff Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal OnOff As Long) As Long
'
'/*********************************************************************************************
' *  LV_TimePowerOnOff                   ��ʱ������
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              pTimeInfo               ��ʱ���������ԣ����ONOFFTIMEINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_TimePowerOnOff Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, pTimeInfo As ONOFFTIMEINFO) As Long
'
'/*********************************************************************************************
' *  LV_SetBrightness                    ��������
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              BrightnessValue         ����ֵ 0~15
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_SetBrightness Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal BrightnessValue As Long) As Long
'
'/*********************************************************************************************
' *  LV_TimeBrightness                   ��ʱ����
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              pBrightnessTimeInfo     ��ʱ�������ԣ����BRIGHTNESSTIMEINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_TimeBrightness Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, pBrightnessTimeInfo As BRIGHTNESSTIMEINFO) As Long
'
'/*********************************************************************************************
' *  LV_SetLanguage                      ����LED��ʾ������
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              LanguageValue           ����ֵ  0.���ģ�Ĭ�ϣ� 1.Ӣ��
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_SetLanguage Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal LanguageValue As Long) As Long
'
'/*********************************************************************************************
' *  LV_LedTest                          LED����
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              TestValue               ����ֵ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_LedTest Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal TestValue As Long) As Long
'
'/*********************************************************************************************
' *  LV_TimeLocker                       LED��ʱ����
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              LockerYear              ������
' *              LockerMonth             ������
' *              LockerDay               ������
' *              LockerHour              ����ʱ
' *              LockerMinute            ������
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_TimeLocker Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, ByVal LockerYear As Long, ByVal LockerMonth As Long, ByVal LockerDay As Long, ByVal LockerHour As Long, ByVal LockerMinute As Long) As Long
'
'/*********************************************************************************************
' *  LV_CancelLocker                     ȡ����ʱ����
' *
' *  ����˵��
' *              pCommunicationInfo      ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_CancelLocker Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO) As Long
'
'/*********************************************************************************************
' *  LV_SetLedCommunicationParameter         ����LEDͨѶ����
' *
' *  ����˵��
' *              pCommunicationInfo          ͨѶ��������ֵ��ʽ��COMMUNICATIONINFO�ṹ��עʾ
' *              pLedCommunicationParameter  ���LEDCOMMUNICATIONPARAMETER�ṹ��עʾ
' *  ����ֵ
' *              0                       �ɹ�
' *              ��0                     ʧ�ܣ�����LV_GetError����ȡ������Ϣ
' ********************************************************************************************/
Public Declare Function LV_SetLedCommunicationParameter Lib "LV_LED.DLL" (pCommunicationInfo As COMMUNICATIONINFO, pLedCommunicationParameter As LEDCOMMUNICATIONPARAMETER) As Long
'
'
'
'/*********************************************************************************************
' *  LV_GetError                             ��ȡ������Ϣ��ֻ֧�����ģ�
' *
' *  ����˵��
' *              nErrCode                    ����ִ�з��صĴ������
' *              nMaxSize                    pErrStr�ַ����������Ĵ�С��Ϊ�ַ��ĸ��������ֽ�����
' *              pErrStr                     ����ȡ������Ϣ���ַ�����ַ
' ********************************************************************************************/
'typedef void        (__stdcall *_LV_GetError)(int nErrCode,int nMaxCount,OUT LPTSTR pErrStr);
Public Declare Sub LV_GetError Lib "LV_LED.DLL" (ByVal nErrCode As Long, ByVal nMaxSize As Long, ByVal pErrStr As String)














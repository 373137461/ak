Imports System.Runtime.InteropServices

Public Class Form1

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim ErrStr As String
        Dim nResult As Long
        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
        LedCommunicationInfo.LedNumber = 1
        '//广播通讯********************************************************************************
        'CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
        '//串口通讯********************************************************************************
        'CommunicationInfo.SendType=2;//串口通讯
        'CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
        'CommunicationInfo.Baud=9600;//波特率
        'CommunicationInfo.LedNumber=1;

        nResult = LV_SetBasicInfo(LedCommunicationInfo, 2, 64, 32)
        If nResult Then
            ErrStr = Space(256)
            LV_GetError(nResult, 256, ErrStr)
            MsgBox(ErrStr)
        Else
            MsgBox("设置屏参成功")
        End If
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim ErrStr As String
        Dim nResult As Long
        Dim hProgram As Long
        Dim ARect As AREARECT
        Dim FProp As FONTPROP


        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
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
        FProp.FontName = "黑体"
        FProp.FontSize = 12
        FProp.FontColor = COLOR_RED

        Call LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "胡半仙到此一游~", FProp, 4)

        nResult = LV_Send(LedCommunicationInfo, hProgram)
        LV_DeleteProgram(hProgram)
        If nResult Then
            ErrStr = Space(256)
            LV_GetError(nResult, 256, ErrStr)
            MsgBox(ErrStr)
        Else
            MsgBox("发送成功")
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim ErrStr As String
        Dim nResult As Long
        Dim hProgram As Long
        Dim ARect As AREARECT
        Dim FProp As FONTPROP
        Dim PProp As PLAYPROP


        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
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



        FProp.FontName = "黑体"
        FProp.FontSize = 12
        FProp.FontColor = COLOR_RED

        PProp.InStyle = 0
        PProp.DelayTime = 3
        PProp.Speed = 4

        '可以添加多个子项到图文区，如下添加可以选一个或多个添加
        Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_STRING, "上海灵信视觉技术股份有限公司", FProp, PProp, 0, 0) '通过字符串添加一个多行文本到图文区，参数说明见声明注示
        'Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_FILE, "test.rtf", FProp, PProp, 0, 0) '通过rtf文件添加一个多行文本到图文区，参数说明见声明注示
        'Call LV_AddMultiLineTextToImageTextArea(hProgram, 1, 1, ADDTYPE_FILE, "test.txt", FProp, PProp, 0, 0) '通过txt文件添加一个多行文本到图文区，参数说明见声明注示


        nResult = LV_Send(LedCommunicationInfo, hProgram)
        LV_DeleteProgram(hProgram)
        If nResult Then
            ErrStr = Space(256)
            LV_GetError(nResult, 256, ErrStr)
            MsgBox(ErrStr)
        Else
            MsgBox("发送成功")
        End If

    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Dim ErrStr As String
        Dim nResult As Long
        Dim hProgram As Long
        Dim ARect As AREARECT
        Dim PProp As PLAYPROP


        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
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
        LV_DeleteProgram(hProgram)
        If nResult Then
            ErrStr = Space(256)
            LV_GetError(nResult, 256, ErrStr)
            MsgBox(ErrStr)
        Else
            MsgBox("发送成功")
        End If
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Dim ErrStr As String
        Dim nResult As Long
        Dim hProgram As Long
        Dim ARect As AREARECT
        Dim FProp As FONTPROP


        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
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
        FProp.FontName = "宋体"
        FProp.FontSize = 12
        FProp.FontColor = COLOR_RED

        nResult = LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "上海灵信视觉技术股份有限公司~", FProp, 4)

        ARect.left = 0
        ARect.top = 16
        ARect.width = 64
        ARect.height = 16


        Dim DigitalClockInfo As DIGITALCLOCKAREAINFO

        DigitalClockInfo.TimeColor = COLOR_RED
        DigitalClockInfo.ShowStrFont.FontName = "宋体"
        DigitalClockInfo.ShowStrFont.FontSize = 12
        DigitalClockInfo.IsShowHour = 1
        DigitalClockInfo.IsShowMinute = 1

        nResult = LV_AddDigitalClockArea(hProgram, 1, 2, ARect, DigitalClockInfo) '//注意区域号不能一样，详见函数声明注示


        nResult = LV_Send(LedCommunicationInfo, hProgram)
        LV_DeleteProgram(hProgram)
        If nResult Then
            ErrStr = Space(256)
            LV_GetError(nResult, 256, ErrStr)
            MsgBox(ErrStr)
        Else
            MsgBox("发送成功")
        End If
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Dim ErrStr As String
        Dim nResult As Long
        Dim hProgram As Long
        Dim ARect As AREARECT
        Dim FProp As FONTPROP
        Dim DigitalClockInfo As DIGITALCLOCKAREAINFO

        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
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
        FProp.FontName = "宋体"
        FProp.FontSize = 12
        FProp.FontColor = COLOR_RED

        nResult = LV_QuickAddSingleLineTextArea(hProgram, 1, 1, ARect, ADDTYPE_STRING, "上海灵信视觉技术股份有限公司~", FProp, 4)

        ARect.left = 0
        ARect.top = 16
        ARect.width = 64
        ARect.height = 16

        DigitalClockInfo.TimeColor = COLOR_RED
        DigitalClockInfo.ShowStrFont.FontName = "宋体"
        DigitalClockInfo.ShowStrFont.FontSize = 12
        DigitalClockInfo.IsShowHour = 1
        DigitalClockInfo.IsShowMinute = 1

        nResult = LV_AddDigitalClockArea(hProgram, 1, 2, ARect, DigitalClockInfo) '//注意区域号不能一样，详见函数声明注示

        ''''''''''''''''''''''''''''''''''''''''''''''''
        LV_AddProgram(hProgram, 2, 0, 1)


        ARect.left = 0
        ARect.top = 0
        ARect.width = 64
        ARect.height = 16
        FProp.FontName = "宋体"
        FProp.FontSize = 12
        FProp.FontColor = COLOR_GREEN

        nResult = LV_QuickAddSingleLineTextArea(hProgram, 2, 1, ARect, ADDTYPE_STRING, "胡半仙到此一游~", FProp, 4)

        ARect.left = 0
        ARect.top = 16
        ARect.width = 64
        ARect.height = 16

        DigitalClockInfo.TimeColor = COLOR_GREEN
        DigitalClockInfo.ShowStrFont.FontName = "黑体"
        DigitalClockInfo.ShowStrFont.FontSize = 12
        DigitalClockInfo.IsShowHour = 1
        DigitalClockInfo.IsShowMinute = 1
        DigitalClockInfo.TimeFormat = 2

        nResult = LV_AddDigitalClockArea(hProgram, 2, 2, ARect, DigitalClockInfo) '//注意区域号不能一样，详见函数声明注示


        nResult = LV_Send(LedCommunicationInfo, hProgram)
        LV_DeleteProgram(hProgram)
        If nResult Then
            ErrStr = Space(256)
            LV_GetError(nResult, 256, ErrStr)
            MsgBox(ErrStr)
        Else
            MsgBox("发送成功")
        End If
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        Dim LedCommunicationInfo As New COMMUNICATIONINFO
        LedCommunicationInfo.SendType = 0
        LedCommunicationInfo.IpStr = "192.168.1.245"
        LedCommunicationInfo.LedNumber = 1

        Dim info As New ONOFFTIMEINFO

        Dim nsize As Integer

        ReDim info.TimeFlag(2)
        ReDim info.StartHour(2)
        ReDim info.StartMinute(2)
        ReDim info.EndHour(2)
        ReDim info.EndMinute(2)

        info.TimeFlag(0) = 1
        info.StartHour(0) = 16
        info.StartMinute(0) = 5
        info.EndHour(0) = 16
        info.EndMinute(0) = 6

        Call LV_TimePowerOnOff(LedCommunicationInfo, info)

        ' Call LV_AdjustTime(LedCommunicationInfo)
    End Sub
End Class

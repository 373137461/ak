// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "LedDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog
CLedDll g_Dll;

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	g_Dll.InitDll();


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::OnButton1() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//定义一通讯参数结构体变量用于对设定的LED通讯，具体对此结构体元素赋值说明见COMMUNICATIONINFO结构体定义部份注示
//TCP通讯********************************************************************************
	CommunicationInfo.SendType=0;//设为固定IP通讯模式，即TCP通讯
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//给IpStr赋值LED控制卡的IP
	CommunicationInfo.LedNumber=1;//LED屏号为1，注意socket通讯和232通讯不识别屏号，默认赋1就行了，485必需根据屏的实际屏号进行赋值
//广播通讯********************************************************************************
	//CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
//串口通讯********************************************************************************
	//CommunicationInfo.SendType=2;//串口通讯
	//CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
	//CommunicationInfo.Baud=9600;//波特率
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//节目句柄
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//根据传的参数创建节目句柄，64是屏宽点数，32是屏高点数，2是屏的颜色，注意此处屏宽高及颜色参数必需与设置屏参的屏宽高及颜色一致，否则发送时会提示错误
	//此处可自行判断有未创建成功，hProgram返回NULL失败，非NULL成功,一般不会失败

	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//添加一个节目，参数说明见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//区域坐标属性结构体变量
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=32;

	FONTPROP FontProp;//文字属性
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("宋体"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_GREEN;

	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_STRING,_T("上海灵信视觉技术股份有限公司"),&FontProp,4);//快速通过字符添加一个单行文本区域，函数见函数声明注示
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.rtf"),NULL,4);//快速通过rtf文件添加一个单行文本区域，函数见函数声明注示
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.txt"),&FontProp,4);//快速通过txt文件添加一个单行文本区域，函数见函数声明注示

	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//发送，见函数声明注示
	g_Dll.LV_DeleteProgram(hProgram);//删除节目内存对象，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("发送成功"));
	}
	


}

void CDemoDlg::OnButton2() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//定义一通讯参数结构体变量用于对设定的LED通讯，具体对此结构体元素赋值说明见COMMUNICATIONINFO结构体定义部份注示
	//TCP通讯********************************************************************************
	CommunicationInfo.SendType=0;//设为固定IP通讯模式，即TCP通讯
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//给IpStr赋值LED控制卡的IP
	CommunicationInfo.LedNumber=1;//LED屏号为1，注意socket通讯和232通讯不识别屏号，默认赋1就行了，485必需根据屏的实际屏号进行赋值
	//广播通讯********************************************************************************
	//CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
	//串口通讯********************************************************************************
	//CommunicationInfo.SendType=2;//串口通讯
	//CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
	//CommunicationInfo.Baud=9600;//波特率
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//节目句柄
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//根据传的参数创建节目句柄，64是屏宽点数，32是屏高点数，2是屏的颜色，注意此处屏宽高及颜色参数必需与设置屏参的屏宽高及颜色一致，否则发送时会提示错误
	//此处可自行判断有未创建成功，hProgram返回NULL失败，非NULL成功,一般不会失败
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//添加一个节目，参数说明见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//区域坐标属性结构体变量
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=32;
	
	nResult=g_Dll.LV_AddImageTextArea(hProgram,1,1,&AreaRect,FALSE);
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	PLAYPROP PlayProp;//显示属性
	PlayProp.DelayTime=3;
	PlayProp.InStyle=0;
	PlayProp.OutStyle=0;
	PlayProp.Speed=1;

	//可以添加多个子项到图文区，如下添加可以选一个或多个添加
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.bmp"),&PlayProp);
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.jpg"),&PlayProp);
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.png"),&PlayProp);
	PlayProp.Speed=3;
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.gif"),&PlayProp);

	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//发送，见函数声明注示
	g_Dll.LV_DeleteProgram(hProgram);//删除节目内存对象，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("发送成功"));
	}
}

void CDemoDlg::OnButton3() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//定义一通讯参数结构体变量用于对设定的LED通讯，具体对此结构体元素赋值说明见COMMUNICATIONINFO结构体定义部份注示
	//ZeroMemory(&CommunicationInfo,sizeof(COMMUNICATIONINFO));
//TCP通讯********************************************************************************
	CommunicationInfo.SendType=0;//设为固定IP通讯模式，即TCP通讯
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.88"));//给IpStr赋值LED控制卡的IP
	CommunicationInfo.LedNumber=1;//LED屏号为1，注意socket通讯和232通讯不识别屏号，默认赋1就行了，485必需根据屏的实际屏号进行赋值
//广播通讯********************************************************************************
	//CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
//串口通讯********************************************************************************
	//CommunicationInfo.SendType=2;//串口通讯
	//CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
	//CommunicationInfo.Baud=9600;//波特率
	//CommunicationInfo.LedNumber=1;
	
	
	nResult=g_Dll.LV_SetBasicInfo(&CommunicationInfo,1,128,32);//设置屏参，屏的颜色为2即为双基色，64为屏宽点数，32为屏高点数，具体函数参数说明见函数声明注示
	if(nResult)//如果失败则可以调用LV_GetError获取中文错误信息
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
	}
	else
	{
		MessageBox(_T("设置成功"));
	}
}

void CDemoDlg::OnButton4() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//定义一通讯参数结构体变量用于对设定的LED通讯，具体对此结构体元素赋值说明见COMMUNICATIONINFO结构体定义部份注示
	//TCP通讯********************************************************************************
	CommunicationInfo.SendType=0;//设为固定IP通讯模式，即TCP通讯
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.98"));//给IpStr赋值LED控制卡的IP
	CommunicationInfo.LedNumber=1;//LED屏号为1，注意socket通讯和232通讯不识别屏号，默认赋1就行了，485必需根据屏的实际屏号进行赋值
	//广播通讯********************************************************************************
	//CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
	//串口通讯********************************************************************************
	//CommunicationInfo.SendType=2;//串口通讯
	//CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
	//CommunicationInfo.Baud=9600;//波特率
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//节目句柄
	hProgram=g_Dll.LV_CreateProgram(64,32,3);//根据传的参数创建节目句柄，64是屏宽点数，32是屏高点数，2是屏的颜色，注意此处屏宽高及颜色参数必需与设置屏参的屏宽高及颜色一致，否则发送时会提示错误
	//此处可自行判断有未创建成功，hProgram返回NULL失败，非NULL成功,一般不会失败
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//添加一个节目，参数说明见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//区域坐标属性结构体变量
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=32;

	nResult=g_Dll.LV_AddImageTextArea(hProgram,1,1,&AreaRect,FALSE);
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	FONTPROP FontProp;//文字属性
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("宋体"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;


	PLAYPROP PlayProp;//显示属性
	PlayProp.DelayTime=3;
	PlayProp.InStyle=0;
	PlayProp.OutStyle=0;
	PlayProp.Speed=1;

	//可以添加多个子项到图文区，如下添加可以选一个或多个添加
	nResult=g_Dll.LV_AddStaticTextToImageTextArea(hProgram,1,1,ADDTYPE_STRING,_T("上海灵信视觉技术股份有限公司"),&FontProp,3,0,FALSE);
 	//nResult=g_Dll.LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_STRING,_T("上海灵信视觉技术股份有限公司"),&FontProp,&PlayProp,0,FALSE);//通过字符串添加一个多行文本到图文区，参数说明见声明注示
	//nResult=g_Dll.LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_FILE,_T("test.rtf"),NULL,&PlayProp,0,FALSE);//通过rtf文件添加一个多行文本到图文区，参数说明见声明注示
	//nResult=g_Dll.LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_FILE,_T("test.txt"),&FontProp,&PlayProp,0,FALSE);//通过txt文件添加一个多行文本到图文区，参数说明见声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//发送，见函数声明注示
	g_Dll.LV_DeleteProgram(hProgram);//删除节目内存对象，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("发送成功"));
	}
}

void CDemoDlg::OnButton5() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//定义一通讯参数结构体变量用于对设定的LED通讯，具体对此结构体元素赋值说明见COMMUNICATIONINFO结构体定义部份注示
	//TCP通讯********************************************************************************
	CommunicationInfo.SendType=0;//设为固定IP通讯模式，即TCP通讯
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//给IpStr赋值LED控制卡的IP
	CommunicationInfo.LedNumber=1;//LED屏号为1，注意socket通讯和232通讯不识别屏号，默认赋1就行了，485必需根据屏的实际屏号进行赋值
	//广播通讯********************************************************************************
	//CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
	//串口通讯********************************************************************************
	//CommunicationInfo.SendType=2;//串口通讯
	//CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
	//CommunicationInfo.Baud=9600;//波特率
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//节目句柄
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//根据传的参数创建节目句柄，64是屏宽点数，32是屏高点数，2是屏的颜色，注意此处屏宽高及颜色参数必需与设置屏参的屏宽高及颜色一致，否则发送时会提示错误
	//此处可自行判断有未创建成功，hProgram返回NULL失败，非NULL成功,一般不会失败
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//添加一个节目，参数说明见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//区域坐标属性结构体变量
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=16;
	
	FONTPROP FontProp;//文字属性
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("宋体"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;
	
	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_STRING,_T("上海灵信视觉技术股份有限公司"),&FontProp,4);//快速通过字符添加一个单行文本区域，函数见函数声明注示
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.rtf"),NULL,4);//快速通过rtf文件添加一个单行文本区域，函数见函数声明注示
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.txt"),&FontProp,4);//快速通过txt文件添加一个单行文本区域，函数见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	AreaRect.left=0;
	AreaRect.top=16;
	AreaRect.width=64;
	AreaRect.height=16;

	DIGITALCLOCKAREAINFO DigitalClockAreaInfo;
	ZeroMemory(&DigitalClockAreaInfo,sizeof(DIGITALCLOCKAREAINFO));
	DigitalClockAreaInfo.TimeColor=COLOR_RED;
	_tcscpy(DigitalClockAreaInfo.ShowStrFont.FontName,_T("宋体"));
	DigitalClockAreaInfo.ShowStrFont.FontSize=12;
	DigitalClockAreaInfo.IsShowHour=TRUE;
	DigitalClockAreaInfo.IsShowMinute=TRUE;
	nResult=g_Dll.LV_AddDigitalClockArea(hProgram,1,2,&AreaRect,&DigitalClockAreaInfo);//注意区域号不能一样，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}


	
	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//发送，见函数声明注示
	g_Dll.LV_DeleteProgram(hProgram);//删除节目内存对象，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("发送成功"));
	}
	
}

void CDemoDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//定义一通讯参数结构体变量用于对设定的LED通讯，具体对此结构体元素赋值说明见COMMUNICATIONINFO结构体定义部份注示
	//TCP通讯********************************************************************************
	CommunicationInfo.SendType=0;//设为固定IP通讯模式，即TCP通讯
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//给IpStr赋值LED控制卡的IP
	CommunicationInfo.LedNumber=1;//LED屏号为1，注意socket通讯和232通讯不识别屏号，默认赋1就行了，485必需根据屏的实际屏号进行赋值
	//广播通讯********************************************************************************
	//CommunicationInfo.SendType=1;//设为单机直连，即广播通讯无需设LED控制器的IP地址
	//串口通讯********************************************************************************
	//CommunicationInfo.SendType=2;//串口通讯
	//CommunicationInfo.Commport=1;//串口的编号，如设备管理器里显示为 COM3 则此处赋值 3
	//CommunicationInfo.Baud=9600;//波特率
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//节目句柄
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//根据传的参数创建节目句柄，64是屏宽点数，32是屏高点数，2是屏的颜色，注意此处屏宽高及颜色参数必需与设置屏参的屏宽高及颜色一致，否则发送时会提示错误
	//此处可自行判断有未创建成功，hProgram返回NULL失败，非NULL成功,一般不会失败
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//添加一个节目，参数说明见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	AREARECT AreaRect;//区域坐标属性结构体变量
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=16;
	
	FONTPROP FontProp;//文字属性
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("宋体"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;
	
	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_STRING,_T("上海灵信视觉技术股份有限公司"),&FontProp,4);//快速通过字符添加一个单行文本区域，函数见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	AreaRect.left=0;
	AreaRect.top=16;
	AreaRect.width=64;
	AreaRect.height=16;
	
	DIGITALCLOCKAREAINFO DigitalClockAreaInfo;
	ZeroMemory(&DigitalClockAreaInfo,sizeof(DIGITALCLOCKAREAINFO));
	DigitalClockAreaInfo.TimeColor=COLOR_RED;
	_tcscpy(DigitalClockAreaInfo.ShowStrFont.FontName,_T("宋体"));
	DigitalClockAreaInfo.ShowStrFont.FontSize=12;
	DigitalClockAreaInfo.IsShowHour=TRUE;
	DigitalClockAreaInfo.IsShowMinute=TRUE;
	nResult=g_Dll.LV_AddDigitalClockArea(hProgram,1,2,&AreaRect,&DigitalClockAreaInfo);//注意区域号不能一样，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	nResult=g_Dll.LV_AddProgram(hProgram,2,0,1);//添加第二个节目，注意节目号不同相同
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=16;

	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("宋体"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;

	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,2,1,&AreaRect,ADDTYPE_STRING,_T("胡半仙到此一游~"),&FontProp,8);//快速通过字符添加一个单行文本区域，函数见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	AreaRect.left=0;
	AreaRect.top=16;
	AreaRect.width=64;
	AreaRect.height=16;

	DigitalClockAreaInfo.TimeColor=COLOR_YELLOW;
	DigitalClockAreaInfo.TimeFormat=2;
	_tcscpy(DigitalClockAreaInfo.ShowStrFont.FontName,_T("黑体"));
	DigitalClockAreaInfo.ShowStrFont.FontSize=12;
	DigitalClockAreaInfo.IsShowHour=TRUE;
	DigitalClockAreaInfo.IsShowMinute=TRUE;
	nResult=g_Dll.LV_AddDigitalClockArea(hProgram,2,2,&AreaRect,&DigitalClockAreaInfo);//注意区域号不能一样，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}


	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//发送，见函数声明注示
	g_Dll.LV_DeleteProgram(hProgram);//删除节目内存对象，详见函数声明注示
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//见函数声明注示
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("发送成功"));
	}
}

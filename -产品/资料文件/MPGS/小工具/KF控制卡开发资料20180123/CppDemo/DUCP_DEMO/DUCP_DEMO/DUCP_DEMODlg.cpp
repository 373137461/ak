
// DUCP_DEMODlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DUCP_DEMO.h"
#include "DUCP_DEMODlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define USE_STATIC_LIB		0


#include <stdint.h>
#include "DUCP.H"

#if USE_STATIC_LIB
#include "DUCP_HOST.H"
#include "MBmsg.h"
#pragma comment(lib, "../Debug/DUCP.lib")
#else

typedef int8_t(*cbSTKOut_t)(uint8_t * p, uint32_t size);

typedef void(*MB_STK_SetOutCallback_t)(cbSTKOut_t cb);
MB_STK_SetOutCallback_t MB_STK_SetOutCallback = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_TWIN_Del_t)(int WinID);
DUCP_HOST_TWIN_Del_t DUCP_HOST_TWIN_Del = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_PIC_Del_t)(int WinID);
DUCP_HOST_PIC_Del_t DUCP_HOST_PIC_Del = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_2D_SetColor_t)(int Color);
DUCP_HOST_2D_SetColor_t DUCP_HOST_2D_SetColor = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_2D_FillRect_t)(int x0, int y0, int x1, int y1);
DUCP_HOST_2D_FillRect_t DUCP_HOST_2D_FillRect = 0; //函数指针 	

typedef DUCP_ERR_T(*DUCP_HOST_2D_DrawSysIcon_t)(int x0, int y0, int Num, int Denom, int IconIndex);
DUCP_HOST_2D_DrawSysIcon_t DUCP_HOST_2D_DrawSysIcon = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_PIC_Create_t)(int WinID, int x0, int y0, int xSize, int ySize);
DUCP_HOST_PIC_Create_t DUCP_HOST_PIC_Create = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_PIC_Add_t)(int WinID, int FID, uint8_t EnterMode, uint8_t EnterSpeed,
	uint8_t StopMode, uint8_t StopTime, uint8_t ExitMode, uint8_t ExitSpeed);
DUCP_HOST_PIC_Add_t DUCP_HOST_PIC_Add = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_TWIN_Create_t)(int WinID, int Stile, int x0, int y0, int xSize, int ySize);
DUCP_HOST_TWIN_Create_t DUCP_HOST_TWIN_Create = 0; //函数指针 

typedef DUCP_ERR_T(*DUCP_HOST_TWIN_DisText_t)(	int WinID,
												const char * pText,
												int EnterMode,
												int EnterSpeed,
												int DelayMode,
												int DelayTime,
												int EixtMode,
												int EixtSpeed,
												int FontIndex,
												int TextColor,
												int BkColor,
												int DisTimes);
DUCP_HOST_TWIN_DisText_t DUCP_HOST_TWIN_DisText = 0; //函数指针 



typedef DUCP_ERR_T	(*DUCP_HOST_TTS_Play_t)(const char * pText, uint8_t Opt);
DUCP_HOST_TTS_Play_t DUCP_HOST_TTS_Play = 0; //函数指针 


typedef int8_t(*MB_STK_In_t)(uint8_t * pBuff, uint16_t Size);
MB_STK_In_t MB_STK_In = 0; //函数指针 

typedef DUCP_ERR_T (*DUCP_HOST_TWIN_DownTextFile_t)(int WinID,
												int FileID,
												const char * pText,
												int EnterMode,
												int EnterSpeed,
												int DelayMode,
												int DelayTime,
												int EixtMode,
												int EixtSpeed,
												int FontIndex,
												int TextColor,
												int BkColor);
DUCP_HOST_TWIN_DownTextFile_t DUCP_HOST_TWIN_DownTextFile = 0; //函数指针 
#endif


static SOCKET	DUCP_NetSocket = 0;
SOCKADDR_IN		DUCP_NetPoint;
WSADATA         wd;
HINSTANCE		hDUCP_Dll; //DLL句柄 


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDUCP_DEMODlg 对话框



CDUCP_DEMODlg::CDUCP_DEMODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDUCP_DEMODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDUCP_DEMODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDUCP_DEMODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DISTEXT, &CDUCP_DEMODlg::OnBnClickedButtonDistext)
	ON_BN_CLICKED(IDC_BUTTON_PLAYVOICE, &CDUCP_DEMODlg::OnBnClickedButtonPlayvoice)
	ON_BN_CLICKED(IDC_BUTTON_DEMO1, &CDUCP_DEMODlg::OnBnClickedButtonDemo1)
	ON_BN_CLICKED(IDC_BUTTON_DEMO2, &CDUCP_DEMODlg::OnBnClickedButtonDemo2)
END_MESSAGE_MAP()




/*
	协议栈的数据输出回调函数
*/
static uint8_t cbDUCP_DataOut(uint8_t * Data, int Size)
{
	uint8_t  TxBuff[512];
	uint8_t  RxBuff[512];
	int RSize;

	if (Size > 512) {
		return 0xff;
	}
	for (int i = 0; i < Size; i++)
	{
		TxBuff[i] = Data[i];
	}

	/*发送数据到显示屏*/
	sendto(DUCP_NetSocket, (char *)TxBuff, Size, 0, (SOCKADDR*)&DUCP_NetPoint, sizeof(SOCKADDR));

	/*接收显示屏回复的数据*/
	RSize = recvfrom(DUCP_NetSocket, (char *)RxBuff, sizeof(RxBuff), 0, 0, 0);

	/*将显示屏的回复的数据传输给协议栈*/
	if (RSize != SOCKET_ERROR) {
		MB_STK_In(RxBuff, RSize);
		return 0;
	}
	return 0xff;
}


// CDUCP_DEMODlg 消息处理程序

BOOL CDUCP_DEMODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#if !USE_STATIC_LIB
	// TODO:  在此添加额外的初始化代码
	hDUCP_Dll = LoadLibrary(_T("DUCP.dll"));//加载DLL,需要将DLL放到工程目录下. 

	if (hDUCP_Dll) {
		MB_STK_SetOutCallback = (MB_STK_SetOutCallback_t)GetProcAddress(hDUCP_Dll, "MB_STK_SetOutCallback");
		DUCP_HOST_TWIN_Del = (DUCP_HOST_TWIN_Del_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_TWIN_Del");
		DUCP_HOST_PIC_Del = (DUCP_HOST_PIC_Del_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_PIC_Del");
		DUCP_HOST_2D_SetColor = (DUCP_HOST_2D_SetColor_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_2D_SetColor");
		DUCP_HOST_2D_FillRect = (DUCP_HOST_2D_FillRect_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_2D_FillRect");
		DUCP_HOST_2D_DrawSysIcon = (DUCP_HOST_2D_DrawSysIcon_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_2D_DrawSysIcon");
		DUCP_HOST_PIC_Create = (DUCP_HOST_PIC_Create_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_PIC_Create");
		DUCP_HOST_PIC_Add = (DUCP_HOST_PIC_Add_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_PIC_Add");
		DUCP_HOST_TWIN_Create = (DUCP_HOST_TWIN_Create_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_TWIN_Create");
		DUCP_HOST_TWIN_DisText = (DUCP_HOST_TWIN_DisText_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_TWIN_DisText");
		DUCP_HOST_TTS_Play = (DUCP_HOST_TTS_Play_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_TTS_Play");
		MB_STK_In = (MB_STK_In_t)GetProcAddress(hDUCP_Dll, "MB_STK_In");
		DUCP_HOST_TWIN_DownTextFile = (DUCP_HOST_TWIN_DownTextFile_t)GetProcAddress(hDUCP_Dll, "DUCP_HOST_TWIN_DownTextFile");
	}
	else {
		while (1);
	}
#endif

	((CEdit *)GetDlgItem(IDC_EDIT_WID))->SetWindowText(_T("0"));
	((CEdit *)GetDlgItem(IDC_EDIT_TEXT))->SetWindowText(_T("欢迎光临"));

	/*1.初始化操作*/
	int Ret = WSAStartup(MAKEWORD(2, 2), &wd);
	if (Ret != 0) {
		return -1;
	}
	if (HIBYTE(wd.wVersion) != 2 || LOBYTE(wd.wVersion) != 2) {
		WSACleanup();
		return -1;
	}

	/*定义网络环境变量 默认IP为192.168.0.10，端口为7*/
	DUCP_NetPoint.sin_addr.S_un.S_addr = inet_addr("192.168.0.10");
	DUCP_NetPoint.sin_family = AF_INET;
	DUCP_NetPoint.sin_port = htons(7);

	/*创建客户端socket*/
	if (DUCP_NetSocket == 0) {
		DUCP_NetSocket = socket(AF_INET, SOCK_DGRAM, 0);
	}
	struct timeval tv_out;
	tv_out.tv_sec = 500;//等待
	tv_out.tv_usec = 1000;
	setsockopt(DUCP_NetSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv_out, sizeof(tv_out));

	/*#1.设置协议栈的回调函数*/
	MB_STK_SetOutCallback((cbSTKOut_t)cbDUCP_DataOut);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDUCP_DEMODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDUCP_DEMODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDUCP_DEMODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDUCP_DEMODlg::OnBnClickedButtonDistext()
{
	// TODO:  在此添加控件通知处理程序代码
	int WID;
	CString str;
	CString strWID;

	((CEdit *)GetDlgItem(IDC_EDIT_TEXT))->GetWindowText(str);
	((CEdit *)GetDlgItem(IDC_EDIT_WID))->GetWindowText(strWID);
	WID = atoi(strWID);
	DUCP_HOST_TWIN_DisText(WID, str.GetBuffer(), 0X15, 1, 0X00, 2, 0X15, 1, 3, 0XFF, 0X00, 0);
}


void CDUCP_DEMODlg::OnBnClickedButtonPlayvoice()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	((CEdit *)GetDlgItem(IDC_EDIT_TEXT))->GetWindowText(str);
	DUCP_HOST_TTS_Play(str.GetBuffer(), 0x01);
}


void CDUCP_DEMODlg::OnBnClickedButtonDemo1()
{
	// TODO:  在此添加控件通知处理程序代码
	DUCP_HOST_TWIN_Create(0, 0, 0, 0, 64, 16);
	DUCP_HOST_TWIN_Create(1, 0, 0, 16, 64, 16);
	DUCP_HOST_TWIN_Create(2, 0, 0, 32, 64, 16);
	DUCP_HOST_TWIN_Create(3, 0, 0, 48, 64, 16);
	DUCP_HOST_TWIN_Create(4, 0, 0, 64, 64, 16);
	DUCP_HOST_TWIN_Create(5, 0, 0, 80, 64, 16);
	DUCP_HOST_TWIN_Create(6, 0, 0, 96, 64, 16);
	DUCP_HOST_TWIN_Create(7, 0, 0, 112, 64, 16);

	DUCP_HOST_TWIN_DownTextFile(0,
								0,
								"现在时间`C`Y年`M月`D日 星期`V `H:`N:`S",
								0X15,
								1,
								0X00,
								2,
								0X15,
								1,
								3,
								0XFF,
								0);

		for (int i = 1; i < 8; i++) {
			DUCP_HOST_TWIN_DownTextFile(i,
										0,
										"欢迎使用",
										0X15,
										1,
										0X00,
										2,
										0X15,
										1,
										3,
										0XFF,
										0);
		}
}

void CDUCP_DEMODlg::OnBnClickedButtonDemo2()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码
	DUCP_HOST_TWIN_Del(0);
	DUCP_HOST_TWIN_Del(1);
	DUCP_HOST_PIC_Del(4);
	DUCP_HOST_PIC_Del(5);

	DUCP_HOST_2D_SetColor(0);
	DUCP_HOST_2D_FillRect(0, 0, 63, 31);
	DUCP_HOST_2D_DrawSysIcon(-7, 0, 1, 3, 43);

	DUCP_HOST_PIC_Create(4, 24, 16, 48, 16);
	DUCP_HOST_PIC_Add(4, 45, 1, 2, 0, 0, 6, 6);

	DUCP_HOST_TWIN_Create(0, 0, 19, 0, 48, 8);
	DUCP_HOST_TWIN_Create(1, 0, 17, 8, 48, 8);


	DUCP_HOST_TWIN_DisText(0,
						"`H:`N:`S",
						0X00,
						1,
						0X08,
						255,
						0x00,
						1,
						0,
						0XFF,
						0, 0);

	DUCP_HOST_TWIN_DisText(1,
							"`D-`M-`Y",
							0X00,
							1,
							0X08,
							255,
							0x00,
							1,
							0,
							0XFF,
							0, 0);
}

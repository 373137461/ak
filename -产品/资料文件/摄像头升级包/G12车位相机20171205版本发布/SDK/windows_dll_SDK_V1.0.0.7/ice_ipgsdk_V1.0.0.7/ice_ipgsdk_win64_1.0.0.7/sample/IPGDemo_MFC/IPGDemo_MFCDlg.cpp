// IPGDemo_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "IPGDemo_MFCDlg.h"
#include "LocalDlg.h"
#include "TransDlg.h"
#include "SystemDlg.h"
#include "PortDlg.h"
#include "AlgoDlg.h"
#include "DevSearchDlg.h"
#include "LightCtrl.h"

#include <Shlwapi.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#ifdef _WIN64
#pragma comment(lib,  "ice_ipgsdk-x64\\lib\\ice_ipgsdk.lib")
#else
#pragma comment(lib,  "ice_ipgsdk\\lib\\ice_ipgsdk.lib")
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCDlg dialog

CIPGDemo_MFCDlg::CIPGDemo_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPGDemo_MFCDlg::IDD, pParent), m_total_count(0), 
	m_bExit(FALSE), m_hMutex(NULL), m_pcPicData(NULL), m_nDeviceEventCount(0)
{
	//{{AFX_DATA_INIT(CIPGDemo_MFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_hSDK, 0, sizeof(m_hSDK));
	memset(m_nTotalSpaceNum, 0, sizeof(m_nTotalSpaceNum));
	memset(m_nRecvPortCount, 0, sizeof(m_nRecvPortCount));
	memset(m_nRecvPortCount_RS232, 0, sizeof(m_nRecvPortCount_RS232));
	m_szPath[0] = '\0';
}

void CIPGDemo_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPGDemo_MFCDlg)
	DDX_Control(pDX, IDC_LIST_INFO, m_ctrlInfoList);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_ctrlPosList);
	DDX_Control(pDX, IDC_LIST_CAMERA, m_ctrlCameraList);
	DDX_Control(pDX, IDC_IPADDRESS_CAMERA, m_ctrlCameraAddr);
	DDX_Control(pDX, IDC_LIST_ALRAM, m_ctrlAlarmList);
	DDX_Control(pDX, IDC_STATIC_VIDEO4, m_ctrlVideo4Static);
	DDX_Control(pDX, IDC_STATIC_VIDEO3, m_ctrlVideo3Static);
	DDX_Control(pDX, IDC_STATIC_VIDEO2, m_ctrlVideo2Static);
	DDX_Control(pDX, IDC_STATIC_VIDEO1, m_ctrlVideo1Static);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPGDemo_MFCDlg, CDialog)
	//{{AFX_MSG_MAP(CIPGDemo_MFCDlg)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_LBN_SELCHANGE(IDC_LIST_CAMERA, OnSelchangeListCamera)
	ON_BN_CLICKED(IDC_BUTTON_STATUS, OnButtonStatus)
	ON_BN_CLICKED(IDC_BUTTON_ALL, OnButtonAll)
	ON_COMMAND(IDC_BUTTON_CONFIG, OnButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_TRANS_RS485, OnButtonTransRs485)
	ON_BN_CLICKED(IDC_BUTTON_TRANS_RS232, OnButtonTransRs232)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM, OnButtonSystem)
	ON_BN_CLICKED(IDC_BUTTON_PORT, OnButtonPort)
	ON_BN_CLICKED(IDC_BUTTON_ALGO, OnButtonAlgo)
	ON_COMMAND(ID_DEVSEARCH, OnDevsearch)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LIGHTCTL, &CIPGDemo_MFCDlg::OnBnClickedButtonLightctl)
	ON_BN_CLICKED(IDC_BUTTON_DEVTIME, &CIPGDemo_MFCDlg::OnBnClickedButtonDevtime)
	ON_BN_CLICKED(IDC_BUTTON_SYNCTIME, &CIPGDemo_MFCDlg::OnBnClickedButtonSynctime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCDlg message handlers

#define BUF_SIZE (2 * 1024 * 1024)

extern CIPGDemo_MFCApp theApp;

void GetModulePath(char *path, int size)
{
	GetModuleFileName(theApp.m_hInstance, path, size);

	TCHAR szDir[_MAX_DIR];
	TCHAR szDrive[_MAX_DRIVE];
	_splitpath(path, szDrive, szDir, NULL, NULL);

	strcpy(path, szDrive);
	strcat(path, szDir);
}

void __stdcall SDK_OnDeviceEvent(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4)
{
	CIPGDemo_MFCDlg *dlg = (CIPGDemo_MFCDlg*)theApp.m_pMainWnd;

	CString strText;
	if (0 == u32EventType)
        strText.Format("%s : 当前状态离线", pcIP);
    else if (1 == u32EventType)
        strText.Format("%s : 当前状态在线", pcIP);
    else if (2 == u32EventType)
    {
        dlg->m_nDeviceEventCount++;
		strText.Format("%s IO状态改变 : %d%d%d%d", pcIP, 
			u32EventData1, u32EventData2, u32EventData3, u32EventData4);
    }

	WaitForSingleObject(dlg->m_hMutex, INFINITE);
	if (!dlg->m_bExit)
	{
		if (dlg->m_ctrlInfoList.GetCount() > 10000)
			dlg->m_ctrlInfoList.ResetContent();

		dlg->m_ctrlInfoList.InsertString(0, strText);
	}
	ReleaseMutex(dlg->m_hMutex);
}

BOOL CIPGDemo_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
	if (NULL == m_hMutex)
		return FALSE;

	m_pcPicData = (char*)malloc(BUF_SIZE);
	if (NULL == m_pcPicData)
		return FALSE;

	m_ctrlCameraAddr.SetAddress(ntohl(inet_addr("192.168.55.100")));
	
	RECT rect;
	m_ctrlAlarmList.GetWindowRect(&rect);
	int width = (rect.right - rect.left)/11;

	m_ctrlAlarmList.InsertColumn(0, "序号");
	m_ctrlAlarmList.InsertColumn(1, "相机IP");
	m_ctrlAlarmList.InsertColumn(2, "时间");
	m_ctrlAlarmList.InsertColumn(3, "车位ID");
	m_ctrlAlarmList.InsertColumn(4, "车位状态");
	m_ctrlAlarmList.InsertColumn(5, "车牌号码");
	m_ctrlAlarmList.InsertColumn(6, "车牌颜色");
	m_ctrlAlarmList.InsertColumn(7, "车位类型");
	m_ctrlAlarmList.InsertColumn(8, "事件类型");
	m_ctrlAlarmList.SetColumnWidth(0, width);
	m_ctrlAlarmList.SetColumnWidth(1, 2 * width);
	m_ctrlAlarmList.SetColumnWidth(2, 2 * width);
	m_ctrlAlarmList.SetColumnWidth(3, width);
	m_ctrlAlarmList.SetColumnWidth(4, width);
	m_ctrlAlarmList.SetColumnWidth(5, width);
	m_ctrlAlarmList.SetColumnWidth(6, width);
	m_ctrlAlarmList.SetColumnWidth(7, width);
	m_ctrlAlarmList.SetColumnWidth(8, width);
	m_ctrlAlarmList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	char szPath[1024];
	GetModulePath(szPath, 1024);
	strcat(szPath, "\\param.dat");

	FILE *fp = fopen(szPath, "rb");
	if (NULL != fp)
	{
		int len = fread(m_szPath, 1, 1024, fp);
		fclose(fp);

		m_szPath[len] = '\0';
	}
	else
	{
		sprintf(m_szPath, "%s\\snap", szPath);
	}

	ICE_IPCSDK_SetDeviceEventCallBack(NULL, SDK_OnDeviceEvent, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPGDemo_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPGDemo_MFCDlg::OnPaint() 
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
HCURSOR CIPGDemo_MFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void mkdir_p(const char *path)
{
	if (PathFileExists(path) || ('\0' == path[0]))
		return;

	CString strPath = path;
	mkdir_p(strPath.Left(strPath.ReverseFind('\\')));

	CreateDirectory(strPath, NULL);
}

void CIPGDemo_MFCDlg::SavePic(const ICE_CHAR *pcIP, ICE_CHAR *pcPicData, ICE_U32 u32PicLen)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	char szPath[1024];
	sprintf(szPath, "%s\\车位抓拍_MFC\\%s\\%04d%02d%02d", m_szPath, pcIP, st.wYear, st.wMonth, st.wDay);

	if (-1 == (_access(szPath, 0)))
		mkdir_p(szPath);

	char prefix[1024], name[1024];
	sprintf(prefix, "%s\\%04d%02d%02d%02d%02d%02d", 
		szPath, st.wYear, st.wMonth, st.wDay, 
		st.wHour, st.wMinute, st.wSecond);

	sprintf(name, "%s.jpg", prefix);
	if (-1 != (_access(name, 0)))
	{
		int count = 1;
		while (count <= 10)
		{
			sprintf(name, "%s_%d.jpg", prefix, count++);
			if (-1 == (_access(name, 0)))
				break;
		}
	}

	FILE *fp = fopen(name, "wb");
	if (NULL == fp)
		return;
	
	fwrite(pcPicData, 1, u32PicLen, fp);
	fclose(fp);
}

void CIPGDemo_MFCDlg::UpdateInfo(const ICE_CHAR *pcIP, const ICE_PARKING_SPACE_OUTPUT_S *output, int index)
{
	if (m_ctrlAlarmList.GetItemCount() > 10000)
		m_ctrlAlarmList.DeleteAllItems();

	CString strText;

	m_total_count++;
	strText.Format("%d", m_total_count);

	m_ctrlAlarmList.InsertItem(0, strText);
	m_ctrlAlarmList.SetItemText(0, 1, pcIP);

	SYSTEMTIME st;
	GetLocalTime(&st);

	strText.Format("%04d-%02d-%02d %02d:%02d:%02d", 
		st.wYear, st.wMonth, st.wDay, 
		st.wHour, st.wMinute, st.wSecond);
	m_ctrlAlarmList.SetItemText(0, 2, strText);

	strText.Format("%d", index + 1);
	m_ctrlAlarmList.SetItemText(0, 3, strText);

	static const char *status[] = {"无", "车位有车", "空车位", "单车占多车位", "车位禁用"};
	int enParkingPlaceStatus = 0;

	switch (output->enParkingPlaceStatus)
	{
	case ICE_IPG_EVENT_TYPE_NOON:
	default:
		enParkingPlaceStatus = 0;
		break;

	case ICE_IPG_EVENT_TYPE_HAVE_CAR:
		enParkingPlaceStatus = 1;
		break;

	case ICE_IPG_EVENT_TYPE_EMPTY_PLACE:
		enParkingPlaceStatus = 2;
		break;

	case ICE_IPG_EVENT_TYPE_OCCUPY_MULTIPLACE:
		enParkingPlaceStatus = 3;
		break;

	case ICE_IPG_EVENT_TYPE_DISABLED:
		enParkingPlaceStatus = 4;
		break;
	}

	m_ctrlAlarmList.SetItemText(0, 4, status[enParkingPlaceStatus]);
	m_ctrlAlarmList.SetItemText(0, 5, output->stPlateInfo.as8PlateNum);

	static const char *colors[] = {"未知", "蓝色", "黄色", "白色", "黑色", "绿色", "绿色", "黄绿色"};
	if ((output->stPlateInfo.ePlateColor >= 0) && (output->stPlateInfo.ePlateColor <= 7))
		m_ctrlAlarmList.SetItemText(0, 6, colors[output->stPlateInfo.ePlateColor]);

	static const char *cartypes[] = {"临时", "预定", "固定"};
	if ((output->s32CarType >= 0) && (output->s32CarType <= 2))
		m_ctrlAlarmList.SetItemText(0, 7, cartypes[output->s32CarType]);

	static const char *eventtypes[] = {"无变化", "入车", "出车"};
	if ((output->s32EventType >= 0) && (output->s32EventType <= 2))
		m_ctrlAlarmList.SetItemText(0, 8, eventtypes[output->s32EventType]);
}

void __stdcall SDK_OnParkingSpaceInfo(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_PARKING_SPACE_RESULT_S *pstParkingResult, ICE_CHAR *pcPicData, ICE_U32 u32PicLen, 
	void *pvReserve, ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4)
{
	CIPGDemo_MFCDlg *dlg = (CIPGDemo_MFCDlg*)theApp.m_pMainWnd;

	WaitForSingleObject(dlg->m_hMutex, INFINITE);
	if (!dlg->m_bExit)
	{
		int count = __min(ICE_MAX_PARKING_SPACE_NUM, pstParkingResult->u8ParkingPlaceNum);
		for (int i = 0; i < count; i++)
			dlg->UpdateInfo(pcIP, pstParkingResult->astOutput + i, i);

		dlg->SavePic(pcIP, pcPicData, u32PicLen);
	}
	ReleaseMutex(dlg->m_hMutex);
}

void __stdcall SDK_OnSerialPort(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len)
{
	int index = (int)pvParam;
	CIPGDemo_MFCDlg *dlg = (CIPGDemo_MFCDlg*)theApp.m_pMainWnd;

	dlg->m_nRecvPortCount[index]++;

	CString strText;
	strText.Format("%d : %s 接收到RS485数据 %d 字节", dlg->m_nRecvPortCount[index], pcIP, u32Len);

	char szText[4096];
	for (int i = 0; i < u32Len; i++)
		sprintf(szText + i * 3, "%02X ", (BYTE)pcData[i]);

	WaitForSingleObject(dlg->m_hMutex, INFINITE);
	if (!dlg->m_bExit)
	{
		if (dlg->m_ctrlInfoList.GetCount() > 10000)
			dlg->m_ctrlInfoList.ResetContent();

		dlg->m_ctrlInfoList.InsertString(0, szText);
		dlg->m_ctrlInfoList.InsertString(0, strText);
	}
	ReleaseMutex(dlg->m_hMutex);
}

void __stdcall SDK_OnSerialPort_RS232(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len)
{
	int index = (int)pvParam;
	CIPGDemo_MFCDlg *dlg = (CIPGDemo_MFCDlg*)theApp.m_pMainWnd;

	dlg->m_nRecvPortCount_RS232[index]++;

	CString strText;
	strText.Format("%d : %s 接收到RS232数据 %d 字节", dlg->m_nRecvPortCount_RS232[index], pcIP, u32Len);

	char szText[4096];
	for (int i = 0; i < u32Len; i++)
		sprintf(szText + i * 3, "%02X ", (BYTE)pcData[i]);

	WaitForSingleObject(dlg->m_hMutex, INFINITE);
	if (!dlg->m_bExit)
	{
		if (dlg->m_ctrlInfoList.GetCount() > 10000)
			dlg->m_ctrlInfoList.ResetContent();

		dlg->m_ctrlInfoList.InsertString(0, szText);
		dlg->m_ctrlInfoList.InsertString(0, strText);
	}
	ReleaseMutex(dlg->m_hMutex);
}

void CIPGDemo_MFCDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	for (; i < 4; i++)
	{
		if (NULL == m_hSDK[i])
			break;
	}

	if (4 == i)
		return;

	DWORD dwAddr = 0;
	m_ctrlCameraAddr.GetAddress(dwAddr);

	struct in_addr addr;
	addr.S_un.S_addr = htonl(dwAddr);

	char ip[32];
	strcpy(ip, inet_ntoa(addr));

	m_hSDK[i] = ICE_IPCSDK_Login(ip, 0, 0, 0, 0, 0);
	if (NULL == m_hSDK[i])
	{
		MessageBox("登录失败");
		return;
	}

	static HWND hWnd[] = {m_ctrlVideo1Static.m_hWnd, m_ctrlVideo2Static.m_hWnd, 
		m_ctrlVideo3Static.m_hWnd, m_ctrlVideo4Static.m_hWnd};

	ICE_U32 u32Result = ICE_IPCSDK_StartStream(m_hSDK[i], 1, (ICE_U32)hWnd[i]);
	if (0 == u32Result)
	{
		ICE_IPCSDK_Logout(m_hSDK[i]);
		MessageBox("启动实时视频预览失败");
		return;
	}

	ICE_IPCSDK_SetParkingSpaceInfoCallBack(m_hSDK[i], SDK_OnParkingSpaceInfo, NULL);
	ICE_IPCSDK_SetSerialPortCallBack(m_hSDK[i], SDK_OnSerialPort, (void*)i);
	ICE_IPCSDK_SetSerialPortCallBack_RS232(m_hSDK[i], SDK_OnSerialPort_RS232, (void*)i);

	int index = m_ctrlCameraList.AddString(ip);
	m_ctrlCameraList.SetItemData(index, i);

	m_nTotalSpaceNum[i] = 2;
	m_ctrlPosList.ResetContent();
	ICE_IPCSDK_GetParkingSpaceNum(m_hSDK[i], m_nTotalSpaceNum + i);

	char szText[16];
	for (ICE_U32 j = 0; j < m_nTotalSpaceNum[i]; j++)
	{
		sprintf(szText, "%d", j + 1);
		m_ctrlPosList.AddString(szText);
	}

	m_ctrlPosList.SetCurSel(0);
	m_ctrlCameraList.SetCurSel(index);
}

void CIPGDemo_MFCDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	for (int i = 0; i < 4; i++)
	{
		if (NULL == m_hSDK[i])
			continue;

		ICE_IPCSDK_Logout(m_hSDK[i]);
		m_hSDK[i] = NULL;
	}

	if (NULL != m_pcPicData)
	{
		free(m_pcPicData);
		m_pcPicData = NULL;
	}

	if (NULL != m_hMutex)
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}
}

void CIPGDemo_MFCDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);

	ICE_IPCSDK_Logout(m_hSDK[index]);
	m_hSDK[index] = NULL;

	m_ctrlCameraList.DeleteString(nCurSel);
}

void CIPGDemo_MFCDlg::OnSelchangeListCamera() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	CString strText;
	m_ctrlCameraList.GetText(nCurSel, strText);
	m_ctrlCameraAddr.SetAddress(ntohl(inet_addr(strText)));

	int index = m_ctrlCameraList.GetItemData(nCurSel);
	m_ctrlPosList.ResetContent();

	char szText[16];
	for (ICE_U32 i = 0; i < m_nTotalSpaceNum[index]; i++)
	{
		sprintf(szText, "%d", i + 1);
		m_ctrlPosList.AddString(szText);
	}

	m_ctrlPosList.SetCurSel(0);
}

#define MAX_WAIT 10

void CIPGDemo_MFCDlg::OnButtonStatus() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);

	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	ICE_PARKING_SPACE_OUTPUT_S stResult;
	memset(&stResult, 0, sizeof(stResult));

	ICE_U32 u32SpaceNum = 0, u32PicLen = 0;
	ICE_U32 result = ICE_IPCSDK_GetSingleParkingSpaceStatus(m_hSDK[index], nPos, &u32SpaceNum, 
		&stResult, m_pcPicData, BUF_SIZE, &u32PicLen, NULL, 0, NULL);
	if (ICE_STATUS_OK != result)
		return;

	CString strIP;
	m_ctrlCameraList.GetText(nCurSel, strIP);

	int i = 0;
	for (; i < MAX_WAIT; i++)
	{
		DWORD dwResult = WaitForSingleObject(m_hMutex, 100);
		if (WAIT_OBJECT_0 == dwResult)
			break;

		MSG msg;
		while (PeekMessage(&msg, m_hWnd,  0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (MAX_WAIT == i)
		return;

	UpdateInfo(strIP, &stResult, nPos);
	SavePic(strIP, m_pcPicData, u32PicLen);
	ReleaseMutex(m_hMutex);
}

void CIPGDemo_MFCDlg::OnButtonAll() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);

	ICE_PARKING_SPACE_RESULT_S stResult;
	memset(&stResult, 0, sizeof(stResult));

	ICE_U32 u32SpaceNum = 0, u32PicLen = 0;
	ICE_U32 result = ICE_IPCSDK_GetAllParkingSpaceStatus(m_hSDK[index], 
		&stResult, m_pcPicData, BUF_SIZE, &u32PicLen, NULL, NULL);
	if (ICE_STATUS_OK != result)
		return;

	CString strIP;
	m_ctrlCameraList.GetText(nCurSel, strIP);

	int i = 0;
	for (; i < MAX_WAIT; i++)
	{
		DWORD dwResult = WaitForSingleObject(m_hMutex, 100);
		if (WAIT_OBJECT_0 == dwResult)
			break;

		MSG msg;
		while (PeekMessage(&msg, m_hWnd,  0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (MAX_WAIT == i)
		return;

	for (int i = 0; i < stResult.u8ParkingPlaceNum; i++)
		UpdateInfo(strIP, stResult.astOutput + i, i);

	SavePic(strIP, m_pcPicData, u32PicLen);
	ReleaseMutex(m_hMutex);
}

void CIPGDemo_MFCDlg::OnButtonConfig() 
{
	// TODO: Add your command handler code here
	CLocalDlg dlg;
	if (IDCANCEL == dlg.DoModal())
		return;

	WaitForSingleObject(m_hMutex, INFINITE);
	strcpy(m_szPath, dlg.m_strPath);
	ReleaseMutex(m_hMutex);
}

void CIPGDemo_MFCDlg::OnButtonTransRs485() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);
	CTransDlg dlg(m_hSDK[index], 0);
	if (IDCANCEL == dlg.DoModal())
		return;

	//ICE_IPCSDK_TransSerialPort(m_hSDK[index], dlg.m_trans_buf, dlg.m_trans_len);
}

void CIPGDemo_MFCDlg::OnButtonTransRs232() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);
	CTransDlg dlg(m_hSDK[index], 1);
	if (IDCANCEL == dlg.DoModal())
		return;

	//ICE_IPCSDK_TransSerialPort_RS232(m_hSDK[index], dlg.m_trans_buf, dlg.m_trans_len);
}

void CIPGDemo_MFCDlg::OnButtonSystem() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);

	CSystemDlg dlg;
	dlg.m_nSpaceNum = m_nTotalSpaceNum[index];

	ICE_U32 value;
	for (ICE_U32 i = 0; i < m_nTotalSpaceNum[index]; i++)
	{
		ICE_U32 result = ICE_IPCSDK_GetEnableParkingSpace(m_hSDK[index], i, &value);
		if (ICE_STATUS_OK == result)
			dlg.m_enables[i] = value;

		result = ICE_IPCSDK_GetParkingSpaceType(m_hSDK[index], i, &value);
		if (ICE_STATUS_OK == result)
			dlg.m_types[i] = value;
	}

	char ip[32];
	ICE_U32 result = ICE_IPCSDK_GetRemoteDevState(m_hSDK[index], &value, ip, NULL, NULL);
	if (ICE_STATUS_OK == result)
	{
		dlg.m_bControl = value;
		strcpy(dlg.m_szControlIP, ip);
	}

	result = ICE_IPCSDK_GetControlDevState(m_hSDK[index], &value, ip, NULL, NULL);
	if (ICE_STATUS_OK == result)
	{
		dlg.m_bRemote = value;
		strcpy(dlg.m_szRemoteIP, ip);
	}

	http_conf_t param;
	memset(&param, 0, sizeof(param));
	
	result = ICE_IPCSDK_GetCGIParam(m_hSDK[index], &param);
	if (ICE_STATUS_OK == result)
		memcpy( &dlg.m_stHttpConf, &param, sizeof(param));
	
	if (IDCANCEL == dlg.DoModal())
		return;

	for (ICE_U32 i = 0; i < m_nTotalSpaceNum[index]; i++)
	{
		ICE_IPCSDK_SetEnableParkingSpace(m_hSDK[index], i, dlg.m_enables[i]);
		ICE_IPCSDK_SetParkingSpaceType(m_hSDK[index], i, dlg.m_types[i]);
	}

	ICE_IPCSDK_SetRemoteDevState(m_hSDK[index], dlg.m_bControl, dlg.m_szControlIP, 0, 0);
	ICE_IPCSDK_SetControlDevState(m_hSDK[index], dlg.m_bRemote, dlg.m_szRemoteIP, 0, 0);
	ICE_IPCSDK_SetCGIParam(m_hSDK[index], &dlg.m_stHttpConf);
}

void CIPGDemo_MFCDlg::OnButtonPort() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);
	CPortDlg dlg;

	ICE_U32 result = ICE_IPCSDK_GetUARTCfg(m_hSDK[index], &dlg.m_param);
	if (ICE_STATUS_OK != result)
	{
		MessageBox("获取参数失败");
		return;
	}

	if (IDCANCEL == dlg.DoModal())
		return;

	ICE_IPCSDK_SetUARTCfg(m_hSDK[index], &dlg.m_param);
}

void CIPGDemo_MFCDlg::OnButtonAlgo() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);

	CAlgoDlg dlg;
	dlg.m_width = 1920, dlg.m_height = 1080;
	if (2 == m_nTotalSpaceNum[index])
	{
		dlg.m_width = 1280;
		dlg.m_height = 720;
	}
	else if (3 == m_nTotalSpaceNum[index])
	{
		dlg.m_width = 1920;
		dlg.m_height = 1080;
	}

	ICE_IPG_PLACE_CONFIG_S param = {0};
	ICE_U32 result = ICE_IPCSDK_GetAllParkingSpaceLoops(m_hSDK[index], &param, dlg.m_width, dlg.m_height);
	if (ICE_STATUS_OK != result)
	{
		MessageBox("获取参数失败");
		return;
	}

	dlg.m_bCustom = param.bSpecialPlace;
	dlg.m_nSpaceNum = m_nTotalSpaceNum[index];

	for (ICE_U32 i = 0; i < m_nTotalSpaceNum[index]; i++)
	{
		dlg.m_rect[i].left = param.stPlaceParam[i].stRecRect.s16Left;
		dlg.m_rect[i].top = param.stPlaceParam[i].stRecRect.s16Top;
		dlg.m_rect[i].right = param.stPlaceParam[i].stRecRect.s16Right;
		dlg.m_rect[i].bottom = param.stPlaceParam[i].stRecRect.s16Bottom;
	}

	if (IDCANCEL == dlg.DoModal())
		return;

	param.bSpecialPlace = (ICE_BOOL)dlg.m_bCustom;
	for (ICE_U32 i = 0; i < m_nTotalSpaceNum[index]; i++)
	{
		param.stPlaceParam[i].stRecRect.s16Left = (short)dlg.m_rect[i].left;
		param.stPlaceParam[i].stRecRect.s16Top = (short)dlg.m_rect[i].top;
		param.stPlaceParam[i].stRecRect.s16Right = (short)dlg.m_rect[i].right;
		param.stPlaceParam[i].stRecRect.s16Bottom = (short)dlg.m_rect[i].bottom;
	}

	ICE_IPCSDK_SetAllParkingSpaceLoops(m_hSDK[index], &param, dlg.m_width, dlg.m_height);
}

void CIPGDemo_MFCDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	WaitForSingleObject(m_hMutex, INFINITE);
	m_bExit = TRUE;
	ReleaseMutex(m_hMutex);

	CDialog::OnClose();
}

void CIPGDemo_MFCDlg::OnDevsearch()
{
	// TODO: 在此添加命令处理程序代码
	CDevSearchDlg dlg;
	dlg.DoModal();
}

void CIPGDemo_MFCDlg::OnBnClickedButtonLightctl()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);

	CLightCtrl dlg;

	LightCtlParam param = {0};
	ICE_U32 result = ICE_IPCSDK_GetLightCtlParam(m_hSDK[index], &param);
	if (ICE_STATUS_OK != result)
	{
		MessageBox("获取参数失败");
		return;
	}


	dlg.m_nStyle = param.u8LightEn;
	dlg.m_nColor = param.u8Color;

	if (IDCANCEL == dlg.DoModal())
		return;

	param.u8LightEn = dlg.m_nStyle;
	param.u8Color = dlg.m_nColor;

	result = ICE_IPCSDK_SetLightCtlParam(m_hSDK[index], &param);
	if (ICE_STATUS_OK != result)
	{
		MessageBox("设置参数失败");
		return;
	}
}

void CIPGDemo_MFCDlg::OnBnClickedButtonDevtime()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);
	if (m_hSDK[index] == NULL)
		return;

	unsigned short year = 0;
	unsigned char month = 0, day = 0, hour = 0, minute = 0, second = 0;
	int success = ICE_IPCSDK_GetDevTime(m_hSDK[index],&year, &month, &day, &hour, &minute, &second);
	if (success)
	{
		CString strText;
		strText.Format("相机时间: %04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
		m_ctrlInfoList.InsertString(0, strText);
	}
	else
		m_ctrlInfoList.InsertString(0, "获取相机时间失败");
}

void CIPGDemo_MFCDlg::OnBnClickedButtonSynctime()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCurSel = m_ctrlCameraList.GetCurSel();
	if (-1 == nCurSel)
		return;

	int index = m_ctrlCameraList.GetItemData(nCurSel);
	if (m_hSDK[index] == NULL)
		return;

	time_t t = time(NULL);
	struct tm *ptm = localtime(&t);

	int success = ICE_IPCSDK_SyncTime(m_hSDK[index], (short)ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, 
		ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	if (success)
		m_ctrlInfoList.InsertString(0, "时间同步成功");
	else
		m_ctrlInfoList.InsertString(0, "时间同步失败");
}

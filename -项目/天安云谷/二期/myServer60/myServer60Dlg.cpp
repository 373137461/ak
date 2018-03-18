// myServer60Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "myServer60.h"
#include "myServer60Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "ag_Clocker.h"
#include "OPCServerObject.h"
#include <atlbase.h>
#include  <math.h>

int g_ItemCount	= 100;
int g_ChangeGap = 1;
int g_ChangeCount = 100;

#define TS_TEST

#ifdef TS_TEST
int g_YCValue = 1;
int g_YMValue = 2;
int g_YXValue = 3;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class dataReceiver :
	public COPCReceiveData
{
public:

	virtual void newData(LPCTSTR name, DWORD /*clientId*/, FILETIME &/*time*/, VARIANT &value, WORD Quality )
	{
		double v = 0.0;
		CComVariant  val = value;
		switch( val.vt ) {
			case VT_I2:
			case VT_I4:
			case VT_INT:		v = val.intVal; break;
			case VT_FILETIME:	break;
			case VT_R4:			v = val.fltVal; break;
			case VT_R8:			v = val.dblVal; break;
			case VT_EMPTY:
				v = -1.999999; break;
			default:
				v = 1.999999; break;
		};
		printf("Param changed [%s] value=%f Quality = %d\n", name, v, Quality );	
	}

	/// after calls newData, called newItemIsReceived
	virtual void newItemIsReceived( DWORD count ) { count; }
virtual void StatusChanged( int , const char * ) { };

};
//GUID CLSID_OPCServerEXE = { 0x4ea2713d, 0xca07, 0x11d4, {0xbe, 0xf5, 0x0, 0x0, 0x21, 0x20, 0xdb, 0x5F} };//5E
GUID CLSID_OPCServerEXE = { 0x4ea2713d, 0xca07, 0x11d4, {0xbe, 0xf5, 0x0, 0x0, 0x21, 0x20, 0xFA, 0x6B} };//5E
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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
// CMyServer60Dlg dialog

CMyServer60Dlg::CMyServer60Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyServer60Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyServer60Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyServer60Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyServer60Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyServer60Dlg, CDialog)
	//{{AFX_MSG_MAP(CMyServer60Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyServer60Dlg message handlers

BOOL CMyServer60Dlg::OnInitDialog()
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
#ifdef TS_TEST
	CString strFilePath;
	::GetModuleFileName(NULL,strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath = strFilePath.Left(strFilePath.ReverseFind(_T('\\')));
	strFilePath += _T("\\myServer60.ini");
	g_ItemCount = GetPrivateProfileInt(_T("global"), _T("ItemCount"), 0, strFilePath);
	g_ChangeGap = GetPrivateProfileInt(_T("global"), _T("ChangeGap"), 0, strFilePath);
	g_ChangeCount = GetPrivateProfileInt(_T("global"), _T("ChangeCount"), 0, strFilePath);
#endif
	//OnOK();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyServer60Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyServer60Dlg::OnPaint() 
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
HCURSOR CMyServer60Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
COPCServerObject *server = NULL; 
void CMyServer60Dlg::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(1);
	char str[1024] = {0};
	CoInitialize(NULL);

	server= CreateNewOPCServerObject();

	// define data event receiver 
	dataReceiver receiver;

	// set server name and clsid
	//这里是OPC服务的ID，客户端连接他就行啦 ！！！
	server->setServerProgID( _T("OPC.my6.0Server") );
	server->setServerCLSID( CLSID_OPCServerEXE );

	// set delimeter for params name 
	server->SetDelimeter( "." );

	// register server as COM/DCOM object 
	server->RegisterServer();

	// define server values tree
	//这里是创建OPC数据项的地方，加入你的数据项名称！
//	server->AddTag("Values.flt1", VT_R4 );
//	server->AddTag("Values.flt2", VT_R4 );
	{
		CAG_Clocker cl("Create COUNT_PARAM tags",false);

		for(int i=0;i<COUNT_PARAM;++i) {
//			sprintf(str,"RandomValues.int%d",i+1);
//			server->AddTag( str ,VT_I4 );
		}
		for (i=0; i<g_ItemCount; i++)
		{
			sprintf(str, "YCInfo.YC %d", i);
			server->AddTag(str, VT_I4);
			sprintf(str, "YMInfo.YM %d", i);
			server->AddTag(str, VT_I4);
			sprintf(str, "YXInfo.YX %d", i);
			server->AddTag(str, VT_I4);
		}
	}

	// setup object will be received add values change 
	server->setDataReceiver( &receiver );
	
	// create COM class factory and register it 
	server->StartServer( OPC_STATUS_RUNNING );

	AfxMessageBox(_T("启动成功！"));
	//refresh the data!
		
	SetTimer(1,g_ChangeGap*1000,NULL);
}

void CMyServer60Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
		if(server==NULL)
			return;
		char str2[1024] = {0};
		srand( (unsigned)time( NULL ) );
	
		//你自己想用自己的数据源
		static double x=0;
		x=x+0.1;
		int i = 0;
#ifdef TS_TEST
		for (i=0; i<g_ChangeCount; i++)
		{
			sprintf(str2, "YCInfo.YC %d", i);
			server->WriteValue(str2, server->FILETIME_NULL(), 192, g_YCValue+i);
			sprintf(str2, "YMInfo.YM %d", i);
			server->WriteValue(str2, server->FILETIME_NULL(), 192, g_YMValue+i);
			sprintf(str2, "YXInfo.YX %d", i);
			server->WriteValue(str2, server->FILETIME_NULL(), 192, g_YXValue+i);
		}
		g_YCValue++;
		g_YMValue++;
		g_YXValue++;
#else
		for (i=0; i<g_ItemCount; i++)
		{
			sprintf(str2, "YCInfo.YC %d", i);
			server->WriteValue(str2, server->FILETIME_NULL(), 192, CComVariant(rand()));
			sprintf(str2, "YMInfo.YM %d", i);
			server->WriteValue(str2, server->FILETIME_NULL(), 192, CComVariant(rand()));
			sprintf(str2, "YXInfo.YX %d", i);
			server->WriteValue(str2, server->FILETIME_NULL(), 192, CComVariant(rand()));
		}
#endif
//		server->WriteValue( "Values.flt1", server->FILETIME_NULL(), 192, CComVariant( sin(x) ) );
//		server->WriteValue( "Values.flt2", server->FILETIME_NULL(), 192, CComVariant( cos(x) ) );
		for(i=0;i<COUNT_PARAM;++i)
		{
//			sprintf(str2, "RandomValues.int%d",i+1);
//			server->WriteValue( str2 , server->FILETIME_NULL(), 192, CComVariant( rand() ) );
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CMyServer60Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(server!=NULL)
	{
		KillTimer(1);
	server->StopServer();
//	server->UnregisterServer();


	CoUninitialize();
	}
	AfxMessageBox(_T("服务已停止！"));
}

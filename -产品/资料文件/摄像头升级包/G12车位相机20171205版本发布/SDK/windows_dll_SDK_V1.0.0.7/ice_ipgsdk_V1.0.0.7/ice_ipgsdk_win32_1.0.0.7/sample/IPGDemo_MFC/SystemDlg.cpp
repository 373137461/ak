// SystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg dialog


CSystemDlg::CSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemDlg::IDD, pParent), m_nSpaceNum(0)
	, m_bHttpEnable(FALSE)
	, m_strHttpAddr(_T(""))
	, m_bSmallPic(FALSE)
	, m_bBigPic(FALSE)
	, m_bUploadEnbale(FALSE)
	, m_bHeartbeatEnable(FALSE)
	, m_nUploadInterval(1)
	, m_nHeartbeatInterval(1)
{
	//{{AFX_DATA_INIT(CSystemDlg)
	m_enable = -1;
	m_type = -1;
	m_bControl = FALSE;
	m_bRemote = FALSE;
	//}}AFX_DATA_INIT
	memset(m_enables, 0, sizeof(m_enables));
	memset(m_types, 0, sizeof(m_types));
	m_szControlIP[0] = '\0';
	m_szRemoteIP[0] = '\0';
	memset(&m_stHttpConf, 0, sizeof(m_stHttpConf));
}


void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemDlg)
	DDX_Control(pDX, IDC_IPADDRESS_REMOTE, m_ctrlRemoteAddr);
	DDX_Control(pDX, IDC_IPADDRESS_CONTROL, m_ctrlControlAddr);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_ctrlPosList);
	DDX_Radio(pDX, IDC_RADIO_ENABLE0, m_enable);
	DDX_Radio(pDX, IDC_RADIO_TYPE0, m_type);
	DDX_Check(pDX, IDC_CHECK_CONTROL, m_bControl);
	DDX_Check(pDX, IDC_CHECK_REMOTE, m_bRemote);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_HTTP_ENABLE, m_bHttpEnable);
	DDX_Text(pDX, IDC_EDIT_HTTP_ADDR, m_strHttpAddr);
	DDX_Check(pDX, IDC_CHECK_SMALLPIC, m_bSmallPic);
	DDX_Check(pDX, IDC_CHECK_BIGPIC, m_bBigPic);
	DDX_Check(pDX, IDC_CHECK_UPLOAD_ENABLE, m_bUploadEnbale);
	DDX_Check(pDX, IDC_CHECK_HEARTBEAT_ENABLE, m_bHeartbeatEnable);
	DDX_Text(pDX, IDC_EDIT_UPLOAD_INTERVAL, m_nUploadInterval);
	DDX_Text(pDX, IDC_EDIT_HEARTBEAT_INTERVAL, m_nHeartbeatInterval);
}


BEGIN_MESSAGE_MAP(CSystemDlg, CDialog)
	//{{AFX_MSG_MAP(CSystemDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION, OnSelchangeComboPosition)
	ON_BN_CLICKED(IDC_RADIO_ENABLE0, OnRadioEnable0)
	ON_BN_CLICKED(IDC_RADIO_ENABLE1, OnRadioEnable1)
	ON_BN_CLICKED(IDC_RADIO_TYPE0, OnRadioType0)
	ON_BN_CLICKED(IDC_RADIO_TYPE1, OnRadioType1)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, OnRadioType2)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_UPLOAD_INTERVAL, &CSystemDlg::OnEnChangeEditUploadInterval)
	ON_EN_CHANGE(IDC_EDIT_HEARTBEAT_INTERVAL, &CSystemDlg::OnEnChangeEditHeartbeatInterval)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg message handlers

void CSystemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	DWORD dwAddr = 0;
	struct in_addr addr;

	m_ctrlControlAddr.GetAddress(dwAddr);
	addr.S_un.S_addr = htonl(dwAddr);
	strcpy(m_szControlIP, inet_ntoa(addr));

	m_ctrlRemoteAddr.GetAddress(dwAddr);
	addr.S_un.S_addr = htonl(dwAddr);
	strcpy(m_szRemoteIP, inet_ntoa(addr));

	m_stHttpConf.http_enable = m_bHttpEnable;
	strcpy(m_stHttpConf.http_addr, m_strHttpAddr);
	m_stHttpConf.small_pic = m_bSmallPic;
	m_stHttpConf.big_pic = m_bBigPic;
	m_stHttpConf.upload_enable = m_bUploadEnbale;
	m_stHttpConf.upload_interval = m_nUploadInterval;
	m_stHttpConf.heartbeat_enable = m_bHeartbeatEnable;
	m_stHttpConf.heartbeat_interval = m_nHeartbeatInterval;

	CDialog::OnOK();
}

void CSystemDlg::OnSelchangeComboPosition() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	UpdateData();
	m_enable = m_enables[nPos];
	m_type = m_types[nPos];
	UpdateData(FALSE);
}

BOOL CSystemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szText[16];
	for (int j = 0; j < m_nSpaceNum; j++)
	{
		sprintf(szText, "%d", j + 1);
		m_ctrlPosList.AddString(szText);
	}

	m_ctrlPosList.SetCurSel(0);
	m_ctrlControlAddr.SetAddress(ntohl(inet_addr(m_szControlIP)));
	m_ctrlRemoteAddr.SetAddress(ntohl(inet_addr(m_szRemoteIP)));

	m_enable = m_enables[0];
	m_type = m_types[0];

	m_bHttpEnable = m_stHttpConf.http_enable;
	m_strHttpAddr.Format("%s", m_stHttpConf.http_addr);
	m_bSmallPic = m_stHttpConf.small_pic;
	m_bBigPic = m_stHttpConf.big_pic;
	m_bUploadEnbale = m_stHttpConf.upload_enable;
	m_nUploadInterval = m_stHttpConf.upload_interval;
	m_bHeartbeatEnable = m_stHttpConf.heartbeat_enable;
	m_nHeartbeatInterval = m_stHttpConf.heartbeat_interval;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemDlg::OnRadioEnable0() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	m_enables[nPos] = 0;
}

void CSystemDlg::OnRadioEnable1() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	m_enables[nPos] = 1;
}

void CSystemDlg::OnRadioType0() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	m_types[nPos] = 0;
}

void CSystemDlg::OnRadioType1() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	m_types[nPos] = 1;
}

void CSystemDlg::OnRadioType2() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	m_types[nPos] = 2;
}

void CSystemDlg::OnEnChangeEditUploadInterval()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_nUploadInterval < 1)
		GetDlgItem(IDC_EDIT_UPLOAD_INTERVAL)->SetWindowText("1");
	else if (m_nUploadInterval > 60)
		GetDlgItem(IDC_EDIT_UPLOAD_INTERVAL)->SetWindowText("60");
	//UpdateData(FALSE);
}

void CSystemDlg::OnEnChangeEditHeartbeatInterval()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData();
	if (m_nHeartbeatInterval < 1)
		GetDlgItem(IDC_EDIT_HEARTBEAT_INTERVAL)->SetWindowText("1");
	else if (m_nHeartbeatInterval > 60)
		GetDlgItem(IDC_EDIT_HEARTBEAT_INTERVAL)->SetWindowText("60");
	//UpdateData(FALSE);
}

// PortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "PortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPortDlg dialog


CPortDlg::CPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPortDlg)
	m_bEnable = FALSE;
	m_bEnable2 = FALSE;
	m_baudrate = -1;
	m_baudrate2 = -1;
	m_databits = -1;
	m_databits2 = -1;
	m_flowctrl = -1;
	m_flowctrl2 = -1;
	m_parity = -1;
	m_parity2 = -1;
	m_stopbits = -1;
	m_stopbits2 = -1;
	//}}AFX_DATA_INIT
	memset(&m_param, 0, sizeof(m_param));
}


void CPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPortDlg)
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_ENABLE2, m_bEnable2);
	DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE, m_baudrate);
	DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE2, m_baudrate2);
	DDX_CBIndex(pDX, IDC_COMBO_DATABITS, m_databits);
	DDX_CBIndex(pDX, IDC_COMBO_DATABITS2, m_databits2);
	DDX_CBIndex(pDX, IDC_COMBO_FLOWCTRL, m_flowctrl);
	DDX_CBIndex(pDX, IDC_COMBO_FLOWCTRL2, m_flowctrl2);
	DDX_CBIndex(pDX, IDC_COMBO_PARITY, m_parity);
	DDX_CBIndex(pDX, IDC_COMBO_PARITY2, m_parity2);
	DDX_CBIndex(pDX, IDC_COMBO_STOPBITS, m_stopbits);
	DDX_CBIndex(pDX, IDC_COMBO_STOPBITS2, m_stopbits2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPortDlg, CDialog)
	//{{AFX_MSG_MAP(CPortDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortDlg message handlers

void CPortDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	m_param.uart_param[0].uartEn = m_bEnable;
	m_param.uart_param[0].baudRate = m_baudrate;
	m_param.uart_param[0].dataBits = m_databits;
	m_param.uart_param[0].parity = m_parity;
	m_param.uart_param[0].stopBits = m_stopbits;
	m_param.uart_param[0].flowControl = m_flowctrl;

	m_param.uart_param[1].uartEn = m_bEnable2;
	m_param.uart_param[1].baudRate = m_baudrate2;
	m_param.uart_param[1].dataBits = m_databits2;
	m_param.uart_param[1].parity = m_parity2;
	m_param.uart_param[1].stopBits = m_stopbits2;
	m_param.uart_param[1].flowControl = m_flowctrl2;
	CDialog::OnOK();
}

BOOL CPortDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bEnable = m_param.uart_param[0].uartEn;
	m_baudrate = m_param.uart_param[0].baudRate;
	m_databits = m_param.uart_param[0].dataBits;
	m_parity = m_param.uart_param[0].parity;
	m_stopbits = m_param.uart_param[0].stopBits;
	m_flowctrl = m_param.uart_param[0].flowControl;

	m_bEnable2 = m_param.uart_param[1].uartEn;
	m_baudrate2 = m_param.uart_param[1].baudRate;
	m_databits2 = m_param.uart_param[1].dataBits;
	m_parity2 = m_param.uart_param[1].parity;
	m_stopbits2 = m_param.uart_param[1].stopBits;
	m_flowctrl2 = m_param.uart_param[1].flowControl;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

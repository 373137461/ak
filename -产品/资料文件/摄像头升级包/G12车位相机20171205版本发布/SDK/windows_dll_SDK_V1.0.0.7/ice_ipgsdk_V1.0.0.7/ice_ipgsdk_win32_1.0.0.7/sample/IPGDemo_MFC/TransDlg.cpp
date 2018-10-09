// TransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "TransDlg.h"

#ifdef _WIN64
#include "ice_ipgsdk-x64\\include\\ice_ipcsdk.h"
#else
#include "ice_ipgsdk\\include\\ice_ipcsdk.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog


CTransDlg::CTransDlg(void *hSDK, int type, CWnd* pParent /*=NULL*/)
	: CDialog(CTransDlg::IDD, pParent), m_trans_len(0), m_hSDK(hSDK), m_type(type)
{
	//{{AFX_DATA_INIT(CTransDlg)
	m_strData = _T("");
	//}}AFX_DATA_INIT
	memset(m_trans_buf, 0, sizeof(m_trans_buf));
}


void CTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransDlg)
	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrlDataEdit);
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransDlg, CDialog)
	//{{AFX_MSG_MAP(CTransDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransDlg message handlers

BOOL CTransDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYDOWN == pMsg->message)
	{
		if (pMsg->hwnd == m_ctrlDataEdit)
		{
			if (((pMsg->wParam >= '0') && (pMsg->wParam <=  '9')) || 
				((pMsg->wParam >= 'a') && (pMsg->wParam <= 'f')) || 
				((pMsg->wParam >= 'A') && (pMsg->wParam <= 'F')) || isspace(pMsg->wParam) || 
				(VK_BACK == pMsg->wParam) || (VK_DELETE == pMsg->wParam) || 
				(VK_CONTROL == pMsg->wParam) || (VK_ESCAPE == pMsg->wParam) || 
				(VK_LEFT == pMsg->wParam) || (VK_RIGHT == pMsg->wParam) || 
				(VK_UP == pMsg->wParam) || (VK_DOWN == pMsg->wParam) || 
				((GetKeyState(VK_CONTROL) < 0) && (('C' == pMsg->wParam) || ('V' == pMsg->wParam))))
			{
				return CDialog::PreTranslateMessage(pMsg);
			}
			else
			{
				MessageBeep(-1);
				return TRUE;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CTransDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	int len = m_strData.GetLength(), count = 0;
	for (int i = 0; i < len; i++)
	{
		char data = m_strData[i];
		if (isspace(data))
			continue;

		int value = 0;
		if (isdigit(data))
			value = data - '0';
		else
			value = 10 + data - 'A';

		if ((len - 1 == i) && (0 != ((count + 1) % 2)))
		{
			m_trans_buf[m_trans_len] = value;
			m_trans_len++;
		}
		else
		{
			if (0 == (count++ % 2))
			{
				m_trans_buf[m_trans_len] = value << 4;
			}
			else
			{
				m_trans_buf[m_trans_len] += value;
				m_trans_len++;
			}
		}
	}

	if (0 == m_type)
		ICE_IPCSDK_TransSerialPort(m_hSDK, m_trans_buf, m_trans_len);
	else
		ICE_IPCSDK_TransSerialPort_RS232(m_hSDK, m_trans_buf, m_trans_len);

	m_trans_len = 0;
	//CDialog::OnOK();
}

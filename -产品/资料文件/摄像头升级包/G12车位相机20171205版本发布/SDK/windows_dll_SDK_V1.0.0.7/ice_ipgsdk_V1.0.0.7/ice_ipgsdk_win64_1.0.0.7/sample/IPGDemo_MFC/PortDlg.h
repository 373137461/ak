#if !defined(AFX_PORTDLG_H__EAB3A885_0883_4862_8D0D_429D417A1657__INCLUDED_)
#define AFX_PORTDLG_H__EAB3A885_0883_4862_8D0D_429D417A1657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PortDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPortDlg dialog

#ifdef _WIN64
#include "ice_ipgsdk-x64\\include\\ice_ipcsdk.h"
#else
#include "ice_ipgsdk\\include\\ice_ipcsdk.h"
#endif

class CPortDlg : public CDialog
{
// Construction
public:
	CPortDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPortDlg)
	enum { IDD = IDD_DIALOG_PORT };
	BOOL	m_bEnable;
	BOOL	m_bEnable2;
	int		m_baudrate;
	int		m_baudrate2;
	int		m_databits;
	int		m_databits2;
	int		m_flowctrl;
	int		m_flowctrl2;
	int		m_parity;
	int		m_parity2;
	int		m_stopbits;
	int		m_stopbits2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPortDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	ICE_UART_PARAM m_param;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTDLG_H__EAB3A885_0883_4862_8D0D_429D417A1657__INCLUDED_)

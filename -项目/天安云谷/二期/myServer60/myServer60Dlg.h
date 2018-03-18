// myServer60Dlg.h : header file
//

#if !defined(AFX_MYSERVER60DLG_H__B7787EF8_38A8_490A_B4E6_FA6FB0096F69__INCLUDED_)
#define AFX_MYSERVER60DLG_H__B7787EF8_38A8_490A_B4E6_FA6FB0096F69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyServer60Dlg dialog

class CMyServer60Dlg : public CDialog
{
// Construction
public:
	CMyServer60Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyServer60Dlg)
	enum { IDD = IDD_MYSERVER60_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyServer60Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyServer60Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERVER60DLG_H__B7787EF8_38A8_490A_B4E6_FA6FB0096F69__INCLUDED_)

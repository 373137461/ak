#if !defined(AFX_TRANSDLG_H__F9B926F1_FD4F_4E78_B8D6_C546B3603847__INCLUDED_)
#define AFX_TRANSDLG_H__F9B926F1_FD4F_4E78_B8D6_C546B3603847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog

class CTransDlg : public CDialog
{
// Construction
public:
	CTransDlg(void *hSDK, int type, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransDlg)
	enum { IDD = IDD_DIALOG_TRANS };
	CEdit	m_ctrlDataEdit;
	CString	m_strData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	char m_trans_buf[4096];
	int m_trans_len;

	void *m_hSDK;
	int m_type;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSDLG_H__F9B926F1_FD4F_4E78_B8D6_C546B3603847__INCLUDED_)

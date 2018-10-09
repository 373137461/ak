#if !defined(AFX_LOCALDLG_H__40ECE3C2_3603_4285_A4D4_F034CE18AB87__INCLUDED_)
#define AFX_LOCALDLG_H__40ECE3C2_3603_4285_A4D4_F034CE18AB87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalDlg dialog

class CLocalDlg : public CDialog
{
// Construction
public:
	CLocalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLocalDlg)
	enum { IDD = IDD_DIALOG_LOCAL };
	CString	m_strPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocalDlg)
	afx_msg void OnButtonBrowse();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALDLG_H__40ECE3C2_3603_4285_A4D4_F034CE18AB87__INCLUDED_)

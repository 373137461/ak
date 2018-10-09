#if !defined(AFX_ALGODLG_H__56934AE6_F285_434D_8869_0165F2C6DE48__INCLUDED_)
#define AFX_ALGODLG_H__56934AE6_F285_434D_8869_0165F2C6DE48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlgoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlgoDlg dialog

class CAlgoDlg : public CDialog
{
// Construction
public:
	CAlgoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlgoDlg)
	enum { IDD = IDD_DIALOG_ALGO };
	CComboBox	m_ctrlPosList;
	BOOL	m_bCustom;
	int		m_res;
	int		m_left;
	int		m_top;
	int		m_right;
	int		m_bottom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlgoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlgoDlg)
	afx_msg void OnSelchangeComboPosition();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditLeft();
	afx_msg void OnChangeEditTop();
	afx_msg void OnChangeEditRight();
	afx_msg void OnChangeEditBottom();
	afx_msg void OnSelchangeComboRes();
	//}}AFX_MSG
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_nSpaceNum, m_width, m_height;
	RECT m_rect[3];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALGODLG_H__56934AE6_F285_434D_8869_0165F2C6DE48__INCLUDED_)

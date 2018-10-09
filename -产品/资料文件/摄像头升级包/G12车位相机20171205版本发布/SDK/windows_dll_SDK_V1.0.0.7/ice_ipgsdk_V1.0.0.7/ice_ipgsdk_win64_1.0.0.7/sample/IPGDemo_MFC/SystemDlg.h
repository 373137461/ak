#if !defined(AFX_SYSTEMDLG_H__786136B4_ECCC_4261_8AF6_DE58826314DD__INCLUDED_)
#define AFX_SYSTEMDLG_H__786136B4_ECCC_4261_8AF6_DE58826314DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg dialog

#ifdef _WIN64
#include "ice_ipgsdk-x64\\include\\ice_com_type.h"
#else
#include "ice_ipgsdk\\include\\ice_com_type.h"
#endif
class CSystemDlg : public CDialog
{
// Construction
public:
	CSystemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemDlg)
	enum { IDD = IDD_DIALOG_SYSTEM };
	CIPAddressCtrl	m_ctrlRemoteAddr;
	CIPAddressCtrl	m_ctrlControlAddr;
	CComboBox	m_ctrlPosList;
	int		m_enable;
	int		m_type;
	BOOL	m_bControl;
	BOOL	m_bRemote;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemDlg)
	virtual void OnOK();
	afx_msg void OnSelchangeComboPosition();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioEnable0();
	afx_msg void OnRadioEnable1();
	afx_msg void OnRadioType0();
	afx_msg void OnRadioType1();
	afx_msg void OnRadioType2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_nSpaceNum, m_enables[3], m_types[3];
	char m_szControlIP[32], m_szRemoteIP[32];
	http_conf_t m_stHttpConf;
	BOOL m_bHttpEnable;
	CString m_strHttpAddr;
	BOOL m_bSmallPic;
	BOOL m_bBigPic;
	BOOL m_bUploadEnbale;
	BOOL m_bHeartbeatEnable;
	int m_nUploadInterval;
	int m_nHeartbeatInterval;
	afx_msg void OnEnChangeEditUploadInterval();
	afx_msg void OnEnChangeEditHeartbeatInterval();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMDLG_H__786136B4_ECCC_4261_8AF6_DE58826314DD__INCLUDED_)

// IPGDemo_MFCDlg.h : header file
//

#if !defined(AFX_IPGDEMO_MFCDLG_H__7A9C0B62_1F3D_423D_A691_AFCB19F90B7C__INCLUDED_)
#define AFX_IPGDEMO_MFCDLG_H__7A9C0B62_1F3D_423D_A691_AFCB19F90B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCDlg dialog

#ifdef _WIN64
#include "ice_ipgsdk-x64\\include\\ice_ipcsdk.h"
#else
#include "ice_ipgsdk\\include\\ice_ipcsdk.h"
#endif

class CIPGDemo_MFCDlg : public CDialog
{
// Construction
public:
	CIPGDemo_MFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPGDemo_MFCDlg)
	enum { IDD = IDD_IPGDEMO_MFC_DIALOG };
	CListBox	m_ctrlInfoList;
	CComboBox	m_ctrlPosList;
	CListBox	m_ctrlCameraList;
	CIPAddressCtrl	m_ctrlCameraAddr;
	CListCtrl	m_ctrlAlarmList;
	CStatic	m_ctrlVideo4Static;
	CStatic	m_ctrlVideo3Static;
	CStatic	m_ctrlVideo2Static;
	CStatic	m_ctrlVideo1Static;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPGDemo_MFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPGDemo_MFCDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnDestroy();
	afx_msg void OnButtonClose();
	afx_msg void OnSelchangeListCamera();
	afx_msg void OnButtonStatus();
	afx_msg void OnButtonAll();
	afx_msg void OnButtonConfig();
	afx_msg void OnButtonTransRs485();
	afx_msg void OnButtonTransRs232();
	afx_msg void OnButtonSystem();
	afx_msg void OnButtonPort();
	afx_msg void OnButtonAlgo();
	afx_msg void OnDevsearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ICE_HANDLE m_hSDK[4];
	ICE_U32 m_nTotalSpaceNum[4];

	char *m_pcPicData;
	char m_szPath[1024];

public:
	int m_total_count;
	int m_nRecvPortCount[4];
	int m_nRecvPortCount_RS232[4];
	int m_nDeviceEventCount;
	BOOL m_bExit;
	HANDLE m_hMutex;

	void SavePic(const ICE_CHAR *pcIP, ICE_CHAR *pcPicData, ICE_U32 u32PicLen);
	void UpdateInfo(const ICE_CHAR *pcIP, const ICE_PARKING_SPACE_OUTPUT_S *output, int index);
	afx_msg void OnBnClickedButtonLightctl();
	afx_msg void OnBnClickedButtonDevtime();
	afx_msg void OnBnClickedButtonSynctime();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPGDEMO_MFCDLG_H__7A9C0B62_1F3D_423D_A691_AFCB19F90B7C__INCLUDED_)

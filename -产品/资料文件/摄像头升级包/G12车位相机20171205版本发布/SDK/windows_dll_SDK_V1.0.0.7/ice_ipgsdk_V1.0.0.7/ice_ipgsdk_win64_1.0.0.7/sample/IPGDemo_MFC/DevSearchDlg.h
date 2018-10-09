#pragma once
#include "afxcmn.h"


// CDevSearchDlg 对话框

class CDevSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CDevSearchDlg)

public:
	CDevSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevSearchDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DEV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlCameraList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonModip();
	void ShowDevData(CString strDev);
//	afx_msg void OnNMClickListDevlist(NMHDR *pNMHDR, LRESULT *pResult);
};

#pragma once
#include "afxwin.h"


// CLightCtrl 对话框

class CLightCtrl : public CDialog
{
	DECLARE_DYNAMIC(CLightCtrl)

public:
	CLightCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLightCtrl();

// 对话框数据
	enum { IDD = IDD_DIALOG_LIGHTCTL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CComboBox m_ctrlStyle;
	CComboBox m_ctrlColor;
	int m_nStyle;
	int m_nColor;
};

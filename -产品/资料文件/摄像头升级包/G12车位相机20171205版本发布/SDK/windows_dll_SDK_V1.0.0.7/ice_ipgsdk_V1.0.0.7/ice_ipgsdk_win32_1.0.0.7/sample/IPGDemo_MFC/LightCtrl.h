#pragma once
#include "afxwin.h"


// CLightCtrl �Ի���

class CLightCtrl : public CDialog
{
	DECLARE_DYNAMIC(CLightCtrl)

public:
	CLightCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLightCtrl();

// �Ի�������
	enum { IDD = IDD_DIALOG_LIGHTCTL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

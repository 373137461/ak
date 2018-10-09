#pragma once


// CIPDlg 对话框

class CIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CIPDlg)

public:
	CIPDlg(const char *ip, const char* gateway, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIPDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	CString m_strMask;
	CString m_strGateway;
};

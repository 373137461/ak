#pragma once


// CIPDlg �Ի���

class CIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CIPDlg)

public:
	CIPDlg(const char *ip, const char* gateway, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIPDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	CString m_strMask;
	CString m_strGateway;
};

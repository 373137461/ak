
// DUCP_DEMODlg.h : ͷ�ļ�
//

#pragma once


// CDUCP_DEMODlg �Ի���
class CDUCP_DEMODlg : public CDialogEx
{
// ����
public:
	CDUCP_DEMODlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DUCP_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDistext();
	afx_msg void OnBnClickedButtonPlayvoice();
	afx_msg void OnBnClickedButtonDemo1();
	afx_msg void OnBnClickedButtonDemo2();
};

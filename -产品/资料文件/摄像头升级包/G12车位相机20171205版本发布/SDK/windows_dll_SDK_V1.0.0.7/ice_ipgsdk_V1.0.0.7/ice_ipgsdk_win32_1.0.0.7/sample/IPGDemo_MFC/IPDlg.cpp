// IPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "IPDlg.h"


// CIPDlg �Ի���

IMPLEMENT_DYNAMIC(CIPDlg, CDialog)

CIPDlg::CIPDlg(const char *ip, const char* gateway, CWnd* pParent /*=NULL*/)
	: CDialog(CIPDlg::IDD, pParent)
	, m_strIP(ip)
	, m_strMask(_T("255.255.255.0"))
	, m_strGateway(gateway)
{
}

CIPDlg::~CIPDlg()
{
}

void CIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_MASK, m_strMask);
	DDX_Text(pDX, IDC_EDIT_GATEWAY, m_strGateway);
}


BEGIN_MESSAGE_MAP(CIPDlg, CDialog)
END_MESSAGE_MAP()


// CIPDlg ��Ϣ�������

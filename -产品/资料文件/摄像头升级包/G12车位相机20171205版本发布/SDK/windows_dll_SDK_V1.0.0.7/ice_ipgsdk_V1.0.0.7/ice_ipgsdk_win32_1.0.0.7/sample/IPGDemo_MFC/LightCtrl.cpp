// LightCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "LightCtrl.h"


// CLightCtrl �Ի���

IMPLEMENT_DYNAMIC(CLightCtrl, CDialog)

CLightCtrl::CLightCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CLightCtrl::IDD, pParent), m_nStyle(0), m_nColor(0)
{

}

CLightCtrl::~CLightCtrl()
{
}

void CLightCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_ctrlStyle);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_ctrlColor);
}


BEGIN_MESSAGE_MAP(CLightCtrl, CDialog)
END_MESSAGE_MAP()


// CLightCtrl ��Ϣ�������

BOOL CLightCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_nStyle >= 0)
		m_ctrlStyle.SetCurSel(m_nStyle);

	if (m_nColor > 0)
		m_ctrlColor.SetCurSel(m_nColor - 1);
	else
		m_ctrlColor.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLightCtrl::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_nStyle = m_ctrlStyle.GetCurSel();
	m_nColor = m_ctrlColor.GetCurSel() + 1;
	CDialog::OnOK();
}

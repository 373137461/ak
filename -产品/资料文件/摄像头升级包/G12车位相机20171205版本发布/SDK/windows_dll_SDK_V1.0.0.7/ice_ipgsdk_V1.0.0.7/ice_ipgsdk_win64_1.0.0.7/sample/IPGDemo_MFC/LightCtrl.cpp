// LightCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "LightCtrl.h"


// CLightCtrl 对话框

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


// CLightCtrl 消息处理程序

BOOL CLightCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_nStyle >= 0)
		m_ctrlStyle.SetCurSel(m_nStyle);

	if (m_nColor > 0)
		m_ctrlColor.SetCurSel(m_nColor - 1);
	else
		m_ctrlColor.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLightCtrl::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_nStyle = m_ctrlStyle.GetCurSel();
	m_nColor = m_ctrlColor.GetCurSel() + 1;
	CDialog::OnOK();
}

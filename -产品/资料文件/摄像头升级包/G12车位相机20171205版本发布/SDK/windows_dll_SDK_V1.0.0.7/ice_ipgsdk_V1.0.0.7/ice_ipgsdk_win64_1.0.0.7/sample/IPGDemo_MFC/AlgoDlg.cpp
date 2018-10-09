// AlgoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "AlgoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlgoDlg dialog


CAlgoDlg::CAlgoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlgoDlg::IDD, pParent), m_nSpaceNum(0), m_width(0), m_height(0)
{
	//{{AFX_DATA_INIT(CAlgoDlg)
	m_bCustom = FALSE;
	m_res = -1;
	m_left = 0;
	m_top = 0;
	m_right = 0;
	m_bottom = 0;
	//}}AFX_DATA_INIT
}


void CAlgoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlgoDlg)
	DDX_Control(pDX, IDC_COMBO_POSITION, m_ctrlPosList);
	DDX_Check(pDX, IDC_CHECK_CUSTOM, m_bCustom);
	DDX_CBIndex(pDX, IDC_COMBO_RES, m_res);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_left);
	DDX_Text(pDX, IDC_EDIT_TOP, m_top);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_right);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_bottom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlgoDlg, CDialog)
	//{{AFX_MSG_MAP(CAlgoDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION, OnSelchangeComboPosition)
	ON_EN_CHANGE(IDC_EDIT_LEFT, OnChangeEditLeft)
	ON_EN_CHANGE(IDC_EDIT_TOP, OnChangeEditTop)
	ON_EN_CHANGE(IDC_EDIT_RIGHT, OnChangeEditRight)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM, OnChangeEditBottom)
	ON_CBN_SELCHANGE(IDC_COMBO_RES, OnSelchangeComboRes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlgoDlg message handlers

void GetRes(int nIndex, int *width, int *height)
{
    switch (nIndex)
    {
        case 0:
		default:
            *width = 1920;
            *height = 1080;
            break;

        case 1:
            *width = 1600;
            *height = 900;
            break;

        case 2:
            *width = 1280;
            *height = 720;
            break;

        case 3:
            *width = 960;
            *height = 540;
            break;

        case 4:
            *width = 704;
            *height = 396;
            break;
    }
}

void CAlgoDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	GetRes(m_res, &m_width, &m_height);
	CDialog::OnOK();
}

int GetResIndex(int width, int height)
{
	int nIndex = 0;

    if ((width == 1920) && (height == 1080))
        nIndex = 0;
    else if ((width == 1600) && (height == 900))
        nIndex = 1;
    else if ((width == 1280) && (height == 720))
        nIndex = 2;
    else if ((width == 960) && (height == 540))
        nIndex = 3;
    else if ((width == 704) && (height == 396))
        nIndex = 4;

    return nIndex;
}

BOOL CAlgoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_res = GetResIndex(m_width, m_height);

	char szText[16];
	for (int j = 0; j < m_nSpaceNum; j++)
	{
		sprintf(szText, "%d", j + 1);
		m_ctrlPosList.AddString(szText);
	}

	m_ctrlPosList.SetCurSel(0);
	
	m_left = m_rect[0].left;
	m_top = m_rect[0].top;
	m_right = m_rect[0].right;
	m_bottom = m_rect[0].bottom;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlgoDlg::OnSelchangeComboPosition() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	UpdateData();
	m_left = m_rect[nPos].left;
	m_top = m_rect[nPos].top;
	m_right = m_rect[nPos].right;
	m_bottom = m_rect[nPos].bottom;
	UpdateData(FALSE);
}

void CAlgoDlg::OnChangeEditLeft() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	UpdateData();
	m_rect[nPos].left = m_left;
}

void CAlgoDlg::OnChangeEditTop() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	UpdateData();
	m_rect[nPos].top = m_top;
}

void CAlgoDlg::OnChangeEditRight() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	UpdateData();
	m_rect[nPos].right = m_right;
}

void CAlgoDlg::OnChangeEditBottom() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	UpdateData();
	m_rect[nPos].bottom = m_bottom;
}

void CAlgoDlg::OnSelchangeComboRes() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (-1 == m_res)
		return;

	int width, height;
	GetRes(m_res, &width, &height);

	float rx = (float)width/m_width;
	float ry = (float)height/m_height;

	for (int i = 0; i < 3; i++)
	{
		m_rect[i].left = (int)(m_rect[i].left * rx);
		m_rect[i].top = (int)(m_rect[i].top * ry);
		m_rect[i].right = (int)(m_rect[i].right * rx);
		m_rect[i].bottom = (int)(m_rect[i].bottom * ry);
	}

	m_width = width;
	m_height = height;

	int nPos = m_ctrlPosList.GetCurSel();
	if (-1 == nPos)
		return;

	m_left = m_rect[nPos].left;
	m_top = m_rect[nPos].top;
	m_right = m_rect[nPos].right;
	m_bottom = m_rect[nPos].bottom;
	UpdateData(FALSE);
}

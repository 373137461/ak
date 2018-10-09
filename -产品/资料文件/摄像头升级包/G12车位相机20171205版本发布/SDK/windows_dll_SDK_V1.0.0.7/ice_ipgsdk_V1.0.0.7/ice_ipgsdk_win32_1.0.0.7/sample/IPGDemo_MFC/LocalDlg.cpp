// LocalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "LocalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalDlg dialog


CLocalDlg::CLocalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLocalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalDlg)
	m_strPath = _T("");
	//}}AFX_DATA_INIT
}


void CLocalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalDlg)
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalDlg, CDialog)
	//{{AFX_MSG_MAP(CLocalDlg)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalDlg message handlers

void CLocalDlg::OnButtonBrowse() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	char path[MAX_PATH];
	strcpy(path, m_strPath);

	BROWSEINFO bi;
	memset(&bi, 0, sizeof(BROWSEINFO));

	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_USENEWUI | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
		return;

	SHGetPathFromIDList(idl, path);

	m_strPath = path;
	UpdateData(FALSE);
}

extern void GetModulePath(char *path, int size);

void CLocalDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	char szPath[1024];
	GetModulePath(szPath, 1024);
	strcat(szPath, "\\param.dat");

	FILE *fp = fopen(szPath, "wb");
	if (NULL != fp)
	{
		fwrite(m_strPath, 1, m_strPath.GetLength(), fp);
		fclose(fp);
	}

	CDialog::OnOK();
}

BOOL CLocalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szPath[1024];
	GetModulePath(szPath, 1024);
	strcat(szPath, "\\param.dat");

	FILE *fp = fopen(szPath, "rb");
	if (NULL != fp)
	{
		int len = fread(szPath, 1, 1024, fp);
		fclose(fp);

		szPath[len] = '\0';
	}
	else
	{
		sprintf(szPath, "%s\\snap", szPath);
	}

	UpdateData();
	m_strPath = szPath;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

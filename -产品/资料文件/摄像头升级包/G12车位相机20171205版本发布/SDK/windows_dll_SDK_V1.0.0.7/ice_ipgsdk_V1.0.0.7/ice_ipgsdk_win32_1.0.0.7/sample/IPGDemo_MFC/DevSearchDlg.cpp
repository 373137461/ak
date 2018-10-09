// DevSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "DevSearchDlg.h"
#include "IPDlg.h"
#ifdef _WIN64
#include "ice_ipgsdk-x64\\include\\ice_ipcsdk.h"
#else
#include "ice_ipgsdk\\include\\ice_ipcsdk.h"
#endif


// CDevSearchDlg 对话框

IMPLEMENT_DYNAMIC(CDevSearchDlg, CDialog)

CDevSearchDlg::CDevSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevSearchDlg::IDD, pParent)
{

}

CDevSearchDlg::~CDevSearchDlg()
{
}

void CDevSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVLIST, m_ctrlCameraList);
}


BEGIN_MESSAGE_MAP(CDevSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDevSearchDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_MODIP, &CDevSearchDlg::OnBnClickedButtonModip)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_DEVLIST, &CDevSearchDlg::OnNMClickListDevlist)
END_MESSAGE_MAP()


// CDevSearchDlg 消息处理程序

BOOL CDevSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrlCameraList.InsertColumn(0, "id");
	m_ctrlCameraList.InsertColumn(1, "mac");
	m_ctrlCameraList.InsertColumn(2, "ip");
	m_ctrlCameraList.InsertColumn(3, "ver");
	m_ctrlCameraList.InsertColumn(4, "hwInfo");
	m_ctrlCameraList.InsertColumn(5, "");
	m_ctrlCameraList.InsertColumn(6, "");
	m_ctrlCameraList.SetColumnWidth(0, 60);
	m_ctrlCameraList.SetColumnWidth(1, 130);
	m_ctrlCameraList.SetColumnWidth(2, 110);
	m_ctrlCameraList.SetColumnWidth(3, 520);
	m_ctrlCameraList.SetColumnWidth(4, 160);
	m_ctrlCameraList.SetColumnWidth(5, 0);
	m_ctrlCameraList.SetColumnWidth(6, 0);
	m_ctrlCameraList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDevSearchDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrlCameraList.DeleteAllItems();
	char result[4096];
	memset(result, 0, sizeof(result));

	char subText[512];
	memset(subText, 0, sizeof(subText));

	int  pos = 1, nItem = 0, count = 0;
	BOOL nFlag = FALSE;
	char text[16];
	memset(text, 0, sizeof(text));

	ICE_IPCSDK_SearchDev(result);
	
	char *subpch = strtok(result, "\r\n");

	while(subpch != NULL)
	{
		strcpy(subText, subpch);
		ShowDevData(subText);
		subpch = strtok(NULL, "\r\n");
	}

	MessageBox("搜索完成！");
}

void CDevSearchDlg::ShowDevData(CString strDev)
{
	int nPos = strDev.Find("\t");
	CString strInfo;
	int  pos = 1, nItem = 0, count = 0;
	BOOL nFlag = FALSE;
	char text[16];
	memset(text, 0, sizeof(text));

	while(nPos != -1)
	{
		strInfo = strDev.Left(nPos);

		if (!nFlag)
		{
			count = m_ctrlCameraList.GetItemCount();
			sprintf(text, "%d", count + 1);
			nItem = m_ctrlCameraList.InsertItem(count, text);
			nFlag = TRUE;
		}

		m_ctrlCameraList.SetItemText(nItem, pos, strInfo);
		pos++;

		strDev = strDev.Mid(nPos+1);
		nPos = strDev.Find("\t");
	}

	if (!strDev.IsEmpty())
	{
		if ((strDev.Compare("\r\n")))
			strDev = strDev.Left(strDev.GetLength() - 2);
		m_ctrlCameraList.SetItemText(nItem, pos, strDev);
	}
}

void CDevSearchDlg::OnBnClickedButtonModip()
{
	// TODO: 在此添加控件通知处理程序代码
	int item = m_ctrlCameraList.GetNextItem(-1, LVNI_SELECTED); 
	if (-1 == item)
		return;

	CString strMac = m_ctrlCameraList.GetItemText(item, 1);
	CString strIP = m_ctrlCameraList.GetItemText(item, 2);

	CString strGateway = strIP.Left(strIP.ReverseFind('.') + 1) + "1";

	CIPDlg dlg(strIP, strGateway);
	if (IDCANCEL == dlg.DoModal())
		return;

	ICE_IPCSDK_ModifyDevIP(strMac, dlg.m_strIP, dlg.m_strMask, dlg.m_strGateway);
}

//void CDevSearchDlg::OnNMClickListDevlist(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: 在此添加控件通知处理程序代码
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//
//	UINT flag = 0;
//	m_ctrlCameraList.HitTest(pNMListView->ptAction, &flag);
//	if (flag == LVHT_ONITEMSTATEICON)
//		return;
//
//	int count = m_ctrlCameraList.GetItemCount();
//	if (count <= 0)
//		return;
//
//	for (int i = 0; i < count; i++)
//		m_ctrlCameraList.SetCheck(i, FALSE);
//
//	int nItem = m_ctrlCameraList.GetNextItem(-1, LVNI_SELECTED);
//	if (-1 == nItem)
//		return;
//
//	m_ctrlCameraList.SetCheck(nItem, TRUE);
//	*pResult = 0;
//}

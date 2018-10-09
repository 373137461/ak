// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "LedDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog
CLedDll g_Dll;

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	g_Dll.InitDll();


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::OnButton1() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//����һͨѶ�����ṹ��������ڶ��趨��LEDͨѶ������Դ˽ṹ��Ԫ�ظ�ֵ˵����COMMUNICATIONINFO�ṹ�嶨�岿��עʾ
//TCPͨѶ********************************************************************************
	CommunicationInfo.SendType=0;//��Ϊ�̶�IPͨѶģʽ����TCPͨѶ
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//��IpStr��ֵLED���ƿ���IP
	CommunicationInfo.LedNumber=1;//LED����Ϊ1��ע��socketͨѶ��232ͨѶ��ʶ�����ţ�Ĭ�ϸ�1�����ˣ�485�����������ʵ�����Ž��и�ֵ
//�㲥ͨѶ********************************************************************************
	//CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
//����ͨѶ********************************************************************************
	//CommunicationInfo.SendType=2;//����ͨѶ
	//CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
	//CommunicationInfo.Baud=9600;//������
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//��Ŀ���
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//���ݴ��Ĳ���������Ŀ�����64�����������32�����ߵ�����2��������ɫ��ע��˴�����߼���ɫ�����������������ε�����߼���ɫһ�£�������ʱ����ʾ����
	//�˴��������ж���δ�����ɹ���hProgram����NULLʧ�ܣ���NULL�ɹ�,һ�㲻��ʧ��

	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//���һ����Ŀ������˵������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//�����������Խṹ�����
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=32;

	FONTPROP FontProp;//��������
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("����"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_GREEN;

	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_STRING,_T("�Ϻ������Ӿ������ɷ����޹�˾"),&FontProp,4);//����ͨ���ַ����һ�������ı����򣬺�������������עʾ
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.rtf"),NULL,4);//����ͨ��rtf�ļ����һ�������ı����򣬺�������������עʾ
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.txt"),&FontProp,4);//����ͨ��txt�ļ����һ�������ı����򣬺�������������עʾ

	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//���ͣ�����������עʾ
	g_Dll.LV_DeleteProgram(hProgram);//ɾ����Ŀ�ڴ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("���ͳɹ�"));
	}
	


}

void CDemoDlg::OnButton2() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//����һͨѶ�����ṹ��������ڶ��趨��LEDͨѶ������Դ˽ṹ��Ԫ�ظ�ֵ˵����COMMUNICATIONINFO�ṹ�嶨�岿��עʾ
	//TCPͨѶ********************************************************************************
	CommunicationInfo.SendType=0;//��Ϊ�̶�IPͨѶģʽ����TCPͨѶ
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//��IpStr��ֵLED���ƿ���IP
	CommunicationInfo.LedNumber=1;//LED����Ϊ1��ע��socketͨѶ��232ͨѶ��ʶ�����ţ�Ĭ�ϸ�1�����ˣ�485�����������ʵ�����Ž��и�ֵ
	//�㲥ͨѶ********************************************************************************
	//CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
	//����ͨѶ********************************************************************************
	//CommunicationInfo.SendType=2;//����ͨѶ
	//CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
	//CommunicationInfo.Baud=9600;//������
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//��Ŀ���
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//���ݴ��Ĳ���������Ŀ�����64�����������32�����ߵ�����2��������ɫ��ע��˴�����߼���ɫ�����������������ε�����߼���ɫһ�£�������ʱ����ʾ����
	//�˴��������ж���δ�����ɹ���hProgram����NULLʧ�ܣ���NULL�ɹ�,һ�㲻��ʧ��
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//���һ����Ŀ������˵������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//�����������Խṹ�����
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=32;
	
	nResult=g_Dll.LV_AddImageTextArea(hProgram,1,1,&AreaRect,FALSE);
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	PLAYPROP PlayProp;//��ʾ����
	PlayProp.DelayTime=3;
	PlayProp.InStyle=0;
	PlayProp.OutStyle=0;
	PlayProp.Speed=1;

	//������Ӷ�����ͼ������������ӿ���ѡһ���������
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.bmp"),&PlayProp);
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.jpg"),&PlayProp);
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.png"),&PlayProp);
	PlayProp.Speed=3;
	nResult=g_Dll.LV_AddFileToImageTextArea(hProgram,1,1,_T("test.gif"),&PlayProp);

	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//���ͣ�����������עʾ
	g_Dll.LV_DeleteProgram(hProgram);//ɾ����Ŀ�ڴ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("���ͳɹ�"));
	}
}

void CDemoDlg::OnButton3() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//����һͨѶ�����ṹ��������ڶ��趨��LEDͨѶ������Դ˽ṹ��Ԫ�ظ�ֵ˵����COMMUNICATIONINFO�ṹ�嶨�岿��עʾ
	//ZeroMemory(&CommunicationInfo,sizeof(COMMUNICATIONINFO));
//TCPͨѶ********************************************************************************
	CommunicationInfo.SendType=0;//��Ϊ�̶�IPͨѶģʽ����TCPͨѶ
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.88"));//��IpStr��ֵLED���ƿ���IP
	CommunicationInfo.LedNumber=1;//LED����Ϊ1��ע��socketͨѶ��232ͨѶ��ʶ�����ţ�Ĭ�ϸ�1�����ˣ�485�����������ʵ�����Ž��и�ֵ
//�㲥ͨѶ********************************************************************************
	//CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
//����ͨѶ********************************************************************************
	//CommunicationInfo.SendType=2;//����ͨѶ
	//CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
	//CommunicationInfo.Baud=9600;//������
	//CommunicationInfo.LedNumber=1;
	
	
	nResult=g_Dll.LV_SetBasicInfo(&CommunicationInfo,1,128,32);//�������Σ�������ɫΪ2��Ϊ˫��ɫ��64Ϊ���������32Ϊ���ߵ��������庯������˵������������עʾ
	if(nResult)//���ʧ������Ե���LV_GetError��ȡ���Ĵ�����Ϣ
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
	}
	else
	{
		MessageBox(_T("���óɹ�"));
	}
}

void CDemoDlg::OnButton4() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//����һͨѶ�����ṹ��������ڶ��趨��LEDͨѶ������Դ˽ṹ��Ԫ�ظ�ֵ˵����COMMUNICATIONINFO�ṹ�嶨�岿��עʾ
	//TCPͨѶ********************************************************************************
	CommunicationInfo.SendType=0;//��Ϊ�̶�IPͨѶģʽ����TCPͨѶ
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.98"));//��IpStr��ֵLED���ƿ���IP
	CommunicationInfo.LedNumber=1;//LED����Ϊ1��ע��socketͨѶ��232ͨѶ��ʶ�����ţ�Ĭ�ϸ�1�����ˣ�485�����������ʵ�����Ž��и�ֵ
	//�㲥ͨѶ********************************************************************************
	//CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
	//����ͨѶ********************************************************************************
	//CommunicationInfo.SendType=2;//����ͨѶ
	//CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
	//CommunicationInfo.Baud=9600;//������
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//��Ŀ���
	hProgram=g_Dll.LV_CreateProgram(64,32,3);//���ݴ��Ĳ���������Ŀ�����64�����������32�����ߵ�����2��������ɫ��ע��˴�����߼���ɫ�����������������ε�����߼���ɫһ�£�������ʱ����ʾ����
	//�˴��������ж���δ�����ɹ���hProgram����NULLʧ�ܣ���NULL�ɹ�,һ�㲻��ʧ��
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//���һ����Ŀ������˵������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//�����������Խṹ�����
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=32;

	nResult=g_Dll.LV_AddImageTextArea(hProgram,1,1,&AreaRect,FALSE);
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	FONTPROP FontProp;//��������
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("����"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;


	PLAYPROP PlayProp;//��ʾ����
	PlayProp.DelayTime=3;
	PlayProp.InStyle=0;
	PlayProp.OutStyle=0;
	PlayProp.Speed=1;

	//������Ӷ�����ͼ������������ӿ���ѡһ���������
	nResult=g_Dll.LV_AddStaticTextToImageTextArea(hProgram,1,1,ADDTYPE_STRING,_T("�Ϻ������Ӿ������ɷ����޹�˾"),&FontProp,3,0,FALSE);
 	//nResult=g_Dll.LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_STRING,_T("�Ϻ������Ӿ������ɷ����޹�˾"),&FontProp,&PlayProp,0,FALSE);//ͨ���ַ������һ�������ı���ͼ����������˵��������עʾ
	//nResult=g_Dll.LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_FILE,_T("test.rtf"),NULL,&PlayProp,0,FALSE);//ͨ��rtf�ļ����һ�������ı���ͼ����������˵��������עʾ
	//nResult=g_Dll.LV_AddMultiLineTextToImageTextArea(hProgram,1,1,ADDTYPE_FILE,_T("test.txt"),&FontProp,&PlayProp,0,FALSE);//ͨ��txt�ļ����һ�������ı���ͼ����������˵��������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//���ͣ�����������עʾ
	g_Dll.LV_DeleteProgram(hProgram);//ɾ����Ŀ�ڴ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("���ͳɹ�"));
	}
}

void CDemoDlg::OnButton5() 
{
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//����һͨѶ�����ṹ��������ڶ��趨��LEDͨѶ������Դ˽ṹ��Ԫ�ظ�ֵ˵����COMMUNICATIONINFO�ṹ�嶨�岿��עʾ
	//TCPͨѶ********************************************************************************
	CommunicationInfo.SendType=0;//��Ϊ�̶�IPͨѶģʽ����TCPͨѶ
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//��IpStr��ֵLED���ƿ���IP
	CommunicationInfo.LedNumber=1;//LED����Ϊ1��ע��socketͨѶ��232ͨѶ��ʶ�����ţ�Ĭ�ϸ�1�����ˣ�485�����������ʵ�����Ž��и�ֵ
	//�㲥ͨѶ********************************************************************************
	//CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
	//����ͨѶ********************************************************************************
	//CommunicationInfo.SendType=2;//����ͨѶ
	//CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
	//CommunicationInfo.Baud=9600;//������
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//��Ŀ���
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//���ݴ��Ĳ���������Ŀ�����64�����������32�����ߵ�����2��������ɫ��ע��˴�����߼���ɫ�����������������ε�����߼���ɫһ�£�������ʱ����ʾ����
	//�˴��������ж���δ�����ɹ���hProgram����NULLʧ�ܣ���NULL�ɹ�,һ�㲻��ʧ��
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//���һ����Ŀ������˵������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	AREARECT AreaRect;//�����������Խṹ�����
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=16;
	
	FONTPROP FontProp;//��������
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("����"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;
	
	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_STRING,_T("�Ϻ������Ӿ������ɷ����޹�˾"),&FontProp,4);//����ͨ���ַ����һ�������ı����򣬺�������������עʾ
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.rtf"),NULL,4);//����ͨ��rtf�ļ����һ�������ı����򣬺�������������עʾ
	//nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_FILE,_T("test.txt"),&FontProp,4);//����ͨ��txt�ļ����һ�������ı����򣬺�������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	AreaRect.left=0;
	AreaRect.top=16;
	AreaRect.width=64;
	AreaRect.height=16;

	DIGITALCLOCKAREAINFO DigitalClockAreaInfo;
	ZeroMemory(&DigitalClockAreaInfo,sizeof(DIGITALCLOCKAREAINFO));
	DigitalClockAreaInfo.TimeColor=COLOR_RED;
	_tcscpy(DigitalClockAreaInfo.ShowStrFont.FontName,_T("����"));
	DigitalClockAreaInfo.ShowStrFont.FontSize=12;
	DigitalClockAreaInfo.IsShowHour=TRUE;
	DigitalClockAreaInfo.IsShowMinute=TRUE;
	nResult=g_Dll.LV_AddDigitalClockArea(hProgram,1,2,&AreaRect,&DigitalClockAreaInfo);//ע������Ų���һ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}


	
	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//���ͣ�����������עʾ
	g_Dll.LV_DeleteProgram(hProgram);//ɾ����Ŀ�ڴ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("���ͳɹ�"));
	}
	
}

void CDemoDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	int nResult;
	COMMUNICATIONINFO CommunicationInfo;//����һͨѶ�����ṹ��������ڶ��趨��LEDͨѶ������Դ˽ṹ��Ԫ�ظ�ֵ˵����COMMUNICATIONINFO�ṹ�嶨�岿��עʾ
	//TCPͨѶ********************************************************************************
	CommunicationInfo.SendType=0;//��Ϊ�̶�IPͨѶģʽ����TCPͨѶ
	_tcscpy(CommunicationInfo.IpStr,_T("192.168.1.245"));//��IpStr��ֵLED���ƿ���IP
	CommunicationInfo.LedNumber=1;//LED����Ϊ1��ע��socketͨѶ��232ͨѶ��ʶ�����ţ�Ĭ�ϸ�1�����ˣ�485�����������ʵ�����Ž��и�ֵ
	//�㲥ͨѶ********************************************************************************
	//CommunicationInfo.SendType=1;//��Ϊ����ֱ�������㲥ͨѶ������LED��������IP��ַ
	//����ͨѶ********************************************************************************
	//CommunicationInfo.SendType=2;//����ͨѶ
	//CommunicationInfo.Commport=1;//���ڵı�ţ����豸����������ʾΪ COM3 ��˴���ֵ 3
	//CommunicationInfo.Baud=9600;//������
	//CommunicationInfo.LedNumber=1;
	
	HPROGRAM hProgram;//��Ŀ���
	hProgram=g_Dll.LV_CreateProgram(64,32,2);//���ݴ��Ĳ���������Ŀ�����64�����������32�����ߵ�����2��������ɫ��ע��˴�����߼���ɫ�����������������ε�����߼���ɫһ�£�������ʱ����ʾ����
	//�˴��������ж���δ�����ɹ���hProgram����NULLʧ�ܣ���NULL�ɹ�,һ�㲻��ʧ��
	
	nResult=g_Dll.LV_AddProgram(hProgram,1,0,1);//���һ����Ŀ������˵������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	AREARECT AreaRect;//�����������Խṹ�����
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=16;
	
	FONTPROP FontProp;//��������
	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("����"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;
	
	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,1,1,&AreaRect,ADDTYPE_STRING,_T("�Ϻ������Ӿ������ɷ����޹�˾"),&FontProp,4);//����ͨ���ַ����һ�������ı����򣬺�������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	
	AreaRect.left=0;
	AreaRect.top=16;
	AreaRect.width=64;
	AreaRect.height=16;
	
	DIGITALCLOCKAREAINFO DigitalClockAreaInfo;
	ZeroMemory(&DigitalClockAreaInfo,sizeof(DIGITALCLOCKAREAINFO));
	DigitalClockAreaInfo.TimeColor=COLOR_RED;
	_tcscpy(DigitalClockAreaInfo.ShowStrFont.FontName,_T("����"));
	DigitalClockAreaInfo.ShowStrFont.FontSize=12;
	DigitalClockAreaInfo.IsShowHour=TRUE;
	DigitalClockAreaInfo.IsShowMinute=TRUE;
	nResult=g_Dll.LV_AddDigitalClockArea(hProgram,1,2,&AreaRect,&DigitalClockAreaInfo);//ע������Ų���һ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	nResult=g_Dll.LV_AddProgram(hProgram,2,0,1);//��ӵڶ�����Ŀ��ע���Ŀ�Ų�ͬ��ͬ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	
	AreaRect.left=0;
	AreaRect.top=0;
	AreaRect.width=64;
	AreaRect.height=16;

	ZeroMemory(&FontProp,sizeof(FONTPROP));
	_tcscpy(FontProp.FontName,_T("����"));
	FontProp.FontSize=12;
	FontProp.FontColor=COLOR_RED;

	nResult=g_Dll.LV_QuickAddSingleLineTextArea(hProgram,2,1,&AreaRect,ADDTYPE_STRING,_T("�����ɵ���һ��~"),&FontProp,8);//����ͨ���ַ����һ�������ı����򣬺�������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}

	AreaRect.left=0;
	AreaRect.top=16;
	AreaRect.width=64;
	AreaRect.height=16;

	DigitalClockAreaInfo.TimeColor=COLOR_YELLOW;
	DigitalClockAreaInfo.TimeFormat=2;
	_tcscpy(DigitalClockAreaInfo.ShowStrFont.FontName,_T("����"));
	DigitalClockAreaInfo.ShowStrFont.FontSize=12;
	DigitalClockAreaInfo.IsShowHour=TRUE;
	DigitalClockAreaInfo.IsShowMinute=TRUE;
	nResult=g_Dll.LV_AddDigitalClockArea(hProgram,2,2,&AreaRect,&DigitalClockAreaInfo);//ע������Ų���һ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}


	nResult=g_Dll.LV_Send(&CommunicationInfo,hProgram);//���ͣ�����������עʾ
	g_Dll.LV_DeleteProgram(hProgram);//ɾ����Ŀ�ڴ���������������עʾ
	if(nResult)
	{
		CString ErrStr;
		g_Dll.LV_GetError(nResult,256,ErrStr.GetBufferSetLength(256));//����������עʾ
		ErrStr.ReleaseBuffer();
		MessageBox(ErrStr);
		return;
	}
	else
	{
		MessageBox(_T("���ͳɹ�"));
	}
}

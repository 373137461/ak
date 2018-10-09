// IPGDemo_MFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IPGDemo_MFC.h"
#include "IPGDemo_MFCDlg.h"

#ifdef _WIN64
#include "ice_ipgsdk-x64\\include\\ice_ipcsdk.h"
#else
#include "ice_ipgsdk\\include\\ice_ipcsdk.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCApp

BEGIN_MESSAGE_MAP(CIPGDemo_MFCApp, CWinApp)
	//{{AFX_MSG_MAP(CIPGDemo_MFCApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCApp construction

CIPGDemo_MFCApp::CIPGDemo_MFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIPGDemo_MFCApp object

CIPGDemo_MFCApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCApp initialization

BOOL CIPGDemo_MFCApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	ICE_IPCSDK_Init();

	CIPGDemo_MFCDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CIPGDemo_MFCApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	ICE_IPCSDK_Fini();
	return CWinApp::ExitInstance();
}

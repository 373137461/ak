// IPGDemo_MFC.h : main header file for the IPGDEMO_MFC application
//

#if !defined(AFX_IPGDEMO_MFC_H__27A10F44_B893_49BA_BC79_4695438A8DC7__INCLUDED_)
#define AFX_IPGDEMO_MFC_H__27A10F44_B893_49BA_BC79_4695438A8DC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPGDemo_MFCApp:
// See IPGDemo_MFC.cpp for the implementation of this class
//

class CIPGDemo_MFCApp : public CWinApp
{
public:
	CIPGDemo_MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPGDemo_MFCApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPGDemo_MFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPGDEMO_MFC_H__27A10F44_B893_49BA_BC79_4695438A8DC7__INCLUDED_)

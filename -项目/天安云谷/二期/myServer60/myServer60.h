// myServer60.h : main header file for the MYSERVER60 application
//

#if !defined(AFX_MYSERVER60_H__F218F0BB_D0E5_42D2_95C0_64B2BFE2E3C0__INCLUDED_)
#define AFX_MYSERVER60_H__F218F0BB_D0E5_42D2_95C0_64B2BFE2E3C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyServer60App:
// See myServer60.cpp for the implementation of this class
//

class CMyServer60App : public CWinApp
{
public:
	CMyServer60App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyServer60App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyServer60App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERVER60_H__F218F0BB_D0E5_42D2_95C0_64B2BFE2E3C0__INCLUDED_)

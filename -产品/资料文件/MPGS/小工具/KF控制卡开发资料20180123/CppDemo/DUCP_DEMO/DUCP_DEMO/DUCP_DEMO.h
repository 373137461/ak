
// DUCP_DEMO.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDUCP_DEMOApp: 
// �йش����ʵ�֣������ DUCP_DEMO.cpp
//

class CDUCP_DEMOApp : public CWinApp
{
public:
	CDUCP_DEMOApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDUCP_DEMOApp theApp;
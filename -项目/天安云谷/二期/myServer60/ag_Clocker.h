
#pragma once

#include <time.h>
#include "ag_File.h"

/// Class for gauging time intervals of operations
class CAG_Clocker
{
	CString name;
	clock_t start_clock;
	bool m_toFile;
	bool m_Stop;
public:
	void start()
	{
		start_clock = clock();
		m_Stop = false;
	}
	double stop()
	{
		m_Stop = true;
		clock_t finish_clock = clock();
		return  (finish_clock - start_clock) / 1000.;
	}

	CAG_Clocker(LPCTSTR filename = NULL, bool toFile = true)
	{
		m_toFile = toFile;
		name = filename;
		start();
	}
	~CAG_Clocker()
	{
		if( m_Stop ) 
			return ;
		CString tstr;

		double duration = stop();
//		CTime::GetCurrentTime().
		tstr.Format( _T("CLOCKER [%s] - Result %2.3f seconds"), (LPCTSTR)name, duration );
//		ATLTRACE(_T("%s\n"),tstr);
		printf(_T("%s\n"),tstr);
		
		if(m_toFile) {
			AGFile file(CString(_T("c:\\")) + name + _T(".log"),_T("a+t"));
			fseek(file,SEEK_END,0);
			if(file) 
				_ftprintf(file,_T("%s\n"),(LPCTSTR)tstr);
		}
	}
};


#define RELEASE_CLOCK(a)  CAG_Clocker clocker(_T(#a));
#define RELEASE_CLOCK_NOLOG(a)  CAG_Clocker clocker(_T(#a),false);

#ifdef _DEBUG
	#define DEBUG_CLOCK(a)  CAG_Clocker clocker(_T(#a));
#else
	#define DEBUG_CLOCK(a) ;
#endif

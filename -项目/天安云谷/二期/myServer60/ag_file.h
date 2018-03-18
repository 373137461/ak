
#pragma once


#include <stdio.h>

/// Simple wrapper around stdlib FILE*
class AGFile
{
	FILE *handle;
public:
	AGFile()
	{
		handle = NULL;
	}
	AGFile(LPCTSTR file, LPCTSTR mode)
	{
		handle = NULL;
		fopen(file, mode);
	}

	~AGFile()
	{
		fclose();
	}

	FILE* operator =(FILE* file)
	{
		fclose();
		return handle = file;
	}

	operator FILE*()
	{
		return handle;
	}
	//operator bool()
	//{
	//	return handle != NULL;
	//}


	FILE* fopen(LPCTSTR file, LPCTSTR mode)
	{
		AGFile::fclose();
		handle = ::_tfopen(file,mode);
		return handle;
	}

	int fclose()
	{
		int r = EOF;
		if(	handle ) {
			r = ::fclose( handle );
			handle = NULL;
		}
		return r;
	}
	//int printf(LPCTSTR format, ... )
	//{
	//	va_list marker;

	//	va_start( marker, format );     /* Initialize variable arguments. */
	//	int ret = _vftprintf( handle, format, marker );
	//	va_end( marker );
	//	return ret;
	//}
};
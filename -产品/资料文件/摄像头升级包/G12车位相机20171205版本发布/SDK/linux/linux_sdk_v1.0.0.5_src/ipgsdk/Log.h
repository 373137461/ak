#ifndef LOG_H__
#define LOG_H__


#include <time.h>
#include "thread.h"


#define CONTENT_TITLE 32

#define LEVEL_FATAL 50000
#define LEVEL_ERROR 40000
#define LEVEL_WARN 30000
#define LEVEL_INFO 20000
#define LEVEL_DEBUG 10000
 
#define LOG_INFO(format, ...) do \
{\
	CLog::GetInstance()->Logf(""format"  file:"__FILE__", function:"__FUNCTION__",line: %05d", ##__VA_ARGS__, __LINE__); \
} while (0)\



class CLog
{

public:
	CLog(void);
	//CLog (const CLog &);
	~CLog(void);
	//overloaded 
	//const CLog & operator = (const CLog &);

private:
	pthread_mutex_t  m_Lock;
	//FILE * m_File;
	struct tm m_Time;
	char szContentTitle[CONTENT_TITLE];
	char m_FilePath[256];
	char m_ip[16];
	int m_nEnableLog;
	char m_fileName[512];
	char m_flag_fname[512];
private:
	//FILE * GetFileFp();
	void GetFileName();


public:
	static void Init();
	static void Fini();

	// get instance
	static CLog * GetInstance();
	void Logf(const char * lpFormat, ...);
	void setFilePath(char *pFilePath);
	void setIp(const char *pIp);
	void mkdir_p(const char *path);
	void setEnableLog(int nEnableLog);

	void Logf(int level, const char * lpFormat, ...);
};



#endif // Log_h__

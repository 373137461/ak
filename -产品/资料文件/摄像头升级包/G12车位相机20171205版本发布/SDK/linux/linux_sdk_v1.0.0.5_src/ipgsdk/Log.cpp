#include "Log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#endif

#ifdef USE_LOG4CXX
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/dailyrollingfileappender.h>

#ifdef _WIN32
#ifdef _WIN64
#pragma comment(lib, "log4cxx-x64\\lib\\log4cxx.lib")
#else
#pragma comment(lib, "log4cxx\\lib\\log4cxx.lib")
#endif
#endif

using namespace log4cxx;
#endif

#ifdef _WIN32
#define access _access
#define mkdir(path, mode) _mkdir(path)
#endif

CLog::CLog(void)
{
	//m_File = NULL;
	m_nEnableLog = 0;
	memset(m_FilePath, 0, sizeof(m_FilePath));
	memset(m_ip, 0, sizeof(m_ip));
	strcpy(m_ip, "192.168.55.100");
	CREATE_MUTEX(m_Lock);
	memset(m_fileName, 0, sizeof(m_fileName));

#ifdef _WIN32
	extern HMODULE g_hModule;

	strcpy(m_FilePath, "D:\\");
	GetModuleFileName(g_hModule, m_flag_fname, MAX_PATH);

	TCHAR szDir[_MAX_DIR];
	TCHAR szDrive[_MAX_DRIVE];
	_splitpath_s(m_flag_fname, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, NULL, 0, NULL, 0);

	strcpy_s(m_flag_fname, MAX_PATH, szDrive);
	strcat_s(m_flag_fname, MAX_PATH, szDir);
	strcat_s(m_flag_fname, MAX_PATH, "\\ice_ipcsdk_log.txt");
#else
	strcpy(m_FilePath, "log");
	strcpy(m_flag_fname, "ice_ipcsdk_log.txt");
#endif
}

CLog::~CLog(void)
{
	DESTROY_MUTEX(m_Lock);
}

void CLog::Init()
{
#ifdef USE_LOG4CXX
	PropertyConfigurator::configure("log4cxx.properties");
#endif
}

void CLog::Fini()
{
#ifdef USE_LOG4CXX
	LogManager::shutdown();
#endif
}

/*static */CLog m_Log;
CLog * CLog::GetInstance()
{
	return &m_Log;
}

void CLog::Logf(const char * lpFormat, ... )
{
#ifdef USE_LOG4CXX
	char szText[8192];

	va_list args;
	va_start(args, lpFormat);
	vsprintf(szText, lpFormat, args);
	va_end(args);

	LoggerPtr rootLogger = Logger::getRootLogger();
	LOG4CXX_INFO(rootLogger, szText);
#else
	/*GetFileName();

	char szText[4096];
	strcpy(szText, szContentTitle);
	va_list args;
	va_start(args, lpFormat);
	vsprintf(szText + strlen(szText), lpFormat, args);
	va_end(args);
	strcat(szText, "\n");
	OutputDebugString(szText);*/

	if (!m_nEnableLog && (-1 != access(m_flag_fname, 0)))
		m_nEnableLog = 1;

	if (0 == m_nEnableLog)
		return;

	MUTEX_LOCK(m_Lock);

	GetFileName();
	FILE *fp = fopen(m_fileName, "a+");

	if(NULL != fp)
	{
		//DWORD dwWrite = 0;	

		// write the time
		fwrite(szContentTitle, sizeof(char), strlen(szContentTitle), fp);

		va_list args;
		va_start(args, lpFormat);
		vfprintf(fp, lpFormat, args);
		va_end(args);

		// write the enter under windows

		fwrite("\n", sizeof(char), 1, fp);
		//::WriteFile(m_File, "\r\n", 2, &dwWrite, NULL);
		fclose(fp);
	}

	MUTEX_UNLOCK(m_Lock);
#endif
}

void CLog::GetFileName()
{
	//memset(m_fileName, 0, sizeof(m_fileName));

	time_t t = time(NULL);
	struct tm *ptm = localtime(&t);
	memcpy(&m_Time, ptm, sizeof(m_Time));

	int ms = 0;
#ifdef _WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    ms = st.wMilliseconds;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ms = tv.tv_usec / 1000;
#endif

	sprintf(szContentTitle, "%04d-%02d-%02d %02d:%02d:%02d:%03d ", 
		1900 + ptm->tm_year, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, ms);

	//char szFileName [512] = {0};
	char szFilePath[512] = {0};
	sprintf(szFilePath, "%s/%s/%04d%02d%02d/%02d", 
		m_FilePath, m_ip, 1900 + ptm->tm_year, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour);
	mkdir_p(szFilePath);

	sprintf(m_fileName,"%s/ipcLog.txt", szFilePath);
	/*fopen_s(&m_File, szFileName, "a+");
	return m_File;*/
}

void CLog::setFilePath(char *pFilePath)
{
	if (NULL == pFilePath)
		return;

	strcpy(m_FilePath, pFilePath);
}

void CLog::setIp(const char *pIp)
{
	if (NULL == pIp)
		return;

	strcpy(m_ip, pIp);
}

void CLog::mkdir_p(const char *fileName)
{
	if (('\0' == fileName[0]) || access(fileName,0) != -1)
		return;

	char *tag = (char*)fileName;
	for(; *tag; tag++)
	{
		if ((*tag == '\\') || (*tag == '/'))
		{
			char buf[256],path[256];

			strcpy(buf,fileName);
			buf[strlen(fileName)-strlen(tag)+1] = '\0';

			strcpy(path,buf);
			if (access(path, 0)==-1)
				mkdir(path, 0777);
		}
	}

	mkdir(fileName, 0777);
}

void CLog::setEnableLog(int nEnableLog)
{
#ifdef USE_LOG4CXX
	if (nEnableLog && !m_nEnableLog)
	{
		AppenderList list = Logger::getRootLogger()->getAllAppenders();

		LayoutPtr layout(new PatternLayout(LOG4CXX_STR("[%-5p][%d] - %m%n")));

		wchar_t tmp[1024];
		MultiByteToWideChar(CP_ACP, 0, m_FilePath, -1, tmp, 1024);

		wchar_t szPath[1024];
		swprintf(szPath, L"%s\\log\\ice_ipcsdk.log", tmp);

		DailyRollingFileAppender *fa = new DailyRollingFileAppender(layout, szPath, LOG4CXX_STR("yyyy-MM-dd"));
		if (NULL == fa)
			return;

		helpers::Pool pool;
		fa->activateOptions(pool);

		LoggerPtr rootLogger = Logger::getRootLogger();
		rootLogger->setLevel(Level::getDebug());
		rootLogger->addAppender(fa);
	}
	else if (!nEnableLog && m_nEnableLog)
	{
		Logger::getRootLogger()->closeNestedAppenders();
	}
#endif

	m_nEnableLog = nEnableLog;

}

void CLog::Logf(int level, const char * lpFormat, ...)
{
#ifdef USE_LOG4CXX
	char szText[8192];

	va_list args;
	va_start(args, lpFormat);
	vsprintf(szText, lpFormat, args);
	va_end(args);

	LoggerPtr rootLogger = Logger::getRootLogger();

	switch (level)
	{
	case LEVEL_FATAL:
		LOG4CXX_FATAL(rootLogger, szText);
		break;

	case LEVEL_ERROR:
		LOG4CXX_ERROR(rootLogger, szText);
		break;

	case LEVEL_WARN:
		LOG4CXX_WARN(rootLogger, szText);
		break;

	case LEVEL_INFO:
	default:
		LOG4CXX_INFO(rootLogger, szText);
		break;

	case LEVEL_DEBUG:
		LOG4CXX_DEBUG(rootLogger, szText);
		break;
	}
#else
	/*GetFileName();

	char szText[4096];
	strcpy(szText, szContentTitle);
	va_list args;
	va_start(args, lpFormat);
	vsprintf(szText + strlen(szText), lpFormat, args);
	va_end(args);
	strcat(szText, "\n");
	OutputDebugString(szText);*/

	if (!m_nEnableLog && (-1 != access(m_flag_fname, 0)))
		m_nEnableLog = 1;

	if (0 == m_nEnableLog)
		return;

	MUTEX_LOCK(m_Lock);

	GetFileName();
	FILE *fp = fopen(m_fileName, "a+");

	if(NULL != fp)
	{
		//DWORD dwWrite = 0;	

		// write the time
		fwrite(szContentTitle, sizeof(char), strlen(szContentTitle), fp);

		va_list args;
		va_start(args, lpFormat);
		vfprintf(fp, lpFormat, args);
		va_end(args);

		// write the enter under windows

		fwrite("\n", sizeof(char), 1, fp);
		//::WriteFile(m_File, "\r\n", 2, &dwWrite, NULL);
		fclose(fp);
	}

	MUTEX_UNLOCK(m_Lock);
#endif
}

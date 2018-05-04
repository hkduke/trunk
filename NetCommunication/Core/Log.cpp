
#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include "Log.h"


namespace NetCom
{
	Log::Log(const std::string& strName, bool bDebugOut/* = false*/, bool bSupperFile /*= true*/)
		:m_bDebugOut(bDebugOut),m_bSupperFile(bSupperFile), m_bSupperTime(true), m_strName(strName),
		m_pFileLog(NULL)
	{
		// 是否支持文件操作
		if (m_bSupperFile)
		{
			//m_fstrLog.open(strName);
			m_pFileLog = fopen(strName.c_str(), "w");
		}
	}


	Log::~Log(void)
	{
		// 关闭日志文件
		if (m_bSupperFile && (NULL != m_pFileLog))
		{
			// 刷新 保存文件
			// m_fstrLog.flush();
			fflush(m_pFileLog);

			// 关闭文件
			// m_fstrLog.close();
			fclose(m_pFileLog);
		}
	}

	// 日志信息
	void Log::SetLogMessage(const std::string& strLog, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		// 设置最后时间
		m_strLastLog = strLog;
		m_uiCode = uiCode;

		// 盘点是否采用控制台输出
		if (m_bDebugOut && !maskDebug)
		{
			std::cerr<<strLog.c_str()<<std::endl;
		}

		// 判断是否需要数据支持
		if (!m_bSupperFile)
		{
			// 不支持文件
			return;
		}

		char szLine[20] = {0};
		//_StringStreamBase strOutLog;

		// 是否取用时间
		if (m_bSupperTime)
		{
			// 获取时间
			struct tm* pTime;
			time_t cTime;
			time(&cTime);

			// 获取系统时间
			pTime = localtime(&cTime);

			sprintf(szLine, "%d-%d-%d %d:%d:%d",pTime->tm_year + 1990, pTime->tm_mon+1, pTime->tm_mday, \
				pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
			// 写入缓存
			/*strOutLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ": ";*/
		}

		char szOutLog[256] = {0};
		//m_fstrLog << strLog.c_str() << std::endl;
		sprintf(szOutLog, "%s   %s\n\0",szLine, strLog.c_str());
		fwrite(szOutLog, sizeof(char) * strlen(szOutLog), sizeof(char), m_pFileLog);
		// 刷新缓存 写入文件
//		m_fstrLog.flush();			
		fflush(m_pFileLog);
	}

	// 获取错误信息
	const std::string& Log::GetErrorMessage(void) const
	{
		return m_strName;
	}

	// 获取是否支持属性
	bool Log::IsDebugOut(void) const
	{
		return (m_bDebugOut);
	}

	// 获取是否支持文件属性
	bool Log::IsSupperFile(void) const
	{
		return (m_bSupperFile);
	}

	// 获取是否支持时间
	bool Log::IsTimeStampEnabled(void) const
	{
		return (m_bSupperTime);
	}
}



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
		// �Ƿ�֧���ļ�����
		if (m_bSupperFile)
		{
			//m_fstrLog.open(strName);
			m_pFileLog = fopen(strName.c_str(), "w");
		}
	}


	Log::~Log(void)
	{
		// �ر���־�ļ�
		if (m_bSupperFile && (NULL != m_pFileLog))
		{
			// ˢ�� �����ļ�
			// m_fstrLog.flush();
			fflush(m_pFileLog);

			// �ر��ļ�
			// m_fstrLog.close();
			fclose(m_pFileLog);
		}
	}

	// ��־��Ϣ
	void Log::SetLogMessage(const std::string& strLog, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		// �������ʱ��
		m_strLastLog = strLog;
		m_uiCode = uiCode;

		// �̵��Ƿ���ÿ���̨���
		if (m_bDebugOut && !maskDebug)
		{
			std::cerr<<strLog.c_str()<<std::endl;
		}

		// �ж��Ƿ���Ҫ����֧��
		if (!m_bSupperFile)
		{
			// ��֧���ļ�
			return;
		}

		char szLine[20] = {0};
		//_StringStreamBase strOutLog;

		// �Ƿ�ȡ��ʱ��
		if (m_bSupperTime)
		{
			// ��ȡʱ��
			struct tm* pTime;
			time_t cTime;
			time(&cTime);

			// ��ȡϵͳʱ��
			pTime = localtime(&cTime);

			sprintf(szLine, "%d-%d-%d %d:%d:%d",pTime->tm_year + 1990, pTime->tm_mon+1, pTime->tm_mday, \
				pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
			// д�뻺��
			/*strOutLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ": ";*/
		}

		char szOutLog[256] = {0};
		//m_fstrLog << strLog.c_str() << std::endl;
		sprintf(szOutLog, "%s   %s\n\0",szLine, strLog.c_str());
		fwrite(szOutLog, sizeof(char) * strlen(szOutLog), sizeof(char), m_pFileLog);
		// ˢ�»��� д���ļ�
//		m_fstrLog.flush();			
		fflush(m_pFileLog);
	}

	// ��ȡ������Ϣ
	const std::string& Log::GetErrorMessage(void) const
	{
		return m_strName;
	}

	// ��ȡ�Ƿ�֧������
	bool Log::IsDebugOut(void) const
	{
		return (m_bDebugOut);
	}

	// ��ȡ�Ƿ�֧���ļ�����
	bool Log::IsSupperFile(void) const
	{
		return (m_bSupperFile);
	}

	// ��ȡ�Ƿ�֧��ʱ��
	bool Log::IsTimeStampEnabled(void) const
	{
		return (m_bSupperTime);
	}
}



#ifndef _LOG_H_
#define _LOG_H_

#pragma once
#include "../Public/ILog.h"
#include <fstream>
#include <string>
namespace NetCom
{

	typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > _StringStreamBase;
	class Log : public ILog
	{
	public:
		explicit Log(const std::string& strName, bool bDebugOut = false, bool bSupperFile = true);
		virtual ~Log(void);

		// �������
		const std::string& GetName(void) const { return (m_strName); }
		// ��־��Ϣ
		void SetLogMessage(const std::string& strLog, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false);
		// ��ȡ������Ϣ
		const std::string& GetErrorMessage(void) const;
		// ��ȡ�Ƿ��ļ�֧������
		bool IsDebugOut(void) const;
		// ��ȡ�Ƿ�֧���ļ�����
		bool IsSupperFile(void) const;
		// ��ȡ�Ƿ�֧��ʱ��
		bool IsTimeStampEnabled(void) const;
		// ���ô�����
		//SET_GET_PROPERTY(Code, UINT, ui);


	private:
		bool m_bDebugOut; // �������������̨����
		bool m_bSupperFile; //�Ƿ�֧��
		bool m_bSupperTime; // ʹ��ʱ��
		std::string m_strName; // ��־�ļ�
		//std::ofstream m_fstrLog; // ϵͳ�ļ�
		FILE* m_pFileLog;
		std::string m_strLastLog; // ��ȡ����
		UINT m_uiCode; // ������
	};
}

#endif
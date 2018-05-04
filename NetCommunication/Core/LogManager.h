#ifndef _LOGSYSTEM_H_
#define _LOGSYSTEM_H_
#pragma once
#include "SimpleFileChannel.h"
#include <map>
#include "Export.h"
#include "Logger.h"
#include "AutoPtr.h"
#include "WindowsConsoleChannel.h"
#include "FileChannel.h"
#include "../Core/SplitterChannel.h"
using namespace std;

//class Singleton;
namespace NetCom
{
	using NetCom::Logger;
	using NetCom::SimpleFileChannel;
	using NetCom::AutoPtr;

	class NETCOMMUNICATION_EXPORT LogManager 
	{
	public:
		// 构造函数
		explicit LogManager(void);
		// 析构函数
		virtual ~LogManager();

		void LogInit();

		// 创建默认日志
		virtual bool  CreateLog(const std::string& strLog, bool bDefaultLog = false,\
			bool debuggerOutput = true, bool suppressFileOutput = false);

		void WriteMessage(const std::string& message);

		void WriteMessage(const std::string& fmt, const Any& value1);
		void WriteMessage(const std::string& fmt, const Any& value1,  const Any& value2);
		void WriteMessage(const std::string& fmt, const Any& value1, const Any& value2 , const Any& value3);
		void WriteMessage(const std::string& fmt, const Any& value1, const Any& value2 , const Any& value3, const Any& value4);
		static LogManager& GetInstance();

	private:
		AutoPtr<WindowsConsoleChannel> m_pChannel;
		AutoPtr<FileChannel> m_pFileChannel;
		AutoPtr<SplitterChannel> m_pSplitter;
		Logger * m_log;
		Logger * logConsole;
	};
}


#endif // LOGSYSTEM_H

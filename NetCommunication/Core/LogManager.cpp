
#include "LogManager.h"
#include "../Core/SingletonHolder.h"
#include "../Core/PropertyFileConfiguration.h"
#include "../Core/LoggingConfigurator.h"
namespace NetCom
{
	LogManager::LogManager(void)
	{
	}

	LogManager::~LogManager()
	{

	}

	void LogManager::LogInit()
	{
		AutoPtr<PropertyFileConfiguration> pConf = new PropertyFileConfiguration("./Config/LogConf.properties");
		LoggingConfigurator log_configurator;
		log_configurator.configure(pConf);
		m_log = &Logger::root();
#ifdef _WIN32
		SetConsoleOutputCP(10000);
		CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。  
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = 16; // leave X as zero  
		info.FontWeight = FW_NORMAL;
		wcscpy(info.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
#endif
	}

	// 创建默认日志
	bool LogManager::CreateLog(const string& strLog, bool bDefaultLog, bool debuggerOutput , bool suppressFileOutput )
	{
		return false;
	}

	void LogManager::WriteMessage(const std::string &fmt)
	{
		m_log->information(fmt);
		//logFile->information(fmt);
	}

	void LogManager::WriteMessage(const std::string& fmt, const Any& value1)
	{
		m_log->information(fmt, value1);
		//logFile->information(fmt,value1);
	}

	void LogManager::WriteMessage(const std::string& fmt, const Any& value1, const Any& value2)
	{
		m_log->information(fmt, value1, value2);
		//logFile->information(fmt, value1, value2);
	}

	void LogManager::WriteMessage(const std::string& fmt, const Any& value1, const Any& value2, const Any& value3)
	{
		m_log->information(fmt, value1, value2, value3);
		//logFile->information(fmt, value1, value2, value3);
	}

	void LogManager::WriteMessage(const std::string& fmt, const Any& value1, const Any& value2, const Any& value3, const Any& value4)
	{
		m_log->information(fmt, value1, value2, value3, value4);
		//logFile->information(fmt, value1, value2, value3, value4);
	}

	namespace
	{
		SingletonHolder<LogManager> m_log_;
	}

	LogManager& LogManager::GetInstance()
	{
		return *m_log_.get();
	}

}

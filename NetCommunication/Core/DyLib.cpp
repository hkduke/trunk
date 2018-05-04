#include "DyLib.h"
#include "LogManager.h"
#if defined ( __WIN32__ ) || defined( _WIN32 )
#  define WIN32_LEAN_AND_MEAN
#  if !defined(NOMINMAX) && defined(_MSC_VER)
#   define NOMINMAX // required to stop windows.h messing up std::min
#  endif
#  include <Windows.h>
#else 
#include <dlfcn.h>
#endif

#include "CoreComponent.h"

namespace NetCom
{
	DyLib::DyLib(const std::string& fileName):m_strName(fileName)
	{

	}


	DyLib::~DyLib(void)
	{

	}

	// 获得错误信息
	std::string DyLib::GetDyLibLastError(void)
	{
#if defined( __WIN32__ ) || defined( _WIN32 )
		LPVOID lpMsgBuf=nullptr;
// 		FormatMessage(
// 			FORMAT_MESSAGE_ALLOCATE_BUFFER |
// 			FORMAT_MESSAGE_FROM_SYSTEM |
// 			FORMAT_MESSAGE_IGNORE_INSERTS,
// 			NULL,
// 			GetLastError(),
// 			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
// 			(LPTSTR) &lpMsgBuf,
// 			0,
// 			NULL
// 			);
		std::string ret = (char*)lpMsgBuf;
		// Free the buffer.
		LocalFree( lpMsgBuf );
		return ret;
#else
		return std::string(dlerror());
#endif
	}

	// 载入文件
	void DyLib::Load(void)
	{
		CoreComponent::GetInstance().WriteLogMsg("加载插件" + m_strName);
		std::string strName = m_strName;
		// 判断是否为windows操作系统
#if defined( __WIN32__ ) || defined( _WIN32 )
		if (strName.substr(strName.length() - 4, 4) != ".dll")
		{
			strName += ".dll";
		}
#elif defined linux
		if (strName.find(".so") == String::npos)
			strName += ".so";
#else
		if (strName.substr(name.length() - 6, 6) != ".dylib")
			strName += ".dylib";
#endif

		// 导入动态库
		m_hInstance = (DYNLIB_HANDLE)DYNLIB_LOAD(strName.c_str());
		if (NULL == m_hInstance)
		{
			std::string strError = GetDyLibLastError();
			CoreComponent::GetInstance().WriteLogMsg("加载插件" + m_strName + "失败" + strError, ERROR_NOT_FIND);
			throw ERROR_EXCEPT;
		}

		CoreComponent::GetInstance().WriteLogMsg("成功加载插件" + m_strName );
	}

	// 卸载文件
	void DyLib::Unload(void)
	{
		CoreComponent::GetInstance().WriteLogMsg("卸载插件" + m_strName);
		// 卸载
		if (DYNLIB_UNLOAD(m_hInstance))
		{
			CoreComponent::GetInstance().WriteLogMsg("卸载插件" + m_strName + "失败");
			throw ERROR_EXCEPT;
		}

		CoreComponent::GetInstance().WriteLogMsg("成功加载插件" + m_strName );
	}

	void* DyLib::GetSymbol( const std::string& strName ) const throw()
	{
		return (void*)DYNLIB_GETSYM( m_hInstance, strName.c_str() );
	}
}

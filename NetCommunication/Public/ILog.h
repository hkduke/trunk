#ifndef _ILOG_H_
#define _ILOG_H_

#pragma once
#include "CoreCommon.h"
#include "ErrorInfo.h"
#include <string>
namespace NetCom
{
	using namespace  std;
	enum LogMessageLevel
	{
		LML_TRIVIAL = 1,
		LML_NORMAL = 2,
		LML_CRITICAL = 3
	};

	class  ILog
	{
	public:
		//************************************
		// Method:    GetName 
		///获取日志名称
		// FullName:  VR_Soft::ILog::GetName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const std::string& GetName(void) const = 0;
		
		//************************************
		// Method:    SetLogMessage
		/// 日志信息
		// FullName:  VR_Soft::ILog::SetLogMessage
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const VRString & strLog 日志名称
		// Parameter: UINT uiCode	日志编码格式
		// Parameter: \ LogMessageLevel lml 日志信息级别
		// Parameter: bool maskDebug 是否进行调试
		//************************************
		virtual void SetLogMessage(const std::string& strLog, UINT uiCode = ERROR_OK,\
			LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
		
		//************************************
		// Method:    GetErrorMessage
		/// 获取错误信息
		// FullName:  VR_Soft::ILog::GetErrorMessage
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const std::string& GetErrorMessage(void) const = 0;
		
		//************************************
		// Method:    IsDebugOut
		/// 获取是否文件支持属性
		// FullName:  VR_Soft::ILog::IsDebugOut
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual bool IsDebugOut(void) const = 0;
		
		//************************************
		// Method:    IsSupperFile
		/// 获取是否支持文件属性
		// FullName:  VR_Soft::ILog::IsSupperFile
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual bool IsSupperFile(void) const = 0;
		
		//************************************
		// Method:    IsTimeStampEnabled
		/// 获取是否支持时间
		// FullName:  VR_Soft::ILog::IsTimeStampEnabled
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual bool IsTimeStampEnabled(void) const = 0;
	};
}
#endif // _ILOG_H_
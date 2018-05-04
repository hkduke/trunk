/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  日志系统接口			                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ILOGMANAGER_H_
#define _ILOGMANAGER_H_

#pragma once

#include "ILog.h"
//#include "SingleTmp.h"

class Singleton;
namespace NetCom
{
	class  ILogManager : public Singleton<ILogManager>
	{
	public:
		
		//************************************
		// Method:    ~ILogManager
		/// 析构函数
		// FullName:  VR_Soft::ILogManager::~ILogManager
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~ILogManager() { }
		
		//************************************
		// Method:    CreateLog
		/// 创建默认日志
		// FullName:  VR_Soft::ILogManager::CreateLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: const VRString & strLog	创建的入职名称
		// Parameter: bool bDefaultLog 是否是默认的日志
		// Parameter: \ bool debuggerOutput 是否调试信息输出
		// Parameter: bool suppressFileOutput	是否支持文件操作，比如直接打开日志文件
		//************************************
		virtual ILog* CreateLog(const std::string& strLog, bool bDefaultLog = false,\
			bool debuggerOutput = true, bool suppressFileOutput = false) = 0;
		
		//************************************
		// Method:    GetDefaultLog
		/// 获得默认的系统日志
		// FullName:  VR_Soft::ILogManager::GetDefaultLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: void
		//************************************
		virtual ILog* GetDefaultLog(void) = 0;
		
		//************************************
		// Method:    SetDefaultLog
		/// 设置当前系统日志 返回原来的系统日志
		// FullName:  VR_Soft::ILogManager::SetDefaultLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: ILog * pLog 缺省日志接口
		//************************************
		virtual ILog* SetDefaultLog(ILog* pLog) = 0;

		
		//************************************
		// Method:    GetLog
		/// 获得系统日志对象
		// FullName:  VR_Soft::ILogManager::GetLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: const VRString & strLog 获取日志对象的名称
		//************************************
		virtual ILog* GetLog(const std::string& strLog) = 0;
		
		//************************************
		// Method:    DestoryLog
		/// 销毁日志对象
		// FullName:  VR_Soft::ILogManager::DestoryLog
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const VRString & strLog 销毁日志的名称
		//************************************
		virtual void DestoryLog(const std::string& strLog) = 0;

		//************************************
		// Method:    DestoryLog
		/// 销毁日志
		// FullName:  VR_Soft::ILogManager::DestoryLog
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ILog * pLog 需要销毁的日志对象
		//************************************
		virtual void DestoryLog(ILog* pLog) = 0;
		
		//************************************
		// Method:    SetLogMessage
		/// 写入系统日志
		// FullName:  VR_Soft::ILogManager::SetLogMessage
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const VRString & strMsg 消息内容
		// Parameter: UINT uiCode	消息编码
		// Parameter: LogMessageLevel lml	消息级别
		// Parameter: bool maskDebug   是否调试
		//************************************
		virtual void SetLogMessage(const std::string& strMsg, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
	};
}

#endif
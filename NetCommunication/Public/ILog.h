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
		///��ȡ��־����
		// FullName:  VR_Soft::ILog::GetName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const std::string& GetName(void) const = 0;
		
		//************************************
		// Method:    SetLogMessage
		/// ��־��Ϣ
		// FullName:  VR_Soft::ILog::SetLogMessage
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const VRString & strLog ��־����
		// Parameter: UINT uiCode	��־�����ʽ
		// Parameter: \ LogMessageLevel lml ��־��Ϣ����
		// Parameter: bool maskDebug �Ƿ���е���
		//************************************
		virtual void SetLogMessage(const std::string& strLog, UINT uiCode = ERROR_OK,\
			LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
		
		//************************************
		// Method:    GetErrorMessage
		/// ��ȡ������Ϣ
		// FullName:  VR_Soft::ILog::GetErrorMessage
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const std::string& GetErrorMessage(void) const = 0;
		
		//************************************
		// Method:    IsDebugOut
		/// ��ȡ�Ƿ��ļ�֧������
		// FullName:  VR_Soft::ILog::IsDebugOut
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual bool IsDebugOut(void) const = 0;
		
		//************************************
		// Method:    IsSupperFile
		/// ��ȡ�Ƿ�֧���ļ�����
		// FullName:  VR_Soft::ILog::IsSupperFile
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual bool IsSupperFile(void) const = 0;
		
		//************************************
		// Method:    IsTimeStampEnabled
		/// ��ȡ�Ƿ�֧��ʱ��
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
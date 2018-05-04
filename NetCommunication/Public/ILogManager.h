/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־ϵͳ�ӿ�			                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
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
		/// ��������
		// FullName:  VR_Soft::ILogManager::~ILogManager
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~ILogManager() { }
		
		//************************************
		// Method:    CreateLog
		/// ����Ĭ����־
		// FullName:  VR_Soft::ILogManager::CreateLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: const VRString & strLog	��������ְ����
		// Parameter: bool bDefaultLog �Ƿ���Ĭ�ϵ���־
		// Parameter: \ bool debuggerOutput �Ƿ������Ϣ���
		// Parameter: bool suppressFileOutput	�Ƿ�֧���ļ�����������ֱ�Ӵ���־�ļ�
		//************************************
		virtual ILog* CreateLog(const std::string& strLog, bool bDefaultLog = false,\
			bool debuggerOutput = true, bool suppressFileOutput = false) = 0;
		
		//************************************
		// Method:    GetDefaultLog
		/// ���Ĭ�ϵ�ϵͳ��־
		// FullName:  VR_Soft::ILogManager::GetDefaultLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: void
		//************************************
		virtual ILog* GetDefaultLog(void) = 0;
		
		//************************************
		// Method:    SetDefaultLog
		/// ���õ�ǰϵͳ��־ ����ԭ����ϵͳ��־
		// FullName:  VR_Soft::ILogManager::SetDefaultLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: ILog * pLog ȱʡ��־�ӿ�
		//************************************
		virtual ILog* SetDefaultLog(ILog* pLog) = 0;

		
		//************************************
		// Method:    GetLog
		/// ���ϵͳ��־����
		// FullName:  VR_Soft::ILogManager::GetLog
		// Access:    virtual public 
		// Returns:   VR_Soft::ILog*
		// Qualifier:
		// Parameter: const VRString & strLog ��ȡ��־���������
		//************************************
		virtual ILog* GetLog(const std::string& strLog) = 0;
		
		//************************************
		// Method:    DestoryLog
		/// ������־����
		// FullName:  VR_Soft::ILogManager::DestoryLog
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const VRString & strLog ������־������
		//************************************
		virtual void DestoryLog(const std::string& strLog) = 0;

		//************************************
		// Method:    DestoryLog
		/// ������־
		// FullName:  VR_Soft::ILogManager::DestoryLog
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: ILog * pLog ��Ҫ���ٵ���־����
		//************************************
		virtual void DestoryLog(ILog* pLog) = 0;
		
		//************************************
		// Method:    SetLogMessage
		/// д��ϵͳ��־
		// FullName:  VR_Soft::ILogManager::SetLogMessage
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const VRString & strMsg ��Ϣ����
		// Parameter: UINT uiCode	��Ϣ����
		// Parameter: LogMessageLevel lml	��Ϣ����
		// Parameter: bool maskDebug   �Ƿ����
		//************************************
		virtual void SetLogMessage(const std::string& strMsg, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
	};
}

#endif
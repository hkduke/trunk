
#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#pragma once
#include <string>
#include "../Core/CoreCommon.h"
using namespace std;
namespace NetCom
{
	class  IPlugin
	{
	public:
		
		//************************************
		// Method:    ~IPlugin
		/// ��������
		// FullName:  VR_Soft::IPlugin::~IPlugin
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~IPlugin() { }
		
		//************************************
		// Method:    GetPluginName
		/// ��ȡ�������
		// FullName:  VR_Soft::IPlugin::GetPluginName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginName(void) const = 0;
		
		//************************************
		// Method:    GetPluginVersion
		/// ��ò���汾
		// FullName:  VR_Soft::IPlugin::GetPluginVersion
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginVersion(void) const = 0;
		
		//************************************
		// Method:    GetPluginDiscribe
		/// ��ò������
		// FullName:  VR_Soft::IPlugin::GetPluginDiscribe
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string& GetPluginDiscribe(void) const = 0;
		
		//************************************
		// Method:    Install
		/// ��װ���
		// FullName:  VR_Soft::IPlugin::Install
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Install(void) = 0;
		
		//************************************
		// Method:    Initialise
		/// ��ʼ�����
		// FullName:  VR_Soft::IPlugin::Initialise
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Initialise(void) = 0;
		
		//************************************
		// Method:    Shutdown
		/// ������
		// FullName:  VR_Soft::IPlugin::Shutdown
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Shutdown(void) = 0;
		
		//************************************
		// Method:    UnInstall
		/// ж�ز��
		// FullName:  VR_Soft::IPlugin::UnInstall
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void UnInstall(void) = 0;
	};

	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllInstallPlugin(IComManager* pComManager);	

	//// ж�ز���ӿں���
	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllUnInstallPlugin(IComManager* pComManager);
	// ע������
#define REGISTER_NETCOM_PLUGIN(classname, export_style) \
	IPlugin* pPlugin = NULL;\
	EXTERN_CPP export_style void DllInstallPlugin(void) {\
	pPlugin = new classname; \
	IComManager::GetInstance().InstallPlugin(pPlugin);\
	}\
	EXTERN_CPP export_style void DllUnInstallPlugin(void){ \
	IComManager::GetInstance().UnInstallPlugin(pPlugin); VRSOFT_DELETE(pPlugin);\
	}
}

#endif // _PLUGIN_H_
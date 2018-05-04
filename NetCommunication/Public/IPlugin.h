
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
		/// 析构函数
		// FullName:  VR_Soft::IPlugin::~IPlugin
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~IPlugin() { }
		
		//************************************
		// Method:    GetPluginName
		/// 获取插件名称
		// FullName:  VR_Soft::IPlugin::GetPluginName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginName(void) const = 0;
		
		//************************************
		// Method:    GetPluginVersion
		/// 获得插件版本
		// FullName:  VR_Soft::IPlugin::GetPluginVersion
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginVersion(void) const = 0;
		
		//************************************
		// Method:    GetPluginDiscribe
		/// 获得插件描述
		// FullName:  VR_Soft::IPlugin::GetPluginDiscribe
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string& GetPluginDiscribe(void) const = 0;
		
		//************************************
		// Method:    Install
		/// 安装插件
		// FullName:  VR_Soft::IPlugin::Install
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Install(void) = 0;
		
		//************************************
		// Method:    Initialise
		/// 初始化插件
		// FullName:  VR_Soft::IPlugin::Initialise
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Initialise(void) = 0;
		
		//************************************
		// Method:    Shutdown
		/// 清除插件
		// FullName:  VR_Soft::IPlugin::Shutdown
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Shutdown(void) = 0;
		
		//************************************
		// Method:    UnInstall
		/// 卸载插件
		// FullName:  VR_Soft::IPlugin::UnInstall
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void UnInstall(void) = 0;
	};

	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllInstallPlugin(IComManager* pComManager);	

	//// 卸载插件接口函数
	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllUnInstallPlugin(IComManager* pComManager);
	// 注册插件宏
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
#pragma once

#include "../Public/IPlugin.h"
#include "CAN.h"
namespace NetCom
{
	class CANPlugin :
		public IPlugin
	{
	public:
		CANPlugin(void);
		~CANPlugin(void);


		//************************************
		// Method:    ~IPlugin
		/// 析构函数
		// FullName:  VR_Soft::IPlugin::~IPlugin
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		
		//************************************
		// Method:    GetPluginName
		/// 获取插件名称
		// FullName:  VR_Soft::IPlugin::GetPluginName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginName(void) const;
		
		//************************************
		// Method:    GetPluginVersion
		/// 获得插件版本
		// FullName:  VR_Soft::IPlugin::GetPluginVersion
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginVersion(void) const;
		
		//************************************
		// Method:    GetPluginDiscribe
		/// 获得插件描述
		// FullName:  VR_Soft::IPlugin::GetPluginDiscribe
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string& GetPluginDiscribe(void) const;
		
		//************************************
		// Method:    Install
		/// 安装插件
		// FullName:  VR_Soft::IPlugin::Install
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Install(void) ;
		
		//************************************
		// Method:    Initialise
		/// 初始化插件
		// FullName:  VR_Soft::IPlugin::Initialise
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Initialise(void) ;
		
		//************************************
		// Method:    Shutdown
		/// 清除插件
		// FullName:  VR_Soft::IPlugin::Shutdown
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Shutdown(void) ;
		
		//************************************
		// Method:    UnInstall
		/// 卸载插件
		// FullName:  VR_Soft::IPlugin::UnInstall
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void UnInstall(void) ;



		CAN m_can;

	};




}


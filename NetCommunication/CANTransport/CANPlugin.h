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
		/// ��������
		// FullName:  VR_Soft::IPlugin::~IPlugin
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		
		//************************************
		// Method:    GetPluginName
		/// ��ȡ�������
		// FullName:  VR_Soft::IPlugin::GetPluginName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginName(void) const;
		
		//************************************
		// Method:    GetPluginVersion
		/// ��ò���汾
		// FullName:  VR_Soft::IPlugin::GetPluginVersion
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string GetPluginVersion(void) const;
		
		//************************************
		// Method:    GetPluginDiscribe
		/// ��ò������
		// FullName:  VR_Soft::IPlugin::GetPluginDiscribe
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string& GetPluginDiscribe(void) const;
		
		//************************************
		// Method:    Install
		/// ��װ���
		// FullName:  VR_Soft::IPlugin::Install
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Install(void) ;
		
		//************************************
		// Method:    Initialise
		/// ��ʼ�����
		// FullName:  VR_Soft::IPlugin::Initialise
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Initialise(void) ;
		
		//************************************
		// Method:    Shutdown
		/// ������
		// FullName:  VR_Soft::IPlugin::Shutdown
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Shutdown(void) ;
		
		//************************************
		// Method:    UnInstall
		/// ж�ز��
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


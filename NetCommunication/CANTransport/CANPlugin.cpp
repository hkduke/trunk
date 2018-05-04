#include "CANPlugin.h"
#include "../Core/CoreComponent.h"
namespace NetCom
{
	CANPlugin::CANPlugin(void)
	{
	}


	CANPlugin::~CANPlugin(void)
	{
	}

	const std::string CANPlugin::GetPluginName(void) const
	{
		return string("CAN設備");
	}

	const std::string CANPlugin::GetPluginVersion(void) const
	{
		return "1.0";
	}

	const std::string& CANPlugin::GetPluginDiscribe(void) const
	{
		return string("CAN總綫插件");
	}

	void CANPlugin::Install(void)
	{

	}

	void CANPlugin::Initialise(void)
	{
		CoreComponent::GetInstance().WriteLogMsg("開始啓動CAN設備。。。。。。");
		bool isRes = m_can.initDevice();
		if(isRes)
		{
			CoreComponent::GetInstance().WriteLogMsg("啓動CAN設備失敗。。。。。。");
		}
		else
		{
			CoreComponent::GetInstance().WriteLogMsg("啓動CAN設備成功。。。。。。");
		}

	}

	void CANPlugin::Shutdown(void)
	{
		
	}

	void CANPlugin::UnInstall(void)
	{

	}
}


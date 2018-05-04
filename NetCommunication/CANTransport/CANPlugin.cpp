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
		return string("CAN�O��");
	}

	const std::string CANPlugin::GetPluginVersion(void) const
	{
		return "1.0";
	}

	const std::string& CANPlugin::GetPluginDiscribe(void) const
	{
		return string("CAN���Q���");
	}

	void CANPlugin::Install(void)
	{

	}

	void CANPlugin::Initialise(void)
	{
		CoreComponent::GetInstance().WriteLogMsg("�_ʼ����CAN�O�䡣����������");
		bool isRes = m_can.initDevice();
		if(isRes)
		{
			CoreComponent::GetInstance().WriteLogMsg("����CAN�O��ʧ��������������");
		}
		else
		{
			CoreComponent::GetInstance().WriteLogMsg("����CAN�O��ɹ�������������");
		}

	}

	void CANPlugin::Shutdown(void)
	{
		
	}

	void CANPlugin::UnInstall(void)
	{

	}
}


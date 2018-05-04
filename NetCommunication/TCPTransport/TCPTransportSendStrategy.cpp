#include "TCPTransportSendStrategy.h"
#include <string>
namespace NetCom
{
	TCPTransportSendStrategy::TCPTransportSendStrategy()
	{
		//Transport ** ts = GetTransport();
		//*ts = new TCPTransport;
	}


	TCPTransportSendStrategy::~TCPTransportSendStrategy()
	{
	}

	int TCPTransportSendStrategy::Send(UInt32 topic, UInt8 * data, UInt32 size, TransactionType type)
	{
		
 		return 1;
	}

	void TCPTransportSendStrategy::InitStrategy()
	{
	}

	std::string TCPTransportSendStrategy::name()const
	{
		return "TCPTransportSendStrategy";
	}

	NetCom::DataLinkMap* TCPTransportSendStrategy::GetDataLinkMap()
	{
		return nullptr;
	}

	void TCPTransportSendStrategy::pocoInitializeLibrary()
	{
		std::cout << "PluginLibrary initializing" << std::endl;
	}
	void TCPTransportSendStrategy::pocoUninitializeLibrary()
	{
		std::cout << "PluginLibrary uninitializing" << std::endl;
	}

}

POCO_BEGIN_MANIFEST(NetCom::ITransportSendStrategy)
POCO_EXPORT_CLASS(NetCom::TCPTransportSendStrategy)
POCO_END_MANIFEST

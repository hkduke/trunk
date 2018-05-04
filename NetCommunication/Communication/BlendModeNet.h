#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"
#include "../Sockets/DatagramSocket.h"
#include "../Sockets/SocketAddress.h"

// ¶ÁÈ¡Êý¾Ý
namespace NetCom
{
	class DataLinkMap;
	class Transport;
	class DataSampleElementList;
	class NETCOMMUNICATION_EXPORT BlendModeNet
	{
	public:
		BlendModeNet(DataSampleElementList * ptr = nullptr);
		~BlendModeNet();

		void Init();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		DataSampleElementList * GetDataSampleElementList();
		void Push(UInt8 * data , UInt32 len);
		void Run();

		void Send(UInt8 * data, UInt32 len);
		void ReadData();
	private:
		DataLinkMap * m_pDataLinkMap;
		DataSampleElementList * m_dataList;
		Transport * m_pTransport;
		Thread * _thread;
		UInt32 m_dataCount;
		FastMutex m_lock;
		UInt16 m_port;
		DatagramSocket * m_sendSocket;
		SocketAddress m_sendAddrss;
		SocketAddress m_receiveAddrss;
		DatagramSocket *m_receiveSocket;
	};
}

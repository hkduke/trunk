#include "Transport.h"
#include "DataLinkMap.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
#include "../Core/Publisher.h"
#include "../Core/Subscribe.h"
#include "../Communication/FileSendQueue.h"
#include "../Core/RunnableAdapter.h"
#include "../Core/Thread.h"
#include "../Core/Mutex.h"
#include "../Communication/MsgPushCommon.h"
namespace NetCom
{
	Transport::Transport():m_ParticipatorType(NetType_None),m_Establishreactor(false)
	{
	}

	Transport::~Transport()
	{
	}

	void Transport::SetDataLinkMap(DataLinkMap * ptr)
	{
		m_datamap = ptr;
	}

	bool Transport::Init()
	{
		m_datamap = new DataLinkMap;
		m_pSendQueue = new MsgPushCommon;
		m_pSendQueue->Init();
		m_pSendQueue->SetDataLinkMap(m_datamap);

		
		m_pSendQueue->Run();
		return true;
	}


// 	void Transport::run()
// 	{
// 		Thread _thread;
// 		//SendQueue sq;
// 		RunnableAdapter<SendQueue> runnable(*m_pSendQueue, &SendQueue::ProcessQueue);
// 		_thread.start(runnable);
// 		_thread.join();
// 	}

	void Transport::Stop()
	{

	}

	void Transport::Send(UInt32 tocpic, const UInt8 * data, UInt32 len, TransactionType type)
	{

		//Timestamp currentTime;
		m_pSendQueue->Push(tocpic,(UInt8*)data, len, type);
		//std::cout << __FUNCTION__ << "::::" << (int)currentTime.elapsed() << std::endl;



	}


	void Transport::Start()
	{

	}

	bool Transport::JudgeType()
	{
		NodeBase * node = ResourceManager::GetInstance().GetCurrentNode();


		return /*(m_Publisher!=nullptr ||m_Subscribe!=nullptr)*/false;
	}

	NetCom::NetType Transport::GetNetType()
	{
		return m_ParticipatorType;
	}

// 	Publisher * Transport::GetPublisher()
// 	{
// 		return m_Publisher;
// 	}
// 
// 	NetCom::Subscribe * Transport::GetSubscribe()
// 	{
// 		return m_Subscribe;
// 	}

	DataLinkMap* Transport::GetDataLinkMap()
	{
		return m_datamap;
	}

	DataSampleElementList* Transport::GetDataSampleElementList()
	{
		return m_DataSampleElementList;
	}

	bool Transport::GetReactorEstablish()
	{
		return m_Establishreactor;
	}

	void Transport::SetReactorEstablishFlag(bool es)
	{
		m_Establishreactor = es;
	}

	void Transport::SendAll(UInt8 * data, UInt32 len)
	{

	}

}


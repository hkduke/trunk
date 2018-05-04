
//#include "../Sockets/DatagramSocket.h"
//#include "../Sockets/SocketAddress.h"
//#include "../Sockets/MulticastSocket.h"
#include "../Core/Framework.h"
#include "../TCPTransport/TCPTransport.h"
#include <iostream>


#include <vector>
#include "../Core/NodeDirectoryPack.h"
#include "../Core/Any.h"

std::vector<NetCom::Any> m_vector;

namespace NetCom
{
	void NodeJion(void*) {}
// 	TCPTransport tcp;
// 	std::vector<Any> vec;
// 	SendData send(&vec);
// void NodeJion(void *);
// void NodeJion(void*)
// {
// 	tcp.Init();
// 	TCPTransport::IpaddressSet& ipset = tcp.GetIpaddressSet();
// 	send.m_ipset = &ipset;
// 	for (TCPTransport::IpaddressSet::iterator iter = ipset.begin(); iter != ipset.end(); iter++)
// 	{
// 		Thread* t1 = new Thread;
// 		RunnableAdapter<SendData> *m_runnable = new RunnableAdapter<SendData>(send, &SendData::run);
// 		t1->start(*m_runnable);
// 	}

	//tcp->RealseHandle();
//}
}



int main(int argc, char** argv)
{

	NetCom::Framework* fram  = new NetCom::Framework;
	fram->Init();
// 	std::vector<Any> vect;
// 	vect.push_back(int(3));
// 	vect.push_back(int(4));
// 	vect.push_back(int(5));
// 	NetCom::NodeDirectoryPack pack;
// 	pack.FillData();
	
	fram->GetNodeDiscover()->RegisterHandle(NetCom::NodeJion);
	printf("end\n");
	getchar();
	return 0;
}
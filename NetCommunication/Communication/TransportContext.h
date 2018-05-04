#pragma once
#include "Transport.h"
#include <vector>

// 传输策略上下文

namespace NetCom
{
	class TransportContext
	{
		typedef std::vector<Transport*> TransportContextSet;
	public:
		TransportContext();
		~TransportContext();

		static Transport *CreateContext(const std::string &context);

		TransportContextSet* GetTransportStrategy();
	private:
		TransportContextSet  m_transportcontext;
	};
}

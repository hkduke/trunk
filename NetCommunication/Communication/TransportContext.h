#pragma once
#include "Transport.h"
#include <vector>

// �������������

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

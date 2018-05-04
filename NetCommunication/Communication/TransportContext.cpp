#include "TransportContext.h"

namespace NetCom
{
	TransportContext::TransportContext()
	{

	}

	TransportContext::~TransportContext()
	{

	}

	Transport * TransportContext::CreateContext(const std::string &context)
	{
		return nullptr;
	}

	TransportContext::TransportContextSet* TransportContext::GetTransportStrategy()
	{
		return &m_transportcontext;
	}

}

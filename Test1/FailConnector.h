#pragma once

#include "../Sockets/StreamSocket.h"
#include "../Reactor/SocketNotification.h"
#include "../Reactor/SocketAcceptor.h"
#include "../Reactor/SocketConnector.h"
#include "ClientServiceHandler.h"
namespace NetCom
{
	class FailConnector : public SocketConnector<ClientServiceHandler>
	{
	public:
		FailConnector(SocketAddress& address, SocketReactor& reactor) :
			SocketConnector<ClientServiceHandler>(address, reactor),
			_failed(false),
			_shutdown(false)
		{
			//reactor.addEventHandler(socket(), Observer<FailConnector, TimeoutNotification>(*this, &FailConnector::onTimeout));
			reactor.addEventHandler(socket(), Observer<FailConnector, ShutdownNotification>(*this, &FailConnector::onShutdown));
		}

		void onShutdown(ShutdownNotification* pNf)
		{
			pNf->release();
			_shutdown = true;
		}

		void onTimeout(TimeoutNotification* pNf)
		{
			pNf->release();
			_failed = true;
			reactor()->stop();
		}

		void onError(int error)
		{
			_failed = true;
			reactor()->stop();
		}

		bool failed() const
		{
			return _failed;
		}

		bool shutdown() const
		{
			return _shutdown;
		}

	private:
		bool _failed;
		bool _shutdown;
	};
}

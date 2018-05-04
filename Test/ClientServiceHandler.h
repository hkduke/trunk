#pragma once

#include <sstream>
#include "../Sockets/StreamSocket.h"
#include "../Reactor/SocketReactor.h"
#include "../Reactor/SocketNotification.h"

namespace NetCom
{
	class ClientServiceHandler
	{
	public:
		ClientServiceHandler(StreamSocket& socket, SocketReactor& reactor);
		~ClientServiceHandler();

		void onReadable(ReadableNotification* pNf);
		void onWritable(WritableNotification* pNf);
		void onTimeout(TimeoutNotification* pNf);

		static std::string data();

		static void resetData();

		static bool timeout();

		static bool getCloseOnTimeout();

		static void setCloseOnTimeout(bool flag)
		{
			_closeOnTimeout = flag;
		}

		static bool readableError()
		{
			return _readableError;
		}

		static bool writableError()
		{
			return _writableError;
		}

		static bool timeoutError()
		{
			return _timeoutError;
		}

		static void setOnce(bool once = true)
		{
			_once = once;
		}

	private:
		void checkReadableObserverCount(std::size_t oro)
		{
			if (((oro == 0) && _reactor.hasEventHandler(_socket, _or)) ||
				((oro > 0) && !_reactor.hasEventHandler(_socket, _or)))
			{
				_readableError = true;
			}
		}

		void checkWritableObserverCount(std::size_t ow)
		{
			if (((ow == 0) && _reactor.hasEventHandler(_socket, _ow)) ||
				((ow > 0) && !_reactor.hasEventHandler(_socket, _ow)))
			{
				_writableError = true;
			}
		}

		void checkTimeoutObserverCount(std::size_t ot)
		{
			if (((ot == 0) && _reactor.hasEventHandler(_socket, _ot)) ||
				((ot > 0) && !_reactor.hasEventHandler(_socket, _ot)))
			{
				_timeoutError = true;
			}
		}

		StreamSocket                                         _socket;
		SocketReactor&                                       _reactor;
		Observer<ClientServiceHandler, ReadableNotification> _or;
		Observer<ClientServiceHandler, WritableNotification> _ow;
		Observer<ClientServiceHandler, TimeoutNotification>  _ot;
		std::stringstream                                    _str;

		static std::string                                   _data;
		static bool                                          _readableError;
		static bool                                          _writableError;
		static bool                                          _timeoutError;
		static bool                                          _timeout;
		static bool                                          _closeOnTimeout;
		static bool                                          _once;
	};

}
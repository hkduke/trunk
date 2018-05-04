#include "ClientServiceHandler.h"
#include "../Core/LogManager.h"

namespace NetCom
{

	bool ClientServiceHandler::_readableError = false;
	bool ClientServiceHandler::_timeout = false;
	bool ClientServiceHandler::_timeoutError = false;
	bool ClientServiceHandler::_closeOnTimeout = false;
	bool ClientServiceHandler::_writableError = false;
	bool ClientServiceHandler::_once = false;

	std::string ClientServiceHandler::_data = "";
	NetCom::ClientServiceHandler::ClientServiceHandler(StreamSocket & socket, SocketReactor & reactor) :
		_socket(socket),
		_reactor(reactor),
		_or(*this, &ClientServiceHandler::onReadable),
		_ow(*this, &ClientServiceHandler::onWritable),
		_ot(*this, &ClientServiceHandler::onTimeout)
	{
		_timeout = false;
		_readableError = false;
		_writableError = false;
		_timeoutError = false;
		checkReadableObserverCount(0);
		_reactor.addEventHandler(_socket, _or);
		checkReadableObserverCount(1);
		checkWritableObserverCount(0);
		_reactor.addEventHandler(_socket, _ow);
		checkWritableObserverCount(1);
		checkTimeoutObserverCount(0);
		_reactor.addEventHandler(_socket, _ot);
		checkTimeoutObserverCount(1);
	}

	NetCom::ClientServiceHandler::~ClientServiceHandler()
	{

	}

	void NetCom::ClientServiceHandler::onReadable(ReadableNotification* pNf)
	{
		pNf->release();
		char buffer[32];
		int n = _socket.receiveBytes(buffer, sizeof(buffer));
		if (n > 0)
		{
			_str.write(buffer, n);
		}
		else
		{
			checkReadableObserverCount(1);
			_reactor.removeEventHandler(_socket, Observer<ClientServiceHandler, ReadableNotification>(*this, &ClientServiceHandler::onReadable));
			checkReadableObserverCount(0);
			if (_once || _data.size() >= 3072) _reactor.stop();
			_data += _str.str();
			delete this;
		}
		LogManager::GetInstance().WriteMessage("读取数据，大小:%d", n);
	}

	void NetCom::ClientServiceHandler::onWritable(WritableNotification * pNf)
	{
		pNf->release();
		checkWritableObserverCount(1);
		_reactor.removeEventHandler(_socket, Observer<ClientServiceHandler, WritableNotification>(*this, &ClientServiceHandler::onWritable));
		checkWritableObserverCount(0);
		std::string data(1024, 'x');
		_socket.sendBytes(data.data(), (int)data.length());
		_socket.shutdownSend();
		LogManager::GetInstance().WriteMessage("写入数据。");
	}

	void NetCom::ClientServiceHandler::onTimeout(TimeoutNotification * pNf)
	{
		pNf->release();
		_timeout = true;
		if (_closeOnTimeout)
		{
			_reactor.stop();
			delete this;
		}
		LogManager::GetInstance().WriteMessage("超时。");
	}

	std::string NetCom::ClientServiceHandler::data()
	{
		return _data;
	}

	void NetCom::ClientServiceHandler::resetData()
	{
		_data.clear();
	}

	bool NetCom::ClientServiceHandler::timeout()
	{
		return _timeout;
	}

	bool NetCom::ClientServiceHandler::getCloseOnTimeout()
	{
		return _closeOnTimeout;
	}

}

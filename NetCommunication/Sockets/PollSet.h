//
// PollSet.h
//
// Library: Net
// Package: Sockets
// Module:  PollSet
//
// Definition of the PollSet class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_PollSet_INCLUDED
#define Net_PollSet_INCLUDED


#include "Socket.h"
#include <map>


namespace NetCom {



class PollSetImpl;


class Net_API PollSet
	/// A set of sockets that can be efficiently polled as a whole.
	///
	/// If supported, PollSet is implemented using epoll (Linux) or
	/// poll (BSD) APIs. A fallback implementation using select()
	/// is also provided.
{
public:
	enum Mode
	{
		POLL_READ  = 0x01,
		POLL_WRITE = 0x02,
		POLL_ERROR = 0x04
	};

	typedef std::map<Socket, int> SocketModeMap;

	PollSet();
		/// Creates an empty PollSet.

	~PollSet();
		/// Destroys the PollSet.

	void add(const Socket& socket, int mode);
		/// Adds the given socket to the set, for polling with
		/// the given mode, which can be an OR'd combination of
		/// POLL_READ, POLL_WRITE and POLL_ERROR.

	void remove(const Socket& socket);
		/// Removes the given socket from the set.

	void update(const Socket& socket, int mode);
		/// Updates the mode of the given socket.

	void clear();
		/// Removes all sockets from the PollSet.

	SocketModeMap poll(const Timespan& timeout);
		/// Waits until the state of at least one of the PollSet's sockets
		/// changes accordingly to its mode, or the timeout expires.
		/// Returns a PollMap containing the sockets that have had
		/// their state changed.

private:
	PollSetImpl* _pImpl;

	PollSet(const PollSet&);
	PollSet& operator = (const PollSet&);
};


} // namespace Poco::Net


#endif // Net_PollSet_INCLUDED

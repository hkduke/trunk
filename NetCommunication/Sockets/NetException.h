//
// NetException.h
//
// Library: Net
// Package: NetCore
// Module:  NetException
//
// Definition of the NetException class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_NetException_INCLUDED
#define Net_NetException_INCLUDED


#include "Net.h"
#include "Exception.h"


namespace NetCom {



POCO_DECLARE_EXCEPTION(Foundation_API, NetException, IOException)
POCO_DECLARE_EXCEPTION(Foundation_API, InvalidAddressException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, InvalidSocketException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, ServiceNotFoundException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, ConnectionAbortedException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, ConnectionResetException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, ConnectionRefusedException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, DNSException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, HostNotFoundException, DNSException)
POCO_DECLARE_EXCEPTION(Foundation_API, NoAddressFoundException, DNSException)
POCO_DECLARE_EXCEPTION(Foundation_API, InterfaceNotFoundException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, NoMessageException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, MessageException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, MultipartException, MessageException)
POCO_DECLARE_EXCEPTION(Foundation_API, HTTPException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, NotAuthenticatedException, HTTPException)
POCO_DECLARE_EXCEPTION(Foundation_API, UnsupportedRedirectException, HTTPException)
POCO_DECLARE_EXCEPTION(Foundation_API, FTPException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, SMTPException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, POP3Exception, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, ICMPException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, NTPException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, HTMLFormException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, WebSocketException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, UnsupportedFamilyException, NetException)
POCO_DECLARE_EXCEPTION(Foundation_API, AddressFamilyMismatchException, NetException)


} // namespace Poco::Net


#endif // Net_NetException_INCLUDED

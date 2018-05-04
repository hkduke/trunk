//
// NamedEvent_WIN32.cpp
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "NamedEvent_WIN32U.h"
#include "Error.h"
#include "Exception.h"
#include "Format.h"
#include "UnicodeConverter.h"


namespace NetCom {


NamedEventImpl::NamedEventImpl(const std::string& name):
	_name(name)
{
	UnicodeConverter::toUTF16(_name, _uname);
	_event = CreateEventW(NULL, FALSE, FALSE, _uname.c_str());
	if (!_event)
	{
		DWORD dwRetVal = GetLastError(); 
		throw SystemException(format("cannot create named event %s [Error %d: %s]", _name, (int)dwRetVal, Error::getMessage(dwRetVal)));
	}
}


NamedEventImpl::~NamedEventImpl()
{
	CloseHandle(_event);
}


void NamedEventImpl::setImpl()
{
	if (!SetEvent(_event))
		throw SystemException("cannot signal named event", _name);
}


void NamedEventImpl::waitImpl()
{
	switch (WaitForSingleObject(_event, INFINITE))
	{
	case WAIT_OBJECT_0:
		return;
	default:
		throw SystemException("wait for named event failed", _name);
	}
}


} // namespace Poco

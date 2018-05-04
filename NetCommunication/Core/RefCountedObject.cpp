//
// RefCountedObject.cpp
//
// Library: Foundation
// Package: Core
// Module:  RefCountedObject
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "RefCountedObject.h"


namespace NetCom {


RefCountedObject::RefCountedObject(): _counter(1)
{
}


RefCountedObject::~RefCountedObject()
{
}


} // namespace Poco

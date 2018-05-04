#pragma once

#include "AutoPtr.h"
#include <string>

namespace NetCom {

class  INotification
{
public:
	typedef AutoPtr<INotification> Ptr;
	
	INotification() {}
		/// Creates the notification.

	virtual std::string name() const
	{
		return typeid(*this).name();
	}
		/// Returns the name of the notification.
		/// The default implementation returns the class name.

protected:
	virtual ~INotification() {}
};


} 


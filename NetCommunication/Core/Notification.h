
#pragma once 
#include "../Public/INotification.h"
#include "RefCountedObject.h"
namespace NetCom {


class  Notification :public RefCountedObject
	/// The base class for all notification classes used
	/// with the NotificationCenter and the NotificationQueue
	/// classes.
	/// The Notification class can be used with the AutoPtr
	/// template class.
{
public:
	typedef AutoPtr<Notification> Ptr;
	
	Notification();
		/// Creates the notification.

	virtual std::string name() const;
		/// Returns the name of the notification.
		/// The default implementation returns the class name.

protected:
	virtual ~Notification();
};


} 


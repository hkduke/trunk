

#include "Notification.h"
#include <typeinfo>


namespace NetCom {


Notification::Notification()
{
}


Notification::~Notification()
{
}


std::string Notification::name() const
{
	return typeid(*this).name();
}


} // namespace Poco

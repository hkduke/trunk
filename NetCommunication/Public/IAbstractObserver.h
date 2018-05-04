#pragma  once


namespace NetCom {


class  IAbstractObserver
	/// The base class for all instantiations of
	/// the Observer and NObserver template classes.
{
public:
	IAbstractObserver()
	{

	}
	IAbstractObserver(const IAbstractObserver& observer)
	{

	}
	virtual ~IAbstractObserver() 
	{

	}
	
	IAbstractObserver& operator = (const IAbstractObserver& observer)
	{
		return *this;
	}
	

	virtual void notify(Notification* pNf) const = 0;
	virtual bool equals(const IAbstractObserver& observer) const = 0;
	virtual bool accepts(Notification* pNf) const = 0;
	virtual IAbstractObserver* clone() const = 0;
	virtual void disable() = 0;
};


} // namespace Poco


#endif // Foundation_AbstractObserver_INCLUDED

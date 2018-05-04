#include <QVariant>
#include "shapeproperty.h"
#include "QStringList"

class CShapePropertyPrivate
{
public:
	QString m_propertyName;
	QVariant m_value;
	int m_type;
	QStringList m_names;
	QString m_code;
	QVariant minimum;
	QVariant maxmum;
	QVariant singleStep;
	int decimals;
	//ModelPara * para;
};

CShapeProperty::CShapeProperty(const QString &pname, 
								int type, 
								const QVariant &pvalue  , 
								const QStringList *names/* = 0*/)
: d_ptr(new CShapePropertyPrivate)
{
	d_ptr->m_propertyName = pname;
	d_ptr->m_type = type;
	d_ptr->m_value = pvalue;
	//d_ptr->para = NULL;
	if (names != 0)
	{
		d_ptr->m_names = *names;
	}
d_ptr->minimum = 0;
d_ptr->maxmum = 100;
d_ptr->decimals = 3;
d_ptr->singleStep =1;
}


CShapeProperty::~CShapeProperty()
{
	delete d_ptr;
	if (!mChildrenPropertys.isEmpty())
	{
		qDeleteAll(mChildrenPropertys);
	}
}

QString CShapeProperty::propertyName()
{
	return d_ptr->m_propertyName;
}

const QVariant &CShapeProperty::value() const
{
	return d_ptr->m_value;
}

const QVariant & CShapeProperty::mimimum() const
{
	return d_ptr->minimum;
}

const QVariant & CShapeProperty::maxmum() const
{
	return d_ptr->maxmum;
}

const QVariant & CShapeProperty::singleStep() const
{
	return d_ptr->singleStep;
}

const int & CShapeProperty::decimals() const
{
	return d_ptr->decimals;
}

void CShapeProperty::setMimimum(const QVariant &mim)
{
	d_ptr->minimum = mim;
}

void CShapeProperty::setMaxMum(const QVariant &max)
{
	d_ptr->maxmum = max;
}

void CShapeProperty::setSingleStep(const QVariant &singleStep)
{
	d_ptr->singleStep = singleStep;
}

void CShapeProperty::setDecimals(const int& decimals)
{
	d_ptr->decimals = decimals;
}

int CShapeProperty::type()
{
	return d_ptr->m_type;
}

QStringList CShapeProperty::names()
{
	if (d_ptr->m_names.isEmpty())
	{
		return QStringList();
	}
	else
	{
		return d_ptr->m_names;
	}	
}

// void CShapeProperty::setPara(ModelPara *para)
// {
// 	d_ptr->para = para;
// }
// 
// ModelPara* CShapeProperty::para()
// {
// 	return d_ptr->para;
// }

QList<CShapeProperty*> CShapeProperty::subPropertys() const
{
	return mChildrenPropertys;
}

void CShapeProperty::addSubProperty(CShapeProperty *subProp)
{
	mChildrenPropertys.append(subProp);
}

QString CShapeProperty::Code()
{
	return d_ptr->m_code;
}

void CShapeProperty::setCode(const QString &code)
{
	d_ptr->m_code = code;
}

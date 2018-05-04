#ifndef _SHAPEPROPERTY_H_
#define _SHAPEPROPERTY_H_

class CShapePropertyPrivate;

#include <QDebug>
#include <QStringList>

class CShapeProperty
{
public:
	CShapeProperty(const QString &pname, 
					int type, 
					const QVariant &pvalue ,
					const QStringList *names = 0);
	~CShapeProperty();
public:
	QString propertyName();
	QString Code();
	void setCode(const QString &code);
	const QVariant &value() const;
	const QVariant &mimimum() const;
	const QVariant &maxmum() const;
	const QVariant &singleStep() const;
	const int &decimals() const;
	void setMimimum(const QVariant &mim);
	void setMaxMum(const QVariant &mim);
	void setSingleStep(const QVariant &singleStep);
	void setDecimals(const int& decimals);
	int type();
	QStringList names();

// 	void setPara(ModelPara *para);
// 	ModelPara* para();

	QList<CShapeProperty*> subPropertys() const;
	void addSubProperty(CShapeProperty *subProp);

private:
	CShapePropertyPrivate *d_ptr;
	QList<CShapeProperty*> mChildrenPropertys;
};

typedef QList<CShapeProperty *> CPropertyList;

inline QDebug operator<<(QDebug debug, CShapeProperty * prop)
{
	debug.nospace() << "CShapeProperty("
		<<  prop->propertyName() << ","
		<<  prop->type() << ","
		<<  prop->value()<< ","
		<< prop->names() <<  ")";
	return debug.space();
}


#endif // _SHAPEPROPERTY_H_
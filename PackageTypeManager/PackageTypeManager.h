#pragma once

#include "packagetypemanager_global.h"
#include "XmlPackage.h"
#include <QXmlStreamReader>
#include <QVariant>
#include <QMap>
#include <QByteArray>
#include <QBitArray>

struct SubProperty {
	int index;
	int len;
};

struct Property {
	int len;
	int pos;
	QString type;
	SubProperty sub;
};

class PACKAGETYPEMANAGER_EXPORT PackageTypeManager
{
public:
	PackageTypeManager();
public:
	//XML����
	bool initInterpreter(const QString& fileName);
	
	//�������ݽ���
	bool setName(QString name);
	bool setData(const QByteArray& data);
	QByteArray getDataElement(QString field);
	QString getElementType(QString field);


	//�ϳ���������
	void setDataElement(QString field, QString value);
	void setRawDataElement(QString field, QByteArray value);
	QByteArray getData();

	static XmlPackage xmlP;

private:
	void setMap();
	int getLen(Field f);
	void swapType(QString type, QString value);

	Package m_p;
	QByteArray m_data;
	QString m_name;
	QMap<QString, QByteArray> byteMap;
	QMap<QString, QBitArray> bitMap;
	
};

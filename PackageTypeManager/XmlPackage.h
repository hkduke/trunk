#pragma once
#include <QString>
#include <QVector>
#include <QXmlStreamReader>
#include <QVariant>
#include <QMap>

struct SubField {
	QString name;
	int index;
	int len;
	SubField()
	{
		len = 1;
	}
};

struct Field{
	QString name;
	QString type;
	QVector<SubField> subField;
	QString array;
	QVariant value;

	Field()
	{
		array = "";
		value = 0;
		subField.clear();
		type = "uint8";
	}
};

struct PackageHead {
	QString name;
	QVector<Field> field;
};

struct Package {
	PackageHead head;
	QVector<Field> field;
	QString name;
	QString type;
	QString headName;
	int id;
	QString algorithm;
	Package()
	{
		type = "default";
	}
};

class XmlPackage
{
public:
	XmlPackage();
	~XmlPackage();

	bool readXml(const QString& fileName);
	void beginRead();
	void readDevice();
	void readType();
	void readHead();
	void readSubPackage();
	void readPackage();

	Field readField();
	SubField readSubField();

	void set();

	void test();

	QVector<Package> packages;

	QString deviceName;
	int id;
	QString byteOrder;
	QMap<QString, int> types;

private:
	QXmlStreamReader xml;
	QVector<PackageHead> headers;
};
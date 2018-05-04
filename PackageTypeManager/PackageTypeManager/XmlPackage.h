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
	PackageHead()
	{
		name = "";
	}

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
		id = -1;
	}
};

class XmlPackage
{
public:
	XmlPackage();
	~XmlPackage();

	bool writeXml(QString fileName);

	bool readXml(const QString& fileName);


	void test();

	QVector<Package> packages;

	QString deviceName;
	int id;
	QString byteOrder;
	QMap<QString, int> types;
	QString dataVersion;

private:
	void beginRead();
	void readDevice();
	void readType();
	void readHead();
	void readSubPackage();
	void readPackage();

	void writeField(Field f);
	void writeSubField(SubField sub);

	Field readField();
	SubField readSubField();

	void set();


private:
	QXmlStreamReader xml;
	QXmlStreamWriter writer;
	QVector<PackageHead> headers;
};
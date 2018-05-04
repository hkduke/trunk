#include "PackageTypeManager.h"

XmlPackage PackageTypeManager::xmlP;

PackageTypeManager::PackageTypeManager()
{
	
}

bool PackageTypeManager::initInterpreter(const QString & fileName)
{
	if (xmlP.readXml(fileName))
	{
		xmlP.test();
		return true;
	}

	return false;
}

bool PackageTypeManager::setName(QString name)
{
	if (name == NULL)
		return false;
	else
	{
		m_name = name;
		foreach(Package p, xmlP.packages)
		{
			if (p.name == m_name)
			{
				m_p = p;
				setMap();
			}
		}
	}
	return false;
}

bool PackageTypeManager::setData(const QByteArray & data)
{
	if (data.isEmpty())
		return false;
	else
		m_data = data;
	return false;
}

QByteArray PackageTypeManager::getDataElement(QString field)
{
	foreach(QString str, byteMap)
	{
		if (str == field)
		{
			return byteMap[str];
			break;
		}
	}
	return QByteArray();
}

QString PackageTypeManager::getElementType(QString field)
{
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;
	foreach(Field f1, f)
	{
		if (f1.name == field)
			return f1.type;
	}
	return NULL;
}

void PackageTypeManager::setDataElement(QString field, QString value)
{
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;
	foreach(Field f1, f)
	{
		if (f1.name == field)
		{
			QByteArray b = value.toLatin1();
			byteMap[f1.name] = b;
		}
	}
}

void PackageTypeManager::setRawDataElement(QString field, QByteArray value)
{
	foreach(QString str, byteMap)
	{
		if (str == field)
		{
			byteMap[str] = value;
			break;
		}
	}
}

QByteArray PackageTypeManager::getData()
{
	QByteArray b;
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;

	foreach(Field f1, f)
	{
		if (byteMap.contains(f1.name))
		{
			b += byteMap[f1.name];
		}
		else
			return QByteArray();
	}
	return b;
	
}


int PackageTypeManager::getLen(Field f)
{
	if (f.array.isEmpty())//非数组
	{
		if (f.type == "uint8" || f.type == "int8")
			return 1;
		else if (f.type == "uint16" || f.type == "int16")
			return 2;
		else if (f.type == "bool" || f.type == "uint32" || f.type == "int32" || f.type == "float")
			return 4;
		else if (f.type == "uint64" || f.type == "int64" || f.type == "double")
			return 8;
		else if (!getElementType(f.name).isNull())
		{
			if (xmlP.types.contains(f.name))
			{
				return xmlP.types.value(f.name);
			}
			else
				return -1;
		}
		else
			return -1;
	}
	else//数组
	{
		QByteArray byteArray = getDataElement(f.array);
		int array;
		bool ok;
		if (byteArray.isEmpty())
		{
			array = f.array.toInt(&ok);
		}
		else
		{
			array = byteArray.toInt(&ok);
		}
		if (!ok)
			return -1;
		if (f.type == "uint8" || f.type == "int8")
			return 1 * array;
		else if (f.type == "uint16" || f.type == "int16")
			return 2 * array;
		else if (f.type == "bool" || f.type == "uint32" || f.type == "int32" || f.type == "float")
			return 4 * array;
		else if (f.type == "uint64" || f.type == "int64" || f.type == "double")
			return 8 * array;
		else if (!getElementType(f.name).isNull())
		{
			if (xmlP.types.contains(f.name))
			{
				return xmlP.types.value(f.name) * array;
			}
			else
				return -1;
		}
		else
			return -1;
	}
	return -1;
}

void PackageTypeManager::swapType(QString type, QString value)
{
	if (type == "uint8")
	{

	}
	else if (type == "int8")
	{

	}
	else if (type == "uint16")
	{

	}
	else if (type == "int16")
	{

	}
	else if (type == "bool")
	{

	}
	else if (type == "uint32")
	{

	}
	else if (type == "int32")
	{

	}
	else if (type == "float")
	{

	}
	else if (type == "uint64")
	{

	}
	else if (type == "int64")
	{

	}
	else if (type == "double")
	{

	}



}

void PackageTypeManager::setMap()
{
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;
	foreach(Field f1, f)
	{
		QByteArray byteArray;
		byteArray.resize(getLen(f1));
		byteMap.insert(f1.name, byteArray);
		if (!f1.subField.isEmpty())
		{
			foreach(SubField sub, f1.subField)
			{
				QBitArray bitArray;
				bitArray.resize(sub.len);
				bitMap.insert(sub.name, bitArray);
				QByteArray b;
				b.resize(sub.len / 8 + 1);
				byteMap.insert(sub.name, b);
			}
		}
	}
}

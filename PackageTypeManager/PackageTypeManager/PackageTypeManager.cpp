#include "PackageTypeManager.h"
#include <QDebug>
XmlPackage PackageTypeManager::xmlP;

PackageTypeManager::PackageTypeManager()
{
	
}

bool PackageTypeManager::initInterpreter(const QString & fileName)
{
	if (xmlP.readXml(fileName))
	{
		//xmlP.test();
		return true;
	}
	return false;
}

bool PackageTypeManager::writeXML(QString fileName)
{
	xmlP.writeXml(fileName);
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
	{
		m_data = data;
		resetMap();

	}
	return false;
}

QByteArray PackageTypeManager::getDataElement(QString field)
{
	if (byteMap.contains(field))
	{
		return byteMap[field];
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
	if (byteMap.contains(field))
	{
		byteMap[field] = value.toLatin1();
	}
}

void PackageTypeManager::setRawDataElement(QString field, QByteArray value)
{
	if (byteMap.contains(field))
	{
		byteMap[field] = value;
	}
		
}

QByteArray PackageTypeManager::getData()
{
	QByteArray b;
	b.clear();
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


void PackageTypeManager::resetMap()
{
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;
	if (!m_data.isEmpty())
	{
		foreach(Field f1, f)
		{
			int pos = getPos(f1.name);
			QByteArray b;
			for (int i = 0; i < getLen(f1); i++)
			{
				if (m_data.size() < pos)
					return;
				b += m_data[pos + i];
			}
			byteMap[f1.name] = b;
			if (!f1.subField.isEmpty())
			{
				foreach(SubField sub, f1.subField)
				{
					SubProperty s = getSubPos(f1, sub);
					QBitArray bits(s.len);
					for (int i = 0; i < b.count(); ++i)
						for (int j = 0, k = 0; j < 8 , k < s.len; ++j, ++k)
							bits.setBit(k, b.at(i)&(1 << j));
					QByteArray arr;
					arr.resize(s.len / 8 + 1);
					arr.fill(0);
					for (int i = 0; i < s.len; i++)
					{
						arr[i / 8] = (arr.at(i / 8) | ((bits[i] ? 1 : 0) << (i % 8)));
					}
					byteMap[sub.name, arr];
				}
			}
		}

	}
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
			array |= byteArray[0] & 0x000000ff;
			array |= ((byteArray[1] << 8) & 0x0000ff00);
			array |= ((byteArray[2] << 16) & 0x00ff0000);
			array |= ((byteArray[3] << 24) & 0xff000000);
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

//HACK
void PackageTypeManager::swapByteOrder(QByteArray arr)
{
	
}

SubProperty PackageTypeManager::getSubPos(Field f, SubField sub)
{
	SubProperty subPro;
	foreach(Field f1, m_p.field)
	{
		if (f1.name == f.name)
		{
			foreach(SubField sub1, f1.subField)
			{
				if (sub1.name == sub.name)
				{
					subPro.index = sub1.index;
					subPro.len = sub1.len;
				}
			}
		}
	}
	return subPro;
}

int PackageTypeManager::getPos(QString name)
{
	Property p;
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;
	int pos = 0;
	foreach(Field f1, f)
	{
		if (f1.name == name)
			return pos;
		pos += getLen(f1);
	}
	return -1;
}


void PackageTypeManager::setMap()
{
	QVector<Field> f;
	f += m_p.head.field;
	f += m_p.field;
	foreach(Field f1, f)
	{
		QByteArray byteArray;
		int len = getLen(f1);
		if (len == -1)
			byteArray.resize(0);
		else
			byteArray.resize(len);
		byteMap.insert(f1.name, byteArray);
		if (!f1.subField.isEmpty())
		{
			foreach(SubField sub, f1.subField)
			{
				/*QBitArray bitArray;
				bitArray.resize(sub.len);
				bitMap.insert(sub.name, bitArray);*/
				QByteArray b;
				b.resize(sub.len / 8 + 1);
				byteMap.insert(sub.name, b);
			}
		}
	}
	//foreach(Field f1, f)
	//{
	//	QByteArray byteArray;
	//	byteArray.clear();
	//	byteMap.insert(f1.name, byteArray);
	//	if (!f1.subField.isEmpty())
	//	{
	//		foreach(SubField sub, f1.subField)
	//		{
	//			QByteArray b;
	//			b.clear();
	//			byteMap.insert(sub.name, byteArray);
	//		}
	//	}
	//}
}

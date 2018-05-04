#include "BasePackage.h"
#include "../Core/Types.h"
#include <assert.h>
#include <QDebug>




BasePackage::BasePackage()
{
}


BasePackage::~BasePackage()
{
}

bool BasePackage::setPackage(const std::string & str)
{
	package.setName(QString::fromLocal8Bit(str.c_str()));
	//setDefaultValue();
	return true;
}

bool BasePackage::readXml(const std::string& fileName)
{
	return package.initInterpreter(QString::fromLocal8Bit(fileName.c_str()));
}

bool BasePackage::setValue(const std::string& fieldName, Any any)
{
	QString fName = QString::fromLocal8Bit(fieldName.c_str());
	QVector<Field> field;
	field += package.m_p.head.field;
	field += package.m_p.field;
	foreach(Field f, field)
	{
		if (f.name == fName)
		{
			//package.byteMap[f.name] = changeValueType(any, f.type);
			QByteArray a = changeValueType(any, f.type);
			
			package.setRawDataElement(f.name, a);
			return true;
		}
		foreach(SubField sub, f.subField)
		{
			if (sub.name == fName)
			{
				//package.byteMap[sub.name] = changeValueType(any, "bit", sub.len);
				package.setRawDataElement(sub.name, changeValueType(any, "bit", sub.len));
				return true;
			}
		}
	}
	return false;
}

int BasePackage::getAllLen()
{
	QVector<Field> field;
	field += package.m_p.head.field;
	field += package.m_p.field;
	int len=0;
	for (int i = 0; i < field.size(); i++)
	{
		if (field[i].array.isEmpty())
			return -1;
		len += package.getLen(field[i]);
	}
	return len;
}

//void BasePackage::setDefaultValue()
//{
//	QVector<Field> f;
//	f += package.m_p.head.field;
//	f += package.m_p.field;
//	
//	foreach(Field field, f)
//	{
//		if (field.type == "uint8")
//		{
//			UInt8 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "int8")
//		{
//			Int8 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "uint16")
//		{
//			UInt16 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "int16")
//		{
//			Int16 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "uint32")
//		{
//			UInt32 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "int32")
//		{
//			Int32 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "uint64")
//		{
//			UInt64 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "int64")
//		{
//			Int64 a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "bool")
//		{
//			bool a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "float")
//		{
//			float a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//		else if (field.type == "double")
//		{
//			double a = 0;
//			setValue(field.name.toStdString(), a);
//		}
//	}
//}

//void BasePackage::setUseDefienedType()
//{
//	for (int i = 0; i < package.xmlP.packages.size(); i++)
//	{
//		Package p = package.xmlP.packages[i];
//		if (p.type != "default")
//		{
//
//		}
//	}
//
//}


Any BasePackage::changeType(QByteArray byte, QString type, int len)
{
	bit_vector b;
	if (type == "bit")
	{
		//QBitArray bits(len);
		//QBitArray bits;
		QBitArray bits(byte.count() * 8);
		// Convert from QByteArray to QBitArray
		for (int i = 0; i < byte.count(); ++i)
			for (int b = 0; b < 8; ++b)
				bits.setBit(i * 8 + b, byte.at(i)&(1 << b));

		/*for (int i = 0; i < byte.count(); ++i)
			for (int j = 0, k = 0; j < 8, k < len; ++j, ++k)
				bits.setBit(k, byte.at(i)&(1 << j));*/
		for (int i = 0; i < len; i++)
		{
			//std::bitset<1> b1 =bits[i];
			std::bitset<1> b1 = bits.at(i);
			b.push_back(b1);
		}
		return b;
	}
	else if (type == "uint8")
	{
		return *reinterpret_cast<const UInt8*>(byte.data());
	}
	else if (type == "int8")
	{
		return *reinterpret_cast<const Int8*>(byte.data());
	}
	else if (type == "uint16")
	{
		return *reinterpret_cast<const UInt16*>(byte.data());
	}
	else if (type == "int16")
	{
		return *reinterpret_cast<const Int16*>(byte.data());
	}
	else if (type == "uint32")
	{
		return *reinterpret_cast<const UInt32*>(byte.data());
	}
	else if (type == "int32")
	{
		return *reinterpret_cast<const Int32*>(byte.data());
	}
	else if (type == "uint64")
	{
		return *reinterpret_cast<const UInt64*>(byte.data());
	}
	else if (type == "int64")
	{
		return *reinterpret_cast<const Int64*>(byte.data());
	}
	else if (type == "bool")
	{
		return *reinterpret_cast<const bool*>(byte.data());
	}
	else if (type == "float")
	{
		return *reinterpret_cast<const float*>(byte.data());
	}
	else if (type == "double")
	{
		return *reinterpret_cast<const double*>(byte.data());
	}


	return Any();
}

QByteArray BasePackage::changeValueType(Any any, QString type, int len)
{

	if (type == "bit")
	{
		bit_vector s = AnyCast<bit_vector>(any);
		QByteArray arr;
		arr.resize(s.size() / 8 + 1);
		arr.fill(0);
		for (int i = 0; i < s.size(); i++)//             100000
		{
			arr[i / 8] = (arr.at(i / 8) | ((s[i][0] ? 1 : 0) << (i % 8)));
		}
		return arr;
	}
	else if (type == "uint8")
	{
		//poco_assert(any.type() == typeid(UInt8));
		UInt8 v = AnyCast<UInt8>(any);
		QByteArray a = QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));;
		qDebug() << a;
		return a.data();
	}
	else if (type == "int8")
	{
		//poco_assert(any.type() == typeid(Int8));
		Int8 v = AnyCast<Int8>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "uint16")
	{
		//poco_assert(any.type() == typeid(UInt16));
		UInt16 v = AnyCast<UInt16>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "int16")
	{
		//poco_assert(any.type() == typeid(Int16));
		Int16 v = AnyCast<Int16>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "uint32")
	{
		//poco_assert(any.type() == typeid(UInt32));
		UInt32 v = AnyCast<UInt32>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "int32")
	{
		//poco_assert(any.type() == typeid(Int32));
		Int32 v = AnyCast<Int32>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "uint64")
	{
		//poco_assert(any.type() == typeid(UInt64));
		UInt64 v = AnyCast<UInt64>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "int64")
	{
		//poco_assert(any.type() == typeid(Int64));
		Int64 v = AnyCast<Int64>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "bool")
	{
		//poco_assert(any.type() == typeid(bool));
		bool v = AnyCast<bool>(any);
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "float")
	{
		//poco_assert(any.type() == typeid(float));
		float v = AnyCast<float>(any);//
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "double")
	{
		//poco_assert(any.type() == typeid(double));
		double v = AnyCast<double>(any);// 
		return QByteArray(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	return QByteArray();
}

Any BasePackage::getValue(const std::string& fieldName)
{
	QString fName = QString::fromLocal8Bit(fieldName.c_str());
	QVector<Field> field;
	field += package.m_p.head.field;
	field += package.m_p.field;
	foreach(Field f, field)
	{
		if (f.name == fName)
		{
			return changeType(package.byteMap[f.name], f.type);
		}
		foreach(SubField sub, f.subField)
		{
			if (sub.name == fName)
			{
				return changeType(package.byteMap[sub.name], "bit", sub.len);
			}
		}
	}
	return Any();
}

std::vector<unsigned char> BasePackage::allData()
{
	QByteArray d = package.getData();
	std::vector<unsigned char> byte;
	byte.resize(d.size());
	for (int i = 0; i < d.size(); i++)
	{
		byte[i] = d[i];
	}
	return byte;
}

std::vector<std::string> BasePackage::getAllFieldName()
{
	QVector<Field> field;
	field += package.m_p.head.field;
	field += package.m_p.field;

	std::vector<std::string> str;
	foreach(Field f, field)
	{
		str.push_back(f.name.toLocal8Bit().data());
		foreach(SubField sub, f.subField)
			str.push_back(sub.name.toLocal8Bit().data());
	}
	return str;
}

std::vector<std::string> BasePackage::getAllPackageName()
{
	std::vector<std::string> str;
	foreach(Package p, package.xmlP.packages)
		str.push_back(p.name.toLocal8Bit().data());
	return str;
}

int BasePackage::getID()
{
	return package.m_p.id;
}

void BasePackage::setData(std::vector<unsigned char> byte)
{
	QByteArray d;
	//std::vector<unsigned char> byte;
	d.resize(byte.size());
	for (int i = 0; i < byte.size(); i++)
	{
		d[i] = byte[i];
	}
	package.setData(d);
}

std::string BasePackage::getType(std::string fieldName)
{
	return package.getElementType(QString::fromLocal8Bit(fieldName.c_str())).toStdString();
}
#include "BasePackage.h"
#include "Poco/Types.h"
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
	return package.setName(QString::fromLocal8Bit(str.c_str()));
}

bool BasePackage::readXml(const std::string& fileName)
{
	return package.initInterpreter(QString::fromLocal8Bit(fileName.c_str()));
}

bool BasePackage::setValue(const std::string& fieldName, Poco::Any any)
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
			qDebug() << a;
			package.setRawDataElement(f.name, a.data());
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

Poco::Any BasePackage::changeType(QByteArray byte, QString type, int len)
{
	if (type == "bit")
	{
		QBitArray bits(len);
		for (int i = 0; i < byte.count(); ++i)
			for (int j = 0, k = 0; j < 8, k < len; ++j, ++k)
				bits.setBit(k, byte.at(i)&(1 << j));
		std::string s;
		for (int i = 0; i < bits.size(); i++)
		{
			if (bits[i])
				s[i] = 1;
			else
				s[i] = 0;
		}
		return s;
	}
	else if (type == "uint8")
	{
		return *reinterpret_cast<const Poco::UInt8*>(byte.data());
	}
	else if (type == "int8")
	{
		return *reinterpret_cast<const Poco::Int8*>(byte.data());
	}
	else if (type == "uint16")
	{
		return *reinterpret_cast<const Poco::UInt16*>(byte.data());
	}
	else if (type == "int16")
	{
		return *reinterpret_cast<const Poco::Int16*>(byte.data());
	}
	else if (type == "uint32")
	{
		return *reinterpret_cast<const Poco::UInt32*>(byte.data());
	}
	else if (type == "int32")
	{
		return *reinterpret_cast<const Poco::Int32*>(byte.data());
	}
	else if (type == "uint64")
	{
		return *reinterpret_cast<const Poco::UInt64*>(byte.data());
	}
	else if (type == "int64")
	{
		return *reinterpret_cast<const Poco::Int64*>(byte.data());
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


	return Poco::Any();
}

QByteArray BasePackage::changeValueType(Poco::Any any, QString type, int len)
{
	if (type == "bit")
	{
		std::string s = Poco::AnyCast<std::string>(any);
		QByteArray arr;
		arr.resize(s.size() / 8 + 1);
		for (int i = 0; i < s.size(); i++)
		{
			arr[i / 8] = (arr.at(i / 8) | ((s[i] ? 1 : 0) << (i % 8)));
		}
		return arr;
	}
	else if (type == "uint8")
	{
		//poco_assert(any.type() == typeid(Poco::UInt8));
		Poco::UInt8 v = Poco::AnyCast<Poco::UInt8>(any);
		QByteArray a = QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));;
		qDebug() << a;
		return a.data();
	}
	else if (type == "int8")
	{
		//poco_assert(any.type() == typeid(Poco::Int8));
		Poco::Int8 v = Poco::AnyCast<Poco::Int8>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "uint16")
	{
		//poco_assert(any.type() == typeid(Poco::UInt16));
		Poco::UInt16 v = Poco::AnyCast<Poco::UInt16>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "int16")
	{
		//poco_assert(any.type() == typeid(Poco::Int16));
		Poco::Int16 v = Poco::AnyCast<Poco::Int16>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "uint32")
	{
		//poco_assert(any.type() == typeid(Poco::UInt32));
		Poco::UInt32 v = Poco::AnyCast<Poco::UInt32>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "int32")
	{
		//poco_assert(any.type() == typeid(Poco::Int32));
		Poco::Int32 v = Poco::AnyCast<Poco::Int32>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "uint64")
	{
		//poco_assert(any.type() == typeid(Poco::UInt64));
		Poco::UInt64 v = Poco::AnyCast<Poco::UInt64>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "int64")
	{
		//poco_assert(any.type() == typeid(Poco::Int64));
		Poco::Int64 v = Poco::AnyCast<Poco::Int64>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "bool")
	{
		//poco_assert(any.type() == typeid(bool));
		bool v = Poco::AnyCast<bool>(any);
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "float")
	{
		//poco_assert(any.type() == typeid(float));
		float v = Poco::AnyCast<float>(any);//
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	else if (type == "double")
	{
		//poco_assert(any.type() == typeid(double));
		double v = Poco::AnyCast<double>(any);//
		return QByteArray::fromRawData(reinterpret_cast<const char*>(&v), sizeof(v));
	}
	return QByteArray();
}

Poco::Any BasePackage::getValue(const std::string& fieldName)
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
	return Poco::Any();
}

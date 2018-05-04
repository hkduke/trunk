#pragma once
#include "PackageTypeManager.h"
#include "Any.h"


class  BASEPACKAGE_EXPORT BasePackage
{
public:
	BasePackage();
	~BasePackage();

	bool setPackage(const std::string& str);
	bool readXml(const std::string& fileName);
	bool setValue(const std::string& fieldName, NetCom::Any any);
	NetCom::Any getValue(const std::string& fieldName);

//private:
	NetCom::Any changeType(QByteArray byte, QString type, int len = 0);
	QByteArray changeValueType(NetCom::Any any, QString type, int len = 0);

	PackageTypeManager package;
};


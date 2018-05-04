#pragma once
#include "PackageTypeManager.h"
#include "../Core/Any.h"
#include <bitset>  
typedef std::vector<std::bitset<1> > bit_vector;
using namespace NetCom;
class  NETCOMMUNICATION_EXPORT BasePackage
{
public:
	BasePackage();
	~BasePackage();

	bool setPackage(const std::string& str);
	bool readXml(const std::string& fileName);
	bool setValue(const std::string& fieldName, Any any);
	Any getValue(const std::string& fieldName);
	std::vector<unsigned char> allData();
	void setData(std::vector<unsigned char>);
	std::vector<std::string> getAllFieldName();

	std::string getType(std::string fieldName);

	int getAllLen();

	int getID();

	//void setDefaultValue();
	std::vector<std::string> getAllPackageName();
	void setUseDefienedType();
//private:
	Any changeType(QByteArray byte, QString type, int len = 0);
	QByteArray changeValueType(Any any, QString type, int len = 0);

	PackageTypeManager package;
};


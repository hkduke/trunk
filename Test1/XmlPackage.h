#pragma once
#include <vector>
#include <string>
#include "Export.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT XmlPackage
	{
	public:
		struct SubField {
			std::string name;
			int index;
			int len;
			std::string type;
		};

		struct ChildPackage;

		struct Field {
			std::string name;
			int len;
			std::vector<SubField> subField;
			ChildPackage* subPackage = NULL;
			std::string type;
			int level;
			std::string childName = "";
		};

		struct PackageHeader
		{
			std::string headName = "";
			std::vector<Field> packageDefine;
		};

		struct PackageInformation {
			std::string packageName;
			PackageHeader* header = NULL;
			std::string head;
			std::string id;
			std::vector<Field> packageDesc;
		};

		struct ChildPackageInfo {
			std::string subPackageName;
			std::string parent;
			std::string head;
			std::vector<Field> subPackageDesc;
		};

		struct ChildPackage {
			PackageHeader* childHeader = NULL;
			ChildPackageInfo childPackageInfor;
			std::string name;
		};

		XmlPackage();
		~XmlPackage();

		void readXML(std::string fileName);
		void print();
		void setChild();

		std::vector<std::string> GetFieldList();

		std::vector<PackageInformation> packages;
		std::vector<ChildPackage*> subPackages;
		std::vector<PackageHeader*> Headers;

	};
}


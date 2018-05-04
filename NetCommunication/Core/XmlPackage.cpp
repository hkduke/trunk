#include "XmlPackage.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <exception> 
#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <stdio.h>

namespace NetCom
{

	XmlPackage::XmlPackage()
	{
		packages.clear();
		subPackages.clear();
		Headers.clear();
	}


	XmlPackage::~XmlPackage()
	{
		for (int i = 0; i < subPackages.size(); i++)
		{
			delete subPackages[i];
		}

		for (int i = 0; i < Headers.size(); i++)
		{
			delete Headers[i];
		}
	}
using namespace std;
	std::vector<std::string> XmlPackage::GetFieldList()
	{

		
		std::vector<std::string> tempVector;
		BOOST_FOREACH(PackageInformation &packInf, packages)
		{
			if (packInf.header != NULL)
			{
				//cout << packInf.header->headName << endl;
				
				for (int i = 0; i < packInf.header->packageDefine.size(); i++)
				{
					//cout << packInf.header->packageDefine.at(i).name << ',' << packInf.header->packageDefine.at(i).len << endl;
					tempVector.push_back(packInf.header->packageDefine.at(i).name);
				}
			}

			//cout << packInf.packageName << ',' << packInf.head << packInf.id << endl;
			BOOST_FOREACH(Field field, packInf.packageDesc)
			{
				cout << field.name << ',' << field.len << endl;
				tempVector.push_back(field.name);
				for (int i = 0; i < field.subField.size(); i++)
				{
				//	cout << field.subField.at(i).name << "," << field.subField.at(i).index <<
				//		field.subField.at(i).len << endl;
					tempVector.push_back(field.subField.at(i).name);
				}
				if (field.subPackage != NULL)
				{
					ChildPackage* child = field.subPackage;
					if (child->childHeader != NULL)
					{
						//cout << child->childHeader->headName;
						tempVector.push_back(child->childHeader->headName);
						for (int i = 0; i < child->childHeader->packageDefine.size(); i++)
						{
						//	cout << child->childHeader->packageDefine.at(i).name << ',' << child->childHeader->packageDefine.at(i).len << endl;
							tempVector.push_back(child->childHeader->packageDefine.at(i).name);
						}
					}
					tempVector.push_back(child->childPackageInfor.subPackageName);
					BOOST_FOREACH(Field f, child->childPackageInfor.subPackageDesc)
					{
						//cout << f.name << ',' << f.len << endl;
						tempVector.push_back(f.name);
						for (int i = 0; i < f.subField.size(); i++)
						{
							//cout << f.subField.at(i).name << "," << f.subField.at(i).index <<
							//	f.subField.at(i).len << endl;
							tempVector.push_back(f.subField.at(i).name);
						}
					}
				}
			}
		}
		return tempVector;
	}

	void XmlPackage::readXML(std::string fileName)
	{
		using boost::property_tree::ptree;
		ptree pt;
		try
		{
			read_xml(fileName, pt);
		}
		catch (std::exception& e)
		{
			return;
		}

		BOOST_FOREACH(ptree::value_type &v, pt)
		{
			if (v.first == "head")
			{
				PackageHeader* header = new PackageHeader;
				header->headName = v.second.get<std::string>("<xmlattr>.name");
 				BOOST_FOREACH(ptree::value_type &v1, v.second)
				{			
					if (v1.first == "field")
					{
						Field field;
						field.subField.clear();
						field.name = v1.second.get<std::string>("<xmlattr>.name");
						field.len = v1.second.get<int>("<xmlattr>.len");
						field.type = v1.second.get<std::string>("<xmlattr>.type");
						BOOST_FOREACH(ptree::value_type &v2, v1.second)
						{
							if (v2.first == "subfield")
							{
								SubField subField;
								subField.name = v2.second.get<std::string>("<xmlattr>.name");
								subField.index = v2.second.get<int>("<xmlattr>.index");
								subField.len = v2.second.get<int>("<xmlattr>.len");
								subField.type = v2.second.get<std::string>("<xmlattr>.type");
								field.subField.push_back(subField);
							}
						}
						header->packageDefine.push_back(field);
					}

				}
				if (header->headName == "")
					delete header;
				else
					Headers.push_back(header);
			}
		}

			
		BOOST_FOREACH(ptree::value_type &v, pt)
		{
			if (v.first == "subpackage")
			{
				ChildPackage* child = new ChildPackage;
				child->name = v.second.get<std::string>("<xmlattr>.name");
				child->childPackageInfor.subPackageName = v.second.get<std::string>("<xmlattr>.name");
				child->childPackageInfor.parent = v.second.get<std::string>("<xmlattr>.parent");
				child->childPackageInfor.head = v.second.get<std::string>("<xmlattr>.head");
				for (int i = 0; i < Headers.size(); i++)
				{
					if (child->childPackageInfor.head == Headers.at(i)->headName)
						child->childHeader = Headers.at(i);
				}
				if (child->childHeader == NULL)
					std::cout << "XML文件不可用" << std::endl;
				BOOST_FOREACH(ptree::value_type &v1, v.second)
				{
					if (v1.first == "field")
					{
						Field field;
						field.subField.clear();
						field.name = v1.second.get<std::string>("<xmlattr>.name");
						field.len = v1.second.get<int>("<xmlattr>.len");
						field.childName = v1.second.get<std::string>("<xmlattr>.child", "");
						//field.type = v1.second.get<std::string>("<xmlattr>.type");
						/*for (int i = 0; i < subPackages.size(); i++)
						{
							if (v1.second.get<std::string>("<xmlattr>.child", "") == subPackages.at(i)->childPackageInfor.subPackageName)
							{
								field.subPackage = subPackages.at(i);
							}
						}*/
						BOOST_FOREACH(ptree::value_type &v2, v1.second)
						{
							if (v2.first == "subfield")
							{
								SubField subField;
								subField.name = v2.second.get<std::string>("<xmlattr>.name");
								subField.index = v2.second.get<int>("<xmlattr>.index");
								subField.len = v2.second.get<int>("<xmlattr>.len");
								subField.type = v2.second.get<std::string>("<xmlattr>.type");
								field.subField.push_back(subField);
							}
						}
						child->childPackageInfor.subPackageDesc.push_back(field);
					}
				}
				if (child->childHeader == NULL)
					delete child;
				else
					subPackages.push_back(child);
			}
		}

		BOOST_FOREACH(ptree::value_type &v, pt)
		{
			if (v.first == "package")
			{
				PackageInformation package;
				package.packageName = v.second.get<std::string>("<xmlattr>.name");
				package.head = v.second.get<std::string>("<xmlattr>.head");
				package.id = v.second.get<std::string>("<xmlattr>.id");
				for (int i = 0; i < Headers.size(); i++)
				{
					if (package.head == Headers.at(i)->headName)
						package.header = Headers.at(i);
				}
				if (package.header == NULL)
					std::cout << "XML文件不可用" << std::endl;
				BOOST_FOREACH(ptree::value_type &v1, v.second)
				{
					if(v1.first == "field")
					{
						Field field;
						field.subField.clear();
						field.name = v1.second.get<std::string>("<xmlattr>.name");
						field.len = v1.second.get<int>("<xmlattr>.len");
						field.type = v1.second.get<std::string>("<xmlattr>.type");
						for (int i = 0; i < subPackages.size(); i++)
						{
							if (v1.second.get<std::string>("<xmlattr>.child", "") == subPackages.at(i)->childPackageInfor.subPackageName)
							{
								field.subPackage = subPackages.at(i);
							}
						}
						BOOST_FOREACH(ptree::value_type &v2, v1.second)
						{
							if (v2.first == "subfield")
							{
								SubField subField;
								subField.name = v2.second.get<std::string>("<xmlattr>.name");
								subField.index = v2.second.get<int>("<xmlattr>.index");
								subField.len = v2.second.get<int>("<xmlattr>.len");
								subField.type = v2.second.get<std::string>("<xmlattr>.type");
								field.subField.push_back(subField);
							}
						}
						package.packageDesc.push_back(field);
					}	
				}
				if (package.header != NULL)
					packages.push_back(package);
			}
		}
		setChild();
		
	}

	void XmlPackage::print()
	{
		using namespace std;
		BOOST_FOREACH(PackageInformation &packInf, packages)
		{
			if (packInf.header != NULL)
			{
				cout << packInf.header->headName << endl;
				for (int i = 0; i < packInf.header->packageDefine.size(); i++)
				{
					cout << packInf.header->packageDefine.at(i).name << ',' << packInf.header->packageDefine.at(i).len << endl;
				}
			}

			cout << packInf.packageName << ',' << packInf.head << packInf.id << endl;
			BOOST_FOREACH(Field field, packInf.packageDesc)
			{
				cout << field.name << ',' << field.len << endl;
				for (int i = 0; i < field.subField.size(); i++)
				{
					cout << field.subField.at(i).name << "," << field.subField.at(i).index <<
						field.subField.at(i).len << endl;
				}
				if (field.subPackage != NULL)
				{
					ChildPackage* child = field.subPackage;
					if (child->childHeader != NULL)
					{
						cout << child->childHeader->headName;
						for (int i = 0; i < child->childHeader->packageDefine.size(); i++)
						{
							cout << child->childHeader->packageDefine.at(i).name << ',' << child->childHeader->packageDefine.at(i).len << endl;
						}
					}
					cout << child->childPackageInfor.subPackageName << "," << child->childPackageInfor.parent << ',' <<
						child->childPackageInfor.head << endl;
					BOOST_FOREACH(Field f, child->childPackageInfor.subPackageDesc)
					{
						cout << f.name << ',' << f.len << endl;
						for (int i = 0; i < f.subField.size(); i++)
						{
							cout << f.subField.at(i).name << "," << f.subField.at(i).index <<
								f.subField.at(i).len << endl;
						}
					}
				}
			}
		}
	}

	void XmlPackage::setChild()
	{
		BOOST_FOREACH(ChildPackage* child, subPackages)
		{
			std::vector<Field> field = child->childPackageInfor.subPackageDesc;
			BOOST_FOREACH(Field f, field)
			{
				if (f.childName != "")
				{
					for (int i = 0; i < subPackages.size(); i++)
					{
						if (f.childName == subPackages.at(i)->name)
						{
							f.subPackage = subPackages.at(i);
						}
					}
				}
			}
		}
	}


}
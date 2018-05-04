#include "ParseDictImp.h"
#include"../XML/tinyxml.h"

namespace NetCom
{
	ParseDictImp::ParseDictImp():ParseDict()
	{
		Init();
	}

	ParseDictImp::~ParseDictImp()
	{
	}

	bool ParseDictImp::Init()
	{
		m_pDict = new DictDirectory;
		return true;
	}

	bool ParseDictImp::ParseFile(const std::string &file)
	{
		TiXmlDocument doc(file.c_str());
		bool loadOkay = doc.LoadFile();

		if (!loadOkay) {
			printf("Could not load test file %s. Error='%s'. Exiting.\n", file.c_str(), doc.ErrorDesc());
			return false;
		}
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* pSubXmlElement = root->FirstChildElement();
		for (TiXmlNode*  item = root->FirstChild("Topic");item;item = item->NextSibling("Topic")) 
		{
			std::string topName = pSubXmlElement->Attribute("name");
			TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
			while (NULL != pChildXmlElement)
			{
				std::string  strName = pChildXmlElement->Attribute("name");
				std::string strType = pChildXmlElement->Attribute("type");
				std::string strLength = pChildXmlElement->Attribute("length");
				pChildXmlElement = pChildXmlElement->NextSiblingElement();
				m_pDict->GetDict()->Insert(const_cast<char*>(topName.data()), strName.data(), strType.data(), atoi(strLength.data()));
			}

		}
		return true;
	}

}

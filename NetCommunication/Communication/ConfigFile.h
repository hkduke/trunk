#pragma once

#include <fstream>
#include <iostream>
#include<string>
#include <string.h>
using namespace std;
namespace NetCom
{
	typedef struct ITEMVALUE_TYP
	{
		string strItem; // 项名称
		string strValue; // 值

		ITEMVALUE_TYP(string item, string value):strItem(item),strValue(value)
		{

		}

		bool operator== (const string item)
		{
			return (strItem.compare(item) == 0);
		}

		bool operator== (const string item) const
		{
			return (strItem.compare(item) == 0);
		}
	}ITEMVALUE, *PTR_ITEMVALUE;

	class ConfigFile
	{

	public:
		typedef std::list<ITEMVALUE> LstItemValue;
	public:

		explicit ConfigFile(const string& strFile);
		explicit ConfigFile(void);
		virtual ~ConfigFile(void);

		// 打开配置文件
		virtual bool OpenFile(void);
		// 打开配置文件
		virtual bool OpenFile(const string& strFile);
		// 关闭文件
		virtual void CloseFile(void);
		// 获取文件名称对应项的值
		virtual string GetItemValue(const string& strName, const string& strItem) const;
		// 获得一个项下的所有项目
		virtual const LstItemValue& GetItemValus(const string& strName) const ;
		// 读取文件
		virtual void ReadConfig(void);

		static ConfigFile* CreateConfigFileInstance(const string& strConfigFile);
	protected:
		typedef std::map<string, LstItemValue > MapStrItem;

		// 读取项目名称
		bool ReadItemName(const string& strText, string& strName);
		// 读取项
		bool ReadItem(const string& strText, string& strName, string& strValue);
		// 添加项
		void AddItem(const string& strName, const string& strValueName, const string& strValue);
		// 去掉所有的空格
		string Trim(string& strLine) const;
		// 去掉左边的空格
		string LeftTrim(string& strLine) const;
		// 去掉右边的空格
		string RightTrim(string& strLine) const;
		void Replace(char* szLine);

	private:
		string m_strConfigFile; // 配置文件
		// std::ifstream m_fileOperator; // 文件操作器
		FILE* m_pFile; // 文件句柄

		MapStrItem m_mapStrItem; // 项对应名称
		
	};

}


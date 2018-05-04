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
		string strItem; // ������
		string strValue; // ֵ

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

		// �������ļ�
		virtual bool OpenFile(void);
		// �������ļ�
		virtual bool OpenFile(const string& strFile);
		// �ر��ļ�
		virtual void CloseFile(void);
		// ��ȡ�ļ����ƶ�Ӧ���ֵ
		virtual string GetItemValue(const string& strName, const string& strItem) const;
		// ���һ�����µ�������Ŀ
		virtual const LstItemValue& GetItemValus(const string& strName) const ;
		// ��ȡ�ļ�
		virtual void ReadConfig(void);

		static ConfigFile* CreateConfigFileInstance(const string& strConfigFile);
	protected:
		typedef std::map<string, LstItemValue > MapStrItem;

		// ��ȡ��Ŀ����
		bool ReadItemName(const string& strText, string& strName);
		// ��ȡ��
		bool ReadItem(const string& strText, string& strName, string& strValue);
		// �����
		void AddItem(const string& strName, const string& strValueName, const string& strValue);
		// ȥ�����еĿո�
		string Trim(string& strLine) const;
		// ȥ����ߵĿո�
		string LeftTrim(string& strLine) const;
		// ȥ���ұߵĿո�
		string RightTrim(string& strLine) const;
		void Replace(char* szLine);

	private:
		string m_strConfigFile; // �����ļ�
		// std::ifstream m_fileOperator; // �ļ�������
		FILE* m_pFile; // �ļ����

		MapStrItem m_mapStrItem; // ���Ӧ����
		
	};

}


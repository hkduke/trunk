#include "CoreComponent.h"
#include "FileUtil.h"
const int NMAXLINECOUNT = 1024;

namespace NetCom
{
	FileUtil::FileUtil(void):m_pFile(NULL),m_szFile(NULL)
	{
	}


	FileUtil::FileUtil(const string& strFile)
		:m_pFile(NULL),m_szFile(NULL)
	{
		CopyFileName(strFile);
		Open();
	}

	FileUtil::FileUtil(const FileUtil& other)
		:m_pFile(other.m_pFile)
	{
		CopyFileName(other.m_szFile);
	}

	FileUtil::~FileUtil(void)
	{
		delete(m_szFile);
		Close();
	}

	// ��
	void FileUtil::Open(const string& strFile)
	{
		if (NULL != m_pFile)
		{
			Close();
		}

		// ���ļ�
		m_pFile = fopen(m_szFile, "r");
		
	}

	// ��
	void FileUtil::Open(void)
	{
		Open(m_szFile);
	}

	// �ر�
	void FileUtil::Close(void)
	{
		fclose(m_pFile);
	}

	// �����
	string FileUtil::GetLine()
	{
		if (NULL == m_pFile)
		{
			CoreComponent::GetInstance().WriteLogMsg("�ļ�û�д�", ERROR_NOT_FIND);
			return ("");
		}

		// ��ȡ��
		char szLine[NMAXLINECOUNT] = {0};
		fgets(szLine, NMAXLINECOUNT, m_pFile);
		RemoveN(szLine);
		return (szLine);
	}

	// �Ƿ����
	bool FileUtil::Eof(void)
	{
		return (feof(m_pFile) > 0 ? true : false);
	}

	// �Ƴ���β�� ��\n"
	void FileUtil::RemoveN(char* pszLine)
	{
		// �����Ƿ����\n
		int nCount = (int)strlen(pszLine) - 1;
		char* pLine = pszLine + nCount;
		if ('\n' == *pLine)
		{
			*pLine = '\0';
		}	
	}

	// �����ļ���
	void FileUtil::CopyFileName(const string& strFile)
	{
		delete(m_szFile);

		size_t nSize = strFile.size() + 1;
		m_szFile = new char[nSize];
		memset(m_szFile, 0, nSize);
		strcpy(m_szFile, strFile.c_str());
	}

}

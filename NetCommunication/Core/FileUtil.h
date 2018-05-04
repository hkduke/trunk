
#ifndef _PUBLIC_FILEUTIL_H_
#define _PUBLIC_FILEUTIL_H_

#pragma once

#include <cstdio>
#include <string>
using namespace std;
namespace NetCom
{
	class  FileUtil
	{
	public:
		// ���캯��
		FileUtil(void);
		FileUtil(const string& strFile);
		FileUtil(const FileUtil& other);
		~FileUtil(void);

	public:
		// ��
		void Open(const string& strFile);
		// ��
		void Open(void);
		// �ر�
		void Close(void);
		// �����
		string GetLine();
		// �Ƿ����
		bool Eof(void);

	protected:
		// �Ƴ���β�� ��\n"
		void RemoveN(char* pszLine);
		// �����ļ���
		void CopyFileName(const string& strFile);


	private:
		FILE* m_pFile;
		char* m_szFile;
	};

}

#endif // !_PUBLIC_FILEUTIL_H_
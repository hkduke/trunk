
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
		// 构造函数
		FileUtil(void);
		FileUtil(const string& strFile);
		FileUtil(const FileUtil& other);
		~FileUtil(void);

	public:
		// 打开
		void Open(const string& strFile);
		// 打开
		void Open(void);
		// 关闭
		void Close(void);
		// 获得行
		string GetLine();
		// 是否结束
		bool Eof(void);

	protected:
		// 移除行尾的 “\n"
		void RemoveN(char* pszLine);
		// 设置文件名
		void CopyFileName(const string& strFile);


	private:
		FILE* m_pFile;
		char* m_szFile;
	};

}

#endif // !_PUBLIC_FILEUTIL_H_
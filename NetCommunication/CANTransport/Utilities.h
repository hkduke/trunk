#pragma once

#include <string>
#include "defDataTypes.h"
#include <vector>
class Utilities
{
public:
	typedef std::vector<std::string> StringList;

public:
	Utilities(void);
	~Utilities(void);

	static std::string& Dec2Binary(UINT n);


	static bool ReadFile(const char * file ,  char * dataBuf , long & size);

	static bool WriteFile(const char * file ,const  char * dataBuf, long size);

	static int strtodata(unsigned char *str, unsigned char *data,int len,int flag);

	static void ConvertStrToUChar(char* str, BYTE* UnChar);
	static int chartoint(unsigned char chr, unsigned char *cint);
	static void  ConvertUCharToStr(char* str, BYTE* UnChar, int ucLen =8) ;

	static int count(char * str,const char * delim);
	static void split(const std::string &data ,const char* del , StringList & list);


	static inline void RemoveBitValue(UINT& value, int index)  
	{
		int bit = 1 << index;  
		int nMark = 0;  
		nMark = (~nMark) ^ bit;  
		value &= nMark;  
	}  

	static inline ULONG GetMask(ULONG n,ULONG mask)    
	{    
		mask = mask -1;  
		ULONG a=1;  
		a<<=mask;  
		n&=a;  
		if(n == a)  
		{  
			return 1;  
		}  
		return 0;  
	}  

	static std::string m_buf;
};


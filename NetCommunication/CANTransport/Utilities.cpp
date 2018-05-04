#include "Utilities.h"
#include <stdio.h>
#include <assert.h>
#include <streambuf>
#include <fstream>
using namespace std;
std::string Utilities::m_buf = std::string("\0",32);
Utilities::Utilities(void)
{
}

Utilities::~Utilities(void)
{
}

std::string& Utilities::Dec2Binary(UINT n)
{
	m_buf.clear();
	for(int a=n;a;a=a/2)
	{
		m_buf=m_buf+(a%2?'1':'0');
	}
	std::reverse(m_buf.begin(),m_buf.end());
	return m_buf;
}

bool Utilities::ReadFile(const char * file ,char * dataBuf , long & size)
{
	assert(file);
	ifstream infile (file,ifstream::binary);
	// get size of file
	infile.seekg(0,ifstream::end);
	size=infile.tellg();
	infile.seekg(0);

	// allocate memory for file content
	//dataBuf = new char [size];
	//memset(dataBuf,'\0',size);
	// read content of infile
	infile.read (dataBuf,size);
	infile.close();
	//delete [] buffer;
	return true;
}

bool Utilities::WriteFile(const char * file , const char * dataBuf, long size)
{
	ofstream outfile (file,ofstream::binary);
	outfile.write (dataBuf,size);
	outfile.close();
	return true;
}




void Utilities::ConvertStrToUChar(char* str, BYTE* UnChar)  
{  
	int i = 8/*strlen(str)*/, j = 0, counter = 0;  
	char c[2];  
	unsigned int bytes[2];
	for (j = 0; j < i; j += 2)   
	{  
		if(0 == j % 2)  
		{  
			c[0] = str[j];  
			c[1] = str[j + 1];  
			sscanf(c, "%02x" , &bytes[0]);  
			UnChar[counter] = bytes[0];  
			counter++;  
		}  
	}  
	return;  
} 


void Utilities::ConvertUCharToStr(char* str, BYTE* UnChar, int ucLen)  
{  
	int i = 0;  
	for(i = 0; i < ucLen; i++)  
	{  
		sprintf(str + i * 2, "%02x", UnChar[i]);  
	}  
}  


int Utilities::chartoint(unsigned char chr, unsigned char *cint)
{
	unsigned char cTmp;
	cTmp=chr-48;
	if(cTmp>=0&&cTmp<=9)
	{
		*cint=cTmp;
		return 0;
	}
	cTmp=chr-65;
	if(cTmp>=0&&cTmp<=5)
	{
		*cint=(cTmp+10);
		return 0;
	}
	cTmp=chr-97;
	if(cTmp>=0&&cTmp<=5)
	{
		*cint=(cTmp+10);
		return 0;
	}
	return 1;
}


int Utilities::strtodata(unsigned char *str, unsigned char *data,int len,int flag)
{
	unsigned char cTmp=0;
	int i=0;
	for(int j=0;j<len;j++)
	{
		if(chartoint(str[i++],&cTmp))
			return 1;
		data[j]=cTmp;
		if(chartoint(str[i++],&cTmp))
			return 1;
		data[j]=(data[j]<<4)+cTmp;
		if(flag==1)
			i++;
	}
	return 0;
}

void Utilities::split(const std::string &data ,const  char *del ,StringList & list)
{
	char * str = const_cast<char*>(data.data());
	int num = /*count(str,del)*/4;
	char ** arr = ( char ** ) malloc( sizeof(char*) * ( num +1));
	char ** result = arr;
	char * s = strtok(str,del);
	list.push_back(std::string(s));
	while( s != NULL)
	{
		*arr++ = s;
		s = strtok(NULL,del);
		if(s)
		{
			list.push_back(std::string(s));
		}

	}
	//free(arr);
	//return result;
}

int Utilities::count(char * str,const char * delim)
{
	int num = 0;
	while( NULL != ( str = strstr(str,delim) ) ){
		str ++;    
		num ++;
	}            
	return num;
}

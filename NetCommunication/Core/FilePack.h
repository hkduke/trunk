#pragma once
#include "../Core/CommonTool.h"
#include <vector>
#include <iostream>
#include "../Core/Export.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT  FilePack
	{

	public:
		FilePack();
		FilePack(const FilePack& that);
		FilePack& operator =(const FilePack& that);

		~FilePack();
		
	public:
		void ParseFile(void * data);

		char* GetData();

		char* GetFileData();

		int GetPackageType();

		void SetPacketSize(int lenth);

		int GetLenth();

		void SetTotalCheckSum(int begin, UInt16 number);

		UInt16 GetTotalCheckSum(int begin);

		void SetDataCheckSum(int begin, UInt8 number);

		UInt8 GetDataCheckSum(int begin);

		static std::vector<FilePack*> GetFilePackages(void * data,int lenth, std::string fileName,int checkedStyle);

		std::string m_fileName;

		int m_lenth;
		
		int m_packType;

		char *m_data;

		char* m_fileContent;

		UInt8 m_filecheckSum;//文件校验码

		UInt16 m_dataCheckSum;//整个报文校验码

		std::string GetFileName();

		void SetSomeData(void* data,int begin,int lenth);

		static int GetFileSerial(void* buff);//获取文件编号

	private:
		void FillHeader(int i, int packLenth);

		void SetString(void* data, int begin, std::string str);

		int  GetReserveNumber(std::string fileName, int checkedStyle);

		void SetFrameID(int framID);

		void FillFilePack(void * data,int begin,int lenth);
	};

}


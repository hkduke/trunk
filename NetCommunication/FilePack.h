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
		~FilePack();
	public:
		void ParseFile();

		void FillFile(std::string fileName, void* data,int begin, int packLenth,int checkLenth,int framID);

		static std::vector<FilePack> GetFilePackages(void * data,int lenth, std::string fileName,int checkedStyle);

		char m_data[1024];
	private:
		void FillHeader(int i, int packLenth);

		void SetString(void* data, int begin, std::string str);

		int  GetReserveNumber(std::string fileName, int checkedStyle);

		void SetFrameID(int framID);

		void FillFilePack(void * data,int begin,int lenth);
	};

}

